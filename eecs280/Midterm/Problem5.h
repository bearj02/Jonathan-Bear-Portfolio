#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class Instrument {
    int volume;
    bool tuned;

public:
    Instrument(bool isTuned_in, int volume_in);
    virtual void play() = 0;
    bool isTuned() const { return tuned; }
    virtual int getVolume() const { return volume; }
};

class Brass : public Instrument {
    int num_times_played = 0;

public:
    Brass(bool isTuned_in, int volume_in);

    void play() override {
        num_times_played++;
        cout << "Careless whisper" << endl;
    }

    int getVolume() const override {
        if (num_times_played > 2) {
            return Instrument::getVolume() * 2;
        }
        return Instrument::getVolume() / 2;
    }
};

class Strings : public Instrument {
    int numStrings;

public:
    Strings(bool isTuned_in, int volume_in, int numStrings_in);

    void play() override {
        cout << "Twang" << endl;
    }

    int getVolume() const override {
        return Instrument::getVolume() * numStrings;
    }
};

class Band {
    vector<Instrument *> ensemble;
    const int MAX_VOLUME = 100;

public:
    bool soundsGood();
    void add_instrument(Instrument *i) { ensemble.push_back(i); }
};