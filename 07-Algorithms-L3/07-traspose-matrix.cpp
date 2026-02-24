#include <iostream>
#include <string>
#include <iomanip>


void fillMatrixWithOrderedNumbers(int matrix[3][3], int rows, int cols) {
	int n = 0;
	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols; j++) {
			n++;
			matrix[i][j] = n;
		}
	}
}

void printMatrix(int matrix[3][3], int rows, int cols) {
	printf("The following is a 3*3 ordered matrix: \n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			std::cout << std::setw(3) << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void trasposeMatrix(int matrix[3][3], int rows, int cols, int trasposed[3][3]) {

	for (int i = 0; i < rows; i++) {
		
		for (int j = 0; j < cols; j++) {
			trasposed[j][i] = matrix[i][j];
		}
	}
}

int main() {

	int matrix[3][3] = {};
	int rows = 3, cols = 3;

	fillMatrixWithOrderedNumbers(matrix, rows, cols);
	printMatrix(matrix, rows, cols);

	int trasposed[3][3] = {};
	int tRows = 3, tCols = 3;
	trasposeMatrix(matrix, rows, cols, trasposed);
	printMatrix(trasposed, tRows, tCols);
	return 0;
}