#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

// REQUIRES: str1 and str2 point to C-strings
// EFFECTS:  If str1 and str2 contain exactly the same characters, returns 0.
//           Otherwise, return a positive number if the first differing char
//           has a greater value in str1 than in str2 and a negative number in
//           the opposite case (you may NOT call strcmp).
int strcmp_eecs280(const char *str1, const char *str2){

  // Make auxiliary pointers to move. Note: technically
  // we could just use str1 and str2 directly in this case.
  const char *ptr1 = str1;
  const char *ptr2 = str2;

  // Advance both pointers to first mismatched characters.
  while (*ptr1 && *ptr1 == *ptr2) {
    ++ptr1;
    ++ptr2;
  }

  // Subtract characters to get a difference. If positive, it means str1 is
  // greater, negative means str2 is greater, zero means equal.
  return *ptr1 - *ptr2;
}

// EFFECTS:  Prints "Please enter a word: " to prompt the user to enter a word
//           and then reads a word from cin to be returned. After reading the
//           input, clean up by printing a newline to cout.
string get_user_word(){
  string s = "Please enter a word: ";
  cout << s;
  string s1;
  cin >> s1;
  cout << endl;
  return s1;
}


// EFFECTS:  Opens the file "words.txt" and looks for the word passed in as a
//           parameter, returning true if found and false otherwise. If it
//           cannot be opened, it prints an error message and calls exit(1).
// NOTE:     You MUST use the strcmp_eecs280 function (NOT strcmp).
bool find_word(const string &query){
  // Open words.txt file for reading
  ifstream fin("words.txt");

  if (!fin.is_open()) {
    cout << "Couldn't open 'words.txt'" << endl;
    exit(1);
  }

  string word;
  while (fin >> word) {
    // If word is equal to query (strcmp == 0), return true
    if (strcmp_eecs280(query.c_str(), word.c_str()) == 0) {
      return true;
    }
  }

  // If not found, return false
  return false;
}


/******************************* TESTING CODE *******************************/

void test_strcmp_eecs280() {
  assert(strcmp_eecs280("turtle", "frog") > 0);
  assert(strcmp_eecs280("turtle", "turtles") < 0);
  assert(strcmp_eecs280("", "frog") < 0);
  assert(strcmp_eecs280("lizard", "lizard") == 0);
}

int main(){
  test_strcmp_eecs280();

  cout << "Welcome to eecs280 spell checker!" << endl;
  cout << "You may quit at any time by typing \"quit\"." << endl;

  string user_word = get_user_word();

  while (user_word != "quit"){

    if (find_word(user_word)) {
      cout << "It appears " << user_word << " is spelled correctly!" << endl;

    } else {
      cout << "Oops. " << user_word << " is not correctly spelled." << endl;
    }

    user_word = get_user_word();
  }

  cout << "See you again soon. Happy spelling!" << endl;

  return 0;
}
