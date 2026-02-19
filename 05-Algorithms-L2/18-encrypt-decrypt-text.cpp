#include <iostream>
#include <string>

std::string readText() {
	std::string text;
	std::cout << "Please enter the text: " << std::endl;
	std::cin >> text;
	return text;
}

std::string encryptText(std::string text, short encryptionKey) {
	std::string encryptedText = "";
	for (int i = 0; i < text.length(); i++) {
		encryptedText += char(text[i] + encryptionKey);
	}
	return encryptedText;
}

std::string decryptText(std::string text, short encryptionKey) {
	std::string decryptedText = "";
	for (int i = 0; i < text.length(); i++) {
		decryptedText += char(text[i] - encryptionKey);
	}
	return decryptedText;
}


void printEncryptedAndDecryptedText(std::string text, short encryptionKey) {
	std::string encryptedText = encryptText(text, encryptionKey);
	std::string decryptedText = decryptText(encryptedText, encryptionKey);
	std::cout << "Encrypted text: " << encryptedText << std::endl;
	std::cout << "Decrypted text: " << decryptedText << std::endl;
}


int main() {
	short encryptionKey = 2;
	printEncryptedAndDecryptedText(readText(), encryptionKey);
	return 0;
}