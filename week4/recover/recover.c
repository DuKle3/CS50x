#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // argv
    if (argc != 2)
    {
        printf("Usage : ./recover.c <FILE>\n");
        return 1;
    }

    // read the memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // buffer
    uint8_t buffer[BLOCK_SIZE];
    // filename
    char filename[8];
    // file pointer
    FILE *output = NULL;
    // jpg_counter
    int count = 0;
    // jpg_found
    int jpg_found = 0;


    while(fread(&buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // check jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpg_found)
            {
                fclose(output);
            }
            else
            {
                jpg_found = 1;
            }
            sprintf(filename, "%03i.jpg", count);
            output = fopen(filename, "w");
            count++;
        }
        if (jpg_found)
        {
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
    }
    fclose(file);
    fclose(output);
    return 0;
}