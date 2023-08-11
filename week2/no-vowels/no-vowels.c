// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

char replace(char p);

int main(int argc, string argv[])
{
    if (argc == 1)
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
    for (int j = 1; j < argc; j++)
    {
        for (int i = 0; i < strlen(argv[j]); i++)
        {
            argv[j][i] = replace(argv[j][i]);
            printf("%c", argv[j][i]);
        }
        printf(" ");
    }
    printf("\n");
}

char replace(char p)
{
    switch (p)
    {
        case 'a':
            return '6';
        case 'e':
            return '3';
        case 'i':
            return '1';
        case 'o':
            return '0';
        default:
            return p;
    }
}