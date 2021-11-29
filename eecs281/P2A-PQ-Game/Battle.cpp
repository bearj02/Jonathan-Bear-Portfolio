//Project Identifier: 9504853406CBAC39EE89AA3AD238AA12CA198043

#include <vector>
#include <iostream>
#include <getopt.h>
#include <string>    
#include <queue>

#include "Battle.h"
#include "P2random.h"


/*
Notes:
- run on perf when you get a chance
- figure out what that one invalid map row error is due to
- figure out one more test case
- figure out how to use less memory
*/

using namespace std;

/*Battle::~Battle(){
    while(deadzombies.size() > 0){
        Zombie* z = deadzombies.back();
        deadzombies.pop_back();
        delete z;
    }
    while(livingzombies.size() > 0){
        Zombie* z = livingzombies.top();
        livingzombies.pop();
        delete z;
    }
}*/

Battle::~Battle(){}

void Battle::get_options(int argc, char** argv) {
    int option_index = 0, option = 0;

    opterr = false;

    struct option longOpts[] = { 
        { "help", no_argument, nullptr, 'h' },
        {"verbose", no_argument, nullptr, 'v'},
        {"statistics", required_argument, nullptr, 's'},
        {"median", no_argument, nullptr, 'm'},
        { nullptr, 0, nullptr, '\0' } };

    printverbose = false;
    printmedian = false;
    printstats = false;
    stats = 0;
    while ((option = getopt_long(argc, argv, "hvs:m", longOpts, &option_index)) != -1) {
        switch (option) {
        case 'v':
            printverbose = true;
            break;
        case 's':
            printstats = true;
            stats = atoi(optarg);
            break;
        case 'm':
            printmedian = true;
            break;

        case 'h':
            cout << "Usage: \'./ship\n\t[--verbose | -v]\n"
                << "\t[--median | -m]\n"
                << "\t[--statistics | -s] <valid positive integer>\n"
                << "\t[--help | -h]\n"
                << "\t < input file > output file \'" << endl;
            exit(0);
        }
    }

    if (printstats && stats <= 0) {
        cerr << "Invalid stats specified" << endl;
        exit(1);
    }
}

void skipLine() {
    char c;
    cin >> noskipws;
    while (cin >> c && c != '\n') {
        continue;
    }
}

int Battle::read_data() {
    numAlive = 0;
    string input = "";
    skipLine();
    cin >> input >> ws;
    cin >> quivercapacity >> ws;
    cin >> input >> ws;
    cin >> randomseed >> ws;
    cin >> input >> ws;
    cin >> maxranddistance >> ws;
    cin >> input >> ws;
    cin >> maxrandspeed >> ws;
    cin >> input >> ws;
    cin >> maxrandhealth >> ws;

    int currentround = 0;
    int randzombies = 0;
    int namedzombies = 0;
    int runround = 1;
    P2random::initialize(randomseed, maxranddistance, maxrandspeed, maxrandhealth);
    while(cin >> input >> ws) {
        if (input.compare("---") == 0) {
            currentround++;
            continue;
        }
        cin >> currentround >> ws;
        game.resize(currentround);
        while(runround < currentround){
            if(!round(runround)){
                return -1;
            }
            ++runround;
        }
        cin >> input >> ws;
        cin >> randzombies >> ws;
        cin >> input >> ws;
        cin >> namedzombies >> ws;
        int i = 0;
        while (i < randzombies) {
            string tname = P2random::getNextZombieName();
            uint32_t tdistance = P2random::getNextZombieDistance();
            uint32_t tspeed = P2random::getNextZombieSpeed();
            uint32_t thealth = P2random::getNextZombieHealth();
            Zombie temp = {
                tname,
                tdistance,
                tspeed,
                thealth,
                0,
                false
            };
            game[currentround - 1].push_back(temp);
            ++i;
        }
        i = 0;
        while (i < namedzombies) {
            string tname;
            uint32_t tdistance;
            uint32_t tspeed;
            uint32_t thealth;
            cin >> tname >> ws;
            cin >> input >> ws;
            cin >> tdistance >> ws;
            cin >> input >> ws;
            cin >> tspeed >> ws;
            cin >> input >> ws;
            cin >> thealth >> ws;
            Zombie temp = { tname, tdistance, tspeed, thealth, 0, false };
            game[currentround - 1].push_back(temp);
            ++i;
        }
        
    }
    if(!round(runround)){
        return -1;
    }
    ++runround;
    return runround;

}

void Battle::Lose() {
    cout << "DEFEAT IN ROUND " << lastround << "! " << outname << " ate your brains!\n";
    if(printstats){
        printStats();
    }
    //delete this;
}

void Battle::Win() {
    cout << "VICTORY IN ROUND " << lastround << "! " << outname << " was the last zombie.\n";
    if(printstats){
        printStats();
    }
    //delete this;
    //exit(0);
}

void Battle::printStats(){
    cout << "Zombies still active: " << numAlive << "\n";
    cout << "First zombies killed:\n";
    int threshold = min(stats,(uint32_t)deadzombies.size());
    int i = 0;
    while(i < threshold){
        cout << deadzombies[i]->name << " " << (i+1) << "\n";
        ++i;
    }
    cout << "Last zombies killed:\n";
    i = 0;
    while(i < threshold){
        cout << deadzombies[deadzombies.size()-(i+1)]->name << " " << (threshold-i) << "\n";
        ++i;
    }
    vector<Zombie*> allzombies;
    int t = min((int)game.size(),lastround);
    for(int i = 0; i < t; ++i){
        for(size_t j = 0; j < game[i].size(); ++j){
            allzombies.push_back(&(game[i][j]));
        }
    }
    priority_queue<Zombie*, vector<Zombie*>, LifetimeGreater> mostactive(allzombies.begin(), allzombies.end());
    priority_queue<Zombie*, vector<Zombie*>, LifetimeLess> leastactive(allzombies.begin(), allzombies.end());
    int t2 = min((uint32_t)allzombies.size(),stats);
    cout << "Most active zombies:\n";
    for(int j = 0; j < t2; ++j){
        Zombie* z = mostactive.top();
        cout << z->name << " " << z->roundsalive << "\n";
        mostactive.pop();
    }
    cout << "Least active zombies:\n";
    for(int j = 0; j < t2; ++j){
        Zombie* z = leastactive.top();
        cout << z->name << " " << z->roundsalive << "\n";
        leastactive.pop();
    }
}

void Battle::PrintZombie(Zombie* z) {
    cout << z->name << " (distance: " << z->distance << ", speed: " << z->speed << ", health: " << z->health << ")\n";
}

bool Battle::round(int cr) {
    lastround = cr;
    if(printverbose){
        cout << "Round: " << cr << "\n";
    }
    uint32_t arrows = quivercapacity;
    bool playerdied = false;
    int threshold = min(cr-1,(int)game.size());
    for (int i = 0; i < threshold; ++i) {
        for (size_t j = 0; j < game[i].size(); ++j) {
            Zombie* z = &(game[i][j]);
            if (!z->isdead) {
                ++z->roundsalive;
                if (z->distance <= z->speed) {
                    z->distance = 0;
                    if(!playerdied){
                        playerdied = true;
                        outname = z->name;
                    }
                }
                else z->distance -= z->speed;
                if(printverbose){
                    cout << "Moved: ";
                    PrintZombie(z);
                }
            }
        }
    }
    if(cr <= (int) game.size() && !playerdied){
        for (size_t i = 0; i < game[cr - 1].size(); ++i) {
            Zombie* z = &(game[cr-1][i]);
            livingzombies.push(z);
            if(printverbose){
                cout << "Created: ";
                PrintZombie(z);
            }
            ++numAlive;
        }
    }
    updateround(cr);
    
    if (playerdied) {
        return false;
    }
    else{
        while (arrows > 0 && livingzombies.size() > 0) {
            Zombie* z = livingzombies.top();
            outname = z->name;
            --(z->health);
            if (z->health == 0) {
                z->isdead = true;
                deadzombies.push_back(z);
                livingzombies.pop();
                --numAlive;
                if(printverbose){
                    cout << "Destroyed: ";
                    PrintZombie(z);
                }
                if(roundshigh.size() == 0) roundshigh.push(z->roundsalive);
                else if(z->roundsalive >= roundshigh.top()){
                    roundshigh.push(z->roundsalive);
                }
                else roundslow.push(z->roundsalive);
                if(roundshigh.size() - roundslow.size() == 2){
                    roundslow.push(roundshigh.top());
                    roundshigh.pop();
                }
                else if(roundslow.size() - roundshigh.size() == 2){
                    roundshigh.push(roundslow.top());
                    roundslow.pop();
                }
                //continue;
            }
            --arrows;
        }
    }
    if(deadzombies.size() > 0 && printmedian) findMedian(cr);
    return true;
}

void Battle::findMedian(int r){
    int median = 0;
    if(roundshigh.size() == roundslow.size()){
        median = (roundshigh.top() + roundslow.top())/2;
    }
    else if(roundshigh.size() > roundslow.size()){
        median = roundshigh.top();
    }
    else median = roundslow.top();
    cout << "At the end of round " << r << ", the median zombie lifetime is " << median << "\n";
}

void Battle::updateround(int r){
    int threshold = min((int)game.size(), r);
    for(int i = 0; i < threshold; ++i){
        for (size_t j = 0; j < game[i].size(); ++j) {
            Zombie* z = &(game[i][j]);
            if(!(z->isdead)){
                z->roundsalive = r - (i);
                //cout << z->name << " has been alive for " << z->roundsalive << " rounds now\n";
            }
        }
    }
    /*priority_queue<Zombie*, vector<Zombie*>, LifetimeGreater> m;
    priority_queue<Zombie*, vector<Zombie*>, LifetimeLess> n;
    while(roundshigh.size() > 0){
        m.push(roundshigh.top());
        n.push(roundslow.top());
        roundshigh.pop();
        roundslow.pop();
    }
    roundshigh = m;
    roundslow = n;*/
    
}

bool Battle::run(int prerounds) {
    int r = prerounds;
    while(livingzombies.size() > 0) {
        if(!round(r)){
            return false;
        }
        ++r;
    }
    return true;
}

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false);

    try {
        Battle apocalypse;
        apocalypse.get_options(argc, argv);
        int prerounds = apocalypse.read_data();
        if(prerounds == -1) apocalypse.Lose();
        else{
            if(!apocalypse.run(prerounds)) apocalypse.Lose();
            else apocalypse.Win();
        }
        //delete &apocalypse;
        //delete[] &apocalypse.game;
    }
    // Catch runtime_errors, print the message, and exit the
    // program with a non-zero status.
    catch (runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }
    // All done!
    return 0;
}