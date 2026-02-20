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


void printArrayValues(int array[100], int size) {
	std::cout << "Array Elements: ";
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
}

void fillArrayWithOrderedNumbers(int array[100], int size) {
	
	for (int i = 0; i < size; i++) {
		array[i] = ( i + 1 );
	}
}

void swap(int& a, int& b) {

	int temp = a;
	a = b;
	b = temp;
}

void shuffleArrayValues(int array[100], int size) {

	for (int i = 0; i < size; i++) {
		swap(array[randomNumber(1, size) - 1], array[randomNumber(1, size) - 1]);
	}
}

int main() {
	srand((unsigned)std::time(NULL));
	int array[100] = {};
	int size = readPositiveNumber("Enter Number of elements: ");
	fillArrayWithOrderedNumbers(array, size);
	printArrayValues(array, size);
	shuffleArrayValues(array, size);
	std::cout << std::endl;
	printArrayValues(array, size);
	return 0;
}