#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // get the input
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // the layer
    for (int i = 0 ; i < height ; i++)
    {
        // print the space
        for (int space = 0 ; space < height - i - 1 ; space++)
        {
            printf(" ");
        }
        // print the brick (#)
        for (int brick = 0 ; brick < i + 1 ; brick++)
        {
            printf("#");
        }
        // next layer
        printf("\n");
    }
}