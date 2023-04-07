#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

struct Application {
  int memoryUsed; // Size of application on disk in bytes
  string name;
};

class Smartphone {
public:
  // The maximum number of apps allowed to be stored on a Smartphone
  static const int MAX_APPS = 200;

  // The number of apps installed on this Smartphone
  int numApps;

  // Fixed size array of pointers to dynamically allocated Applications.
  Application *apps[MAX_APPS];

public:
  Smartphone() : numApps(0) {}

  // EFFECTS: Deep copies resources from other.
  Smartphone(const Smartphone &other);

  // EFFECTS: Frees resources.
  ~Smartphone(){
      /*for(int i = 0; i < numApps; ++i){
        delete apps[i];
    }*/
  }

  // EFFECTS: Deep copies resources from rhs.
  Smartphone &operator=(const Smartphone &rhs){
    if(this == &rhs){
        return *this;
    }
    numApps = rhs.numApps;
    for(int i = 0; i < numApps; ++i){
        apps[i] = rhs.apps[i];
    }
    return *this;
  }

  void push_back(Application app){
      apps[numApps++] = &app;
  }
};

int main(){
    Application apps[2];
    apps[0] = Application{200,"Flappy Bird"};
    apps[1] = Application{400,"Angry Birds"};
    Smartphone sp;
    sp.push_back(apps[0]);
    sp.push_back(apps[1]);
    Smartphone sp2;
    sp2.push_back(apps[1]);
    sp2.push_back(apps[0]);
    cout << (sp2.apps[0])->name << endl;
    sp2 = sp;
    cout << (sp2.apps[0])->name << endl;
    //delete &sp;
    //delete &sp2;
    int *x = new int(2);
    int *z = new int(4);
    z = new int(5);
    delete x;
    x = z;
    cout << *x << " " << *z << endl;
    delete z;
    //delete x;
}