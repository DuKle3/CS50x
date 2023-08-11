import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: ./dna.py <database> <identity>")
        sys.exit(1)

    # TODO: Read database file into a variable
    # create a list of dict()
    database = []
    csv_file = open(sys.argv[1], "r")
    reader = csv.DictReader(csv_file)
    for identity in reader:
        database.append(identity)

    # TODO: Read DNA sequence file into a variable
    identity_file = open(sys.argv[2], "r")
    sequence = identity_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    # get the key from the dict
    x = database[0]
    # keys list
    keys = []
    for key in x:
        if key != 'name':
            keys.append(key)

    # TODO: Check database for matching profiles
    # iterate each key
    # create a list to store the identity key value
    numbers = []
    for i in range(len(keys)):
        numbers.append(longest_match(sequence, keys[i]))

    # match the database
    for people in database:
        flag = True
        for i in range(len(keys)):
            check = int(people[keys[i]])
            if numbers[i] != check:
                flag = False
                break
        if flag == True:
            print(f"{people['name']}")
            csv_file.close
            identity_file.close
            return
    print("No match")

    csv_file.close
    identity_file.close
    return

# Opimaize
# we can use the reader.fieldname[i] syntax to get the "key's name" in order to shorten the code
# and combine the steps, 1. get key's name
#                        2. calculate the logest_match

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
