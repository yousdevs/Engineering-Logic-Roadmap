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

void printMatrix(int matrix[3][3], int rows, int cols) {
	printf("The following is a 3*3 random matrix: \n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			std::cout << std::setw(3) << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

int calcSumOfMatrix(int matrix[3][3], int rows, int cols) {
	int sum = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			sum += matrix[i][j];
		}
	}
	return sum;
}

void printSumOfMatrix(int matrix[3][3], int rows, int cols) {
	int sum = calcSumOfMatrix(matrix, rows, cols);
	std::cout << "\nSum of the matrix: " << std::to_string(sum) << std::endl;
}

void printMatricesSumEqual(int matrix1[3][3], int rows, int cols, int matrix2[3][3]) {
	int sum1 = calcSumOfMatrix(matrix1, rows, cols);
	int sum2 = calcSumOfMatrix(matrix2, rows, cols);
	std::string equal = (sum1 == sum2) ? "Equal" : "Not Equal";
	std::cout << "\nMatices Are " + equal;
}

int main() {
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));
	int matrix[3][3] = {};
	int rows = 3, cols = 3;

	fillMatrixWithRandomNumbers(matrix, rows, cols);
	printMatrix(matrix, rows, cols);

	printSumOfMatrix(matrix, rows, cols);

	int matrix2[3][3] = {};
	int rows2 = 3, cols2 = 3;

	fillMatrixWithRandomNumbers(matrix2, rows2, cols2);
	printMatrix(matrix2, rows2, cols2);

	printSumOfMatrix(matrix2, rows2, cols2);

	printMatricesSumEqual(matrix, rows, cols, matrix2);

	return 0;
}