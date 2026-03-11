#include "UtilityLib.h"
#include <iostream>



int main() {

	using std::cout;
	using std::endl;

    // Seed random generator
    UtilityLib::seedRandom();
    cout << "Random generator seeded.\n\n";

    // Random number and character
    int randInt = UtilityLib::getRandomInt(1, 100);
    char randChar = UtilityLib::getRandomCharacter(UtilityLib::CharType::CapitalLetter);
    cout << "Random int [1-100]: " << randInt << endl;
    cout << "Random capital letter: " << randChar << "\n\n";
	
    // Random word and key
    std::string word = UtilityLib::generateWord(UtilityLib::CharType::SmallLetter, 6);
    std::string key = UtilityLib::generateKey(); // default capital letters
    cout << "Random word (6 letters): " << word << endl;
    cout << "Random key: " << key << "\n\n";
	
	return 0;
}