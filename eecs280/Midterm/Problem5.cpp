#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include "Problem5.h"

using namespace std;

Strings::Strings(bool isTuned_in, int volume_in, int numStrings_in) : numStrings(numStrings_in), Instrument(isTuned_in, volume_in) {}

// Return true if all instruments are tuned and the sum of volumes across
// all instruments in the ensemble plays below the maximum volume level
bool Band::soundsGood(){
    int totalVolume = 0;
    for(int i = 0; i < static_cast<int>(ensemble.size()); i++){
        if(!ensemble[i]->isTuned())
            return false;
        totalVolume += ensemble[i]->getVolume();
    }
    if(totalVolume >= MAX_VOLUME)
        return false;
    return true;
}

int main() {
    Brass i(true, 2);
    Band band;
    band.add_instrument(&i);
}