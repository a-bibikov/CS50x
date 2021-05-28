import csv
import sys

strands = []
persons = []
sequences = {}


def main():
    if len(sys.argv) != 3:
        print(sys.argv)
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    dataPersonsFile = sys.argv[1]
    dataDnaFile = sys.argv[2]

    # open and read csv file with people data
    with open(dataPersonsFile) as personsFile:
        personsReader = csv.DictReader(personsFile)
        for row in personsReader:
            persons.append(row)
            for col in row:
                if(col != "name"):
                    if col not in strands:
                        strands.append(col)

            # read file with dna data
            with open(dataDnaFile) as dnafile:
                dnaReader = dnafile.read()

    # loop for every STR in STR's array from our data
    for strand in strands:
        # get STR maxumum value
        getMaxLength(dnaReader, strand)

    # compare with our csv file
    checkCandidate(sequences)


def getMaxLength(s, sub):

    # init local variables
    letter = sub[0]
    length = len(sub)
    i = 0
    r = 0
    longest = 0

    # loop for every symbol in dna
    while i < len(s):
        hold = s[i:(i + length)]
        if hold == sub:
            # add one if STR compare with our data
            r += 1
            # check for boundaries
            if (i + length) <= len(s):
                i = i + length
            continue
        else:
            # if result is more then longest^ update longest
            if r > longest:
                longest = r
                r = 0
            else:
                r = 0

        i += 1

    sequences[sub] = longest


def checkCandidate(sequences):
    seq_length = len(strands)

    # check every person to compare
    for p in persons:
        r = 0
        for s in sequences:
            if int(sequences[s]) == int(p[s]):
                r += 1

                if r == seq_length:
                    print(p["name"])
                    return

    print("No match")


main()