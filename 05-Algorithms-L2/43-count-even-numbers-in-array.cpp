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

int countEvens(int arr[100], int size) {
	int evens = 0;
	for (int i = 0; i < size; i++) {
		if ((arr[i] % 2 == 0)) {
			evens++;
		}
	}
	return evens;
}

void printEvensCountOf(int arr[100], int size) {
	int evens = countEvens(arr, size);
	std::cout << "\nEvens count is " << evens;
}

int main() {
	srand((unsigned)std::time(NULL));
	int array[100] = {};
	int size = readPositiveNumber("Enter Number of elements: ");
	fillArrayWithRandomNumbers(array, size);
	printArrayValues(array, size);
	printEvensCountOf(array, size);
	return 0;
}