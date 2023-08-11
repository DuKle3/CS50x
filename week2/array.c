#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
       n = get_int("n : ");
    }
    while(n < 1);

    int arr[n];
    arr[0] = 1;
    for (int i = 0; i < n; i++)
    {
        arr[i+1] = 2 * arr[i];
        printf("%i ",arr[i]);
    }
    printf("\n");
}