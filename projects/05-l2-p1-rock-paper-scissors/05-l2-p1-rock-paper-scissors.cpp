#include <iostream>

short readPositiveNumberInRange(short min, short max, std::string message) {
    short input = 0;
    do {
        std::cout << message;
        std::cout << std::endl;
        std::cin >> input;
    } while (input < min || input > max);

    return input;
}

short askForRoundsCount() {
    return readPositiveNumberInRange(1, 10, "How Many Rounds 1 to 10 ?");
}

void startGame() {
    short rounds = askForRoundsCount();
}

int main()
{
    startGame();
    
}

