//Project Identifier: 01BD41C3BF016AD7E8B6F837DF18926EC3E83350

#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <iostream>
#include <algorithm> // sort
#include <getopt.h>
#include <string>    // needed for VS
#include <queue>
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;

struct Entry{
    int entryID;
    string timestamp;
    string category;
    string message;
    uint64_t time;
};


class TimestampCompare {
public:
    bool operator() (const Entry* left, const uint64_t right) {
        return left->time < right;
    }
};

class TimestampCompare2 {
public:
    bool operator() (const uint64_t left, const Entry* right) {
        return left < right->time;
    }
};

class TimestampPtrCompare{
    public:
    bool operator() (const Entry* left, const Entry* right){
        return left->time < right->time;
    }
};

struct EntryCompare {
    bool operator() (const Entry left, const Entry right) {
        
        if(left.time == right.time){
            string lc = left.category;
            transform(lc.begin(), lc.end(), lc.begin(),::tolower);
            string rc = right.category;
            transform(rc.begin(), rc.end(), rc.begin(),::tolower);
            if(lc == rc){
                return left.entryID < right.entryID;
            }
            return lc < rc;
        }
        return left.time < right.time;
    }
};

struct EntryPtrCompare {
    bool operator() (const Entry* left, const Entry* right) {
        
        if(left->time == right->time){
            string lc = left->category;
            transform(lc.begin(), lc.end(), lc.begin(),::tolower);
            string rc = right->category;
            transform(rc.begin(), rc.end(), rc.begin(),::tolower);
            if(lc == rc){
                return left->entryID < right->entryID;
            }
            return lc < rc;
        }
        return left->time < right->time;
    }
};

class Logger {
public:
    void get_options(int argc, char** argv);
    void read_data();
    bool command(string c);
    void search(string c);
    void excerpt(string c);
    void output(char c);
    bool misc(char c);
    vector<string> getKeywords(string c);
    //void sortExcerptList();
    //size_t partition(size_t left, size_t right);
    //void sortRecentList(/*size_t left, size_t right*/);
    //size_t rpartition(size_t left, size_t right);
    void printEntry(Entry e);
    vector<Entry> master;
    //map<size_t, vector<int>> timestampsorted;
    unordered_map<string,vector<int>> keywordsorted;
    void makeSorted();
    //void addCats();
    //void addTimes(int e);
    size_t hash(string t);
    unordered_map<string,vector<int>> categorysorted;
    
    vector<int> recentsearch;
    deque<int> excerptlist;

    ~Logger();
private:
    int count;
    string filename;
    int mastersize;
    bool searchOccurred;
};

#endif