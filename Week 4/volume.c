// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }
    // Check whether the factor is correct
    int argvlen = strlen(argv[3]);
    for (int i = 0; i < argvlen; i++)
    {
        if (!isdigit(argv[3][i]))
        {
            if (argv[3][i] != '.')
            {
                printf("Usage: ./volume input.wav output.wav factor\n");
                return 1;
            }
        }

    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header
    char c;
    for (int j = 1; j < HEADER_SIZE + 1; j++)
    {
        fread(&c, sizeof(char), 1, input);
        fwrite(&c, sizeof(char), 1, output);
    }

    // Read samples from input file and write updated data to output file
    int16_t sample;
    while (fread(&sample, 2, 1, input))
    {
        sample *= factor;
        fwrite(&sample, 2, 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);
}
