#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check only one arg
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //check 26
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //check repeated characters
    int diff[26] = {0};
    string key = argv[1];

    for (int i = 0; i < 26; i++)
    {
        diff[toupper(key[i]) - 'A']++;
    }

    for (int i = 0; i < 26; i++)
    {
        if (diff[i] != 1)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    //get string
    string text = get_string("plaintext:  ");

    //substitution
    int n = strlen(text);
    for (int i = 0; i < n; i++)
    {
        if (isupper(text[i]))
        {
            text[i] = toupper(key[text[i] - 'A']);
        }
        else if (islower(text[i]))
        {
            text[i] = tolower(key[text[i] - 'a']);
        }
        else
        {
            text[i] = text[i];
        }
    }
    printf("ciphertext: %s\n", text);
    return 0;
}
