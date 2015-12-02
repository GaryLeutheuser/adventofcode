#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <sstream>

using namespace std;

int ribbonArea(vector<int>);

int main() {
    
    ifstream inputFile("input.txt");
    
    string dimensionStr;
    vector<int> dimensions;

    int totalRibbon = 0;
    int i = 0;

    int currL, currW, currH;

    string token;
    stringstream iss;


    if(inputFile.is_open()) {
	// Read dimensions a line at a time 
	while (getline(inputFile, dimensionStr)) {
	    
	    //cout << "At line " << dimensionStr;

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

		    totalRibbon += ribbonArea(dimensions);
		    //cout << totalRibbon << '\n';
		    // Clear vector for next round
		    dimensions.clear();
		    i = 0;
		}

	    }
	    iss.clear();
	    
	    
	    
	    
	}

	cout << totalRibbon << '\n';
    } else
	cout << "Cannot open file\n";

    return 0;
}

int ribbonArea(vector<int> dimensions) {

    int baseLength;
    int extra;
    int length;

    vector<int> smallestSides;

    vector<int>::iterator iter = max_element(dimensions.begin(), dimensions.end());

    int i;
    for (i = 0; i <= 2; i++) {
	if (dimensions[i] < *iter) {
	    smallestSides.push_back(dimensions[i]);
	}
    }

    if(smallestSides.size() == 0) {
	//cout << "*****TRIPLER*****" << '\n';
	smallestSides.push_back(*iter);
	smallestSides.push_back(*iter);
    }

    if(smallestSides.size() < 2) {
	smallestSides.push_back(*iter);
	//cout << "*****DOUBLING*****" << '\n';
    }

    // cout << *minAreaIter << '\n';
    baseLength = 2*smallestSides[0] + 2*smallestSides[1];
    extra = dimensions[0]*dimensions[1]*dimensions[2];

    //cout << " | base is " << smallestSides[0] << " and " << smallestSides[1];

    //cout << " | base: " << baseLength << " | extra: " << extra << '\n';

    length = baseLength + extra;

     //cout << ", length is: " << length << '\n';

    return length;
}
