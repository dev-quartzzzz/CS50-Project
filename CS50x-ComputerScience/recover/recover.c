#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Could not be opened %s\n", argv[1]);
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];

    int i = 0;

    char filename[10];

    FILE *img = NULL;

    int found_image = 0;

    while (fread(buffer, sizeof(char) * BLOCK_SIZE, 1, card) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (found_image == 1)
            {
                fclose(img);
            }
            else
            {
                found_image = 1;
            }
            sprintf(filename, "%03i.jpg", i);

            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(car
                printf("Could not allocate");
                return 1;
            }
            i++;
        }
        if (found_image == 1)
        {
            fwrite(buffer, sizeof(char) * BLOCK_SIZE, 1, img);
        }
    }

    fclose(card);
    if (found_image)
        fclose(img);
}
