// Scrabble Score Calculator, By Roberto Thompson
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points per letter
int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Prototype
int compute_score(string word);

int main(void)
{
    // Prompts the user for the words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Compute scores
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Determine the winner
    if (score1 > score2)
    {
        printf("Player 1 Wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Declares variable score
    int score = 0;

    for (int i = 0, length = strlen(word); i < length; i++)
    {
        // If the character is uppercase
        if (isupper(word[i]))
        {
            // Adds the score for the corresponding letter
            score += points[word[i] - 'A'];
        }
        // If the character is lowercase
        else if (islower(word[i]))
        {
            // Adds the score for the corresponding letter
            score += points[word[i] - 'a'];
        }
    }

    // Return the final score
    return score;
}
