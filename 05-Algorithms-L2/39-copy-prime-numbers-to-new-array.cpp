#include <iostream>

enum enNumberType { Prime = 1, NotPrime = 0 };

enNumberType checkPrime(int number) {
	// we can check if the number is prime by checiking 
	// if it is divisible by any number from 2 to half of the number
	if (number < 2) {
		return enNumberType::NotPrime;
	}
	int half = round(number / 2);
	for (int i = 2; i <= half; i++) {
		if (number % i == 0) {
			return enNumberType::NotPrime;
		}
	}
	return enNumberType::Prime;
}

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

void copyPrimeNumbersIntoArray(int array[100], int targetArray[100], int size, int& targetSize) {

	for (int i = 0; i < size; i++) {
		if (checkPrime(array[i]) == enNumberType::Prime) {
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
	copyPrimeNumbersIntoArray(array, targetArray, size, targetSize);
	printArrayValues(targetArray, targetSize);
	return 0;
}