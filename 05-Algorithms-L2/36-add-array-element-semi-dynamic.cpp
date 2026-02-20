#include <iostream>


int readPositiveNumber(std::string message) {
	int number = 0;
	do
	{
		std::cout << message << std::endl;
		std::cin >> number;
	} while (number < 0);
	return number;
}

void printArrayValues(int array[100], int size) {
	std::cout << "Array Elements: ";
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

void appendNumber(int arr[100], int &length, int number) {
	arr[length] = number;
	length++;
}

int main() {
	int arr[100] = {};
	int length = 0;

	int more = 1;
	while (more == 1) {
		int numberToAppend = readPositiveNumber("\nPlease Enter a number: ");
		appendNumber(arr, length, numberToAppend);
		more = readPositiveNumber("\nDo you want to append more numbers [1]:Yes, [0]:No ?");
	}
	std::cout << "\nArray Length: " << length << std::endl;
	printArrayValues(arr, length);

	return 0;
}