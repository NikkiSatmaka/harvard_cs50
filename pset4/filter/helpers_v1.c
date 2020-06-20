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
            // Swap the pixels
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
    // Initialize a tmp image
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = 0;
            int green = 0;
            int red = 0;
            int count = 0;

            // Middle pixels
            blue += image[i][j].rgbtBlue;
            green += image[i][j].rgbtGreen;
            red += image[i][j].rgbtRed;
            count++;

            // Detect whether it's the left edge
            if (j - 1 >= 0)
            {
                blue += image[i][j - 1].rgbtBlue;
                green += image[i][j - 1].rgbtGreen;
                red += image[i][j - 1].rgbtRed;
                count++;
            }

            // Detect whether it's the right edge
            if (j + 1 < width)
            {
                blue += image[i][j + 1].rgbtBlue;
                green += image[i][j + 1].rgbtGreen;
                red += image[i][j + 1].rgbtRed;
                count++;
            }

            // Detect whether it's the top edge
            if (i - 1 >= 0)
            {
                blue += image[i - 1][j].rgbtBlue;
                green += image[i - 1][j].rgbtGreen;
                red += image[i - 1][j].rgbtRed;
                count++;

                // Detect whether it's the left edge
                if (j - 1 >= 0)
                {
                    blue += image[i - 1][j - 1].rgbtBlue;
                    green += image[i - 1][j - 1].rgbtGreen;
                    red += image[i - 1][j - 1].rgbtRed;
                    count++;
                }

                // Detect whether it's the right edge
                if (j + 1 < width)
                {
                    blue += image[i - 1][j + 1].rgbtBlue;
                    green += image[i - 1][j + 1].rgbtGreen;
                    red += image[i - 1][j + 1].rgbtRed;
                    count++;
                }

            }

            // Detect whether it's the bottom edge
            if (i + 1 < height)
            {
                blue += image[i + 1][j].rgbtBlue;
                green += image[i + 1][j].rgbtGreen;
                red += image[i + 1][j].rgbtRed;
                count++;

                // Detect whether it's the left edge
                if (j - 1 >= 0)
                {
                    blue += image[i + 1][j - 1].rgbtBlue;
                    green += image[i + 1][j - 1].rgbtGreen;
                    red += image[i + 1][j - 1].rgbtRed;
                    count++;
                }

                // Detect whether it's the right edge
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

            // Store the value in tmp image
            tmp[i][j].rgbtBlue = avgBlue;
            tmp[i][j].rgbtGreen = avgGreen;
            tmp[i][j].rgbtRed = avgRed;
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

            // Middle pixels
            xBlue += image[i][j].rgbtBlue * xKernel[1][1];
            xGreen += image[i][j].rgbtGreen * xKernel[1][1];
            xRed += image[i][j].rgbtRed * xKernel[1][1];

            yBlue += image[i][j].rgbtBlue * yKernel[1][1];
            yGreen += image[i][j].rgbtGreen * yKernel[1][1];
            yRed += image[i][j].rgbtRed * yKernel[1][1];

            // Detect whether it's the left edge
            if (j - 1 >= 0)
            {
                xBlue += image[i][j - 1].rgbtBlue * xKernel[1][0];
                xGreen += image[i][j - 1].rgbtGreen * xKernel[1][0];
                xRed += image[i][j - 1].rgbtRed * xKernel[1][0];

                yBlue += image[i][j - 1].rgbtBlue * yKernel[1][0];
                yGreen += image[i][j - 1].rgbtGreen * yKernel[1][0];
                yRed += image[i][j - 1].rgbtRed * yKernel[1][0];
            }

            // Detect whether it's the right edge
            if (j + 1 < width)
            {
                xBlue += image[i][j + 1].rgbtBlue * xKernel[1][2];
                xGreen += image[i][j + 1].rgbtGreen * xKernel[1][2];
                xRed += image[i][j + 1].rgbtRed * xKernel[1][2];

                yBlue += image[i][j + 1].rgbtBlue * yKernel[1][2];
                yGreen += image[i][j + 1].rgbtGreen * yKernel[1][2];
                yRed += image[i][j + 1].rgbtRed * yKernel[1][2];
            }

            // Detect whether it's the top edge
            if (i - 1 >= 0)
            {
                xBlue += image[i - 1][j].rgbtBlue * xKernel[0][1];
                xGreen += image[i - 1][j].rgbtGreen * xKernel[0][1];
                xRed += image[i - 1][j].rgbtRed * xKernel[0][1];

                yBlue += image[i - 1][j].rgbtBlue * yKernel[0][1];
                yGreen += image[i - 1][j].rgbtGreen * yKernel[0][1];
                yRed += image[i - 1][j].rgbtRed * yKernel[0][1];

                // Detect whether it's the left edge
                if (j - 1 >= 0)
                {
                    xBlue += image[i - 1][j - 1].rgbtBlue * xKernel[0][0];
                    xGreen += image[i - 1][j - 1].rgbtGreen * xKernel[0][0];
                    xRed += image[i - 1][j - 1].rgbtRed * xKernel[0][0];

                    yBlue += image[i - 1][j - 1].rgbtBlue * yKernel[0][0];
                    yGreen += image[i - 1][j - 1].rgbtGreen * yKernel[0][0];
                    yRed += image[i - 1][j - 1].rgbtRed * yKernel[0][0];
                }

                // Detect whether it's the right edge
                if (j + 1 < width)
                {
                    xBlue += image[i - 1][j + 1].rgbtBlue * xKernel[0][2];
                    xGreen += image[i - 1][j + 1].rgbtGreen * xKernel[0][2];
                    xRed += image[i - 1][j + 1].rgbtRed * xKernel[0][2];

                    yBlue += image[i - 1][j + 1].rgbtBlue * yKernel[0][2];
                    yGreen += image[i - 1][j + 1].rgbtGreen * yKernel[0][2];
                    yRed += image[i - 1][j + 1].rgbtRed * yKernel[0][2];
                }
            }

            // Detect whether it's the bottom edge
            if (i + 1 < height)
            {
                xBlue += image[i + 1][j].rgbtBlue * xKernel[2][1];
                xGreen += image[i + 1][j].rgbtGreen * xKernel[2][1];
                xRed += image[i + 1][j].rgbtRed * xKernel[2][1];

                yBlue += image[i + 1][j].rgbtBlue * yKernel[2][1];
                yGreen += image[i + 1][j].rgbtGreen * yKernel[2][1];
                yRed += image[i + 1][j].rgbtRed * yKernel[2][1];

                // Detect whether it's the left edge
                if (j - 1 >= 0)
                {
                    xBlue += image[i + 1][j - 1].rgbtBlue * xKernel[2][0];
                    xGreen += image[i + 1][j - 1].rgbtGreen * xKernel[2][0];
                    xRed += image[i + 1][j - 1].rgbtRed * xKernel[2][0];

                    yBlue += image[i + 1][j - 1].rgbtBlue * yKernel[2][0];
                    yGreen += image[i + 1][j - 1].rgbtGreen * yKernel[2][0];
                    yRed += image[i + 1][j - 1].rgbtRed * yKernel[2][0];
                }

                // Detect whether it's the right edge
                if (j + 1 < width)
                {
                    xBlue += image[i + 1][j + 1].rgbtBlue * xKernel[2][2];
                    xGreen += image[i + 1][j + 1].rgbtGreen * xKernel[2][2];
                    xRed += image[i + 1][j + 1].rgbtRed * xKernel[2][2];

                    yBlue += image[i + 1][j + 1].rgbtBlue * yKernel[2][2];
                    yGreen += image[i + 1][j + 1].rgbtGreen * yKernel[2][2];
                    yRed += image[i + 1][j + 1].rgbtRed * yKernel[2][2];
                }
            }

            int blue = round(sqrt(xBlue * xBlue + yBlue * yBlue));
            int green = round(sqrt(xGreen * xGreen + yGreen * yGreen));
            int red = round(sqrt(xRed * xRed + yRed * yRed));

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
