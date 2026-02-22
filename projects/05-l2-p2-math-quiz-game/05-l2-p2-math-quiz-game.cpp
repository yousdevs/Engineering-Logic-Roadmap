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

bool isNumber(std::string s) {
    if (s.empty()) return false;

    int start = (s[0] == '-') ? 1 : 0;
    if (start == 1 && s.length() == 1) return false; // Just a "-" is not a number

    for (int i = start; i < s.length(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
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

int readInteger() {
    std::string input = "";
    bool firstInput = true;
    do {
        if (!firstInput) {
            println("Please enter a valid integer: ");
        }
        else {
            firstInput = false;
        }
        std::cin >> input;
    } while (!isNumber(input));
    return std::stoi(input);
}

// Returns: A random integer between From and To (inclusive).
int getRandomNumberInRange(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

// _________CONSTANTS__________
const short MIN_ALLOWED_QUIZES = 1; // used for input validation
const short MAX_ALLOWED_QUIZES = 100;
const short MIN_QUIZ_DIFFICULTY_LEVEL = 1; // used for mappers validation & input validation
const short MAX_QUIZ_DIFFICULTY_LEVEL = 4;
const short MIN_QUIZ_OPERATOR_ORDER = 1; // used for mappers validation & input validation
const short MAX_QUIZ_OPERATOR_ORDER = 5;
const short OPERAND_RANGE_EASY_MIN = 1;
const short OPERAND_RANGE_EASY_MAX = 10;
const short OPERAND_RANGE_MEDIUM_MIN = 11;
const short OPERAND_RANGE_MEDIUM_MAX = 20;
const short OPERAND_RANGE_HARD_MIN = 21;
const short OPERAND_RANGE_HARD_MAX = 100;

// _________ENUMS & Mappers_________
enum enQuizDifficulty {
    Easy = 1,
    Medium = 2,
    Hard = 3,
    dMix = 4, // avoids unscoped enums conflicts, we can use scoped enums by prefixing enum with class keyword
    // but at current roadmap level we skip it
    _LastActualDifficultyLevel = Hard,
};

enum enQuizOperator {
    Add = 1,
    Sub = 2,
    Multi = 3,
    Div = 4,
    oMix = 5,
    _LastActualOperand = Div,
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


int determineOperand(enQuizDifficulty difficulty) {
    if (difficulty == enQuizDifficulty::dMix) {
        difficulty = enQuizDifficultyFromInt(getRandomNumberInRange(MIN_QUIZ_DIFFICULTY_LEVEL, enQuizDifficulty::_LastActualDifficultyLevel));
    }

    switch (difficulty) {
    case enQuizDifficulty::Easy: return getRandomNumberInRange(OPERAND_RANGE_EASY_MIN, OPERAND_RANGE_EASY_MAX);
    case enQuizDifficulty::Medium: return getRandomNumberInRange(OPERAND_RANGE_MEDIUM_MIN, OPERAND_RANGE_MEDIUM_MAX);
    case enQuizDifficulty::Hard: return getRandomNumberInRange(OPERAND_RANGE_HARD_MIN, OPERAND_RANGE_HARD_MAX);
    default: return getRandomNumberInRange(OPERAND_RANGE_EASY_MIN, OPERAND_RANGE_EASY_MAX); //TODO: Throw an error
    }
}

enQuizOperator determineOperator(enQuizOperator op) {
    if (op != enQuizOperator::oMix) {
        return op;
    }
    return enQuizOperatorFromInt(getRandomNumberInRange(MIN_QUIZ_OPERATOR_ORDER, enQuizOperator::_LastActualOperand));
}

int calculateResult(int operandA, int operandB, enQuizOperator op) {
    switch (op) {
    case enQuizOperator::Add: return operandA + operandB;
    case enQuizOperator::Sub: return operandA - operandB;
    case enQuizOperator::Multi: return operandA * operandB;
    case enQuizOperator::Div: return operandA / operandB; // TODO: handle division by 0
    default: return 0;
    }
}
strQuizQuestion generateQuestion(strUserInputConfig config, short order) {
    strQuizQuestion question = {};
    question.questionId = order;
    question.operandA = determineOperand(config.quizDifficulty);
    question.operandB = determineOperand(config.quizDifficulty);
    question.questionOperator = determineOperator(config.quizOperator);
    question.calculatedResult = calculateResult(question.operandA, question.operandB, question.questionOperator);
    return question;
}

void displayQuestion(strQuizQuestion question, short allQuestionsCount) {

    println("");
    println("Question [" + std::to_string(question.questionId) + "/" + std::to_string(allQuestionsCount) + "]:");
    println("");

    println(std::to_string(question.operandA));
    print(std::to_string(question.operandB));
    print("  ");
    println(enQuizOperatorToString(question.questionOperator));
    println("_________");
}

int getUserAnswer() {
    return readInteger();
}

void displayResult(int calculatedResult, bool isUserAnswerWrong) {
    if (isUserAnswerWrong) {
        println("Wrong Answer :(");
        println("The right answer is " + std::to_string(calculatedResult));
    }
    else {
        println("Right Answer :)");
    }
}

void startGame() {

    strUserInputConfig userInputConfig = askUserForConfig();

    for (short i = 0; i < userInputConfig.quizCount; i++) {

        strQuizQuestion question = generateQuestion(userInputConfig, (i + 1));
        displayQuestion(question, userInputConfig.quizCount);
        int userAnswer = getUserAnswer();
        bool isUserAnswerWrong = !(question.calculatedResult == userAnswer);
        displayResult(question.calculatedResult, isUserAnswerWrong);

        
    }

}


int main()
{
    // Seed the random number generator with the current time.
    // This ensures that we get a different sequence of random numbers on each run.
    srand((unsigned)time(NULL));

    char playAgain = 'N';
    do {
        startGame();
        std::cout << "\nDo You Want to Play Again? Y/N ? ";
        std::cin >> playAgain;
    } while (playAgain == 'Y' || playAgain == 'y');

    return 0;
}
