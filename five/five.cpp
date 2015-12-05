#include <iostream>
#include <string>
#include <fstream>

using std::cout; using std::endl;

using std::string;

using std::getline;
using std::ifstream;

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
  
  int vowelCount = 0;
  int doubleLetter = 0;
  string subString;

  string::iterator iter;
  for(iter = line.begin(); iter != line.end(); ++iter) {
    // Vowel check
    if(*iter == 'a' || *iter == 'e' || *iter == 'i' || *iter == 'o' || *iter == 'u') {
      vowelCount++;
    }
    // Check the 2 character substring
    if(iter > line.begin()) {
      //cout << line.substr((iter-line.begin()-1), 2) << endl;
      subString = line.substr((iter - line.begin() - 1), 2);

      if(subString[0] == subString[1]) {
        doubleLetter = 1;
        //cout << subString << endl;
      }
    
      if(subString == "ab" || subString == "cd" || subString == "pq" || subString == "xy") {
        //cout << subString << endl;
        return 0;
      }

    }
  }
  //cout << endl;

  if(vowelCount >= 3 && doubleLetter) {
    return 1;
  } else {
    return 0;
  }
}
