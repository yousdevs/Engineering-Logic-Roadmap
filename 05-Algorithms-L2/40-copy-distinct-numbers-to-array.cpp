#include <iostream>


void printArrayValues(int array[100], int size) {
	std::cout << "Array Elements: ";
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

void appendElement(int arr[100], int& length, int number) {
	arr[length] = number;
	length++;
}

short searchArray(int array[100], int size, int number) {

	for (int i = 0; i < size; i++) {
		if (array[i] == number) {
			return i;
		}
	}

	return -1;
}

bool checkNumberInArray(int array[100], int size, int number) {
	return (!(searchArray(array, size, number) == -1));
}

void copyDistinctNumbersIntoArray(int array[100], int targetArray[100], int size, int& targetSize) {

	for (int i = 0; i < size; i++) {
		if (!checkNumberInArray(targetArray, targetSize, array[i])) {
			appendElement(targetArray, targetSize, array[i]);
		}
	}
}

int main() {
	srand((unsigned)std::time(NULL));
	int array[100] = {10, 10, 10, 50, 50, 70, 70, 70, 70, 90};
	int size = 10;
	printArrayValues(array, size);

	int targetArray[100] = {};
	int targetSize = 0;
	copyDistinctNumbersIntoArray(array, targetArray, size, targetSize);
	printArrayValues(targetArray, targetSize);
	return 0;
}