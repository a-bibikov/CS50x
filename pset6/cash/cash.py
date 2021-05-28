from cs50 import get_float

quater = 25
dime = 10
nickel = 5
penny = 1


def main():
    # get correct value from input
    while True:
        dollars = get_float("Change owed: ")
        if dollars > 0:
            break
    # convert value into cents
    cents = int(dollars * 100)
    # init counting function with our value
    countCouns(cents)


# fuction: count coints in each type
def countCouns(cents):
    # set initial total coins to zero
    total = 0

    # check each type in array
    for coin in [quater, dime, nickel, penny]:
        # do if is in max value
        while cents >= coin:
            cents = cents - coin
            total += 1
    # print the result
    print(total)


main()
