# Reading Level Analyzer, By Roberto Thompson
from cs50 import get_string

# main function


def main():
    # asks user for input
    text = get_string("Text: ")
    # prototype for letters abstraction
    letters = count_letters(text)
    # prototype for words abstraction
    words = count_words(text)
    # prototype for sentences abstraction
    sentences = count_sentences(text)
    # computes the coleman liau index
    lavg = (letters / words) * 100.0
    savg = (sentences / words) * 100.0
    x = 0.0588 * lavg - 0.296 * savg - 15.8
    grade = round(x)
    # prints the grade level
    if grade < 1:
        print("Before Grade 1")
    elif 1 <= grade <= 16:
        print(f"Grade {grade}")
    else:
        print("Grade 16+")


# count letters abstraction
def count_letters(text):
    letters = 0
    for i in range(len(text)):
        if text[i].isalpha():
            letters += 1
    return letters

# count words abstraction


def count_words(text):
    words = 1
    for i in range(len(text)):
        if text[i] == ' ':
            words += 1
    return words

# count sentences abstraction


def count_sentences(text):
    sentences = 0
    for i in range(len(text)):
        if text[i] in ['.', '!', '?']:
            sentences += 1
    return sentences


# returns abstractions to its main function
if __name__ == "__main__":
    main()
