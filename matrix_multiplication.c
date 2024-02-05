#include <stdio.h>
#include <stdlib.h>

void multiplyMatrices(int **firstMatrix, int **secondMatrix, int **result, int rowFirst, int columnFirst, int rowSecond, int columnSecond)
{
    for (int i = 0; i < rowFirst; ++i)
    {
        for (int j = 0; j < columnSecond; ++j)
        {
            result[i][j] = 0;
        }
    }

    for (int i = 0; i < rowFirst; ++i)
    {
        for (int j = 0; j < columnSecond; ++j)
        {
            for (int k = 0; k < columnFirst; ++k)
            {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

void displayMatrix(int **matrix, int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int rowFirst, columnFirst, rowSecond, columnSecond;

    printf("Enter dimensions of the first matrix (rows columns): ");
    scanf("%d %d", &rowFirst, &columnFirst);

    printf("Enter dimensions of the second matrix (rows columns): ");
    scanf("%d %d", &rowSecond, &columnSecond);

    if (columnFirst != rowSecond)
    {
        printf("Error: The number of columns in the first matrix must be equal to the number of rows in the second matrix.\n");
        return 1;
    }

    // Dynamically allocate memory for matrices
    int **firstMatrix = (int **)malloc(rowFirst * sizeof(int *));
    int **secondMatrix = (int **)malloc(rowSecond * sizeof(int *));
    int **resultMatrix = (int **)malloc(rowFirst * sizeof(int *));

    for (int i = 0; i < rowFirst; ++i)
    {
        firstMatrix[i] = (int *)malloc(columnFirst * sizeof(int));
    }

    for (int i = 0; i < rowSecond; ++i)
    {
        secondMatrix[i] = (int *)malloc(columnSecond * sizeof(int));
    }

    for (int i = 0; i < rowFirst; ++i)
    {
        resultMatrix[i] = (int *)malloc(columnSecond * sizeof(int));
    }

    // Input elements of the matrices
    printf("Enter elements of the first matrix:\n");
    for (int i = 0; i < rowFirst; ++i)
    {
        for (int j = 0; j < columnFirst; ++j)
        {
            scanf("%d", &firstMatrix[i][j]);
        }
    }
    displayMatrix(firstMatrix, rowFirst, columnFirst);
    printf("Enter elements of the second matrix:\n");
    for (int i = 0; i < rowSecond; ++i)
    {
        for (int j = 0; j < columnSecond; ++j)
        {
            scanf("%d", &secondMatrix[i][j]);
        }
    }
    displayMatrix(secondMatrix, rowSecond, columnSecond);
    // Perform matrix multiplication
    multiplyMatrices(firstMatrix, secondMatrix, resultMatrix, rowFirst, columnFirst, rowSecond, columnSecond);

    // Display the result matrix
    printf("Resultant Matrix:\n");
    displayMatrix(resultMatrix, rowFirst, columnSecond);

    // Free allocated memory

    return 0;
}
