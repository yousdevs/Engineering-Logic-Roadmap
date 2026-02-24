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

int main() {
	
	int matrix[3][3] = {};
	int rows = 3, cols = 3;

	fillMatrixWithOrderedNumbers(matrix, rows, cols);
	printMatrix(matrix, rows, cols);

	return 0;
}