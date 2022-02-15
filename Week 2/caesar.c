#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv [])
{
    //check if only 1 key is given
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    string k = argv[1];
    int key = atoi(k);
    int check = 0;
    for (int j = 0; j < strlen(k); j++)
    {

        if (k[j] > 47 && k[j] < 58)
        {
            check++;
        }
    }
    if (check != strlen(k))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    string plaintext = get_string("plaintext:  ");
    int len = strlen(plaintext);
    int keyloop = key % 26;
    char cipher [len];
    for (int i = 0; i < len; i++)
    {
        if ((plaintext[i] > 64 && plaintext[i] < 91) || (plaintext[i] > 96 && plaintext[i] < 123)) // if text is a letter
        {
            if ((plaintext[i] + keyloop > 90 && plaintext[i] + keyloop < 97) || plaintext[i] + keyloop > 122) // if addition goes beyond z or Z
            {
                cipher[i] = plaintext[i] + keyloop - 26; //loop back to a or A
            }
            else
            {
                cipher[i] = plaintext[i] + keyloop; // if addition doesn't need to loop
            }
        }
        else // if text is not a letter
        {
            cipher[i] = plaintext[i];
        }
    }

    printf("ciphertext: ");
    for (int m = 0; m < len; m++)
    {
        printf("%c", cipher[m]);
    }
    printf("\n");
}
