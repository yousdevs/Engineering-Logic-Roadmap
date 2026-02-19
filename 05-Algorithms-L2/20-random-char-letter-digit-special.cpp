#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

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

int main()
{
    srand((unsigned)std::time(NULL));

    std::cout << getRandomCharacter(enCharType::smallLetter) << std::endl;
    std::cout << getRandomCharacter(enCharType::capitalLetter) << std::endl;
    std::cout << getRandomCharacter(enCharType::specialCharacter) << std::endl;
    std::cout << getRandomCharacter(enCharType::digit) << std::endl;

    return 0;
}