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
}


short searchArray(int array[100], int size, int number) {

	for (int i = 0; i < size; i++) {
		if (array[i] == number) {
			return i;
		}
	}
	
	return -1;
}

bool checkNumberinArray(int array[100], int size, int number) {
	return (!(searchArray(array, size, number) == -1));
}

void printSearchResult(bool result, int number) {

	if (result) {
		std::cout << "Number you are looking for is: "
			<< number
			<< "\n"
			<< "Yes, the number is found ";
	}
	else {
		std::cout << "Number you are looking for is: "
			<< number
			<< "\n"
			<< "The number is not found ):";
	}
}

int main() {
	srand((unsigned)std::time(NULL));
	int array[100] = {};
	int size = readPositiveNumber("Enter Number of elements: ");
	fillArrayWithRandomNumbers(array, size);
	printArrayValues(array, size);

	int number = readPositiveNumber("\nPlease Enter a number to search for: \n");
	bool result = checkNumberinArray(array, size, number);
	printSearchResult(result, number);
	return 0;
}