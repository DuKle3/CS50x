#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //get input
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //layer
    for (int i = 0 ; i < height ; i++)
    {
        //space
        for (int space = 0 ; space < height - i - 1 ; space++)
        {
            printf(" ");
        }
        //brick
        for (int j = 0 ; j < 2 ; j++)
        {
            for (int brick = 0 ; brick < i + 1 ; brick++)
            {
                printf("#");
            }
            if (j == 0)
            {
                //middle
                printf("  ");
            }
        }
        printf("\n");
    }
}