#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //store green blue red values
            float blue = image[h][w].rgbtBlue;
            float green = image[h][w].rgbtGreen;
            float red = image[h][w].rgbtRed;

            //calculate average rgb to grayscale value
            int average = round((red + blue + green) / 3);

            //asign average to each pixel
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //calculate sepia values
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);

            //check max values to 255
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            //asign sepia values to each pixel
            image[h][w].rgbtBlue = sepiaBlue;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            //save red green blue to temp values
            int reflectBlue = image[h][w].rgbtBlue;
            int reflectGreen = image[h][w].rgbtGreen;
            int reflectRed = image[h][w].rgbtRed;

            //swap first values
            image[h][w].rgbtBlue = image[h][width - w - 1].rgbtBlue;
            image[h][w].rgbtGreen = image[h][width - w - 1].rgbtGreen;
            image[h][w].rgbtRed = image[h][width - w - 1].rgbtRed;

            //swap second values using temp
            image[h][width - w - 1].rgbtBlue = reflectBlue;
            image[h][width - w - 1].rgbtGreen = reflectGreen;
            image[h][width - w - 1].rgbtRed = reflectRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //save pixel to temp
            tmp[h][w] = image[h][w];
        }
    }


    for (int h = 0; h < height; h++)
    {
        // Loop through columns
        for (int w = 0; w < width; w++)
        {
            //set to 0 each pixel
            float sum_blue = 0;
            float sum_green = 0;
            float sum_red = 0;
            int counter = 0;

            //loop for pixels around
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (h + k < 0 || h + k >= height)
                    {
                        continue;
                    }
                    if (w + l < 0 || w + l >= width)
                    {
                        continue;
                    }

                    sum_green += tmp[h + k][w + l].rgbtGreen;
                    sum_blue += tmp[h + k][w + l].rgbtBlue;
                    sum_red += tmp[h + k][w + l].rgbtRed;
                    counter++;
                }
            }

            //calculate average colors with around pixels
            int blurBlue = round(sum_blue / counter);
            int blurGreen = round(sum_green / counter);
            int blurRed = round(sum_red / counter);

            //set calculated values to each pixel
            image[h][w].rgbtBlue = blurBlue;
            image[h][w].rgbtGreen = blurGreen;
            image[h][w].rgbtRed = blurRed;
        }
    }
    return;
}

