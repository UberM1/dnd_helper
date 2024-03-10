#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

class Dice {
  public:
    static int* roll(int dice, int cuantity) { 
      assert(dice>0);
      assert(cuantity>0);

      int* array = new int[cuantity];
      for (int i=0; i< cuantity; i++){
          array[i] = rand() % dice + 1;
      }
      return array;
    }
};


//given a dice and the cuantity calculates the rolls and prints them to screen
void dice_roll_to_screen(int dice, int quantity) { 
    int* result = Dice::roll(dice, quantity);
    int sum = 0;
    string outcomes = ""; 
    for (int i = 0; i < quantity; i++) {
        sum += result[i];
        outcomes += to_string(result[i]);
        if (i < quantity - 1) {
            outcomes += " + ";
        }
    }

    cout << sum << " = [" << outcomes << "]" << std::endl;

    delete[] result;
}

// rejex used in roll command
regex rollFormat(R"(/roll(\d+)d(\d+))");

void parse_command(string command){
  smatch matchResults;
  if(regex_search(command, matchResults, rollFormat)){
    int cuantity = stoi(matchResults[1].str());
    int dice = stoi(matchResults[2].str());
    dice_roll_to_screen(dice, cuantity);
  }
}


int main() { 
  string buffer;
  cout << "\ndnd_helper@key > ";
  getline(cin, buffer);
  if (!buffer.empty() && buffer[0] == '/') {
    auto pos = find(buffer.begin(), buffer.end(), ' ');
    if(pos == buffer.end()) { 
      parse_command(buffer);
    } else { 
      cout << "\nerror invalid command spaces found\n";
      return 1;
    }
  } else {
    cout << "\nerror invalid command\n";
    return 1;
  }
  return 0;
}