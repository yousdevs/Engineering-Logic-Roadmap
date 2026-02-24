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

int sumArr(int arr[3], int length) {
	int sum = 0;
	for (int i = 0; i < length; i++) {
		sum += arr[i];
	}
	return sum;
}

int sumCols(int matrix[3][3], int col, int rows) {
	int colsSum = 0;
	for (int i = 0; i < rows; i++) {
		colsSum += matrix[i][col];
	}
	return colsSum;
}

void printMatrixColsSum(int matrix[3][3], int rows, int cols) {
	std::cout << "\nThe following are the sums of each column in the matrix: " << std::endl;

	for (int i = 0; i < cols; i++){
		std::cout << "Col " + std::to_string(i + 1) + " Sum is: " + std::to_string(sumCols(matrix, i, rows)) << std::endl;
	}
}

int main() {
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));
	int matrix[3][3] = {};
	int rows = 3, cols = 3;

	fillMatrixWithRandomNumbers(matrix, rows, cols);
	printMatrix(matrix, rows, cols);

	printMatrixColsSum(matrix, rows, cols);


	return 0;
}