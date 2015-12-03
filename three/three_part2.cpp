#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    
    string line;
    
    // Coordinate vector:
    // element 0: x
    // element 1: y
    vector<int> currCoordSanta;
    vector<int> currCoordRobo;

    // Initialize coordinates to origin
    currCoordSanta.push_back(0);
    currCoordSanta.push_back(0);

    currCoordRobo.push_back(0);
    currCoordRobo.push_back(0);
    
    // Whoever's coordinates are currently being read
    vector<int> currCoord;

    int numHouses = 1;
    vector< vector<int> > coordHistory;
    
    // The origin is always visited (first)
    coordHistory.push_back(currCoordSanta);

    ifstream inputFile("input.txt");

    if(inputFile.is_open()) {
        getline(inputFile, line);
        //cout << line << endl;
        inputFile.close();
    } else
        cout << "Cannot open file\n";

    string::iterator iter = line.begin();

    int i;

    for (i = 0; i < line.length(); i++) {
        // Who is being directed?
        if (i % 2 == 0) {
          currCoord = currCoordSanta;
          //cout << "Using santa coords" << endl;
        } else {
          currCoord = currCoordRobo;
          //cout << "Using robo coords" << endl;
        }
        
        // Coordinate update
        if (*(iter+i) == '<') {
          // x--;
          currCoord[0]--;
        } else if (*(iter+i) == '^') {
          // y++;
          currCoord[1]++;
        } else if (*(iter+i) == '>') {
          // x++;
          currCoord[0]++;
        } else if (*(iter+i) == 'v') {
          // y--;
          currCoord[1]--;
        } 

        if (i % 2 == 0) {
          currCoordSanta = currCoord;
        } else {
          currCoordRobo = currCoord;
        }

        //cout << currCoord[0] << "," << currCoord[1] << endl;

        // If it's a new coordinate, add one to numHouses, and add it to the list
        if(find(coordHistory.begin(), coordHistory.end(), currCoord) != coordHistory.end()) {
          // Do nothing...not a new house
          //cout << "Old..." << endl;
        } else {
          // New house!
          numHouses++;
          coordHistory.push_back(currCoord);
          //cout << "New!" << endl;
        }
    }

    cout << numHouses;
    cout << '\n';

    return 0;
}
