#include <iostream>



void readArray(int array[100], int &size) {
	std::cout << "How many elements you want to put in the array? " << std::endl;
	std::cin >> size;
	for (int i = 0; i < size; i++) {
		std::cout << "Enter element [" << i + 1 << "]: " << std::endl;
		std::cin >> array[i];
	}
}

int countNumberInArray(int array[100], int numberToCount, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (array[i] == numberToCount) {
			count++;
		}
	}
	return count;
}

void printResult(int numberToCount, int count, int array[100], int size) {
	std::cout << "The array you entered is: " << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "The number " << numberToCount 
			  << " is repeated " << count 
			  << " times in the array." << std::endl;
}

int main() {
	int array[100];
	int size = 0;
	readArray(array, size);
	
	std::cout << "Enter the element you want to count: " << std::endl;
	int numberToCount = 0;
	std::cin >> numberToCount;

	int count = countNumberInArray(array, numberToCount, size);
	printResult(numberToCount, count, array, size);
	return 0;
}