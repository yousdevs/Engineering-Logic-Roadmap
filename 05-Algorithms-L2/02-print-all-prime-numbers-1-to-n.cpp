#include <iostream>

using namespace std;


int readPositiveNumber(string message) {
	
	int number = 0;
	do
	{
		cout << message << endl;
		cin >> number;
	} while (number <= 0);
	return number;
}

enum enNumberType {Prime=1, NotPrime=0};

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
void printPrimeNumbers(int n) {
	// print all prime numbers from 1 to n
	for (int i = 1; i <= n; i++) {
		if (checkPrime(i) == enNumberType::Prime) {
			cout << i << endl;
		}
	}
}
int main() {
	printPrimeNumbers(readPositiveNumber("Please enter a positive number: "));
}