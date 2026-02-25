#include <iostream>


void printFibonacciSeriesUsingLoop(int steps) {

	int prev1 = 1;
	int prev2 = 0;
	int febNum = 0;

	std::cout << "1\t";
	for (int i = 2; i <= steps; ++i) {
		febNum = prev1 + prev2;
		std::cout << febNum << "\t";
		prev2 = prev1;
		prev1 = febNum;
	}
}

int main() {
	printFibonacciSeriesUsingLoop(10);

	return 0;
}