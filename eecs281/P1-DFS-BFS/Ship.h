//Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A

#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <iostream>
#include <algorithm> // sort
#include <getopt.h>
#include <string>    // needed for VS
#include <deque>

struct p {
    char map;
    char into;
};

struct c {
    int l;
    int r;
    int c;
};

class Ship {
public:
    void read_data();

    void get_options(int argc, char** argv);

    void run();

    void printMap();

    void investigate(int level, int row, int column);

    void backtrace(int level, int row, int column);

    //bool validateEntry(int level, int row, int column, char value);
private:
    std::vector<std::vector<std::vector<p>>> coords;
    char routing = '\0';
    char output = '\0';
    void fillMap();
    void stackPath();
    void queuePath();
    int start_level = 0;
    int start_row = 0;
    int start_column = 0;
    int num_levels = 0;
    int level_size = 0;
    std::deque<c> search_container;
    //std::vector<std::vector<std::vector<char>>> direction_into;
};

#endif