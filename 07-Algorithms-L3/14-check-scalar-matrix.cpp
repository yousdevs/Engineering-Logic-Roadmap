#include <iostream>


bool isScalarMatrix(int matrix[3][3], int rows, int cols) {
	int first = matrix[0][0];
	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < cols; j++) {

			if (i == j && matrix[i][j] != first) {
				return false;
			}
			else if (i != j && matrix[i][j] != 0) {
				return false;
			}

		}
	}
	return true;
}

int main() {
	int matrix[3][3] = {
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1}
	};
	int rows = 3, cols = 3;

	bool isIdentity = isScalarMatrix(matrix, rows, cols);


	if (isIdentity)
		std::cout << "\nYES: Matrix is Scalar.";
	else
		std::cout << "\nNo: Matrix is NOT Scalar.";

	return 0;
}