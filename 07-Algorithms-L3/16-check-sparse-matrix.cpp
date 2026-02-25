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

int countNumberInMatrix(int matrix[3][3], int rows, int cols, int numberToCount) {
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] == numberToCount)  count++;
		}
	}
	return count;
}

bool isMatrixSparse(int matrix[3][3], int rows, int cols) {
	int zerosCount = countNumberInMatrix(matrix, rows, cols, 0);
	return (zerosCount >= ((rows * cols / 2)));
}

int main() {

	int matrix[3][3] = {
		{1, 0, 2},
		{2, 3, 4},
		{4, 5, 4}
	};
	int rows = 3, cols = 3;

	printMatrix(matrix, rows, cols);

	bool isSparse = isMatrixSparse(matrix, rows, cols);

	(isSparse) ? std::cout << "\nYes, The matrix is a sparse" : std::cout << "\nNo, The matrix is not a sparse";
	return 0;
}