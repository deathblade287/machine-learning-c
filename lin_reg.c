#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MIN = 0;
int MAX = 200;

typedef struct matrix {
  int numRows;
  int (*data)[2];
} matrix;

void printMatrix(matrix *mat) {
  for (int i = 0; i < mat->numRows; i++) {
    for (int j = 0; j < 2; j++) {
      printf("%i, ", mat->data[j][i]);
    }
    printf("\n");
  }
}

matrix *randMatrixGen(int rows) {
  matrix *mat = malloc(sizeof(matrix));
  mat->numRows = rows;
  mat->data = malloc(rows * sizeof(*mat->data));

  srand(time(NULL));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 2; j++) {
      mat->data[j][i] = rand() % (MAX - MIN + 1) + MIN;
    }
  }

  return mat;
}

int arrMean(int *arr, int numRows) {
  int sum = 0;
  for (int i = 0; i < numRows; i++) {
    sum += arr[i];
  }
  return sum / numRows;
}

int **transpose(matrix *mat) {
  int **array2D = malloc(mat->numRows * sizeof(int *));
  for (int i = 0; i < mat->numRows; i++) {
    array2D[i] = malloc(2 * sizeof(int));
    array2D[i][0] = mat->data[0][i];
    array2D[i][1] = mat->data[1][i];
  }
  return array2D;
};

int main(void) {

  matrix *mat = randMatrixGen(10);
  printMatrix(mat);

  printf("\nX Mean: %i", arrMean(mat->data[0], mat->numRows));
  printf("\nY Mean: %i", arrMean(mat->data[1], mat->numRows));
  printf("\n");

  int **T = transpose(mat);
  printf("Element 1, 9 = %i", T[9][1]);

  printf("\n");
  return 0;
}
