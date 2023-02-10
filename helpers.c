#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            //get average of all three colors
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen;
            float average = sum / 3;
            //transform to unsigned int 8 bit -- round to the nearest integer
            average = (uint8_t)lrint(average);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE(*image_r)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    //check if malloc succeeded
    if (*image_r == NULL)
    {
        // Handle error
        printf("Memory cannot be allocated!");
        return;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_r[i][width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
            image_r[i][width - j - 1].rgbtRed = image[i][j].rgbtRed;
            image_r[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //record the buffer image "image_r" to the initial image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = image_r[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_r[i][j].rgbtRed;
            image[i][j].rgbtBlue = image_r[i][j].rgbtBlue;
        }
    }

    free(*image_r);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a buffer image image_b
    RGBTRIPLE(*image_b)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    //check if malloc succeeded
    if (*image_b == NULL)
    {
        // Handle error
        printf("Memory cannot be allocated!");
        return;
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            float count = 0;
            float sum_r = 0, sum_g = 0, sum_b = 0;
            //for each el-t of an array let's count average
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    //exclude corner cases
                    if (i + dx >= 0 && i + dx < height && j + dy >= 0 && j + dy < width)
                    {
                        sum_r += image[i + dx][j + dy].rgbtRed;
                        sum_g += image[i + dx][j + dy].rgbtGreen;
                        sum_b += image[i + dx][j + dy].rgbtBlue;
                        count++;
                    }
                }
            }
            //record values in the buffer
            float average = sum_r / count;
            image_b[i][j].rgbtRed = round(average);
            average = sum_g / count;
            image_b[i][j].rgbtGreen = round(average);
            average = sum_b / count;
            image_b[i][j].rgbtBlue = round(average);
        }
    }
    //record the buffer "image_b" to the initial image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = image_b[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_b[i][j].rgbtRed;
            image[i][j].rgbtBlue = image_b[i][j].rgbtBlue;
        }
    }
    free(*image_b);
    return;
}


int GX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int GY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //create a buffer image image_b
    RGBTRIPLE(*image_e)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    //check if malloc succeeded
    if (*image_e == NULL)
    {
        // Handle error
        printf("Memory cannot be allocated!");
        return;
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            //variables to keep the weighed sum for each color
            float xsum_r = 0, xsum_g = 0, xsum_b = 0;
            float ysum_r = 0, ysum_g = 0, ysum_b = 0;

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    //exclude corners as if they were RGB 0,0,0 (black)
                    if (i + dx >= 0 && i + dx < height && j + dy >= 0 && j + dy < width)
                    {
                        xsum_r += image[i + dx][j + dy].rgbtRed * GX[1 + dx][1 + dy];
                        ysum_r += image[i + dx][j + dy].rgbtRed * GY[1 + dx][1 + dy];

                        xsum_g += image[i + dx][j + dy].rgbtGreen * GX[1 + dx][1 + dy];
                        ysum_g += image[i + dx][j + dy].rgbtGreen * GY[1 + dx][1 + dy];

                        xsum_b += image[i + dx][j + dy].rgbtBlue * GX[1 + dx][1 + dy];
                        ysum_b += image[i + dx][j + dy].rgbtBlue * GY[1 + dx][1 + dy];
                    }
                }
                //counted the sums for one pixel, now to process them
                float r_sum = sqrt(pow(xsum_r, 2) + pow(ysum_r, 2));
                float g_sum = sqrt(pow(xsum_g, 2) + pow(ysum_g, 2));
                float b_sum = sqrt(pow(xsum_b, 2) + pow(ysum_b, 2));

                if (r_sum > 255)
                {
                    r_sum = 255;
                }
                if (g_sum > 255)
                {
                    g_sum = 255;
                }
                if (b_sum > 255)
                {
                    b_sum = 255;
                }

                image_e[i][j].rgbtRed = round(r_sum);
                image_e[i][j].rgbtGreen = round(g_sum);
                image_e[i][j].rgbtBlue = round(b_sum);
            }

        }
    }

    //now we swap image and image_e
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtGreen = image_e[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_e[i][j].rgbtRed;
            image[i][j].rgbtBlue = image_e[i][j].rgbtBlue;
        }
    }

    free(*image_e);
    return;
}
