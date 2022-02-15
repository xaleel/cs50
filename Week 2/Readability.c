#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int wordcount(string text);
int sentencecount(string text);
int count_letters(string text);

int main(void)
{
    string text = get_string("Text: ");
    //L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.
    //
    //printf("%i \n", wcount);

    int wcount = wordcount(text);
    int scount = sentencecount(text);
    int lcount = count_letters(text);
    //printf("letters %i \n", lcount);
    double L = (double)lcount * 100 / (double)wcount;
    //printf("words %i \n", wcount);
    //printf("%f \n", L);
    double S = (double)scount * 100 / (double)wcount;
    //printf("sentences %i \n", scount);
    //printf("%f \n", S);




    double index = 0.0588 * L - 0.296 * S - 15.8;
    double result = round(index);
    if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (result < 16)
    {
        printf("Grade %0.f\n", result);
    }
    else
    {
        printf("Grade 16+\n");
    }





}

int wordcount(string text)
{
    int i;
    int count = 1;
    int len = strlen(text);
    for (i = 0; i < len; i++)
    {
        if (text[i] == 32)
        {
            count++;
        }
    }
    return count;

}

int sentencecount(string text)
{
    int j;
    int count2 = 0;
    int leng = strlen(text);
    for (j = 0; j < leng; j++)
    {
        if (text[j] == 46 || text[j] == 33 || text[j] == 63)
        {
            count2++;
        }
    }
    return count2;
}

int count_letters(string text)
{
    int k;
    int count3 = 0;
    int lengt = strlen(text);
    for (k = 0; k < lengt; k++)
    {
        if ((text[k] > 64 && text[k] < 91) || (text [k] > 96 && text[k] < 123))
        {
            count3++;
        }
    }
    return count3;
}
