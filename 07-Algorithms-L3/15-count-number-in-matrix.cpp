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

int countNumberInMatrix(int matrix[3][3], int rows, int cols, int numberToCount) {
	int count = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if(matrix[i][j] == numberToCount)  count++;
		}
	}
	return count;
}

int main() {

	int matrix[3][3] = {
		{1, 0, 2},
		{2, 3, 4},
		{4, 5, 4}
	};
	int rows = 3, cols = 3;

	printMatrix(matrix, rows, cols);

	int numberToCount = readNumber();

	int count = countNumberInMatrix(matrix, rows, cols, numberToCount);

	printf("\nThe number %d appeared in the matrix %d times.", numberToCount, count);

	return 0;
}