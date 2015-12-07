#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::getline;
using std::vector;

vector<int> ExtractCoordinates(string);
void TurnOn(bool [][1000], vector<int>, vector<int>);
void TurnOff(bool [][1000], vector<int>, vector<int>);
void Toggle(bool [][1000], vector<int>, vector<int>);
int CountLights(bool [][1000]);

int main() {
  
  bool lights[1000][1000];

  // Initialize the array
  int i, j;
  for (i = 0; i < 1000; ++i) {
    for (j = 0; j < 1000; ++j) {
      lights[i][j] = false;
    }
  }
  
  ifstream input("input.txt");
  string word, coordinate_pair_string;

  vector<int> start_point, end_point;

  while (input >> word) {
    if (word == "turn") {
      continue;
    
    } else if (word == "toggle") {
      // Get the first coordinate
      input >> coordinate_pair_string;
      start_point = ExtractCoordinates(coordinate_pair_string);
      
      // Throw away the word "through"
      input >> word;

      // Get the second coordinate
      input >> coordinate_pair_string;
      end_point = ExtractCoordinates(coordinate_pair_string);

      Toggle(lights, start_point, end_point);

    } else if (word == "on") {
      // Get the first coordinate
      input >> coordinate_pair_string;
      start_point = ExtractCoordinates(coordinate_pair_string);
      
      // Throw away the word "through"
      input >> word;

      // Get the second coordinate
      input >> coordinate_pair_string;
      end_point = ExtractCoordinates(coordinate_pair_string);

      TurnOn(lights, start_point, end_point);

    } else if (word == "off") {
      // Get the first coordinate
      input >> coordinate_pair_string;
      start_point = ExtractCoordinates(coordinate_pair_string);
      
      // Throw away the word "through"
      input >> word;

      // Get the second coordinate
      input >> coordinate_pair_string;
      end_point = ExtractCoordinates(coordinate_pair_string);

      TurnOff(lights, start_point, end_point);

    }
  }

  cout << CountLights(lights) << endl;

  return 0;
}

// Extracts integer coordinate points from a comma-delimited string containing
// the two coordinates. The first coordinate encountered in the string is saved
// to the first location of the returned vector, and the second coordinate
// encountered in the string is saved to the second location of the returned
// vector.
vector<int> ExtractCoordinates(string coordinate_string) {
  string delimiter = ",";
  size_t comma_position = coordinate_string.find(delimiter);

  string x_string, y_string;
  vector<int> coordinate_pair;

  // Converts coordinate string into x and y strings
  x_string = coordinate_string.substr(0, comma_position);
  coordinate_string.erase(0, comma_position + 1);
  y_string = coordinate_string;
  
  // Converts x and y strings into ints
  coordinate_pair.push_back(stoi(x_string));
  coordinate_pair.push_back(stoi(y_string));

  //cout << coordinate_pair[0] <<  "," << coordinate_pair[1] << endl;
  
  return coordinate_pair;
}

void TurnOn(bool grid[][1000], vector<int> start_point, vector<int> end_point) {
  int i,j;
  for (i = start_point[0]; i <= end_point[0]; ++i) {
    for (j = start_point[1]; j <= end_point[1]; ++j) {
      grid[i][j] = true;
    }
  }
}

void TurnOff(bool grid[][1000], vector<int> start_point, vector<int> end_point) {
  int i,j;
  for (i = start_point[0]; i <= end_point[0]; ++i) {
    for (j = start_point[1]; j <= end_point[1]; ++j) {
      grid[i][j] = false;
    }
  }
}

void Toggle(bool grid[][1000], vector<int> start_point, vector<int> end_point) {
 int i,j;
  for (i = start_point[0]; i <= end_point[0]; ++i) {
    for (j = start_point[1]; j <= end_point[1]; ++j) {
      grid[i][j] = !grid[i][j];
    }
  }
}

int CountLights(bool grid[][1000]) {
  int i, j;
  int num_lights_on = 0;
  for (i = 0; i < 1000; ++i) {
    for (j = 0; j < 1000; ++j) {
      if (grid[i][j] == true) {
        num_lights_on++;
      }
    }
  }
  return num_lights_on;
}
