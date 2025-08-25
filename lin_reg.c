#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int MIN = 0;
int MAX = 200;

typedef struct array {
  int columns;
  int data[];
} array;

typedef struct matrix {
  int rows;
  array *data[];
} matrix;

void printMatrix(matrix *mat) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < 2; j++) {
      printf("%i, ", mat->data[j]->data[i]);
    }
    printf("\n");
  }
}

matrix *randMatrixGen(int rows) {
  matrix *mat =
      malloc(sizeof(matrix) +
             2 * sizeof(array *)); // allocate space for 2 column pointers
  mat->rows = rows;

  // allocate the two column arrays (each with 'rows' ints)
  mat->data[0] = malloc(sizeof(array) + rows * sizeof(int));
  mat->data[0]->columns = rows;
  mat->data[1] = malloc(sizeof(array) + rows * sizeof(int));
  mat->data[1]->columns = rows;

  srand(time(NULL));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < 2; j++) {
      mat->data[j]->data[i] = rand() % (MAX - MIN + 1) + MIN;
    }
  }

  return mat;
}

int arrMean(array *arr) {
  int sum = 0;
  for (int i = 0; i < arr->columns; i++) {
    sum += arr->data[i];
  }
  return sum / arr->columns;
}

matrix *transpose(matrix *mat) {
  matrix *finalMat =
      malloc(sizeof(matrix) +
             mat->rows * sizeof(array *)); // allocate header + pointers
  finalMat->rows = mat->data[0]->columns;  // == mat->rows

  for (int i = 0; i < finalMat->rows; i++) {
    finalMat->data[i] =
        malloc(sizeof(array) +
               2 * sizeof(int)); // each transposed column has 2 elements
    finalMat->data[i]->columns = 2;
    finalMat->data[i]->data[0] = mat->data[0]->data[i];
    finalMat->data[i]->data[1] = mat->data[1]->data[i];
  }
  return finalMat;
}

int main(void) {

  matrix *mat = randMatrixGen(10);
  printMatrix(mat);

  printf("\nX Mean: %i", arrMean(mat->data[0]));
  printf("\nY Mean: %i", arrMean(mat->data[1]));
  printf("\n");

  matrix *T = transpose(mat);
  printf("Element 1, 9 = %i", T->data[9]->data[1]);

  printf("\n");
  return 0;
}
