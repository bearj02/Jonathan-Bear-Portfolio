#ifndef LAB03_H
#define LAB03_H

#include <string>
#include <vector>

// REQUIRES: str1 and str2 point to C-strings
// EFFECTS:  If str1 and str2 contain exactly the same characters, returns 0.
//           Otherwise, return a positive number if the first differing char
//           has a greater value in str1 than in str2 and a negative number in
//           the opposite case (you may NOT call strcmp).
// NOTE:     You should implement this without using cstring library functions.
int strcmp_eecs280(const char *str1, const char *str2);

// EFFECTS:  Prints "Please enter a word: " to prompt the user to enter a word
//           and then reads a word from cin to be returned. After reading the
//           input, clean up by printing a newline to cout.
std::string get_user_word();

// EFFECTS: Opens the given file and returns a vector containing all the words
//          in the file. If the file cannot be opened, prints an error message
//          and returns an empty vector.
std::vector<std::string> read_words_from_file(const std::string &filename);

// EFFECTS:  Returns true if the given word is contained in the vector of valid
//           words.
// NOTE:     You MUST use the strcmp_eecs280 function (NOT strcmp).
//           You should implement this without using cstring library functions.
bool find_word(const char *word, const std::vector<std::string> &valid_words);

#endif /* LAB03_H */
