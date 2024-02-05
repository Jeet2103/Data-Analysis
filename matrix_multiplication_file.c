#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomMatrix(FILE *file, int rows, int cols) {
    srand(time(NULL));  // Seed for random number generation

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fprintf(file, "%d ", rand() % 10);  // Generates random numbers between 0 and 99
        }
        fprintf(file, "\n");
    }
}

void readMatrix(FILE *file, int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
}

void multiplyMatrices(int **matrix1, int **matrix2, int **result, int rows1, int cols1, int rows2, int cols2) {
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

void writeMatrix(FILE *file, int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
}

int main() {
    FILE *inputFile1, *inputFile2, *outputFile;

    // Open input and output files
    inputFile1 = fopen("matrix1.txt", "w");
    inputFile2 = fopen("matrix2.txt", "w");
    outputFile = fopen("result.txt", "w");

    if (inputFile1 == NULL || inputFile2 == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    int rows1, cols1, rows2, cols2;

    // Get matrix dimensions from the user
    printf("Enter dimensions for matrix 1 (rows cols): ");
    scanf("%d %d", &rows1, &cols1);
    printf("Enter dimensions for matrix 2 (rows cols): ");
    scanf("%d %d", &rows2, &cols2);

    // Check if matrices can be multiplied
    if (cols1 != rows2) {
        printf("Matrices cannot be multiplied.\n");
        return 1;
    }

    // Allocate memory for matrices
    int **matrix1 = (int **)malloc(rows1 * sizeof(int *));
    int **matrix2 = (int **)malloc(rows2 * sizeof(int *));
    int **result = (int **)malloc(rows1 * sizeof(int *));
    
    for (int i = 0; i < rows1; ++i) {
        matrix1[i] = (int *)malloc(cols1 * sizeof(int));
        result[i] = (int *)malloc(cols2 * sizeof(int));
    }

    for (int i = 0; i < rows2; ++i) {
        matrix2[i] = (int *)malloc(cols2 * sizeof(int));
    }

    // Generate random matrices and write to files
    generateRandomMatrix(inputFile1, rows1, cols1);
    generateRandomMatrix(inputFile2, rows2, cols2);

    // Close files
    fclose(inputFile1);
    fclose(inputFile2);

    // Reopen files for reading
    inputFile1 = fopen("matrix1.txt", "r");
    inputFile2 = fopen("matrix2.txt", "r");

    // Read matrices from files
    readMatrix(inputFile1, matrix1, rows1, cols1);
    readMatrix(inputFile2, matrix2, rows2, cols2);

    // Perform matrix multiplication
    multiplyMatrices(matrix1, matrix2, result, rows1, cols1, rows2, cols2);

    // Write result to the output file
    writeMatrix(outputFile, result, rows1, cols2);

    // Close files
    fclose(outputFile);

    // Free allocated memory
    for (int i = 0; i < rows1; ++i) {
        free(matrix1[i]);
        free(result[i]);
    }
    free(matrix1);
    free(result);

    for (int i = 0; i < rows2; ++i) {
        free(matrix2[i]);
    }
    free(matrix2);

    return 0;
}
