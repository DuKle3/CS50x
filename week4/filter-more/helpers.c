#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tmp = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            image[i][j].rgbtBlue = tmp;
            image[i][j].rgbtGreen = tmp;
            image[i][j].rgbtRed = tmp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int j = 0; j < width / 2; j++)
    {
        for (int i = 0; i < height; i++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            double red = 0;
            double blue = 0;
            double green = 0;
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    if (i + row < 0 || i + row > height - 1)
                    {
                        continue;
                    }
                    if (j + col < 0 || j + col > width - 1)
                    {
                        continue;
                    }
                    count++;
                    red += image[i + row][j + col].rgbtRed;
                    blue += image[i + row][j + col].rgbtBlue;
                    green += image[i + row][j + col].rgbtGreen;
                }
            }
            tmp[i][j].rgbtRed = round(red / count);
            tmp[i][j].rgbtBlue = round(blue / count);
            tmp[i][j].rgbtGreen = round(green / count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    double Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    double Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = -1;
            double rx = 0, bx = 0, gx = 0, ry = 0, by = 0, gy = 0;
            for (int row = -1; row <= 1; row++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    count ++;
                    if (i + row < 0 || i + row > height - 1)
                    {
                        continue;
                    }
                    if (j + col < 0 || j + col > width - 1)
                    {
                        continue;
                    }
                    rx += Gx[count] * image[i + row][j + col].rgbtRed;
                    bx += Gx[count] * image[i + row][j + col].rgbtBlue;
                    gx += Gx[count] * image[i + row][j + col].rgbtGreen;
                    ry += Gy[count] * image[i + row][j + col].rgbtRed;
                    by += Gy[count] * image[i + row][j + col].rgbtBlue;
                    gy += Gy[count] * image[i + row][j + col].rgbtGreen;
                }
            }
            tmp[i][j].rgbtRed = round(sqrt(rx * rx + ry * ry)) > 255 ? 255 : round(sqrt(rx * rx + ry * ry));
            tmp[i][j].rgbtBlue = round(sqrt(bx * bx + by * by)) > 255 ? 255 : round(sqrt(bx * bx + by * by));
            tmp[i][j].rgbtGreen = round(sqrt(gx * gx + gy * gy)) > 255 ? 255 : round(sqrt(gx * gx + gy * gy));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
