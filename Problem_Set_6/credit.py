from cs50 import get_int


def main():
    number = get_int("Number: ")

    validity = verify(number)
    decision(validity, number)


def verify(x):
    sum = 0
    i = 0
    num = x

    while True:
        if i % 2 == 0:
            sum += num % 10
        else:
            n = (num % 10) * 2
            if n > 9:
                n = n % 10 + int(n / 10)
            sum += n
        i += 1
        num = int(num / 10)
        if num <= 0:
            break

    if sum % 10 == 0:
        return True
    else:
        return False


def decision(valid, no):
    if valid and (int(no / 10000000000000) == 34 or int(no / 10000000000000) == 37):
        print("AMEX")
    elif valid and (int(no / 100000000000000) == 51 or int(no / 100000000000000) == 52 or
                    int(no / 100000000000000) == 53 or int(no / 100000000000000) == 54 or
                    int(no / 100000000000000) == 55):
        print("MASTERCARD")
    elif valid and (int(no / 1000000000000) == 4 or int(no / 1000000000000000) == 4):
        print("VISA")
    else:
        print("INVALID")


main()
