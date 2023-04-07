#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

// Zoom struct
struct Zoom {
    int meeting_id; 
    string meeting_name; 
    string participants_list[100];
    int number_of_participants;
};

// REQUIRES: z points to a valid Zoom meeting.
//           z->number_of_participants > 0;
//           arr points to a valid array of MAX_NUM_ATTENDEES strings
// MODIFIES: *arr
// EFFECTS:  Stores the names of the first x
//           students in the meeting (i.e. the first x names on the 
//           participants_list) in arr
//           If x > z->number_of_participants, stores all of the
//           students on the participants_list.
//           Returns the number participants stored in arr

// EXAMPLE
// [Zoom z initialized to {1, "eecs280_oh", {"christina", "jon", "nicole", "sofia"}, 4} ]
// string arr[MAX_NUM_ATTENDEES];
// Zoom_first_x_students(&z, 2, arr);
// [returns 2, stores {"christina", "jon"} into arr]
int Zoom_first_x_students(const Zoom * z, int x, string *arr) {
    int numToStore = x;
    if(x > z->number_of_participants){
        numToStore = z->number_of_participants;
    }

    for(string* ptr = arr; ptr < (arr + numToStore); ++ptr){
        *ptr = *(z->participants_list + (ptr - arr));
    }
    return numToStore;
}

int main() {
    Zoom z = {1, "eecs280_oh", {"christina", "jon", "nicole", "sofia"}, 4};
    string arr[100];
    int i = Zoom_first_x_students(&z, 2, arr);
    cout << i << endl;
    for(int a = 0; a < i; a++){
        cout << arr[a] << endl;
    }
}