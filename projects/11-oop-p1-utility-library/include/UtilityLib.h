#pragma once

#include <string>
#include <ctime>

class UtilityLib {

public:

    // Character categories used for random generation
    enum class CharType
    {
        SmallLetter = 1,
        CapitalLetter = 2,
        Digit = 3,
        Mixed = 4,
        SpecialCharacter = 5
    };

    // random Engine

    static void seedRandom();

    static int getRandomInt(int min, int max);
    static char getRandomCharacter(CharType type);


    // random Text Generation

    static std::string generateWord(CharType type, short length);
    static std::string generateKey(CharType type = CharType::CapitalLetter);


    // random Data Utilities

    static void fillArrayWithRandomInts(int arr[], int length, int min, int max);

    static void fillArrayWithRandomWords(
        std::string arr[],
        int length,
        CharType type,
        short wordLength
    );

    static void fillArrayWithRandomKeys(
        std::string arr[],
        int length,
        CharType type
    );


    //Swap Utilities

    static void swapValues(int& a, int& b);
    static void swapValues(double& a, double& b);
    static void swapValues(bool& a, bool& b);
    static void swapValues(char& a, char& b);
    static void swapValues(std::string& a, std::string& b);


    // Array Utilities

    static void shuffleArray(int arr[], int length);
    static void shuffleArray(std::string arr[], int length);


   
    // formatting
    
    static std::string tabs(short count);


    // simple Text Encryption

    static std::string encryptText(const std::string& text, short key);
    static std::string decryptText(const std::string& text, short key);
};

/*-------------------------------------
            Implementation
-------------------------------------*/

inline void UtilityLib::seedRandom() {
    // Seed the random number generator with the current time.
    // This ensures that we get a different sequence of random numbers on each run.
    srand((unsigned)time(NULL));
}

inline int UtilityLib::getRandomInt(int min, int max) {
    
    return rand() % (max - min + 1) + min;
}

inline char UtilityLib::getRandomCharacter(CharType type) {

    switch (type) {
    case CharType::CapitalLetter:
        return static_cast<char>(UtilityLib::getRandomInt('A', 'Z'));

    case CharType::SmallLetter:
        return static_cast<char>(UtilityLib::getRandomInt('a', 'z'));

    case CharType::Digit:
        return static_cast<char>(UtilityLib::getRandomInt('0', '9'));

    case CharType::SpecialCharacter:
        return static_cast<char>(UtilityLib::getRandomInt(33, 47));

    case CharType::Mixed:
        return getRandomCharacter(static_cast<CharType>(UtilityLib::getRandomInt(1, 3)));

    default:
        return getRandomCharacter(CharType::CapitalLetter);
    }
}

inline std::string UtilityLib::generateWord(CharType type, short length) {
    
    std::string word;
    word.reserve(length);

    for (short i = 0; i < length; i++) {
        word += UtilityLib::getRandomCharacter(type);
    }
    return word;
}

inline std::string UtilityLib::generateKey(CharType type) {

    const int KEY_GROUPS = 4;
    const int WORD_LENGTH = 4;
    const char DELIM = '-';

    std::string key;
    key.reserve((KEY_GROUPS * WORD_LENGTH) + (KEY_GROUPS - 1));

    key += UtilityLib::generateWord(type, WORD_LENGTH);

    for (int i = 1; i < KEY_GROUPS; i++) {
        key += DELIM;
        key += UtilityLib::generateWord(type, WORD_LENGTH);
    }

    return key;
}


// random Data Utilities

inline void UtilityLib::fillArrayWithRandomInts(int arr[], int length, int min, int max) {
    
    for (int i = 0; i < length; i++) {
        arr[i] = UtilityLib::getRandomInt(min, max);
    }
}

inline void UtilityLib::fillArrayWithRandomWords(
    std::string arr[],
    int length,
    CharType type,
    short wordLength
) {
    for (int i = 0; i < length; i++) {
        arr[i] = UtilityLib::generateWord(type, wordLength);
    }
}

inline void UtilityLib::fillArrayWithRandomKeys(
    std::string arr[],
    int length,
    CharType type
) {
    for (int i = 0; i < length; i++) {
        arr[i] = UtilityLib::generateKey(type);
    }
}

//Swap Utilities

inline void UtilityLib::swapValues(int& a, int& b) {
    
    int temp = a;
    a = b;
    b = temp;
}

inline void UtilityLib::swapValues(double& a, double& b) {
    
    double temp = a;
    a = b;
    b = temp;
}

inline void UtilityLib::swapValues(bool& a, bool& b) {

    bool temp = a;
    a = b;
    b = temp;
}

inline void UtilityLib::swapValues(char& a, char& b) {

    char temp = a;
    a = b;
    b = temp;
}

inline void UtilityLib::swapValues(std::string& a, std::string& b) {

    std::string temp = a;
    a = b;
    b = temp;
}


// Array Utilities

inline void UtilityLib::shuffleArray(int arr[], int length) {
    // Loop backward from the last element down to the second element
    for (int i = length - 1; i > 0; i--) {
        // Pick a random index from 0 to i
        int j = UtilityLib::getRandomInt(0, i);

        // Swap the current element with the randomly selected one
        UtilityLib::swapValues(arr[i], arr[j]);
    }
}

inline void UtilityLib::shuffleArray(std::string arr[], int length) {
    for (int i = length - 1; i > 0; i--) {
        int j = UtilityLib::getRandomInt(0, i);
        UtilityLib::swapValues(arr[i], arr[j]);
    }
}

// formatting

inline std::string UtilityLib::tabs(short count) {
    
    std::string t;
    t.reserve(count);

    for (short i = 0; i < count; i++) {
        t += "\t";
    }
    return t;
}


// simple Text Encryption

inline std::string UtilityLib::encryptText(const std::string& text, short key) {

    std::string encrypted;
    encrypted.reserve(text.length());

    for (const char& t : text) {
        encrypted += static_cast<char>(t + key);
    }
    return encrypted;
}

inline std::string UtilityLib::decryptText(const std::string& text, short key) {

    std::string decrypted;
    decrypted.reserve(text.length());

    for (const char& t : text) {
        decrypted += static_cast<char>(t - key);
    }
    return decrypted;
}