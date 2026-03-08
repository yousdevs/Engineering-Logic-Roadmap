#include <iostream>
#include "StringLib.h";

int main() {

    using std::cout;
    using std::endl;

    cout << "=== StringLib Example ===\n\n";

    // Constructor
    StringLib text("Hello World from StringLib");

    cout << "Original text: " << text.getValue() << endl;


    // =========================
    // Length
    // =========================
    cout << "\n--- Length ---\n";
    cout << "Length: " << text.length() << endl;
    cout << "Length of 'Apple': " << StringLib::length("Apple") << endl;


    // =========================
    // Case transformations
    // =========================
    cout << "\n--- Case Transformations ---\n";

    StringLib upperTest = text;
    upperTest.toUpper();
    cout << "Uppercase: " << upperTest.getValue() << endl;

    StringLib lowerTest = text;
    lowerTest.toLower();
    cout << "Lowercase: " << lowerTest.getValue() << endl;

    StringLib invertTest = text;
    invertTest.invertCase();
    cout << "Invert case: " << invertTest.getValue() << endl;


    // =========================
    // Capitalization
    // =========================
    cout << "\n--- Word Capitalization ---\n";

    StringLib capTest("hello world from stringlib");
    capTest.capitalizeWords();
    cout << "Capitalize words: " << capTest.getValue() << endl;

    StringLib decapTest("Hello World From StringLib");
    decapTest.decapitalizeWords();
    cout << "Decapitalize words: " << decapTest.getValue() << endl;


    // =========================
    // Word / character analysis
    // =========================
    cout << "\n--- Text Analysis ---\n";

    cout << "Word count: " << text.countWords() << endl;
    cout << "Vowel count: " << text.countVowels() << endl;

    cout << "Uppercase count: " << text.countUppercase() << endl;
    cout << "Lowercase count: " << text.countLowercase() << endl;

    cout << "'L' character count (ignore case): "
        << text.countSpecificCharacter('L', false) << endl;

    cout << "'Apple Mac' uppercase characters: "
        << StringLib::countCharacters("Apple Mac",
            StringLib::CharacterType::Uppercase) << endl;


    // =========================
    // Trimming
    // =========================
    cout << "\n--- Trim ---\n";

    StringLib trimExample("   padded text   ");

    StringLib leftTrim = trimExample;
    leftTrim.trimLeft();
    cout << "Trim left: '" << leftTrim.getValue() << "'" << endl;

    StringLib rightTrim = trimExample;
    rightTrim.trimRight();
    cout << "Trim right: '" << rightTrim.getValue() << "'" << endl;

    trimExample.trim();
    cout << "Trim both: '" << trimExample.getValue() << "'" << endl;


    // =========================
    // Split
    // =========================
    cout << "\n--- Split ---\n";

    std::vector<std::string> words = text.split(" ");

    cout << "Split words:\n";
    for (const std::string& w : words) {
        cout << "- " << w << endl;
    }


    // =========================
    // Join
    // =========================
    cout << "\n--- Join ---\n";

    std::string joined = StringLib::join(words, "-");
    cout << "Joined with '-': " << joined << endl;

    std::string arrayWords[] = { "C++", "StringLib", "Example" };
    cout << "Join array: "
        << StringLib::join(arrayWords, 3, " | ")
        << endl;


    // =========================
    // Replace
    // =========================
    cout << "\n--- Replace ---\n";

    StringLib replaceTest("I love C++ and C++ libraries");
    replaceTest.replace("C++", "Modern C++");

    cout << "After replace: " << replaceTest.getValue() << endl;


    // =========================
    // Reverse words
    // =========================
    cout << "\n--- Reverse Words ---\n";

    StringLib reverseTest("one two three four");
    reverseTest.reverseWords();

    cout << "Reversed words: " << reverseTest.getValue() << endl;


    // =========================
    // Remove punctuation
    // =========================
    cout << "\n--- Remove Punctuation ---\n";

    StringLib punctTest("Hello, world! Welcome to C++.");
    punctTest.removePunctuation();

    cout << "Without punctuation: "
        << punctTest.getValue()
        << endl;


    cout << "\n=== End of Example ===\n";


	return 0;
}