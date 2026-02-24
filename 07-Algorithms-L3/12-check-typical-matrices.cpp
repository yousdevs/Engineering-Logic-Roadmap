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

void printCheckTypicalMatrices(int matrix1[3][3], int matrix2[3][3], int rows, int cols) {
	bool isTypical = true;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix1[i][j] != matrix2[i][j]) {
				isTypical = false;
				break;
				
			}
		}
	}
	if (isTypical) {
		std::cout << "\nYes, Matrices Are Typical";
	}
	else {
		std::cout << "\nNo, Matrices Are Not Typical";
	}
}

int main() {
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));
	int matrix[3][3] = {};
	int rows = 3, cols = 3;

	fillMatrixWithRandomNumbers(matrix, rows, cols);
	printMatrix(matrix, rows, cols);



	int matrix2[3][3] = {};
	int rows2 = 3, cols2 = 3;

	fillMatrixWithRandomNumbers(matrix2, rows2, cols2);
	printMatrix(matrix2, rows2, cols2);

	printCheckTypicalMatrices(matrix, matrix2, rows, cols);
	

	return 0;
}