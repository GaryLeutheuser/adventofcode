#include <iostream>
#include <fstream>

using namespace std;

int main() {
    
    string line;
    int floor = 0;

    ifstream inputFile("input.txt");

    if(inputFile.is_open()) {
	getline(inputFile, line);
	inputFile.close();
    } else
	cout << "Cannot open file\n";

    string::iterator iter = line.begin();

    int i;

    for (i = 0; i < line.length(); i++) {
	if (*(iter+i) == '(') {
	    floor++;
	} else if (*(iter+1) == ')') {
	    floor--;
	}
    }

    cout << floor;
    cout << '\n';

    return 0;
}
