#include <stdio.h>
#include <cs50.h>
//Task url: https://cs50.harvard.edu/x/2022/psets/1/mario/more/
int main(void)
{

    int h;
    do
    {
        h = get_int("how high do you want the pyramid to be? ");
    }
    while (h < 1 || h > 8);

//printf("Height: %i \n", h);

for (int i = h; i > 0; i--)
{
    for (int j = 1; j < i; j++)
        {
            printf(" ");
        }
    for (int k = 0; k <= h - i; k++)
    {
        printf("#");
    }
    printf("  ");
    for (int l = 0; l <= h - i; l++)
    {
        printf("#");
    }
    printf("\n");
}
}
