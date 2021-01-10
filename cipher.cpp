#include <iostream> 
#include <string>
#include <assert.h>

using namespace std;

const int LOWER_CAPITAL_BOUND = 64;
const int UPPER_CAPITAL_BOUND = 90;
const int LOWER_NORMAL_BOUND = 97;
const int UPPER_NORMAL_BOUND = 123;
const int SPACE_KEY = 32;

class Cipher {
  public:
    string message;

    Cipher(string x){
      message = stripMessage(x);
    };

      /* A standard Ceaser cipher,
        "CAT" with a right shift of 4:
          C  --->  G
          A  --->  D
          T  --->  X
        Producing: "GDX" */

    static bool isValidLetter(char letter) {
      if (int(letter) > LOWER_CAPITAL_BOUND && int(letter) < UPPER_NORMAL_BOUND || 
          int(letter) > LOWER_NORMAL_BOUND && int(letter) < UPPER_NORMAL_BOUND ||
          int(letter) == SPACE_KEY) {
        return true;
      }
      return false;
    };

    static int convertToASCII(char letter){ 
      /* ASCII values for alphabet */
      /* We check if the letter falls within the range */
      if (!isValidLetter(letter)) {
        cout << "ERROR: Invalid character input. Must be [a-z/A-Z] \n";
        return 0;
      };
      return int(tolower(letter));
    };

    string stripMessage(string message){
      string newMessage = "";
      for (int i = 0; i < message.length(); i++){
        if (isValidLetter(message[i])){
          newMessage += message[i]; 
        }
      }
      return newMessage;
    };

    int modulusShift(int valueASCII, int shift){
      /* We must ensure that the when shifting the message we cycle between */
      /* alphabet, as opposed to accessing random ASCII letters */ 
      
      if (valueASCII == SPACE_KEY){
        return valueASCII;
      }
      else if ((valueASCII + shift) > UPPER_NORMAL_BOUND){
        /* We restart the cycle from the beginning */ 
        return LOWER_NORMAL_BOUND + shift;
      } 
      else if ((valueASCII + shift) < LOWER_NORMAL_BOUND){
        /* We restart the cycle from the end */ 
        return UPPER_NORMAL_BOUND + shift;
      } 
      else {
        return valueASCII + shift;
      }
    };

    string Ceaser(int shift) {
      string newMessage;
      int ASCIIMappings[message.length()];

      /* If the shift results in the same message */
      if (shift % 26 == 0) {
        return message;                                          
      }

      /* Add ASCII values into an array */ 
      for (int i = 0; i < message.length(); i++){
        int tempValue  = convertToASCII(message[i]); 
        int newValue = modulusShift(tempValue, shift);
        ASCIIMappings[i] = newValue;
      }

      /* Convert the array of ASCII in to Char */
      int ASCIIMappingsSize =  sizeof(ASCIIMappings)/sizeof(ASCIIMappings[0]);
      for (int i = 0; i < ASCIIMappingsSize; i++){
        newMessage.push_back(char(ASCIIMappings[i]));
      }
      return newMessage;
    };

  private: 
    string key;
};

int main() {
  string testMessage = "a b c d"; 
  Cipher myMsg(testMessage);
  int shiftValues[3] = {1,-1,26}; 
  for (int i = 0; i < sizeof(shiftValues)/sizeof(shiftValues[0]); i++) {
    switch (shiftValues[i]) {
      case 1: assert(myMsg.Ceaser(1) == "b c d e");
      case -1: assert(myMsg.Ceaser(-1) == "z a b c");
      case 26: assert(myMsg.Ceaser(26) == testMessage);
    } 
  }; 
  return 0;
};



