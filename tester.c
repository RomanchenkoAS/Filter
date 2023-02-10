#include <stdio.h>
#include <math.h>

int main(void)
{
    /* TESTING FOR GRAYSCALE
    int a = 27, b = 28, c = 28;
    float sum = a + b + c;
    float average = lrint(sum / 3);

    printf("Avg: %.2f\n", average); */

     TESTING FOR BLUR
    int dim = 5, inc = 1;
    int arr[dim][dim], arr_new[dim][dim];

    // initialize and print an array
    printf("Input array: \n");
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            arr[i][j] = inc;
            inc++;
            printf("%4i", arr[i][j]);
        }
        printf("\n");
    }


    // "blur"
    for (int row = 0; row < dim; row++)
    {
        for (int column = 0; column < dim; column++)
        {
            int sum = 0, count = 0;
            //for each el-t of an array let's count average
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (row+dx >= 0 && row+dx < dim && column+dy >=0 && column+dy < dim)
                    {
                        sum += arr[row+dx][column+dy];
                        count++;
                    }
                }
            }
            arr_new[row][column] = lrint(sum / count);
        }
        if (row != dim - 1)
        {
            printf("\n");
        }
    }

    // print modified array
    printf("Output array:\n");
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            printf("%4i", arr_new[i][j]);
        }
        printf("\n");
    }

}