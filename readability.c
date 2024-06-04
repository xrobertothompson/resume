//Reading Level Analyzer, By Roberto Thompson
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // asks user for input
    string text = get_string("Text: ");

    // references methods
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // computes the coleman liau index

    double lavg = (double) letters / words * 100;
    double savg = (double) sentences / words * 100;

    double x = 0.0588 * lavg - 0.296 * savg - 15.8;

    int grade = round(x);

    // prints the grade level

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 1 && grade <= 16)
    {
        printf("Grade %d\n", grade);
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
}

// method for returning the number of letters in the text
int count_letters(string text)
{
    int letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

// method for returning the number of words in the text
int count_words(string text)
{
    int words = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isblank(text[i]))
        {
            words++;
        }
    }
    words++;
    return words;
}

// method for returning the number of sentences in the text*
int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}
