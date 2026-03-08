#pragma once

#include <string>
#include <vector>

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





