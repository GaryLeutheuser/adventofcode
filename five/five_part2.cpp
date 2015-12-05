/*
  Really bad bit of code...doesn't complete challenge automatically, requires
  that you manually look through the output list and filter the 'xxx' pairs -
  i.e. the ones where the pair is created by 3 consecutive letters...then
  subtract the number of those there are from the number given by the output.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using std::cout; using std::endl;

using std::string;

using std::getline;
using std::ifstream;

using std::vector;
using std::sort;
using std::unique;

int naughtyOrNice(string);

int main() {
  ifstream input("input.txt");
  
  string line;

  int nice = 0;
  int naughty = 0;

  while(getline(input, line)) {
    //cout << line << endl;

    if (naughtyOrNice(line)) {
      nice++;
    } else {
      naughty++;
    }
  }

  cout << nice << endl;

  return 0;
}

// Returns 1 if nice,
// 0 if naughty
int naughtyOrNice(string line) {
  
  int pair = 0;
  int doubleLetter = 0;
  string subString;

  vector<string> subStrings;

  string::iterator iter;
  for(iter = line.begin(); iter != line.end(); ++iter) {
    // Letter-in-between check (just look at substrings of length 3) 
    if(iter > line.begin()+1) {
      //cout << line.substr((iter-line.begin()-1), 2) << endl;
      subString = line.substr((iter - line.begin() - 2), 3);

      if(subString[0] == subString[2]) {
        doubleLetter = 1;
        //cout << subString << endl;
      }
    }

    if(iter > line.begin()) {
      subString = line.substr((iter - line.begin() - 1), 2);
      subStrings.push_back(subString);
      //cout << subString << endl;

      vector<string>::iterator repeats;
      std::sort(subStrings.begin(), subStrings.end());
      repeats = std::adjacent_find(subStrings.begin(), subStrings.end());
      if(repeats != subStrings.end()) {
        cout << line << endl;
        cout << *repeats << endl;
        pair = 1;
      }
    }
  }
 /* 
  // Now create a listing of substrings we can search through later
  for(iter = line.begin() + 1; iter <= line.end(); iter += 2) { 
      subString = line.substr(iter - line.begin() - 1, 2);
      //cout << subString << endl;
      subStrings.push_back(subString);
  }

  // Finally, see if there's any repeats
  std::sort(subStrings.begin(), subStrings.end());
  
  //cout << *subStrings.begin() << endl;
  
  vector<string>::iterator repeats;
  repeats = std::adjacent_find(subStrings.begin(), subStrings.end());
  if(repeats != subStrings.end()) {
    cout << *repeats << endl;
    pair = 1;
  }
*/

  if(pair && doubleLetter) {
    return 1;
  } else {
    return 0;
  }
}
