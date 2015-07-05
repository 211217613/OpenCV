#include <iostream>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time() */

using namespace std;

int matrixInverse(double matrix[][3]);
double matrixDeterm(double matrix[][3]);
int matrixPrint(double matrix[][3]);
int matrixMult(double matrix1[][3], double matrix2[][3]);
int matrixSolve(double matrix[][3]);

struct Values{
    double Matrix1[3][3];

};



int main()
{
    int option;
    double* ptr_matrix1, *ptr_matrix2;
    double Matrix1[3][3];
    double Matrix2[3][3];
    double Matrix_Mult[3][3] = { { 0, 0, 0}, { 0, 0, 0 }, { 0, 0, 0 } };
    ptr_matrix2 = *Matrix2;
    ptr_matrix1 = *Matrix1;
    srand(time(NULL)); // seed for rand()
    printf("The mem location of matrix1 is: %p \n", &ptr_matrix1);
    printf("The mem location of matrix2 is: %p \n", &ptr_matrix2);
    // Instantiate a struct called M that has two 2d arrays of type double
    //This double for loop auto populates the matrices using
    for(int row = 0; row <= 2; ++row){
        for(int column = 0; column <= 2; column++){
            Matrix1[row][column] = rand() % 10 + 1;  // all nonzero entries for LU decomp
            Matrix2[row][column] = rand() % 10 + 1;  // all nonzero entries for LU decomp
        }
    }
    printf("1 - matrix print\n");
    printf("2 - matrix inverse\n");
    printf("3 - matrix determinant\n");
    printf("4 - matrix multiply\n");
    printf("5 - Solve system of Linear Equations\n");

    cin >> option;

    while(option != 6){
        switch(option){
            case 1: matrixPrint(Matrix1);
                    cout << endl;
                    matrixPrint(Matrix2);
                cin >> option;
                break;
            case 2: matrixInverse(Matrix1);
                    matrixInverse(Matrix2);
                cin >> option;
                break;
            case 3: matrixDeterm(Matrix1);
                    matrixDeterm(Matrix2);
                cin >> option;
                break;
            case 4: matrixMult(Matrix1, Matrix2);
                cin >> option;
                break;
            case 5: matrixSolve(Matrix1);
                cin >> option;
                break;
            case 6: return 0;
                break;
            default: cout << "sdag";
                break;
        }
    }
    return 0;
}
/**
This function call will calculate the determinate of the matrix specified and display both
the original matrix and the determinate
**/
double matrixDeterm(double matrix[][3]){
   //printf("This function will calculate the determinant of both matrices \n");
   double det = matrix[0][0]*(matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
   -             matrix[0][1]*(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
   +             matrix[0][2]*(matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
    matrixPrint(matrix);
    cout << det << endl;
   return det;
}

int matrixInverse(double matrix[][3]){
    int           i, j;

    double        tranpose[3][3]; //The transpose matrix of A
    double        adjoint[3][3]; //The adjoint matrix of A adj(A)
    double        X[3][3]; //The inverse of A (adj(A)/det)
    double        det; //The determinant of A

    det = matrixDeterm(matrix);

    /* Find the transpose matrix (B)/> of A */
    for(i=0 ; i <= 3 ; i++) {
        for(j=0 ; j <= 3 ; j++) {
            tranpose[i][j] = matrix[j][i];
        }
    }


    // Calculate the adjoint matrix (C) of A

    adjoint[0][0] =   tranpose[1][1]*tranpose[2][2] - tranpose[2][1]*tranpose[1][2];
    adjoint[0][1] = -(tranpose[1][0]*tranpose[2][2] - tranpose[2][0]*tranpose[1][2]);
    adjoint[0][2] =   tranpose[1][0]*tranpose[2][1] - tranpose[2][0]*tranpose[1][1];
    adjoint[1][0] = -(tranpose[0][1]*tranpose[2][2] - tranpose[2][1]*tranpose[0][2]);
    adjoint[1][1] =   tranpose[0][0]*tranpose[2][2] - tranpose[2][0]*tranpose[0][2];
    adjoint[1][2] = -(tranpose[0][0]*tranpose[2][1] - tranpose[2][0]*tranpose[0][1]);
    adjoint[2][0] =   tranpose[0][1]*tranpose[1][2] - tranpose[1][1]*tranpose[0][2];
    adjoint[2][1] = -(tranpose[0][0]*tranpose[1][2] - tranpose[1][0]*tranpose[1][2]);
    adjoint[2][2] =   tranpose[0][0]*tranpose[1][1] - tranpose[1][0]*tranpose[0][1];


    /* Calculate the inverse matrix of A (adj(A)/det) */
    for(i=0 ; i <= 2 ; i++) {
        for(j=0 ; j <= 2 ; j++) {
            X[i][j] = adjoint[i][j]/det;
       }
    }

    /* Print the inverse matrix (X) to screen */

    for(i=0 ; i<3 ; i++) {
        printf( "%f %f %f\n", X[i][0], X[i][1], X[i][2] );
  }
    return 0;
}

int matrixPrint(double matrix[][3]){
  for ( int y = 0;  y < 3;  y ++ )
  {
    cout << "[  ";
    for ( int x = 0;  x < 3;  x ++   )
      cout << matrix [y] [x] << "  ";
    cout << "]" << endl;
  }
  cout << endl;

  return 0;
}

int matrixMult(double matrix1[][3], double matrix2[][3]){
    double matrix_Mult[3][3];
    for(int i = 0; i <= 2; i++){
        for(int j = 0; j <= 2; j++){
            for(int k = 0; k <= 2; k++)
            matrix_Mult[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    }

   matrixPrint(matrix1); cout << endl;
   matrixPrint(matrix2); cout << endl;
   matrixPrint(matrix_Mult);
   return 0;
}

// This function will solve a system of linear equations using kramers rule and
// the matrixDeterm() function
int matrixSolve(double matrix[][3]){
// solve the following system of linear equations using Cramer's Rule
// create your own extended matrix to solve
    double coeff_matrix[3][3] {{1.2, 5, -2},{1, -2, 4}, {1, 4.5, -.6}};
    double x_matrix[3][3] {{2, 5, -2},{2, -2, 4}, {10, 4.5, -.6}};
    double y_matrix[3][3] {{1.2, 2, -2},{1, 2, 4}, {1, 10, -.6}};
    double z_matrix[3][3] {{1.2, 5, 2},{1, -2, 2}, {1,4.5,10}};

    Values matrixValues;
    matrixValues.Matrix1[3][3] = coeff_matrix[3][3];

    cout <<"The coeffecient matrix: \n";
    matrixPrint(coeff_matrix);

    cout <<"The x matrix: \n";
    matrixPrint(x_matrix);

    cout <<"The y matrix: \n";
    matrixPrint(y_matrix);

    cout <<"The z matrix: \n";
    matrixPrint(z_matrix);

    double det = matrixDeterm(coeff_matrix);

    // X
    double x_det = matrixDeterm(x_matrix);
    cout <<"X = " << x_det / det << endl;

    // Y
    double y_det = matrixDeterm(y_matrix);
    cout <<"Y = " << y_det / det << endl;

    // Z
    int z_det = matrixDeterm(z_matrix);
    cout <<"Z = " << z_det / det << endl;

    return 0;
}
