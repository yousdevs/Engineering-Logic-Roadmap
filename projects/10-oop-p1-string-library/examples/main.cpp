#include <iostream>
#include "StringLib.h";

int main() {

    using std::cout;
    using std::endl;

    cout << "=== StringLib Example ===\n\n";

    // Constructor
    StringLib text("Hello World from StringLib");

    cout << "Original text: " << text.getValue() << endl;
    
    // Length
    cout << "Length: " << text.length() << endl;
    cout << "Length of 'Apple': " << StringLib::length("Apple") << endl;

	
	return 0;
}