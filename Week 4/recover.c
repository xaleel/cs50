#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("format input ./recover FILENAME.raw\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    BYTE buffer[512];
    int num = 0;//number of output JPEGs
    FILE *img = NULL;//to initialize *img to be able to close it before we create the first jpg
    while (fread(&buffer, 1, 512, f) == 512)// && img != NULL
    {
        char filename [8];
        if (buffer[0] == 255 && buffer [1] == 216 && buffer [2] == 255 && (buffer[3] & 240) == 224) //if start of a new JPEG
        {
            if (num == 0)//if 1st jpg
            {
                sprintf(filename, "%03i.jpg", num); //make new filename
                img = fopen(filename, "w"); //open filename.jpg
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", num); //make new filename
                img = fopen(filename, "w"); //open filename.jpg
            }
            fwrite(&buffer, 1, 512, img); //copy the block in buffer to newfilenamejpg
            num ++;//increase no. of jpgs
        }
        else
        {
            if (num > 0)//don't run before the 1st jpg is found
            {
                fwrite(&buffer, 1, 512, img); //copy the next block in buffer to newfilenamejpg
            }
        }
    }
}
