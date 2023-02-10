#include <stdio.h>
#include <math.h>
#include "bmp.h"

void assign(RGBTRIPLE *pos, int r, int g, int b)
{
    pos->rgbtRed = r;
    pos->rgbtGreen = g;
    pos->rgbtBlue = b;
}


int main(void)
{
    int dim = 3;
    RGBTRIPLE image[dim][dim], image_b[dim][dim];

    assign(&image[0][0], 10, 20, 30);
    assign(&image[0][1], 40, 50, 60);
    assign(&image[0][2], 70, 80, 90);

    assign(&image[1][0], 110, 130, 140);
    assign(&image[1][1], 120, 140, 150);
    assign(&image[1][2], 130, 150, 160);

    assign(&image[2][0], 200, 210, 220);
    assign(&image[2][1], 220, 230, 240);
    assign(&image[2][2], 240, 250, 255);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("(%4i / %4i / %4i) ", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
        }
        printf("\n");
    }
    //printf("r = %i, g = %i, b = %i", image[1][1].rgbtRed, image[1][1].rgbtGreen, image[1][1].rgbtBlue);

    //Now to the blur algorithm
    for (int i = 0; i < dim; i ++)
    {
        for (int j = 0; j < dim; j ++)
        {
            float count = 0;
            long sum_r = 0, sum_g = 0, sum_b = 0;
            //for each el-t of an image let's count average
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    //exclude corner cases
                    if (i + dx >= 0 && i + dx < dim && j + dy >=0 && j + dy < dim)
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
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            image[i][j].rgbtGreen = image_b[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_b[i][j].rgbtRed;
            image[i][j].rgbtBlue = image_b[i][j].rgbtBlue;
        }
    }

    //print initial image
    printf("\nBlurred:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("(%4i / %4i / %4i) ", image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
        }
        printf("\n");
    }

    //We succeeded! :)
}