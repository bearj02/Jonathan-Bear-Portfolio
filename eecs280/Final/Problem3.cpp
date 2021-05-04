#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

// REQUIRES: JewelType has public members:
//              string color;
//              double value;
template <typename JewelType>
class TreasureChest {
private:
    string location;
    vector<JewelType> jewels;

public:
    // Assume any member functions we ask you to  
    // implement are declared correctly here

    // EFFECTS: returns the number of jewels in the treasure chest
    size_t count();

    // EFFECTS: returns the value of all jewels in the treasure chest
    double value();
};

struct Amethyst {
    string color = "violet";
    double value = 5.0;
};

// EFFECTS: returns the number of jewels in the treasure chest
template <typename JewelType>
size_t TreasureChest<JewelType>::count(){
    return jewels.size();
}

// EFFECTS: returns the value of all jewels in the treasure chest
template <typename JewelType>
double TreasureChest<JewelType>::value(){
    double sum = 0;
    for(auto i = jewels.begin(); i != jewels.end(); ++i){
        sum += (*i).value;
    }
    return sum;
}

class EECS280{
    public:
        struct Student{
            string uniqname;
            string favProjectName;
            bool inEECS203;
            Student * next;
            Student * prev;
        };
    private:
        Student * first;
        Student * last;
};

int main(){
    return 0;
}