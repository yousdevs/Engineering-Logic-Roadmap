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
	
    // Fill arrays with random data
    const int arrSize = 5;
    int intArr[arrSize];
    std::string strArr[arrSize];
    std::string keyArr[arrSize];

    UtilityLib::fillArrayWithRandomInts(intArr, arrSize, 10, 50);
    UtilityLib::fillArrayWithRandomWords(strArr, arrSize, UtilityLib::CharType::SmallLetter, 4);
    UtilityLib::fillArrayWithRandomKeys(keyArr, arrSize, UtilityLib::CharType::CapitalLetter);

    cout << "Random int array: ";
    for (int i = 0; i < arrSize; i++) cout << intArr[i] << " ";
    cout << "\n";

    cout << "Random word array: ";
    for (int i = 0; i < arrSize; i++) cout << strArr[i] << " ";
    cout << "\n";

    cout << "Random key array: ";
    for (int i = 0; i < arrSize; i++) cout << keyArr[i] << " ";
    cout << "\n\n";

    // Swap values
    int a = 10, b = 20;
    cout << "Before swap: a=" << a << ", b=" << b << endl;
    UtilityLib::swapValues(a, b);
    cout << "After swap: a=" << a << ", b=" << b << "\n\n";

    double x = 1.5, y = 2.5;
    UtilityLib::swapValues(x, y);
    cout << "After swap doubles: x=" << x << ", y=" << y << "\n\n";

    std::string s1 = "hello", s2 = "world";
    UtilityLib::swapValues(s1, s2);
    cout << "After swap strings: s1=" << s1 << ", s2=" << s2 << "\n\n";

    // Shuffle arrays
    cout << "Original int array: ";
    for (int i = 0; i < arrSize; i++) cout << intArr[i] << " ";
    cout << "\n";
    UtilityLib::shuffleArray(intArr, arrSize);
    cout << "Shuffled int array: ";
    for (int i = 0; i < arrSize; i++) cout << intArr[i] << " ";
    cout << "\n\n";

    cout << "Original string array: ";
    for (int i = 0; i < arrSize; i++) cout << strArr[i] << " ";
    cout << "\n";
    UtilityLib::shuffleArray(strArr, arrSize);
    cout << "Shuffled string array: ";
    for (int i = 0; i < arrSize; i++) cout << strArr[i] << " ";
    cout << "\n\n";

	return 0;
}