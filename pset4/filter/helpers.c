#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half_width = width / 2; j < half_width; j++)
        {
            int tmpBlue = image[i][j].rgbtBlue;
            int tmpGreen = image[i][j].rgbtGreen;
            int tmpRed = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtBlue = tmpBlue;
            image[i][width - 1 - j].rgbtGreen = tmpGreen;
            image[i][width - 1 - j].rgbtRed = tmpRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmpImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = 0;
            int green = 0;
            int red = 0;
            int count = 0;

            blue += image[i][j].rgbtBlue;
            green += image[i][j].rgbtGreen;
            red += image[i][j].rgbtRed;
            count++;

            if (j - 1 >= 0)
            {
                blue += image[i][j - 1].rgbtBlue;
                green += image[i][j - 1].rgbtGreen;
                red += image[i][j - 1].rgbtRed;
                count++;
            }

            if (j + 1 < width)
            {
                blue += image[i][j + 1].rgbtBlue;
                green += image[i][j + 1].rgbtGreen;
                red += image[i][j + 1].rgbtRed;
                count++;
            }

            if (i - 1 >= 0)
            {
                blue += image[i - 1][j].rgbtBlue;
                green += image[i - 1][j].rgbtGreen;
                red += image[i - 1][j].rgbtRed;
                count++;

                    if (j - 1 >= 0)
                    {
                        blue += image[i - 1][j - 1].rgbtBlue;
                        green += image[i - 1][j - 1].rgbtGreen;
                        red += image[i - 1][j - 1].rgbtRed;
                        count++;
                    }

                    if (j + 1 < width)
                    {
                        blue += image[i - 1][j + 1].rgbtBlue;
                        green += image[i - 1][j + 1].rgbtGreen;
                        red += image[i - 1][j + 1].rgbtRed;
                        count++;
                    }

            }

            if (i + 1 < height)
            {
                blue += image[i + 1][j].rgbtBlue;
                green += image[i + 1][j].rgbtGreen;
                red += image[i + 1][j].rgbtRed;
                count++;

                    if (j - 1 >= 0)
                    {
                        blue += image[i + 1][j - 1].rgbtBlue;
                        green += image[i + 1][j - 1].rgbtGreen;
                        red += image[i + 1][j - 1].rgbtRed;
                        count++;
                    }

                    if (j + 1 < width)
                    {
                        blue += image[i + 1][j + 1].rgbtBlue;
                        green += image[i + 1][j + 1].rgbtGreen;
                        red += image[i + 1][j + 1].rgbtRed;
                        count++;
                    }

            }

            int avgBlue = round(blue / (float) count);
            int avgGreen = round(green / (float) count);
            int avgRed = round(red / (float) count);

            tmpImage[i][j].rgbtBlue = avgBlue;
            tmpImage[i][j].rgbtGreen = avgGreen;
            tmpImage[i][j].rgbtRed = avgRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmpImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmpImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmpImage[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
