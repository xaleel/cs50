#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main (int argc, string argv []) {

    //check if only 1 key is given
    if (argc != 2){
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //check if key is 26 char long
    string key = argv[1];
    int klen = strlen(key);
    if (klen != 26){
        printf("Key must contain 26 characters.");
        return 1;
    }
    //check if key has all the letters of the alphabet, each exactly once
    int check = 0;
    for (int a = 0; a < 26; a++){
        for (int q = 0; q < 26; q++){
            if (key[q] == a+65 || key [q] == a+97){
                check++;
                q = 26;
            }
        }
    }
    if (check != 26) {
        printf("Key not valid.\n");
        return 1;
    }




    string phrase = get_string ("plaintext:");
    int length = strlen(phrase);
    char cipher [length];
    int place;
    for (int i=0; i<length; i++){
        if (phrase[i] > 64 && phrase [i] < 91){ //if uppercase
            cipher[i] = key [phrase[i]-65];
            cipher[i] = toupper (cipher[i]);
        } else if (phrase[i] > 96 && phrase [i] < 123){ //if lowercase
            cipher[i] = key [phrase[i]-97];
            cipher[i] = tolower(cipher[i]);
        } else {
            cipher[i] = phrase [i]; //meaning it's not a letter in the alphabet
        }

    }
    printf("ciphertext: ");
    for (int m = 0; m < length; m++)
    {
      printf("%c", cipher[m]);
    }
    printf("\n");
    //printf("ciphertext: %s\n", cipher);

}
