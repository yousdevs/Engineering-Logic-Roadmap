#include <iostream>
#include <iomanip>


void printMatrix(int matrix[3][3], int rows, int cols) {
	printf("The following is a 3*3 random matrix: \n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			std::cout << std::setw(3) << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

int getMaxNumberFrom(int matrix[3][3], int rows, int cols) {
	int max = matrix[0][0];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int currentNumber = matrix[i][j];
			if (currentNumber > max) {
				max = currentNumber;
			}
		}
	}
	return max;
}


int getMinNumberFrom(int matrix[3][3], int rows, int cols) {
	int min = matrix[0][0];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int currentNumber = matrix[i][j];
			if (currentNumber < min) {
				min = currentNumber;
			}
		}
	}
	return min;
}



int main() {

	int matrix[3][3] = {
		{1, 0, 2},
		{2, 3, 4},
		{4, 5, 4}
	};
	int rows = 3, cols = 3;

	printMatrix(matrix, rows, cols);

	int min = getMinNumberFrom(matrix, rows, cols);
	int max = getMaxNumberFrom(matrix, rows, cols);

	printf("\nMin Number is %d", min);
	printf("\nMax Number is %d", max);


	return 0;
}