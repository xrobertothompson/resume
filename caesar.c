// Caesar Cipher Encrypter, By Roberto Thompson
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototype
string compute_cipher(string text, int key);

// command line argument
int main(int argc, string argv[])
{
    // if argc goes beyond the second place in the array
    if (argc != 2)
    {
        // print out error message
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // validates isdigit method
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: %s key\n", argv[0]);
            return 1;
        }
    }

    // converts to int
    int key = atoi(argv[1]);

    // gets plaintext
    string text = get_string("plaintext: ");

    // computes cipher
    string cipher = compute_cipher(text, key);

    // prints cipher text
    printf("ciphertext: %s\n", cipher);

    return 0;
}

// cipher method
string compute_cipher(string text, int key)
{
    // iterates through the plaintext
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // overlying condition that the i needs to check the isalpha condition to progress
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                // converts i to zero based index (alphabetical), adds the key of given user input,
                // mods it to x based zero index, returns to ASCII uppercase letter (alphabetical)
                text[i] = (text[i] - 'A' + key) % 26 + 'A';
            }
            else if (islower(text[i]))
            {
                // converts i to zero based index (alphabetical), adds the key of given user input,
                // mods it to x based zero index, returns to ASCII lowercase letter (alphabetical)
                text[i] = (text[i] - 'a' + key) % 26 + 'a';
            }
        }
    }
    // returns to reference in main method
    return text;
}
