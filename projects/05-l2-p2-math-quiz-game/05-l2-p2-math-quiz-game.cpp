#include <iostream>   
#include <cstdlib>
#include <ctime>
#include <string>

// ______UTILS______
void print(std::string message) {
    std::cout << message;
}

void println(std::string message) {
    std::cout << message << std::endl;
}

unsigned int readPositiveInteger() {
    int integer = 0;
    do {
        println("Please Enter Positive Integer: ");
        std::cin >> integer; // TODO: add string to integer validation
    } while (integer <= 0);
    return integer;
}

short readIntegerInRange(short min, short max) {
    short integer = 0;
    bool firstInput = true;
    do {
        if (!firstInput) {
            println("Please Enter Integer Between " + std::to_string(min) + " and " + std::to_string(max) + " :");
        } else{
            firstInput = false;
        }
        std::cin >> integer; // TODO: add string to integer validation
    } while (integer < min || integer > max);
    return integer;
}

// _________CONSTANTS__________
const short MIN_ALLOWED_QUIZES = 1; // used for input validation
const short MAX_ALLOWED_QUIZES = 100;
const short MIN_QUIZ_DIFFICULTY_LEVEL = 1; // used for mappers validation & input validation
const short MAX_QUIZ_DIFFICULTY_LEVEL = 4;
const short MIN_QUIZ_OPERATOR_ORDER = 1; // used for mappers validation & input validation
const short MAX_QUIZ_OPERATOR_ORDER = 5;

// _________ENUMS & Mappers_________
enum enQuizDifficulty {
    Easy = 1,
    Medium = 2,
    Hard = 3,
    dMix = 4 // avoids unscoped enums conflicts, we can use scoped enums by prefixing enum with class keyword
            // but at current roadmap level we skip it
};

enum enQuizOperator {
    Add = 1,
    Sub = 2,
    Multi = 3,
    Div = 4,
    oMix = 5
};

enQuizDifficulty enQuizDifficultyFromInt(short input) {
    if (input < MIN_QUIZ_DIFFICULTY_LEVEL || input > MAX_QUIZ_DIFFICULTY_LEVEL) {
        return enQuizDifficulty::dMix; 
    }
    return (enQuizDifficulty)input;
}

enQuizOperator enQuizOperatorFromInt(short input) {
    if (input < MIN_QUIZ_OPERATOR_ORDER || input > MAX_QUIZ_OPERATOR_ORDER) {
        return enQuizOperator::oMix;
    }
    return (enQuizOperator)input;
}

std::string enQuizOperatorToString(enQuizOperator op) {
    switch (op) {
    case enQuizOperator::Add:   return "+";
    case enQuizOperator::Sub:   return "-";
    case enQuizOperator::Multi: return "*";
    case enQuizOperator::Div:   return "/";
    default:                    return "Unknown";
    }
}


struct strUserInputConfig {
    short quizCount = 0;
    enQuizDifficulty quizDifficulty = enQuizDifficulty::dMix;
    enQuizOperator quizOperator = enQuizOperator::oMix;
};

strUserInputConfig askUserForConfig() {
    strUserInputConfig userInputConfig;
    
    println("How many quizes do you want to take ?");
    userInputConfig.quizCount = readIntegerInRange(MIN_ALLOWED_QUIZES, MAX_ALLOWED_QUIZES);

    println("Enter Quiz Difficulty: [1] Easy, [2] Medium, [3] Hard, [4] Mix:");
    userInputConfig.quizDifficulty = enQuizDifficultyFromInt(readIntegerInRange(MIN_QUIZ_DIFFICULTY_LEVEL, MAX_QUIZ_DIFFICULTY_LEVEL));

    println("Enter Operator: [1] ADD, [2] SUB, [3] MULTI, [4] DIV, [5] MIX:");
    userInputConfig.quizOperator = enQuizOperatorFromInt(readIntegerInRange(MIN_QUIZ_OPERATOR_ORDER, MAX_QUIZ_OPERATOR_ORDER));
        
    return userInputConfig;
}

struct strQuizQuestion {
    short questionId = 0;
    int operandA = 0;
    int operandB = 0;
    enQuizOperator questionOperator = enQuizOperator::oMix;
    int calculatedResult = 0;
};

void displayQuizQuestion(strQuizQuestion question, short allQuestionsCount) {

    println("");
    println("Question [" + std::to_string(question.questionId) + "/" + std::to_string(allQuestionsCount) + "]:");
    println("");

    println(std::to_string(question.operandA));
    print(std::to_string(question.operandB));
    print("  ");
    println(enQuizOperatorToString(question.questionOperator));
    println("_________");
}

void startGame() {

    strUserInputConfig userInputConfig = askUserForConfig();

    for (short i = 0; i < userInputConfig.quizCount; i++) {

        strQuizQuestion q = {};
        q.questionId = (i+1);
        q.operandA = 1;
        q.operandB = 4;
        q.questionOperator = enQuizOperator::Add;
        q.calculatedResult = 5;
        displayQuizQuestion(q, userInputConfig.quizCount);
    }

}


int main()
{
    char playAgain = 'N';
    do {
        startGame();
        std::cout << "\nDo You Want to Play Again? Y/N ? ";
        std::cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');

    return 0;
}
