#include <iostream>
#include "StringLib.h";

int main() {

    using std::cout;
    using std::endl;

    cout << "=== StringLib Example ===\n\n";

    // Constructor
    StringLib text("Hello World from StringLib");

    cout << "Original text: " << text.getValue() << endl;
    
    // Length
    cout << "Length: " << text.length() << endl;
    cout << "Length of 'Apple': " << StringLib::length("Apple") << endl;

    // Case transformations
    StringLib upperTest = text;
    upperTest.toUpper();
    cout << "Uppercase: " << upperTest.getValue() << endl;

    StringLib lowerTest = text;
    lowerTest.toLower();
    cout << "Lowercase: " << lowerTest.getValue() << endl;

    StringLib invertTest = text;
    invertTest.invertCase();
    cout << "Invert case: " << invertTest.getValue() << endl;
	
    // Word count
    cout << "Word count: " << text.countWords() << endl;
    // Vowel counting
    cout << "Vowel count: " << text.countVowels() << endl;
    // count UpperCase
    cout << "UpperCase count: " << text.countUppercase() << endl;
    // count LowerCase
    cout << "LowerCase count: " << text.countLowercase() << endl;
    // count specific character:
    cout << "'L' character count: " << text.countSpecificCharacter('L', false) << endl;
    // count characters
    cout << "'Apple Mac' Uppercase characters count: " << StringLib::countCharacters("Apple Mac", StringLib::CharacterType::Uppercase) << endl;

    // Trim example
    StringLib trimExample("   padded text   ");
    trimExample.trim();
    cout << "\nTrimmed text: '" << trimExample.getValue() << "'" << endl;


	return 0;
}