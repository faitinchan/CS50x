#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        fclose(card);
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[BLOCK_SIZE];

    // While there's still data left to read from the memory card
    int jpeg_count = 0;
    char filename[8];
    FILE *img = NULL;

    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // Create JDEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (img == NULL)
            {
                sprintf(filename, "%03i.jpg", jpeg_count);
                img = fopen(filename, "w");
            }
            else
            {
                fclose(img);
                jpeg_count++;
                sprintf(filename, "%03i.jpg", jpeg_count);
                img = fopen(filename, "w");
            }
            fwrite(buffer, 1, BLOCK_SIZE, img);
        }
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
    }

    fclose(img);
    fclose(card);
    return 0;
}
