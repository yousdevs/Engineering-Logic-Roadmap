#include <iostream>

int readPositiveNumber(std::string message) {
	int number = 0;
	do
	{
		std::cout << message << std::endl;
		std::cin >> number;
	} while (number <= 0);
	return number;
}

int randomNumber(int from, int to)
{
	int randNum = rand() % (to - from + 1) + from;
	return randNum;
}

void fillArrayWithRandomNumbers(int array[100], int size) {
	for (int i = 0; i < size; i++) {
		array[i] = randomNumber(1, 100);
	}
}

void printArrayValues(int array[100], int size) {
	std::cout << "Array Elements: ";
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}


void copyArray(int sourceArray[100], int targetArray[100], int sourceSize) {
	for (int i = 0; i < sourceSize; i++) {
		targetArray[i] = sourceArray[i];
	}
}

void appendElement(int arr[100], int& length, int number) {
	arr[length] = number;
	length++;
}

void copyOddsArrayWithAppend(int array[100], int targetArray[100], int size, int& targetSize) {

	for (int i = 0; i < size; i++) {
		if (array[i] % 2 != 0) {
			appendElement(targetArray, targetSize, array[i]);
		}
	}
}

int main() {
	srand((unsigned)std::time(NULL));
	int array[100] = {};
	int size = readPositiveNumber("Enter Number of elements: ");
	fillArrayWithRandomNumbers(array, size);
	printArrayValues(array, size);

	int targetArray[100] = {};
	int targetSize = 0;
	copyOddsArrayWithAppend(array, targetArray, size, targetSize);
	printArrayValues(targetArray, targetSize);
	return 0;
}