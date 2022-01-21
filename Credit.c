#include <stdio.h>
#include <cs50.h>
//Task url: https://cs50.harvard.edu/x/2022/psets/1/credit/

int main(void)
{

    long card = get_long("Enter the card number: ");
//printf("%li \n", card);
//first digit from left is a, second is b, etc
//I'm not sure if this is the most efficient way to extract each digit.

int p = card % 10;

int o = card / 10 % 10 ;

int n=card / 100 % 10;
int m = card / 1000 % 10;
int l = card / 10000 % 10;
int k = card / 100000 % 10;
int j = card / 1000000 % 10;
int i = card / 10000000 % 10;
int h = card / 100000000 % 10;
int g = card / 1000000000 % 10;
int f = card / 10000000000 % 10;
int e = card / 100000000000 % 10;
int d = card / 1000000000000 % 10;
int c = card / 10000000000000 % 10;
int b = card / 100000000000000 % 10;
int a = card / 1000000000000000 % 10;


int sum1 = a/5+a*2%10 + c/5+c*2%10 + e/5+e*2%10 + g/5+g*2%10 + i/5+i*2%10 + k/5+k*2%10 + m/5+m*2%10 + o/5+o*2%10;
int sum2 = b+d+f+h+j+l+n+p;
int sum = sum1 + sum2;

if (a == 0 && b == 3)
{
    if ((c==4 || c==7) && sum%10 == 0)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
else
{
    if ((a == 4 || (a == 0 && c == 0 && d == 4)) && sum%10 == 0)
    //LIMITATION: if the card is 16 digits and start with 0004 this code would recognize it as a valid visa card as if it was a 13-digit card that starts with 4. I don't know how to solve this issue
    {
        printf("VISA\n");
    }
    else
    {
        if (a == 5 && (b == 1 || b == 2 || b == 3 || b == 4 || b == 5) && sum%10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
}
