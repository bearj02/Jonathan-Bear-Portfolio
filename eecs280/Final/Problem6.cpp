#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

struct City {
  string name;
  int population;
};

class LargePopulation{
    public:
    LargePopulation(int minPop_in) : minPop(minPop_in) {}

    bool operator()(City c) const{
        return c.population > minPop;
    }

    private:
    int minPop;
};

// REQUIRES: Iterator supports the *, ->, (prefix) ++, ==, and != operators.  
//           begin points to the first City to check
//           end points 1 past the last City to check
//           pred takes one argument of type City and returns a bool
// EFFECTS:  Returns a vector of names of cities in the container for 
//           which pred returns true
template <typename Iterator, typename Pred>
vector<string> city_checker(Iterator begin, Iterator end, Pred pred){
    vector<string> cities;
    for(Iterator i = begin; i != end; ++i){
        if(pred(*i)) cities.push_back((*i).name);
    }
    return cities;
}

// EFFECTS: Prints the names of cities in the vector cities which 
//          have populations larger than the population of compare.
//          Each city name should be followed by a space, including 
//          the final name.
void large_cities(const vector<City> &cities, const City &compare) {
    LargePopulation LPCompare(compare.population);
    vector<string> cityNames = city_checker(cities.begin(),cities.end(),LPCompare);
    for(auto i = cityNames.begin(); i != cityNames.end(); ++i){
        cout << *i << " ";
    }
}

int main(){
    City c1{"Minneapolis",200};
    City c2{"Detroit",400};
    City c3{"Newark",100};
    vector<City> cities;
    cities.push_back(c1);
    cities.push_back(c2);
    cities.push_back(c3);
    City c{"Default",350};
    large_cities(cities,c);
    cout << endl;
}