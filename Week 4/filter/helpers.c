#include "helpers.h"
#include <stdio.h>
#include <math.h>

//can't run without the other files!

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE temp = image [i][j];
            BYTE R = image[i][j].rgbtRed;
            BYTE G = image[i][j].rgbtGreen;
            BYTE B = image[i][j].rgbtBlue;
            BYTE avg = (R + G + B + 1.5) / 3;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempr;
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tempr = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tempr;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempb[height][width];
    int rav = 0;
    int gav = 0;
    int bav = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int div = 0;
            //look at neighboring pixels: nei[row of neighbor][column of neighbor][location of neighbor in the pixel array (i or j)]
            int nei[3][3][2] = {{{i - 1, j - 1}, {i - 1, j}, {i - 1, j + 1}}, {{i, j - 1}, {i, j}, {i, j + 1}}, {{i + 1, j - 1}, {i + 1, j}, {i + 1, j + 1}}};
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (nei[k][l][0] >= 0 && nei[k][l][0] < height && nei[k][l][1] >= 0 && nei[k][l][1] < width) //if neighbor not outside image
                    {
                        rav += image[nei[k][l][0]][nei[k][l][1]].rgbtRed;
                        gav += image[nei[k][l][0]][nei[k][l][1]].rgbtGreen;
                        bav += image[nei[k][l][0]][nei[k][l][1]].rgbtBlue;
                        div++;
                    }
                }
            }
            rav = (rav + div / 2) / div;
            gav = (gav + div / 2) / div;
            bav = (bav + div / 2) / div;
            tempb[i][j].rgbtRed = rav;
            tempb[i][j].rgbtBlue = bav;
            tempb[i][j].rgbtGreen = gav;
            rav = 0;
            bav = 0;
            gav = 0;
            div = 0;
        }
    }
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n] = tempb [m][n];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempe[height][width];

    int Gxm [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gym [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxr = 0;
            int gxg = 0;
            int gxb = 0;
            int gyr = 0;
            int gyg = 0;
            int gyb = 0;
            //look at neighboring pixels: nei[row of neighbor][column of neighbor][location of neighbor in the pixel array (i or j)]
            int nei[3][3][2] = {{{i - 1, j - 1}, {i - 1, j}, {i - 1, j + 1}}, {{i, j - 1}, {i, j}, {i, j + 1}}, {{i + 1, j - 1}, {i + 1, j}, {i + 1, j + 1}}};
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }
                    if (j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }
                    gxb += image[i + k][j + l].rgbtBlue * Gxm[k + 1][l + 1];
                    gyb += image[i + k][j + l].rgbtBlue * Gym[k + 1][l + 1];
                    gxg += image[i + k][j + l].rgbtGreen * Gxm[k + 1][l + 1];
                    gyg += image[i + k][j + l].rgbtGreen * Gym[k + 1][l + 1];
                    gxr += image[i + k][j + l].rgbtRed * Gxm[k + 1][l + 1];
                    gyr += image[i + k][j + l].rgbtRed * Gym[k + 1][l + 1];
                }
            }

            int gr = round(sqrt((gxr * gxr + gyr * gyr)));
            int gg = round(sqrt((gxg * gxg + gyg * gyg)));
            int gb = round(sqrt((gxb * gxb + gyb * gyb)));
            tempe[i][j].rgbtRed = (gr > 255) ? 255 : gr;
            tempe[i][j].rgbtGreen = (gg > 255) ? 255 : gg;
            tempe[i][j].rgbtBlue = (gb > 255) ? 255 : gb;
        }
    }
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n].rgbtRed = tempe[m][n].rgbtRed;
            image[m][n].rgbtGreen = tempe[m][n].rgbtGreen;
            image[m][n].rgbtBlue = tempe[m][n].rgbtBlue;
        }
    }
    return;
}
