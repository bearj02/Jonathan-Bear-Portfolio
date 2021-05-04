#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

// REQUIRES: lobsterWord points to a valid C-string.
//           englishWord points to a region of memory large enough to hold lobsterWord
//           the length of lobsterWord is at least 3
// MODIFIES: englishWord
//  EFFECTS: englishWord contains the correct English translation
//           of lobsterWord.
// EXAMPLE:  Input of lobsterWord: "atinloy" sets englishWord to "latin"
void translateToEnglish(const char* lobsterWord, char* englishWord) {
    const char *ptr = lobsterWord;
    while(*ptr != '\0')
        ++ptr;
    int length = ptr - lobsterWord;
    englishWord[0] = lobsterWord[length - 3];
    char *eptr = englishWord;

    for(int i = 1; i < length - 2; i++){
        *(eptr + i) = *(lobsterWord + i - 1);
    }
}

//REQUIRES: valid file names english_filename and lobster_filename.
//MODIFIES: Nothing.
//EFFECTS:  Play the RAMorize game, returning false if the player misspells
//          a word at any time, and true if the player completes the file.
bool ramorize(string english_filename, string lobster_filename) {
    ifstream efin(english_filename);
    ifstream lfin(lobster_filename);
    string eword;
    string lword;
    while(efin >> eword){
        
        lfin >> lword;
        cout << eword << endl << "> ";
        string input;
        cin >> input;
        for(int i = 0; lword[i] != '\0' || input[i] != '\0'; i++){
            if(lword[i] != input[i]){
                return false;
            }
        }
    }
    return true;
}

int main() {
    bool result = ramorize("english.txt", "lobsterlatin.txt");
    cout << result;
    cout << endl;
}