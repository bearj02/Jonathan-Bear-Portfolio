#include <iostream>
#include <cassert>
#include "lab03.h"

using namespace std;

int main() {
  // Test strcmp_eecs280
  assert(strcmp_eecs280("turtle", "frog") > 0);
  assert(strcmp_eecs280("turtle", "turtles") < 0);
  assert(strcmp_eecs280("", "frog") < 0);
  assert(strcmp_eecs280("lizard", "lizard") == 0);

  // Spellchecker
  cout << "Welcome to eecs280 spell checker!" << endl;
  cout << "You may quit at any time by typing \"quit\"." << endl;

  vector<string> valid_words = read_words_from_file("words.txt");
  string user_word;

  while ((user_word = get_user_word()) != "" && user_word != "quit") {

    if (find_word(user_word.c_str(), valid_words)) {
      cout << "It appears " << user_word << " is spelled correctly!" << endl;

    } else {
      cout << "Oops. " << user_word << " is not correctly spelled." << endl;
    }
  }

  cout << "See you again soon. Happy spelling!" << endl;

  return 0;
}
