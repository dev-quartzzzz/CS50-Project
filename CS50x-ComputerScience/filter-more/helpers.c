#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int temp =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = temp;
            image[i][j].rgbtGreen = temp;
            image[i][j].rgbtBlue = temp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            float counter = 0.00;
            for (int k = i - 1; k < (i + 2) && k < height; k++)
            {
                for (int l = j - 1; l < (j + 2) && l < width; l++)
                {
                    if (k >= 0 && l >= 0)
                    {
                        red += temp[k][l].rgbtRed;
                        green += temp[k][l].rgbtGreen;
                        blue += temp[k][l].rgbtBlue;
                        counter++;
                    }
                }
            }
            image[i][j].rgbtRed = round(red / counter);
            image[i][j].rgbtGreen = round(green / counter);
            image[i][j].rgbtBlue = round(blue / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    int gxArr[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gyArr[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gx_rgbtRed = 0;
            int Gx_rgbtGreen = 0;
            int Gx_rgbtBlue = 0;
            int Gy_rgbtRed = 0;
            int Gy_rgbtBlue = 0;
            int Gy_rgbtGreen = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    int x = i + k;
                    int y = j + l;
                    if (x >= 0 && y >= 0 && x < height && y < width)
                    {
                        Gx_rgbtRed += (gxArr[k + 1][l + 1] * temp[x][y].rgbtRed);
                        Gx_rgbtGreen += (gxArr[k + 1][l + 1] * temp[x][y].rgbtGreen);
                        Gx_rgbtBlue += (gxArr[k + 1][l + 1] * temp[x][y].rgbtBlue);

                        Gy_rgbtRed += (gyArr[k + 1][l + 1] * temp[x][y].rgbtRed);
                        Gy_rgbtGreen += (gyArr[k + 1][l + 1] * temp[x][y].rgbtGreen);
                        Gy_rgbtBlue += (gyArr[k + 1][l + 1] * temp[x][y].rgbtBlue);
                    }
                }
            }
            int red = round(sqrt(pow(Gx_rgbtRed, 2) + pow(Gy_rgbtRed, 2)));
            int green = round(sqrt(pow(Gx_rgbtGreen, 2) + pow(Gy_rgbtGreen, 2)));
            int blue = round(sqrt(pow(Gx_rgbtBlue, 2) + pow(Gy_rgbtBlue, 2)));

            image[i][j].rgbtRed = (red > 255) ? 255 : red;
            image[i][j].rgbtGreen = (green > 255) ? 255 : green;
            image[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }
    return;
}
