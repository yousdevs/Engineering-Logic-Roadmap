#include <iostream>


void printAllWordsFromAToZ() {
	int start = char('A');
	int end = char('Z');
	for (int i = start; i <= end; i++) {
		for (int j = start; j <= end; j++) {
			for (int k = start; k <= end; k++) {
				std::cout << char(i) << char(j) << char(k) << std::endl;
			}
		}
	}
}

int main() {
	printAllWordsFromAToZ();
	return 0;
}