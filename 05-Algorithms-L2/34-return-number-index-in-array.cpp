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

enum enStatus { Found = 1, NotFound = 0 };
struct SearchResult {
	int index;
	int order; // vicual order
	int number;
	enStatus found;
};

SearchResult searchArray(int array[100], int size, int number) {
	SearchResult result;
	for (int i = 0; i < size; i++) {
		if (array[i] == number) {
			result.found = enStatus::Found;
			result.order = i + 1;
			result.number = number;
			result.index = i;
			return result;
		}
	}
	result.found = enStatus::NotFound;
	result.number = number;
	return result;
}

void printSearchResult(SearchResult result) {

	if (result.found == enStatus::Found) {
		std::cout << "Number you are looking for is: "
			<< result.number
			<< "\n"
			<< "The number found at position: "
			<< result.index
			<< "\n"
			<< "The order of the number is: "
			<< result.order;
	}
	else {
		std::cout << "Number you are looking for is: "
			<< result.number
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
	SearchResult result = searchArray(array, size, number);
	printSearchResult(result);
	return 0;
}