// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int lower, upper, digit, symbol;
    int i = 0;
    while (password[i])
    {
        if (islower(password[i]))
        {
            lower = 1;
        }
        if (isupper(password[i]))
        {
            upper = 1;
        }
        if (isdigit(password[i]))
        {
            digit = 1;
        }
        if (isprint(password[i]))
        {
            if (!isalnum(password[i]))
            {
                symbol = 1;
            }
        }
        i++;
    }
    if (lower && upper && digit && symbol)
    {
        return true;
    }
    return false;
}
