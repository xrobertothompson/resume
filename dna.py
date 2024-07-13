# DNA Profiling Program, By Roberto Thompson, with the help of distribution code from the CS50x Program
import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py databases/your_database.csv sequences/your_sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    database_filename = sys.argv[1]
    individuals = []
    with open(database_filename) as db_file:
        reader = csv.DictReader(db_file)
        for row in reader:
            individuals.append(row)

    # TODO: Read DNA sequence file into a variable
    sequence_filename = sys.argv[2]
    with open(sequence_filename) as sequence_file:
        sequence = sequence_file.read().strip()

    # extracts STRs from the CSV file
    str_types = list(individuals[0].keys())[1:]  # Exclude the 'name' column

    # TODO: Find longest match of each STR in DNA sequence
    str_counts = {}
    for subsequence in str_types:
        str_counts[subsequence] = longest_match(sequence, subsequence)

    # TODO: Check database for matching profiles
    for person in individuals:
        match = True
        for subsequence in str_types:
            if int(person[subsequence]) != str_counts[subsequence]:
                match = False
                break
        if match:
            print(person['name'])
            return

    # if no match
    print("No match")


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
