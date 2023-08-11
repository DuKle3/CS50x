#include <cs50.h>
#include <stdio.h>

int count = -1;

int coll(int n);

int main(void)
{
    int n = get_int("int: ");
    int i = coll(n);
    printf("%i\n",count);
    return 0;
}

int coll(int n)
{
    count++;

    if (n == 1)
        return 0;

    if (n % 2 == 0)
    {
        coll(n / 2);
    }
    else
    {
        coll(3 * n + 1);
    }
    return 0;
}