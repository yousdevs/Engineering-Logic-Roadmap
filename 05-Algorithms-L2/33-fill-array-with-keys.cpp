#include <iostream>


enum enCharType {
    smallLetter = 1,
    capitalLetter = 2,
    specialCharacter = 3,
    digit = 4
};

int randomNumber(int from, int to)
{
    int randNum = rand() % (to - from + 1) + from;
    return randNum;
}

char getRandomCharacter(enCharType charType)
{
    switch (charType)
    {
    case enCharType::smallLetter:
        return char(randomNumber(97, 122));
    case enCharType::capitalLetter:
        return char(randomNumber(65, 90));
    case enCharType::specialCharacter:
        return char(randomNumber(33, 47));
    case enCharType::digit:
        return char(randomNumber(48, 57));
    }
    return '\0';
}

int readPositiveNumber(std::string message) {
    int number = 0;
    do
    {
        std::cout << message << std::endl;
        std::cin >> number;
    } while (number <= 0);
    return number;
}

std::string generateKeyPart() {
    std::string keyPart;
    for (int i = 0; i < 4; i++) {
        keyPart += getRandomCharacter(enCharType::capitalLetter);
    }
    return keyPart;
}

std::string generateKey() {
    std::string key;
    for (int i = 0; i < 4; i++) {
        key += generateKeyPart();
        if (i < 3) {
            key += '-';
        }
    }
    return key;
}

void generateKeys(std::string array[100], int length) {
    
    for (int i = 0; i < length; i++) {
        array[i] = generateKey();
    }
}

void printKeys(std::string array[100], int length) {
    std::cout << "Array Elements: " << std::endl;
    
    for (int i = 0; i < length; i++) {
        std::cout << "Key [" << i + 1 << "]: "
            << array[i]
            << std::endl;
    }
}

int main() {
    srand((unsigned)std::time(NULL));

    std::string array[100] = {};
    int length = readPositiveNumber("How many keys you want to generate? ");

    generateKeys(array, length);

    printKeys(array, length);
}