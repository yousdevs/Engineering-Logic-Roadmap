#include <iostream>


void printArrayValues(int array[100], int size) {
	std::cout << "Array Elements: ";
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

bool isPalindromeArray(int arr[100], int size) {
	for (int i = 0; i < size; i++) {
		if (arr[i] != arr[size - i - 1]) {
			return false;
		}
	}
	return true;
}

void printIsPalindromeArray(int array[100] , int size) {
	
	bool isPalindrome = isPalindromeArray(array, size);

	if (isPalindrome) {
		std::cout << "\nYes, it is";
	}
	else {
		std::cout << "\nNo, it is not";
	}

}


int main() {
	srand((unsigned)std::time(NULL));
	int array[100] = { 1, 2, 3, 2, 1};
	int size = 5;
	printArrayValues(array, size);


	
	printIsPalindromeArray(array, size);

	return 0;
}