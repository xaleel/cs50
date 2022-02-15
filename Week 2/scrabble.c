#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//task url: https://cs50.harvard.edu/x/2022/labs/2/
// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("tie!\n");
    }


    // TODO: Print the winner
}

int compute_score(string word)
{
    int j = strlen(word);
    int i;
    int score = 0;
    int index = 0;
    for (i = 0; i < j; i++)
    {
        if (islower((char) word[i]))
        {
            index = (word[i] - 97);
            score += POINTS[index];
        }
        else
        {
            index = (word[i] - 65);
            score += POINTS[index];
        }
    }
    return score;
}
