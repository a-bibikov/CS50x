from cs50 import get_string
index = 0


def main():
    # get string from input
    string = get_string("Text: ")
    # initialize index count function
    countIndex(string)


def countIndex(string):
    # init empty variables for new types count
    letters = 0
    words = 0
    sentences = 0

    L = 0
    S = 0

    for key in range(len(string)):
        if string[key].isalpha() == True:
            letters += 1
        if string[key] == " ":
            words += 1
        if string[key] == "?" or string[key] == "." or string[key] == "!":
            sentences += 1

    L = letters * 100 / (words + 1)
    S = sentences * 100 / (words + 1)

    # index calculating
    index = (0.0588 * L) - (0.296 * S) - 15.8

    index = round(index)

    # print grade status
    if index >= 0 and index < 16:
        print(f"Grade {index}")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Before Grade 1")


main()
