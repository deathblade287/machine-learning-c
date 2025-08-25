#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MIN = 0;
int MAX = 50;

typedef struct array {
  int size;
  int data[];
} array;

typedef struct matrix {
  int rows;
  int columns;
  array *data[];
} matrix;

void printMatrix(matrix *mat) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->columns; j++) {
      printf("%i, ", mat->data[i]->data[j]);
    }
    printf("\n");
  }
}

matrix *randMatrixGen(int rows, int columns) {
  matrix *mat = malloc(sizeof(matrix) + rows * sizeof(array *));
  mat->rows = rows;
  mat->columns = columns;

  srand(time(NULL));

  for (int i = 0; i < rows; i++) {
    mat->data[i] = malloc(sizeof(array) + columns * sizeof(int));
    mat->data[i]->size = columns;
    for (int j = 0; j < columns; j++) {
      mat->data[i]->data[j] = rand() % (MAX - MIN + 1) + MIN;
    }
  }

  return mat;
}

int arrMean(array *arr) {
  int sum = 0;
  for (int i = 0; i < arr->size; i++) {
    sum += arr->data[i];
  }
  return sum / arr->size;
}

matrix *transpose(matrix *mat) {
  matrix *finalMat = malloc(sizeof(matrix) + mat->columns * sizeof(array *));
  finalMat->rows = mat->columns;
  finalMat->columns = mat->rows;

  for (int i = 0; i < finalMat->rows; i++) {
    finalMat->data[i] = malloc(sizeof(array) + finalMat->columns * sizeof(int));
    finalMat->data[i]->size = finalMat->columns;
    for (int j = 0; j < finalMat->columns; j++) {
      finalMat->data[i]->data[j] = mat->data[j]->data[i];
    }
  }
  return finalMat;
}

matrix *matMul(matrix *mat1, matrix *mat2) {
  matrix *finalMat = malloc(sizeof(matrix) + mat1->rows * sizeof(array *));
  finalMat->rows = mat1->rows;
  finalMat->columns = mat2->columns;

  for (int i = 0; i < finalMat->rows; i++) {
    finalMat->data[i] = malloc(sizeof(array) + finalMat->columns * sizeof(int));
    finalMat->data[i]->size = finalMat->columns;
    for (int j = 0; j < finalMat->columns; j++) {
      int sum = 0;
      for (int k = 0; k < mat1->columns; k++) {
        sum += mat1->data[i]->data[k] * mat2->data[k]->data[j];
      }
      finalMat->data[i]->data[j] = sum;
    }
  }

  return finalMat;
}

int main(void) {
  matrix *mat = randMatrixGen(10, 2);
  printMatrix(mat);

  printf("\nX Mean: %i\n", arrMean(mat->data[0]));
  printf("\nY Mean: %i\n", arrMean(mat->data[1]));

  matrix *T = transpose(mat);
  printf("\nTransposed:\n");
  printMatrix(T);

  matrix *product = matMul(mat, T);
  printf("\nProduct:\n");
  printMatrix(product);

  return 0;
}
