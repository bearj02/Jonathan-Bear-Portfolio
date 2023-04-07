#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

struct Activity {
    string name;
    bool completed;
    unsigned int priority; // higher value = higher priority, positive value
};

// REQUIRES: act_ptr points to an Activity object
// MODIFIES: *act_ptr
// EFFECTS:  Initializes an activity with given name and priority.
//           Activities start uncompleted
void Activity_init(Activity *act_ptr, string name_in, int priority_in);

// REQUIRES: act_ptr points to a valid Activity object
// MODIFIES: *act_ptr
// EFFECTS:  Changes activity to have new priority
void Activity_change_priority(Activity *act_ptr, int new_priority);

// REQUIRES: act_ptr points to a valid Activity object
// MODIFIES: *act_ptr
// EFFECTS:  Sets *act_ptr to have been completed
void Activity_set_completion_status(Activity *act_ptr);

// REQUIRES: act_ptr points to a valid Activity object
// EFFECTS:  Returns if the Activity has been completed
bool Activity_is_completed(const Activity *act_ptr);

// REQUIRES: act_ptr points to a valid Activity object
// EFFECTS:  Returns name of the activity
string Activity_name(const Activity *act_ptr);

// REQUIRES: act_ptr points to a valid Activity object
// EFFECTS:  Returns the Activity's priority
int Activity_priority(const Activity *act_ptr);

const int MAX_ACTIVITIES = 50;

struct BucketList {
    int num_activities;
    Activity list[MAX_ACTIVITIES];
};

// REQUIRES:    b_in points to a BucketList object
// MODIFIES:    *b_in
// EFFECTS:     Initializes a BucketList object with num_activities set to 0
void BucketList_init(BucketList *b_in);

// REQUIRES:    b_in points to a valid BucketList object with fewer than 
//              MAX_ACTIVITIES activities
// MODIFIES:    *b_in
// EFFECTS:     Adds Activity to end of list, increments num_activities 
void BucketList_add_activity(BucketList *b_in, Activity act) {
    b_in->list[b_in->num_activities] = act;
    ++b_in->num_activities;
}

// REQUIRES:    b_in points to a valid BucketList object
// EFFECTS:     Returns the number of activities in list that are not complete.
int BucketList_count_incomplete(const BucketList *b_in) {
    int numIncomplete = 0;
    for(const Activity* ptr = b_in->list; ptr < (b_in->list + b_in->num_activities); ++ptr){
        if(!Activity_is_completed(ptr)){
            numIncomplete++;
        }
    }
    return numIncomplete;
}

// REQUIRES:    b_in points to a valid BucketList object
//              *b_in contains exactly one Activity with name act_name
//              *b_in does not contain any duplicate activities
// MODIFIES:    *b_in
// EFFECTS:     Sets the activity of the given name to completed.
void BucketList_complete_activity(BucketList *b_in, string act_name) {
    for(Activity* ptr = b_in->list; ptr < (b_in->list + b_in->num_activities); ++ptr){
        if(Activity_name(ptr) == act_name){
            Activity_set_completion_status(ptr);
        }
    }
}

// REQUIRES:    b_in points to a valid BucketList object
//              b_in contains at least one incomplete activity,
//              and no activities have equal priority
// EFFECTS:     Returns the incomplete activity with the highest priority 
Activity BucketList_find_highest_priority(BucketList *b_in) {
    Activity hp;
    bool foundstart = false;
    for(Activity* ptr = b_in->list; ptr < (b_in->list + b_in->num_activities); ++ptr){
        if(!foundstart && !Activity_is_completed(ptr))
            hp = *ptr;
        if(foundstart && !Activity_is_completed(ptr) && Activity_priority(ptr) > Activity_priority(&hp))
            hp = *ptr;
    }
    return hp;
}

int main() {
    
}