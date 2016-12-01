#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <sstream>

using namespace std;

int paperArea(vector<int>);

int main() {
    
    ifstream inputFile("input.txt");
    
    string dimensionStr;
    vector<int> dimensions;

    int totalPaper = 0;
    int i = 0;

    int currL, currW, currH;

    string token;
    stringstream iss;


    if(inputFile.is_open()) {
	// Read dimensions a line at a time 
	while (getline(inputFile, dimensionStr)) {
	    
	    iss << dimensionStr;

	    while (getline(iss, token, 'x')) {
		
		//cout << token << '\t' << stoi(token) <<  '\n';
		// Add the dimensions to a vector
		
		if (i < 2) {
		    dimensions.push_back(stoi(token));
		    //cout << stoi(token) << '\n';
		    i++;
		} 
		
		else if (i == 2) {
		    dimensions.push_back(stoi(token));
		    
		    //cout << stoi(token) << '\n';

		    totalPaper += paperArea(dimensions);
		    //cout << totalPaper << '\n';
		    // Clear vector for next round
		    dimensions.clear();
		    i = 0;
		}

	    }
	    iss.clear();
	    
	    
	    
	    
	}

	cout << totalPaper << '\n';
    } else
	cout << "Cannot open file\n";

    return 0;
}

int paperArea(vector<int> dimensions) {

    int area;

    vector<int> faceAreas;
    faceAreas.push_back(2*dimensions[0]*dimensions[1]);
    faceAreas.push_back(2*dimensions[1]*dimensions[2]);
    faceAreas.push_back(2*dimensions[0]*dimensions[2]);
    
    vector<int>::iterator minAreaIter = min_element(faceAreas.begin(), faceAreas.end());

    // cout << *minAreaIter << '\n';

    area = accumulate(faceAreas.begin(), faceAreas.end(), 0) + *minAreaIter/2;

//     cout << area << '\n';

    return area;
}
