#include <stdio.h>

int GX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int GY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

// Detect edges
int main(void)
{
    /*GX[0] = {-1, 0, 1};
    GX[1] = {-2, 0, 2};
    GX[2] = {-1, 0, 1};*/

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%4i", GX[i][j]);
        }
        printf("\n");
    }
    return 0;
}