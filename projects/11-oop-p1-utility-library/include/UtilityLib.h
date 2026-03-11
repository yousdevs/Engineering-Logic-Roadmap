#pragma once

#include <string>

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

    /*-------------------------------------
        Random Engine
    -------------------------------------*/

    static void seedRandom();

    static int getRandomInt(int min, int max);
    static char getRandomCharacter(CharType type);


    /*-------------------------------------
        Random Text Generation
    -------------------------------------*/

    static std::string generateWord(CharType type, short length);
    static std::string generateKey(CharType type = CharType::CapitalLetter);


    /*-------------------------------------
        Random Data Utilities
    -------------------------------------*/

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


    /*-------------------------------------
        Swap Utilities
    -------------------------------------*/

    static void swapValues(int& a, int& b);
    static void swapValues(double& a, double& b);
    static void swapValues(bool& a, bool& b);
    static void swapValues(char& a, char& b);
    static void swapValues(std::string& a, std::string& b);


    /*-------------------------------------
        Array Utilities
    -------------------------------------*/

    static void shuffleArray(int arr[], int length);
    static void shuffleArray(std::string arr[], int length);


    /*-------------------------------------
        Formatting
    -------------------------------------*/

    static std::string tabs(short count);


    /*-------------------------------------
        Simple Text Encryption
    -------------------------------------*/

    static std::string encryptText(const std::string& text, short key);
    static std::string decryptText(const std::string& text, short key);
};