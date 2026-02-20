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
		array[i] = randomNumber(-100, 100);
	}
}

void printArrayValues(int array[100], int size) {
	std::cout << "Array Elements: ";
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

int countNegatives(int arr[100], int size) {
	int negs = 0;
	for (int i = 0; i < size; i++) {
		if ((arr[i] < 0)) {
			negs++;
		}
	}
	return negs;
}

void printNegativesCountOf(int arr[100], int size) {
	int negs = countNegatives(arr, size);
	std::cout << "\nNegatives count is " << negs;
}

int main() {
	srand((unsigned)std::time(NULL));
	int array[100] = {};
	int size = readPositiveNumber("Enter Number of elements: ");
	fillArrayWithRandomNumbers(array, size);
	printArrayValues(array, size);
	printNegativesCountOf(array, size);
	return 0;
}