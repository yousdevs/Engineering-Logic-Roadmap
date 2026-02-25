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

int readNumber()
{
	int number;
	std::cout << "Please enter a number?" << std::endl;
	std::cin >> number;
	while (std::cin.fail())
	{
		// user didn't input a number
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid Number, Enter a valid one:" << std::endl;
		std::cin >> number;
	}
	return number;
}

bool isMatrixConatins(int numberToCheck, int matrix[3][3], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] == numberToCheck) return true;
		}
	}
	return false;
}

int main() {

	int matrix[3][3] = {
		{1, 0, 2},
		{2, 3, 4},
		{4, 5, 4}
	};
	int rows = 3, cols = 3;

	printMatrix(matrix, rows, cols);

	int numberToCheck = readNumber();

	bool isExist = isMatrixConatins(numberToCheck, matrix, rows, cols);
	(isExist) ? printf("\nThe number %d appeared in the matrix", numberToCheck) :
		printf("\nThe number %d not exist in the matrix");

	return 0;
}