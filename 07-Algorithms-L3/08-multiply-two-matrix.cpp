#include <iostream>
#include <string>
#include <iomanip>

int generateRandomIntegerInRange(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void fillMatrixWithRandomNumbers(int matrix[3][3], int rows, int cols) {

	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols; j++) {
			matrix[i][j] = generateRandomIntegerInRange(1, 100);
		}
	}
}

void printMatrix(int matrix[3][3], int rows, int cols, std::string message) {
	std::cout << message;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			std::cout << std::setw(3) << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

void multiply2MatrixInto(int resultsMatrix[3][3], int matrix1[3][3], int matrix2[3][3], int rows, int cols) {
	
	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols; j++) {
			resultsMatrix[i][j] = matrix1[i][j] * matrix2[i][j];
		}
	}
}

int main() {
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));
	int matrix[3][3] = {};
	int rows = 3, cols = 3;

	fillMatrixWithRandomNumbers(matrix, rows, cols);
	printMatrix(matrix, rows, cols, "\nMatrix1:\n");

	int matrix2[3][3] = {};
	int rows2 = 3, cols2 = 3;

	fillMatrixWithRandomNumbers(matrix2, rows2, cols2);
	printMatrix(matrix2, rows2, cols2, "\nMatrix2:\n");

	int resultsMatrix[3][3] = {};
	int resultsRows = 3, resultsCols = 3;

	multiply2MatrixInto(resultsMatrix, matrix, matrix2, rows, cols);
	printMatrix(resultsMatrix, resultsRows, resultsCols, "\nResults:\n");
	return 0;
}