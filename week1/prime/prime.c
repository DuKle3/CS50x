#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

#include <math.h>

bool prime(int number)
{
    // TODO
    int max = sqrt(number);
    for (int i = 2 ; i <= max ; i++)
    {
        if ((number % i) == 0)
        {
            return false;
        }
    }
    // except 1
    if (number == 1)
    {
        return false;
    }
    // return the value who has no 因數
    return true;
}
