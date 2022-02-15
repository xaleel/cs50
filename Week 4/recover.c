#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

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
    FILE *img = fopen ("temp.jpg", "r");//to initialize *img to be able to close it before we create the first jpg
    while (fread(&buffer, 1, 512, f) == 512 && img != NULL)
    {
        char filename [8];
        if (buffer[0] == 255 && buffer [1] == 216 && buffer [2] == 255 && (buffer[3] & 240) == 224) //if start of a new JPEG
        {
            fclose(img);//close previous file
            sprintf(filename, "%03i.jpg", num);//make new filename
            img = fopen (filename, "a");//make new jpg with new filename
            fwrite (&buffer, 1, 512, img);//copy the block in buffer to newfilenamejpg
            num ++;//increase no. of jpgs
        }
        else
        {
            if (fopen (filename, "a") != NULL)//if you can open the jpg
            {
                img = fopen (filename, "a");//open filename.jpg
                fwrite (&buffer, 1, 512, img);//copy next block
            }
        }
    }

}
