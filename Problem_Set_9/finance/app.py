import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "POST":
        amount = request.form.get("amount")
        if not amount or float(amount) <= 0:
            return apology("must be positive amount", 400)

        db.execute("INSERT INTO transactions (user_id, stock, price, shares) VALUES (?, ?, ?, ?)",
                   session["user_id"], "cash", float(amount), 0)
        balance = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        db.execute("UPDATE users SET cash=? WHERE id=?",
                   balance[0]["cash"] + float(amount), session["user_id"])

        return redirect("/")

    else:
        stocks = db.execute(
            "SELECT stock, shares FROM holdings WHERE user_id=?", session["user_id"])
        value = 0
        for stock in stocks:
            stock["current_price"] = lookup(stock["stock"])["price"]
            value += stock["current_price"] * stock["shares"]
        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]
        return render_template("index.html", stocks=stocks, cash=cash, value=value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stock_info = lookup(request.form.get("symbol"))
        if stock_info is None:
            return apology("stock's symbol does not exist", 400)

        shares = request.form.get("shares")
        if not shares.isnumeric():
            return apology("invalid input for shares", 400)
        if int(shares) < 0:
            return apology("number of shares must be positive", 400)
        if float(shares) % 1 != 0:
            return apology("cannot buy fractional shares", 400)

        balance = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        if balance[0]["cash"] < stock_info["price"] * float(shares):
            return apology("insufficient funds", 400)

        db.execute("INSERT INTO transactions (user_id, stock, price, shares) VALUES (?, ?, ?, ?)",
                   session["user_id"], stock_info["symbol"], stock_info["price"], float(shares))
        db.execute("UPDATE users SET cash=? WHERE id=?",
                   balance[0]["cash"] - stock_info["price"] * float(shares), session["user_id"])
        if db.execute("SELECT * FROM holdings WHERE user_id=? AND stock=?", session["user_id"], stock_info["symbol"]):
            current_holdings = db.execute(
                "SELECT shares FROM holdings WHERE user_id=? AND stock=?", session["user_id"], stock_info["symbol"])[0]["shares"]
            db.execute("UPDATE holdings SET shares=? WHERE user_id=? AND stock=?",
                       current_holdings + float(shares), session["user_id"], stock_info["symbol"])
        else:
            db.execute("INSERT INTO holdings (user_id, stock, shares) VALUES (?, ?, ?)",
                       session["user_id"], stock_info["symbol"], float(shares))

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT stock, price, shares, Timestamp FROM transactions WHERE user_id=?", session["user_id"])
    for transaction in transactions:
        if float(transaction["shares"]) > 0:
            transaction["type"] = "buy"
        elif transaction["stock"] == "cash":
            transaction["type"] = "deposit"
        else:
            transaction["shares"] = -int(transaction["shares"])
            transaction["type"] = "sell"
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        stock_info = lookup(request.form.get("symbol"))
        if stock_info is not None:
            return render_template("quoted.html", stock_info=stock_info)
        return apology("stock's symbol does not exist", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("username is required", 400)

        password = request.form.get("password")
        if not password:
            return apology("password is required", 400)

        confirmation = request.form.get("confirmation")
        if not confirmation or password != confirmation:
            return apology("passwords do not match", 400)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                       username, generate_password_hash(password))
        except ValueError:
            return apology("username already exists", 400)

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT stock, shares FROM holdings WHERE user_id=?", session["user_id"])
    symbols = []
    for stock in stocks:
        symbols.append(stock["stock"])

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol not in symbols:
            return apology("you do not own this stock", 400)

        holding = 0
        for stock in stocks:
            if stock["stock"] == symbol:
                holding = stock["shares"]
        shares = request.form.get("shares")
        if int(shares) < 0 or int(shares) > holding:
            return apology("invalid quantity", 400)

        stock_info = lookup(symbol)
        balance = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])

        db.execute("INSERT INTO transactions (user_id, stock, price, shares) VALUES (?, ?, ?, ?)",
                   session["user_id"], stock_info["symbol"], stock_info["price"], -float(shares))
        db.execute("UPDATE users SET cash=? WHERE id=?",
                   balance[0]["cash"] + stock_info["price"] * float(shares), session["user_id"])
        current_holdings = db.execute("SELECT shares FROM holdings WHERE user_id=? AND stock=?",
                                      session["user_id"], stock_info["symbol"])[0]["shares"]
        db.execute("UPDATE holdings SET shares=? WHERE user_id=? AND stock=?",
                   current_holdings - float(shares), session["user_id"], stock_info["symbol"])

        return redirect("/")

    else:
        return render_template("sell.html", stocks=stocks)
