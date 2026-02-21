#include <iostream>
#include <string>

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

enum enRoundResult {Player = 1, Computer = 2, NoWinner = 3};

struct strRound {
    enChoice playerChoice = enChoice::Rock;
    enChoice computerChoice = enChoice::Rock;
    enRoundResult result = enRoundResult::NoWinner;
    short roundNumber = 0;
};

enRoundResult getWinner(enChoice playerChoice, enChoice computerChoice) {

    if (playerChoice == computerChoice)
        return enRoundResult::NoWinner;
    
    bool playerWinner = (
        (playerChoice == enChoice::Rock && computerChoice == enChoice::Scissors) ||
        (playerChoice == enChoice::Scissors && computerChoice == enChoice::Paper) ||
        (playerChoice == enChoice::Paper && computerChoice == enChoice::Rock)
        );

    return (playerWinner) ? enRoundResult::Player : enRoundResult::Computer;
}

std::string generateLine(short count) {
    std::string line = "";
    for (short i = 0; i < count; i++) {
        line += '_';
    }
    return line;
}

std::string getChoiceStringFrom(enChoice choice) {
    switch (choice) {
        case enChoice::Rock:
            return "Rock";
        case enChoice::Paper:
            return "Paper";
        case enChoice::Scissors:
            return "Scissors";
    }
}

std::string getRoundResultStringFrom(enRoundResult result) {
    switch (result) {
        case enRoundResult::Player:
            return "You";
        case enRoundResult::Computer:
            return "Computer";
        case enRoundResult::NoWinner:
            return "No Winner";
    }
}

enum enScreenColor {
    Default = '7',  
    Red = '4',
    Green = '2',
    Yellow = '6',
    BrightYellow = 'E' 
};

void setConsoleColor(enScreenColor color) {
    char command[] = "color 07";
    command[6] = (char)color;

    system(command);
}

void displayRoundResult(strRound round) {
    std::cout << generateLine(10)
        << "Round["
        << round.roundNumber
        << "]"
        << generateLine(10)
        << std::endl;
    std::cout << std::endl;
    std::cout << "Your Choice: "
        << getChoiceStringFrom(round.playerChoice)
        << std::endl;
    std::cout << "Computer Choice: "
        << getChoiceStringFrom(round.computerChoice)
        << std::endl;
    std::cout << "Round Winner: "
        << "["
        << getRoundResultStringFrom(round.result)
        << "]"
        << std::endl;
    std::cout << std::endl;
    std::cout << generateLine(28)
        << std::endl;
    std::cout << std::endl;
}

void setConsoleColorBasedOn(enRoundResult result) {
    switch (result) {
        case enRoundResult::NoWinner:
            setConsoleColor(enScreenColor::Yellow);
            break;
        case enRoundResult::Player:
            setConsoleColor(enScreenColor::Green);
            break;
        case enRoundResult::Computer:
            setConsoleColor(enScreenColor::Red);
            break;
    }
}

void startGame() {

    short selectedRoundsCount = askForRoundsCount();

    strRound rounds[11] = {}; // allowed round count is between 1 and 10
    short length = selectedRoundsCount;
    
    for (short i = 0; i < selectedRoundsCount; i++) {
        enChoice playerChoice = askForPlayerChoice(i + 1);
        enChoice computerChoice = askForComputerChoice();
        
        strRound round = {};
        round.roundNumber = (i + 1);
        round.playerChoice = playerChoice;
        round.computerChoice = computerChoice;
        round.result = getWinner(playerChoice, computerChoice);
        
        rounds[i] = round;

        displayRoundResult(round);
        setConsoleColorBasedOn(round.result);
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

