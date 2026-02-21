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

enum enChoice { Rock = 1, Paper = 2, Scissors = 3 };

enChoice getChoiceFrom(int number) {
    switch (number) {
    case enChoice::Rock:
        return enChoice::Rock;
    case enChoice::Paper:
        return enChoice::Paper;
    case enChoice::Scissors:
        return enChoice::Scissors;
    }
}

enChoice askForPlayerChoice(short currentRound){
    std::cout << "Round [" << currentRound << "] begins:" << std::endl;
    std::cout << std::endl;
    std::cout << "Your Choice: "
        << "[" << enChoice::Rock << "], "
        << "[" << enChoice::Paper << "], "
        << "[" << enChoice::Scissors << "] ? ";

    short input = readPositiveNumberInRange(1, 3, "");
    return getChoiceFrom(input);
}

// Returns: A random integer between From and To (inclusive).
int getRandomNumberInRange(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

enChoice askForComputerChoice() {
    int randomNumber = getRandomNumberInRange(1, 3);
    return getChoiceFrom(randomNumber);
}

void startGame() {

    short rounds = askForRoundsCount();
    
    for (int i = 0; i < rounds; i++) {
        enChoice playerChoice = askForPlayerChoice(i + 1);
        enChoice computerChoice = askForComputerChoice();
        std::cout << "\nPlayer choice: " << playerChoice << ", Coputer: " << computerChoice;
    }
}

int main()
{
    // Seed the random number generator with the current time.
    // This ensures that we get a different sequence of random numbers on each run.
    srand((unsigned)time(NULL));

    startGame();

    return 0;
}

