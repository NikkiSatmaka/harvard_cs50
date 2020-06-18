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
            if (avg > 255)
            {
                avg = 255;
            }
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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avgBlue;
            int avgGreen;
            int avgRed;

            if (i == 0)
            {

                //  Top left pixel
                if (j == 0)
                {
                    avgBlue =
                        (
                            image[i][j].rgbtBlue +
                            image[i][j + 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue +
                            image[i + 1][j + 1].rgbtBlue
                        ) / (float) 4;
                    avgGreen =
                        (
                            image[i][j].rgbtGreen +
                            image[i][j + 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen +
                            image[i + 1][j + 1].rgbtGreen
                        ) / (float) 4;
                    avgRed =
                        (
                            image[i][j].rgbtRed +
                            image[i][j + 1].rgbtRed +
                            image[i + 1][j].rgbtRed +
                            image[i + 1][j + 1].rgbtRed
                        ) / (float) 4;
                }

                // Top right pixel
                else if (j == width - 1)
                {
                    avgBlue =
                        (
                            image[i][j].rgbtBlue +
                            image[i][j - 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue +
                            image[i + 1][j - 1].rgbtBlue
                        ) / (float) 4;
                    avgGreen =
                        (
                            image[i][j].rgbtGreen +
                            image[i][j - 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen +
                            image[i + 1][j - 1].rgbtGreen
                        ) / (float) 4;
                    avgRed =
                        (
                            image[i][j].rgbtRed +
                            image[i][j - 1].rgbtRed +
                            image[i + 1][j].rgbtRed +
                            image[i + 1][j - 1].rgbtRed
                        ) / (float) 4;
                }

                // Top middle pixels
                else
                {
                    avgBlue =
                        (
                            image[i][j].rgbtBlue +
                            image[i][j - 1].rgbtBlue +
                            image[i][j + 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue +
                            image[i + 1][j - 1].rgbtBlue +
                            image[i + 1][j + 1].rgbtBlue
                        ) / (float) 6;
                    avgGreen =
                        (
                            image[i][j].rgbtGreen +
                            image[i][j - 1].rgbtGreen +
                            image[i][j + 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen +
                            image[i + 1][j - 1].rgbtGreen +
                            image[i + 1][j + 1].rgbtGreen
                        ) / (float) 6;
                    avgRed =
                        (
                            image[i][j].rgbtRed +
                            image[i][j - 1].rgbtRed +
                            image[i][j + 1].rgbtRed +
                            image[i + 1][j].rgbtRed +
                            image[i + 1][j - 1].rgbtRed +
                            image[i + 1][j + 1].rgbtRed
                        ) / (float) 6;
                }
            }
            else if (i == height - 1)
            {

                // Bottom left pixel
                if (j == 0)
                {
                    avgBlue =
                        (
                            image[i][j].rgbtBlue +
                            image[i][j + 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue +
                            image[i - 1][j + 1].rgbtBlue
                        ) / (float) 4;
                    avgGreen =
                        (
                            image[i][j].rgbtGreen +
                            image[i][j + 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen +
                            image[i - 1][j + 1].rgbtGreen
                        ) / (float) 4;
                    avgRed =
                        (
                            image[i][j].rgbtRed +
                            image[i][j + 1].rgbtRed +
                            image[i - 1][j].rgbtRed +
                            image[i - 1][j + 1].rgbtRed
                        ) / (float) 4;
                }

                // Bottom right pixel
                else if (j == width - 1)
                {
                    avgBlue =
                        (
                            image[i][j].rgbtBlue +
                            image[i][j - 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue +
                            image[i - 1][j - 1].rgbtBlue
                        ) / (float) 4;
                    avgGreen =
                        (
                            image[i][j].rgbtGreen +
                            image[i][j - 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen +
                            image[i - 1][j - 1].rgbtGreen
                        ) / (float) 4;
                    avgRed =
                        (
                            image[i][j].rgbtRed +
                            image[i][j - 1].rgbtRed +
                            image[i - 1][j].rgbtRed +
                            image[i - 1][j - 1].rgbtRed
                        ) / (float) 4;
                }

                // Bottom middle pixels
                else
                {
                    avgBlue =
                        (
                            image[i][j].rgbtBlue +
                            image[i][j - 1].rgbtBlue +
                            image[i][j + 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue +
                            image[i - 1][j - 1].rgbtBlue +
                            image[i - 1][j + 1].rgbtBlue
                        ) / (float) 6;
                    avgGreen =
                        (
                            image[i][j].rgbtGreen +
                            image[i][j - 1].rgbtGreen +
                            image[i][j + 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen +
                            image[i - 1][j - 1].rgbtGreen +
                            image[i - 1][j + 1].rgbtGreen
                        ) / (float) 6;
                    avgRed =
                        (
                            image[i][j].rgbtRed +
                            image[i][j - 1].rgbtRed +
                            image[i][j + 1].rgbtRed +
                            image[i - 1][j].rgbtRed +
                            image[i - 1][j - 1].rgbtRed +
                            image[i - 1][j + 1].rgbtRed
                        ) / (float) 6;
                }
            }
            else
            {

                // Left-most pixels
                if (j == 0)
                {
                    avgBlue =
                        (
                            image[i][j].rgbtBlue +
                            image[i][j + 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue +
                            image[i - 1][j + 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue +
                            image[i + 1][j + 1].rgbtBlue
                        ) / (float) 6;
                    avgGreen =
                        (
                            image[i][j].rgbtGreen +
                            image[i][j + 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen +
                            image[i - 1][j + 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen +
                            image[i + 1][j + 1].rgbtGreen
                        ) / (float) 6;
                    avgRed =
                        (
                            image[i][j].rgbtRed +
                            image[i][j + 1].rgbtRed +
                            image[i - 1][j].rgbtRed +
                            image[i - 1][j + 1].rgbtRed +
                            image[i + 1][j].rgbtRed +
                            image[i + 1][j + 1].rgbtRed
                        ) / (float) 6;
                }

                //  Right-most pixels
                else if (j == width - 1)
                {
                    avgBlue =
                        (
                            image[i][j].rgbtBlue +
                            image[i][j - 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue +
                            image[i - 1][j - 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue +
                            image[i + 1][j - 1].rgbtBlue
                        ) / (float) 6;
                    avgGreen =
                        (
                            image[i][j].rgbtGreen +
                            image[i][j - 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen +
                            image[i - 1][j - 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen +
                            image[i + 1][j - 1].rgbtGreen
                        ) / (float) 6;
                    avgRed =
                        (
                            image[i][j].rgbtRed +
                            image[i][j - 1].rgbtRed +
                            image[i - 1][j].rgbtRed +
                            image[i - 1][j - 1].rgbtRed +
                            image[i + 1][j].rgbtRed +
                            image[i + 1][j - 1].rgbtRed
                        ) / (float) 6;
                }

                //  The rest middle pixels
                else
                {
                    avgBlue =
                        (
                            image[i][j].rgbtBlue +
                            image[i][j - 1].rgbtBlue +
                            image[i][j + 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue +
                            image[i - 1][j - 1].rgbtBlue +
                            image[i - 1][j + 1].rgbtBlue +
                            image[i + 1][j].rgbtBlue +
                            image[i + 1][j - 1].rgbtBlue +
                            image[i + 1][j + 1].rgbtBlue
                        ) / (float) 9;
                    avgGreen =
                        (
                            image[i][j].rgbtGreen +
                            image[i][j - 1].rgbtGreen +
                            image[i][j + 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen +
                            image[i - 1][j - 1].rgbtGreen +
                            image[i - 1][j + 1].rgbtGreen +
                            image[i + 1][j].rgbtGreen +
                            image[i + 1][j - 1].rgbtGreen +
                            image[i + 1][j + 1].rgbtGreen
                        ) / (float) 9;
                    avgRed =
                        (
                            image[i][j].rgbtRed +
                            image[i][j - 1].rgbtRed +
                            image[i][j + 1].rgbtRed +
                            image[i - 1][j].rgbtRed +
                            image[i - 1][j - 1].rgbtRed +
                            image[i - 1][j + 1].rgbtRed +
                            image[i + 1][j].rgbtRed +
                            image[i + 1][j - 1].rgbtRed +
                            image[i + 1][j + 1].rgbtRed
                        ) / (float) 9;
                }
            }

            if (avgBlue > 255)
            {
                avgBlue = 255;
            }

            if (avgGreen > 255)
            {
                avgGreen = 255;
            }

            if (avgRed > 255)
            {
                avgRed = 255;
            }

            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtRed = avgRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
