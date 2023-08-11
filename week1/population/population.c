#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int init_size,end_size ;

    // TODO: Prompt for start size
    do
    {
        init_size = get_int("Start size: ");
    }while(init_size <9);

    // TODO: Prompt for end size
    do
    {
        end_size = get_int("End size: ");
    }while(end_size < init_size);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    int size = init_size;
    while(size < end_size)
    {
        size = size + size/3 - size/4;
        years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n",years);
}
