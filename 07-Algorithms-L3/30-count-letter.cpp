#include <iostream>
#include <string>

short countLetterIn(std::string str, char letter) {
	short counter = 0;
	for (short i = 0; i < str.length(); i++) {
		if (std::tolower(str[i]) == letter) counter++;
	}
	return counter;
}

int main() {

	std::string str = "MUHAMMED abu hadhud";

	char letterToCount = 'm';
	short count = countLetterIn(str, letterToCount);
	printf("\nThe Letter %c appeared %d times", letterToCount, count);

	return 0;
}