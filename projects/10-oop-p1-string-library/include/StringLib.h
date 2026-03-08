#pragma once

#include <string>
#include <vector>
#include <cctype>

class StringLib{

private:
    std::string _value;

public:
    
    StringLib();
    StringLib(const std::string& value);

  
    void setValue(const std::string& value);
    std::string getValue() const;



    static size_t length(const std::string& text);
    size_t length() const;


    static size_t countWords(const std::string& text);
    size_t countWords() const;


    static std::string capitalizeWords(const std::string& text);
    void capitalizeWords();

    static std::string decapitalizeWords(const std::string& text);
    void decapitalizeWords();


    static std::string toUpper(const std::string& text);
    void toUpper();

    static std::string toLower(const std::string& text);
    void toLower();


    static char invertCase(char character);
    static std::string invertCase(const std::string& text);
    void invertCase();


    enum class CharacterType { Lowercase, Uppercase, All };


    static size_t countCharacters(const std::string& text, CharacterType type = CharacterType::All);

    static size_t countUppercase(const std::string& text);
    size_t countUppercase() const;

    static size_t countLowercase(const std::string& text);
    size_t countLowercase() const;

    static size_t countSpecificCharacter(const std::string& text, char letter, bool matchCase = true);
    size_t countSpecificCharacter(char letter, bool matchCase = true) const;


    static bool isVowel(char character);
    static size_t countVowels(const std::string& text);
    size_t countVowels() const;


    static std::vector<std::string> split(const std::string& text, const std::string& delimiter);
    std::vector<std::string> split(const std::string& delimiter) const;

    static std::string join(const std::vector<std::string>& words, const std::string& delimiter);
    static std::string join(const std::string words[], size_t length, const std::string& delimiter);


    static std::string trimLeft(const std::string& text);
    void trimLeft();

    static std::string trimRight(const std::string& text);
    void trimRight();

    static std::string trim(const std::string& text);
    void trim();


    static std::string reverseWords(const std::string& text);
    void reverseWords();

 
    static std::string replace(const std::string& text, const std::string& target, const std::string& replacement, bool matchCase = true);
    void replace(const std::string& target, const std::string& replacement, bool matchCase = true);


    static std::string removePunctuation(const std::string& text);
    void removePunctuation();
};

// =================================================================
// IMPLEMENTATION SECTION
// =================================================================

inline StringLib::StringLib(){
    _value = "";
}

inline StringLib::StringLib(const std::string& value) {
    _value = value;
}

inline void StringLib::setValue(const std::string& value) {
    _value = value;
}

inline std::string StringLib::getValue() const {
    return _value;
}

inline size_t StringLib::length(const std::string& text) {
    return text.length();
}

inline size_t StringLib::length() const {
    return _value.length();
}

inline std::string StringLib::toUpper(const std::string& text) {
    std::string uppered;
    uppered.reserve(text.length());
    for (size_t i = 0; i < text.length(); i++) {
        uppered.push_back(static_cast<char>(std::toupper(text[i])));
    }
    return uppered;
}

inline void StringLib::toUpper() {
    _value = StringLib::toUpper(_value);
}

inline std::string StringLib::toLower(const std::string& text) {
    std::string lowered;
    lowered.reserve(text.length());
    for (size_t i = 0; i < text.length(); i++) {
        lowered.push_back(static_cast<char>(std::tolower(text[i])));
    }
    return lowered;
}

inline void StringLib::toLower() {
    _value = StringLib::toLower(_value);
}

inline char StringLib::invertCase(char character) {
    return std::islower(character) ? static_cast<char>(std::toupper(character)) : static_cast<char>(std::tolower(character));
}

inline std::string StringLib::invertCase(const std::string& text) {
    std::string inverted;
    inverted.reserve(text.length());
    for (size_t i = 0; i < text.length(); i++) {
        inverted.push_back(StringLib::invertCase(text[i]));
    }
    return inverted;
}

inline void StringLib::invertCase() {
    _value = StringLib::invertCase(_value);
}

inline std::string StringLib::capitalizeWords(const std::string& text) {
    std::string capitalized;
    capitalized.reserve(text.length());

    bool isFirstChar = true;
    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];

        if (isFirstChar && c != ' ') {
            capitalized.push_back(static_cast<char>(std::toupper(c)));
            isFirstChar = false;
        }
        else {
            capitalized.push_back(c);
            isFirstChar = (c == ' ');
        }
    }

    return capitalized;
}

inline void StringLib::capitalizeWords() {
    _value = StringLib::capitalizeWords(_value);
}

inline std::string StringLib::decapitalizeWords(const std::string& text) {
    std::string deCapitalized;
    deCapitalized.reserve(text.length());

    bool isFirstChar = true;
    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];

        if (isFirstChar && c != ' ') {
            deCapitalized.push_back(static_cast<char>(std::tolower(c)));
            isFirstChar = false;
        }
        else {
            deCapitalized.push_back(c);
            isFirstChar = (c == ' ');
        }
    }

    return deCapitalized;
}

inline void StringLib::decapitalizeWords() {
    _value = StringLib::decapitalizeWords(_value);
}

inline size_t StringLib::countWords(const std::string& text) {
    size_t counter = 0;
    bool isFirstChar = true;

    for (size_t i = 0; i < text.length(); i++) {
        char c = text[i];

        if (c != ' ' && isFirstChar) {
            counter++;
            isFirstChar = false;
        }
        else if (c == ' ') {
            isFirstChar = true;
        }
    }

    return counter;
}

inline size_t StringLib::countWords() const {
    return StringLib::countWords(_value);
}

inline bool StringLib::isVowel(char character) {
    character = static_cast<char>(std::tolower(character));

    return character == 'a' ||
        character == 'e' ||
        character == 'i' ||
        character == 'o' ||
        character == 'u';
}

inline size_t StringLib::countVowels(const std::string& text) {
    size_t counter = 0;
    for (size_t i = 0; i < text.length(); i++) {
        if (StringLib::isVowel(text[i])) counter++;
    }
    return counter;
}

inline size_t StringLib::countVowels() const {
    return StringLib::countVowels(_value);
}

inline size_t StringLib::countCharacters(const std::string& text, StringLib::CharacterType type) {
    if (type == CharacterType::All)
        return text.length();

    size_t counter = 0;

    for (size_t i = 0; i < text.length(); i++) {

        if (type == CharacterType::Uppercase && std::isupper(text[i]))
            counter++;

        else if (type == CharacterType::Lowercase && std::islower(text[i]))
            counter++;
    }

    return counter;
}

inline size_t StringLib::countUppercase(const std::string& text) {
    return StringLib::countCharacters(text, StringLib::CharacterType::Uppercase);
}

inline size_t StringLib::countUppercase() const {
    return StringLib::countUppercase(_value);
}

inline size_t StringLib::countLowercase(const std::string& text) {
    return StringLib::countCharacters(text, StringLib::CharacterType::Lowercase);
}

inline size_t StringLib::countLowercase() const {
    return StringLib::countLowercase(_value);
}

inline size_t StringLib::countSpecificCharacter(const std::string& text, char letter, bool matchCase) {
    size_t counter = 0;
    for (size_t i = 0; i < text.length(); i++) {
        if (matchCase) {
            if (text[i] == letter) counter++;
        }
        else {
            if (static_cast<char>(std::tolower(letter)) ==
                static_cast<char>(std::tolower(text[i]))) counter++;
        }
    }
    return counter;
}

inline size_t StringLib::countSpecificCharacter(char letter, bool matchCase) const {
    return StringLib::countSpecificCharacter(_value, letter, matchCase);
}

inline std::string StringLib::trimLeft(const std::string& text) {
    
    size_t i = 0;

    while (i < text.length() && text[i] == ' ') {
        i++;
    }

    return text.substr(i);
}

inline void StringLib::trimLeft() {
    _value = StringLib::trimLeft(_value);
}

inline std::string StringLib::trimRight(const std::string& text) {
    
    if (text.empty()) return "";

    size_t i = text.length();

    while (i > 0 && text[i - 1] == ' ') {
        --i;
    }

    return text.substr(0, i);
}

inline void StringLib::trimRight() {
    _value = StringLib::trimRight(_value);
}

inline std::string StringLib::trim(const std::string& text) {
    return StringLib::trimLeft(StringLib::trimRight(text));
}

inline void StringLib::trim() {
    _value = StringLib::trim(_value);
}
