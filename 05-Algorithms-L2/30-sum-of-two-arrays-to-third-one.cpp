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

int sumAllElementsOf(int array[100], int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += array[i];
	}
	return sum;
}

float calculateAverage(int array[100], int size) {

	int sum = sumAllElementsOf(array, size);
	return (float)(sum / size);
}

void printSumOf(int array[100], int size) {

	int sum = sumAllElementsOf(array, size);
	std::cout << "Sum of All Numbers Is: " << sum << std::endl;
}

void printAverageOf(int array[100], int size) {

	float avg = calculateAverage(array, size);
	std::cout << "Average of All Numbers Is: " << avg << std::endl;
}

void sumTwoArraysInto(int target[100], int source1[100], int source2[100], int &targetSize, int sourceSize) {
	for (int i = 0; i < sourceSize; i++) {
		target[i] = source1[i] + source2[i];
		targetSize++;
	}
}

int main() {
	srand((unsigned)std::time(NULL));
	int array[100] = {};
	int size = readPositiveNumber("Enter Number of elements: ");
	fillArrayWithRandomNumbers(array, size);
	printArrayValues(array, size);


	int array2[100] = {};
	int size2 = size;
	fillArrayWithRandomNumbers(array2, size);
	printArrayValues(array2, size2);

	int target[100] = {};
	int targetSize = 0;
	sumTwoArraysInto(target, array, array2, targetSize, size);
	printArrayValues(target, targetSize);

	return 0;
}