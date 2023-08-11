#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while(number <= 1);

    int sum = 0 ;
    long tmp = number / 10 ;
    //check algorithm
    while (tmp > 0)
    {
        int point = tmp % 10 * 2 ;
        if(point < 10)
        {
            sum += point ;
        }
        else
        {
            sum += (point % 10) ;
            sum += (point / 10) ;
        }
        tmp /= 100 ;
    }
    tmp = number;
    while (tmp > 0)
    {
        int point = tmp % 10;
        sum += point ;
        tmp /= 100;
    }

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        int length = 2;
        while (number >= 100)
        {
            number /= 10;
            length ++ ;
        }

        if ((number == 34 || number == 37) && length == 15)
        {
            printf("AMEX\n");
        }
        else if (number > 50 && number < 56 && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else if (number >= 40 && number <= 49 && (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}