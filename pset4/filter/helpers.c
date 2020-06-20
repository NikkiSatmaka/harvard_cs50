#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = 0;
            avg += image[i][j].rgbtBlue;
            avg += image[i][j].rgbtGreen;
            avg += image[i][j].rgbtRed;
            avg = round((float) avg / 3);
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
    RGBTRIPLE tmp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half_width = width / 2; j < half_width; j++)
        {
            // Swap the pixels
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize a tmp image
    RGBTRIPLE tmp[height][width];

    // Iterate every single pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = 0;
            int green = 0;
            int red = 0;
            int count = 0;

            // Iterate every 3x3 box and kernel loc for every single pixel
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    // Check boundaries of each pixel
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        blue += image[k][l].rgbtBlue;
                        green += image[k][l].rgbtGreen;
                        red += image[k][l].rgbtRed;
                        count++;
                    }
                }
            }

            // Store the value in tmp
            tmp[i][j].rgbtBlue = round(blue / (float) count);
            tmp[i][j].rgbtGreen = round(green / (float) count);
            tmp[i][j].rgbtRed = round(red / (float) count);
        }
    }

    // Replace the real image with tmp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    // Initialize the xKernel array
    int xKernel[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    // Initialize the xKernel array
    int yKernel[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Iterate every single pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int xBlue = 0;
            int xGreen = 0;
            int xRed = 0;

            int yBlue = 0;
            int yGreen = 0;
            int yRed = 0;

            // Iterate every 3x3 box and kernel loc for every single pixel
            for (int k = i - 1, xLoc = 0; k < i + 2; k++, xLoc++)
            {
                for (int l = j - 1, yLoc = 0; l < j + 2; l++, yLoc++)
                {
                    // Check boundaries of each pixel
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        xBlue += image[k][l].rgbtBlue * xKernel[xLoc][yLoc];
                        xGreen += image[k][l].rgbtGreen * xKernel[xLoc][yLoc];
                        xRed += image[k][l].rgbtRed * xKernel[xLoc][yLoc];

                        yBlue += image[k][l].rgbtBlue * yKernel[xLoc][yLoc];
                        yGreen += image[k][l].rgbtGreen * yKernel[xLoc][yLoc];
                        yRed += image[k][l].rgbtRed * yKernel[xLoc][yLoc];
                    }
                }
            }

            int blue = round(sqrt(pow(xBlue, 2) + pow(yBlue, 2)));
            int green = round(sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
            int red = round(sqrt(pow(xRed, 2) + pow(yRed, 2)));

            if (blue > 255)
            {
                blue = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (red > 255)
            {
                red = 255;
            }

            // Store the value in tmp image
            tmp[i][j].rgbtBlue = blue;
            tmp[i][j].rgbtGreen = green;
            tmp[i][j].rgbtRed = red;
        }
    }

    // Replace the real image with the tmp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
        }
    }

    return;
}
