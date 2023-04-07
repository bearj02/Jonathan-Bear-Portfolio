#include <iostream>
#include <fstream>
#include "lab03.h"

using namespace std;

// REQUIRES: str1 and str2 point to C-strings
// EFFECTS:  If str1 and str2 contain exactly the same characters, returns 0.
//           Otherwise, return a positive number if the first differing char
//           has a greater value in str1 than in str2 and a negative number in
//           the opposite case (you may NOT call strcmp).
// NOTE:     You should implement this without using cstring library functions.
int strcmp_eecs280(const char *str1, const char *str2) {
  int notEqualAt = 0;
  for(int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++){
    if(str1[i] != str2[i]){
      notEqualAt = i;
      break;
    }
    if(str1[i+1] == '\0' && str2[i+1] == '\0'){
      return 0;
    }
  }
  if(str1[notEqualAt] > str2[notEqualAt]){
    return 1;
  }
  return -1;
}

// EFFECTS:  Prints "Please enter a word: " to prompt the user to enter a word
//           and then reads a word from cin to be returned. After reading the
//           input, clean up by printing a newline to cout.
string get_user_word() {
  cout << "Please enter a word: " << endl;
  string user_word = "";
  cin >> user_word;
  return user_word;
}

// EFFECTS: Opens the given file and returns a vector containing all the words
//          in the file. If the file cannot be opened, prints an error message
//          and returns an empty vector.
vector<string> read_words_from_file(const string &filename) {
  vector<string> words;
  ifstream myfile (filename);
  string word;
  if(myfile.is_open()){
    while(getline(myfile,word)){
      words.push_back(word);
    }
    myfile.close();
  }
  else{
    cout << "Error: The file could not be openened" << endl;
  }
  return words;
}

// EFFECTS:  Returns true if the given word is contained in the vector of valid
//           words.
// NOTE:     You MUST use the strcmp_eecs280 function (NOT strcmp).
//           You should implement this without using cstring library functions.
bool find_word(const char *word, const vector<string> &valid_words) {
  for(int i = 0; i < static_cast<int>(valid_words.size()); i++){
    if(strcmp_eecs280(word, valid_words.at(i).c_str()) == 0){
      return true;
    }
  }
  return false; // TASK 2 - YOUR CODE HERE
}
