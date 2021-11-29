//Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A

#include <vector>
#include <iostream>
#include <getopt.h>
#include <string>    
#include <deque>

#include "Ship.h"


/*
Notes:
- run on perf when you get a chance
- figure out what that one invalid map row error is due to
- figure out one more test case
- figure out how to use less memory
*/

using namespace std;

void Ship::get_options(int argc, char** argv) {
    int option_index = 0, option = 0;

    opterr = false;

    struct option longOpts[] = { 
        { "help", no_argument, nullptr, 'h' },
        {"output", required_argument, nullptr, 'o'},
        {"stack", no_argument, nullptr, 's'},
        {"queue", no_argument, nullptr, 'q'},
        { nullptr, 0, nullptr, '\0' } };

    bool routing_chosen = false;
    while ((option = getopt_long(argc, argv, "ho:sq", longOpts, &option_index)) != -1) {
        switch (option) {
        case 'o':
            output = *optarg;
            break;
        case 's':
            if (routing_chosen) {
                cerr << "Multiple routing modes specified" << endl;
                exit(1);
            }
            routing = 's';
            routing_chosen = true;
            break;
        case 'q':
            if (routing_chosen) {
                cerr << "Multiple routing modes specified" << endl;
                exit(1);
            }
            routing = 'q';
            routing_chosen = true;
            break;

        case 'h':
            cout << "Usage: \'./ship\n\t[--stack | -s]\n"
                << "\t[--queue | -q]\n"
                << "\t[--output | -o] <M for Map or L for List>\n"
                << "\t[--help | -h]\n"
                << "\t < input file > output file \'" << endl;
            exit(0);
        }
    }

    if (!output) output = 'm';
    if (!routing) {
        cerr << "No routing mode specified" << endl;
        exit(1);
    }
    if (output != 'M' && output != 'm' && output != 'L' && output != 'l') {
        cerr << "Invalid output mode specified" << endl;
        cerr << "   Invalid output mode is: " << output << endl;
        exit(1);
    }

}

void Ship::read_data() {

    string coord;
    char input_mode = '\0';

    cin >> input_mode >> ws;
    cin >> num_levels >> ws;
    cin >> level_size >> ws;

    coords.resize(num_levels, vector<vector<p>>(level_size, vector<p>(level_size)));

    if (input_mode == 'L') {

        while (cin >> coord) {
            if (coord[0] == '/' && coord[1] == '/') {
                cin >> coord >> ws;
                continue;
            }
            if (coord[0] == '(') {
                coord = coord.substr(1, coord.size() - 2);

                int level = stoi(coord.substr(0, coord.find(',')));
                coord = coord.substr(coord.find(',') + 1);
                int row = stoi(coord.substr(0, coord.find(',')));
                coord = coord.substr(coord.find(',') + 1);
                int column = stoi(coord.substr(0, coord.find(',')));
                coord = coord.substr(coord.find(',') + 1);
                char value = coord[0];

                if (level >= num_levels) {
                    cerr << "Invalid map level" << endl;
                    cerr << "   Invalid level is: " << level << endl;
                    exit(1);
                }
                if (row >= level_size) {
                    cerr << "Invalid map row" << endl;
                    cerr << "   Invalid row is: " << row << endl;
                    exit(1);
                }
                if (column >= level_size) {
                    cerr << "Invalid map column" << endl;
                    cerr << "   Invalid column is: " << column << endl;
                    exit(1);
                }
                if (value != '.' && value != '#' && value != 'S' && value != 'H' && value != 'E') {
                    cerr << "Invalid map character" << endl;
                    cerr << "   Invalid character is: " << value << endl;
                    exit(1);
                }
                if (value == 'S') {
                    start_level = level;
                    start_row = row;
                    start_column = column;
                }

                coords[level][row][column].map = value;
            }
        }

        fillMap();
    }

    if (input_mode == 'M') {
        int level = 0;
        int row = 0;
        while (getline(cin, coord)) {
            if (coord[0] == '/' && coord[1] == '/') {
                continue;
            }
            if (row == level_size) {
                level++;
                row = 0;
            }
            for (size_t column = 0; column < coord.size(); column++) {
                if (level >= num_levels) {
                    cerr << "Invalid map level" << endl;
                    cerr << "   Invalid level is: " << level << endl;
                    exit(1);
                }
                if (static_cast<int>(column) >= level_size) {
                    cerr << "Invalid map column" << endl;
                    cerr << "   Invalid column is: " << column << endl;
                    exit(1);
                }
                if (row >= level_size) {
                    cerr << "Invalid map row" << endl;
                    cerr << "   Invalid row is: " << row << endl;
                    exit(1);
                }
                if (coord[column] != '.' && coord[column] != '#' && coord[column] != 'S' && coord[column] != 'H' && coord[column] != 'E') {
                    cerr << "Invalid map character" << endl;
                    cerr << "   Invalid character is: " << coord[column] << endl;
                    exit(1);
                }
                if (coord[column] == 'S') {
                    start_level = level;
                    start_row = row;
                    start_column = static_cast<int>(column);
                }
                coords[level][row][column].map = coord[column];
            }
            row++;

        }
    }
}

void Ship::fillMap() {
    for (size_t l = 0; l < coords.size(); l++) {
        for (size_t r = 0; r < coords[l].size(); r++) {
            for (size_t c = 0; c < coords[l][r].size(); c++) {
                if (coords[l][r][c].map == '\0') coords[l][r][c].map = '.';
            }
        }
    }
}

void Ship::printMap() {
    cout << "Start in level " << start_level << ", row " << start_row << ", column " << start_column << "\n";
    for (size_t l = 0; l < coords.size(); l++) {
        cout << "//level " << l << "\n";
        for (size_t r = 0; r < coords[l].size(); r++) {
            for (size_t c = 0; c < coords[l][r].size(); c++) {
                cout << coords[l][r][c].map;
            }
            cout << "\n";
        }
    }
}

void Ship::run() {
    if (routing == 's') {
        stackPath();
    }
    if (routing == 'q') {
        queuePath();
    }
}

void Ship::backtrace(int level, int row, int column) {
    if (output == 'l' || output == 'L') {
        deque<string> path;
        while (level != start_level || row != start_row || column != start_column) {
            if (coords[level][row][column].into == 'n') {
                path.push_front("(" + to_string(level) + "," + to_string(row + 1) + "," + to_string(column) + ",n)");
                row++;
            }
            else if (coords[level][row][column].into == 'e') {
                path.push_front("(" + to_string(level) + "," + to_string(row) + "," + to_string(column - 1) + ",e)");
                column--;
            }
            else if (coords[level][row][column].into == 's') {
                path.push_front("(" + to_string(level) + "," + to_string(row - 1) + "," + to_string(column) + ",s)");
                row--;
            }
            else if (coords[level][row][column].into == 'w') {
                path.push_front("(" + to_string(level) + "," + to_string(row) + "," + to_string(column + 1) + ",w)");
                column++;
            }
            else {
                string direction = "";
                direction += coords[level][row][column].into;
                path.push_front("(" + direction + string(",") + to_string(row) + "," + to_string(column) + "," + to_string(level) + ")");
                level = coords[level][row][column].into - '0';

            }
        }
        cout << "//path taken" << "\n";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << "\n";
        }
    }
    if (output == 'm' || output == 'M') {
        
        while (level != start_level || row != start_row || column != start_column) {
            if (coords[level][row][column].into == 'n') {
                coords[level][row + 1][column].map = 'n';
                row++;
            }
            else if (coords[level][row][column].into == 'e') {
                coords[level][row][column - 1].map = 'e';
                column--;
            }
            else if (coords[level][row][column].into == 's') {
                coords[level][row - 1][column].map = 's';
                row--;
            }
            else if (coords[level][row][column].into == 'w') {
                coords[level][row][column + 1].map = 'w';
                column++;
            }
            else {
                coords[coords[level][row][column].into - '0'][row][column].map = (char)('0' + level);
                level = coords[level][row][column].into - '0';

            }
        }
        printMap();
    }
}

void Ship::investigate(int level, int row, int column) {
    //north
    if (row != 0) {
        if (coords[level][row - 1][column].into == '\0' && coords[level][row - 1][column].map != '#') {
            search_container.push_back({ level, row - 1, column });
            coords[level][row - 1][column].into = 'n';
        }
    }
    //east
    if (column < level_size - 1) {
        if (coords[level][row][column + 1].into == '\0' && coords[level][row][column + 1].map != '#') {
            search_container.push_back({ level, row, column + 1 });
            coords[level][row][column + 1].into = 'e';
        }
    }
    //south
    if (row < level_size - 1) {
        if (coords[level][row + 1][column].into == '\0' && coords[level][row + 1][column].map != '#') {
            search_container.push_back({ level, row + 1, column });
            coords[level][row + 1][column].into = 's';
        }
    }
    //west
    if (column != 0) {
        if (coords[level][row][column - 1].into == '\0' && coords[level][row][column - 1].map != '#') {
            search_container.push_back({ level, row, column - 1 });
            coords[level][row][column - 1].into = 'w';
        }
    }
    //elevator
    if (coords[level][row][column].map == 'E') {
        for (int l = 0; l < num_levels; l++) {
            if (coords[l][row][column].map == 'E' && coords[l][row][column].into == '\0') {
                search_container.push_back({ l, row, column });
                coords[l][row][column].into = (char)('0' + level);
            }
        }
    }
}

void Ship::stackPath() {
    search_container.push_back({ start_level, start_row, start_column });
    //direction_into.resize(num_levels, vector<vector<char>>(level_size, vector<char>(level_size)));
    bool isSolution = false;
    while (!search_container.empty()) {

        int current_level = search_container.back().l;
        int current_row = search_container.back().r;
        int current_column = search_container.back().c;

        search_container.pop_back();

        if (coords[current_level][current_row][current_column].map == 'H') {
            isSolution = true;
            backtrace(current_level, current_row, current_column);
            break;
        }
        investigate(current_level, current_row, current_column);
    }
    if (!isSolution) {
        if (output == 'm' || output == 'M') printMap();
        else cout << "//path taken";
    }
}

void Ship::queuePath() {
    search_container.push_back({ start_level, start_row, start_column });
    //direction_into.resize(num_levels, vector<vector<char>>(level_size, vector<char>(level_size)));
    bool isSolution = false;
    while (!search_container.empty()) {
        
        int current_level = search_container.front().l;
        int current_row = search_container.front().r;
        int current_column = search_container.front().c;

        search_container.pop_front();

        if (coords[current_level][current_row][current_column].map == 'H') {
            isSolution = true;
            backtrace(current_level, current_row, current_column);
            break;
        }
        investigate(current_level, current_row, current_column);
    }
    if (!isSolution) {
        if (output == 'm' || output == 'M') printMap();
        else cout << "//path taken";
    }
}

int main(int argc, char** argv) {

    //TO DO:
    /*
    1. Read File in
    2. Put coords in 3D vector: level, row, column
    */

    ios_base::sync_with_stdio(false);

    try {
        Ship spaceship;
        spaceship.get_options(argc, argv);
        spaceship.read_data();
        spaceship.run();
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