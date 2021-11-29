//Project Identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#ifndef BATTLE_H
#define BATTLE_H

#include <vector>
#include <iostream>
#include <algorithm> // sort
#include <getopt.h>
#include <string>    // needed for VS
#include <queue>
#include <vector>

using namespace std;

struct Zombie {
    string name;
    uint32_t distance;
    uint32_t speed;
    uint32_t health;
    int roundsalive;
    bool isdead;
};

class LifetimeGreater {
public:
    bool operator() ( Zombie* left,  Zombie* right) {
        if (left->roundsalive == right->roundsalive) {
            return right->name < left->name;
        }
        else return (left->roundsalive < right->roundsalive);
    }
};

class LifetimeLess {
public:
    bool operator() ( Zombie* left,  Zombie* right) {
        if (left->roundsalive == right->roundsalive) {
            return right->name < left->name;
        }
        else return (left->roundsalive > right->roundsalive);
    }
};

class BattleCompare {
public:
    bool operator() (const Zombie* left, const Zombie* right) {
        int leftETA = left->distance / left->speed;
        int rightETA = right->distance / right->speed;
        if (leftETA == rightETA) {
            if(left->health == right->health){
                return left->name > right->name;
            }
            else return left->health > right->health;
        }
        else return (leftETA > rightETA);
    }
};

class Battle {
public:
    void get_options(int argc, char** argv);
    int read_data();
    bool run(int prerounds);
    bool round(int cr);
    void updateround(int r);
    void Lose();
    void Win();
    void findMedian(int r);
    void printStats();
    priority_queue<Zombie*, vector<Zombie*>, BattleCompare> livingzombies;
    vector<Zombie*> deadzombies;
    priority_queue<int, vector<int>, greater<int>> roundshigh;
    priority_queue<int> roundslow;
    vector<vector<Zombie>> game;
    void PrintZombie(Zombie* z);
    ~Battle();

private:
    uint32_t quivercapacity;
    uint32_t randomseed;
    uint32_t maxranddistance;
    uint32_t maxrandspeed;
    uint32_t maxrandhealth;
    bool printverbose;
    bool printstats;
    uint32_t stats;
    bool printmedian;
    string outname;
    int lastround;
    int numAlive;
};

#endif