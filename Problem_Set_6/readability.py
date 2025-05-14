from cs50 import get_string

letters = 0
words = 0
sentences = 0

text = get_string("Text: ")

for char in text:
    if char.isalpha():
        letters += 1
    elif char.isspace():
        words += 1
    elif char == '.' or char == '!' or char == '?':
        sentences += 1
words += 1

L = letters * 100 / words
S = sentences * 100 / words
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
