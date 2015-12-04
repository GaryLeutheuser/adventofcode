#include <iostream>
#include <string>
#include "md5.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

int main() {
  
  // define the string key
  const string key = "iwrupvqb";
  // define a variable to hold the test number we're adding to the key
  string number;

  // define a variable for the output of the hash
  string hash;
  
  int i;
  for(i = 0; i > -1; i++) {
    
    number = to_string(i);

    hash = md5(key + number);

    // Does the hash satisfy the needed five 0s?
    if(hash.compare(0,5,"00000") == 0) {
      cout << "Found it @ " + number << endl;
      break;
    } else {
      // cout << "Nope..." << endl;
    }
  }

  return 0;
}
