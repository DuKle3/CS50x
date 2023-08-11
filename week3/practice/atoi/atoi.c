#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO

    // Base case
    int i = 0;
    int count = 0;
    while (input[i + 1])
    {
        count++;
        i++;
    }
    if (count)
    {
        int tmp = input[i] - '0';
        input[i] = 0;
        return 10 * convert(input) + tmp;
    }
    else
    {
        return input[i] - '0';
    }

}