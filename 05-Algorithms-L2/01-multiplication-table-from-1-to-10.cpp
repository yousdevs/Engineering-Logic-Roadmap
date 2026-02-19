#include <iostream>
#include <string>
using namespace std;

float multiply(int a, int b) {
    return a * b;
}
string generateSpace(int count) {
    string spaces = "";
    char space = ' ';
    for (int i = 0; i < count; i++) {
        spaces += space;
	}
    return spaces;
}
string genrateSpaceDinamic(int value) {
	int count = 4 - to_string(value).length();
	return generateSpace(count);
}
string generateLine() {
    string line = "";
    for (int i = 0; i < 44; i++) {
        line += '-';
    }
    return line + "\n";
}

struct Cell {
    int value = 0;
};
struct Row {
    Cell cells[10];
    int length = 10;
};
struct Table {
    Row rows[10];
    int length = 10;
};
void multiplyAll(Table& table) {
    for (int row = 0; row < table.length; row++) {
        for (int cell = 0; cell < table.rows[row].length; cell++) {
            table.rows[row].cells[cell].value = multiply(row + 1, cell + 1);
        }
    }
}
void printTable(Table& table) {
    string t = "";
    //header
    t += generateSpace(4);
    for (int i = 1; i <= table.rows[0].length; i++) {
        t += to_string(i);
		t += genrateSpaceDinamic(i);
    }
    t += "\n";
	t += generateLine();
    //rows
    for (int row = 0; row < table.length; row++) {
        //row index
		t += to_string(row + 1);
		t += genrateSpaceDinamic(row + 1);
        for (int cell = 0; cell < table.rows[row].length; cell++) {
            t += to_string(table.rows[row].cells[cell].value);
            t += genrateSpaceDinamic(table.rows[row].cells[cell].value);
        }
		t += "\n";
    }
	cout << t;
}

int main() {
	cout << "Multiplication Table from 1 to 10:" << endl;
    Table table;
	multiplyAll(table);
	printTable(table);
    return 0;
}


/*
* v1
#include <iostream>
using namespace std;
void printTableHeader() {
    cout << "\n\n\n\t\t Multiplication Table from 1 to 10\n\n";
    cout << "\t";
    for (int i = 1; i <= 10; i++) {
        cout << i << "\t";
    }
    cout << "\n___________________________________________________________________________________\n";
}
string columnSeperator(int value) {
    if (value < 10) {
        return "   |";
    }
    else {
        return "  |";
    }
}
void printMultiplicationTable() {
    printTableHeader();
    for (int i = 1; i <= 10; i++) {
        cout << " " << i << columnSeperator(i) << "\t";
        for (int j = 1; j <= 10; j++) {
            cout << i * j << "\t";
        }
        cout << endl;
    }
}
int main() {

    printMultiplicationTable();
}

*/