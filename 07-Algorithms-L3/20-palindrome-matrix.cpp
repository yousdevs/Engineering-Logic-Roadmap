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

bool isPalindromeArray(int arr[3], int length) {
	for (int i = 0; i < length /2; i++) {
		if (arr[i] != arr[length - 1 - i]) return false;
	}
	return true;
}

bool isPalindromeMatrix(int matrix[3][3], int rows, int cols) {

	for (int i = 0; i < rows; i++) {
		bool isPalindrome = isPalindromeArray(matrix[i], cols);
		if (!isPalindrome) return false;
	}
	return true;
}



int main() {

	int matrix[3][3] = {
		{1, 0, 1},
		{1, 0, 8},
		{1, 0, 1}
	};
	int rows = 3, cols = 3;

	printMatrix(matrix, rows, cols);

	bool isPalindrome = isPalindromeMatrix(matrix, rows, cols);
	(isPalindrome) ? printf("\nYes, palindrome matrix") :
		printf("\nNo, Not a palindrome matrix");


	return 0;
}