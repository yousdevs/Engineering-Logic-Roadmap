#include <iostream>


void printFibonacciSeriesUsingRecursion(int steps, int prev1, int prev2) {
	
	int febNum = 0;
	if (steps > 0) {
		febNum = prev1 + prev2;
		prev2 = prev1;
		prev1 = febNum;
		std::cout << febNum << "\t";
		printFibonacciSeriesUsingRecursion(steps - 1, prev1, prev2);
	}
}

int main() {
	printFibonacciSeriesUsingRecursion(10, 0, 1);

	return 0;
}