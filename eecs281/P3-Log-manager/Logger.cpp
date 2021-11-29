//Project Identifier: 01BD41C3BF016AD7E8B6F837DF18926EC3E83350

#include <vector>
#include <iostream>
#include <fstream>
#include <string>    
#include <queue>
#include <unordered_map>

#include "Logger.h"

/*
Notes:

*/

using namespace std;

Logger::~Logger(){}

void Logger::get_options(int argc, char** argv) {
    if(argc < 2){
        cout << "No argument specified\n";
        exit(1);
    }
    string f = argv[1];
    if(f.compare("-h") == 0 || f.compare("--help") == 0){
        cout << "Usage: \'./logman [LOGFILE]\n"
            << "\t[--help | -h]\n"
            << "\t < command input file > output file \'" << endl;
        exit(0);
    }
    filename = f;
}

void Logger::read_data() {
    mastersize = 0;
    searchOccurred = false;
    ifstream log (filename, ifstream::in);
    string timestamp;
    string category;
    string message;
    while(getline(log,timestamp,'|')){
        getline(log,category,'|');
        getline(log,message);
        int entryID = mastersize;
        size_t time = hash(timestamp);
        master.push_back({entryID,timestamp,category,message,time});
        mastersize++;
    }
    if(log.eof()){
        cout << mastersize << " entries read\n";
    }
    else{
        cout << "Error reading logfile\n";
    }
    log.close();
    sort(master.begin(),master.end(),EntryCompare{});
    makeSorted();
    //addKeys();
    //addCats();
    //addTimes();
}

void Logger::makeSorted(){
    for(int e = 0; e < (int)master.size(); ++e){
        string cat = master[e].category;
        transform(cat.begin(),cat.end(),cat.begin(),::tolower);
        categorysorted[cat].push_back(e);
        string text = cat + " " + master[e].message;
        vector<string> unique_keys = getKeywords(text);
        for(string k : unique_keys){
            keywordsorted[k].push_back(e);
        }
    }
}

/*void Logger::addCats(){
    
    
    
}*/

/*void Logger::addTimes(int e){
    timestampsorted[master[e].time].push_back(e);
}*/

size_t Logger::hash(string t){
    string s = "";
    s += t[0];
    s += t[1];
    s += t[3];
    s += t[4];
    s += t[6];
    s += t[7];
    s += t[9];
    s += t[10];
    s += t[12];
    s += t[13];
    return stoul(s);
}

void Logger::printEntry(Entry e){
    cout << e.timestamp << '|';
    cout << e.category << '|';
    cout << e.message << '\n';
}

bool Logger::command(string c){
    //q
    //#
    if(c[0] == 'q' || c[0] == '#'){
        return misc(c[0]);
    }
    
    //t
    //m
    //c
    //k
    if(c[0] == 't' || c[0] == 'm' || c[0] == 'c' || c[0] == 'k'){
        search(c);
        searchOccurred = true;
        return true;
    }
    //a
    //r
    //d
    //b
    //e
    //s
    //l
    else if(c[0] == 'a' || c[0] == 'r' || c[0] == 'd' || c[0] == 'b' || c[0] == 'e' || c[0] == 's' || c[0] == 'l'){
        excerpt(c);
        return true;
    }
    //g
    //p
    else if(c[0] == 'g' || c[0] == 'p'){
        output(c[0]);
        return true;
    }
    
    else{
        cerr << "Invalid command";
    }
    return true;
}

void Logger::search(string c){
    //timestamps
    if(c[0] == 't'){
        int dividerpos = (int)c.find('|');
        if(dividerpos != 16){
            cerr << "Invalid divider position";
            return;
        }
        string t1 = c.substr(2,14);
        string t2 = c.substr(17,14);
        if(t1.size()!= 14 || t2.size() != 14){
            cerr << "Invalid timestamp format";
            return;
        }
        count = 0;
        recentsearch.clear();
        size_t low = hash(t1);
        size_t high = hash(t2);
        int index = 0;
        while(index < (int)master.size() && master[index].time < low) ++index;
        while(index < (int)master.size() && master[index].time <= high){
            recentsearch.push_back(index);
            ++count;
            ++index;
        }
        cout << "Timestamps search: " << count << " entries found\n";
    }
    //matching
    if(c[0] == 'm'){
        string t = c.substr(2,14);
        count = 0;
        recentsearch.clear();
        if(t.size()!= 14){
            cerr << "Invalid timestamp format";
            return;
        }
        count = 0;
        recentsearch.clear();
        size_t low = hash(t);
        int index = 0;
        while(index < (int)master.size() && master[index].time < low) ++index;
        while(index < (int)master.size() && master[index].time <= low){
            recentsearch.push_back(index);
            ++count;
            ++index;
        }
        cout << "Timestamp search: " << count << " entries found\n";
    }
    //category
    if(c[0] == 'c'){
        string cat = c.substr(2);
        transform(cat.begin(), cat.end(), cat.begin(),::tolower);
        count = (int)categorysorted[cat].size();
        recentsearch.clear();
        recentsearch = categorysorted[cat];
        cout << "Category search: " << count << " entries found\n";

    }
    //keyword
    if(c[0] == 'k'){
        //int count = 0;
        recentsearch.clear();
        vector<string> keywords = getKeywords(c.substr(2));
        //keywords.push_back("#");
        /*for(string k : keywords){
            cout << k << ":\t";
            for(int i : keywordsorted[k]){
                cout << i << " ";
            }
            cout << "\n";
        }*/
        if(keywords.size() == 1){
            recentsearch = keywordsorted[keywords[0]];
        }
        else if (keywords.size() > 1){
            vector<int> temp = keywordsorted[keywords[0]];
            if(temp.size() != 0){
                for(size_t i = 1; i < keywords.size(); ++i){
                    vector<int> temp2 = keywordsorted[keywords[i]];
                    if(temp2.size() == 0){
                        temp.clear();
                        break;
                    }
                    vector<int> result;
                    set_intersection(temp.begin(), temp.end(), temp2.begin(), temp2.end(), back_inserter(result));
                    temp = result;
                    if(temp.size() == 0) break;
                }
                recentsearch = temp;
            }
        }
        count = (int)recentsearch.size();
        cout << "Keyword search: " << count << " entries found\n";
    }
}

vector<string> Logger::getKeywords(string c){
    vector<string> ks;
    string a;
    for(char b : c){
        
        if(isalnum(b)){
            b = (char)tolower(b);
            a.push_back(b);
            
        }
        else if(a.size() > 0){
            if(find(ks.begin(),ks.end(),a) == ks.end())
            ks.push_back(a);
            a.clear();
        }
    }
    if(a.size() > 0 && find(ks.begin(),ks.end(),a) == ks.end()) ks.push_back(a);
    return ks;
}

void Logger::excerpt(string c){
    //append entry
    if(c[0] == 'a'){
        int i = stoi(c.substr(2));
        if(i >= (int)master.size() || i < 0){
            cerr << "a Index out of bounds";
            return;
        }
        int e = 0;
        while(master[e].entryID != i) ++e;
        excerptlist.push_back(e);
        cout << "log entry " << i << " appended\n";
    }
    //append results
    if(c[0] == 'r'){
        if(!searchOccurred){  
            cerr << "No recent search has occurred";
            return;
        }
        //sortRecentList();
        /*for(int i : recentsearch){
            excerptlist.push_back(i);
        }*/
        excerptlist.insert(excerptlist.end(),recentsearch.begin(),recentsearch.end());
        cout << count << " log entries appended\n";
        //recentsearch.clear();
    }
    //delete entry
    if(c[0] == 'd'){
        int i = stoi(c.substr(2));
        if(i >= (int)excerptlist.size() || i < 0){
            cerr << "d Index out of bounds";
            return;
        }
        excerptlist.erase(excerptlist.begin()+i);
        cout << "Deleted excerpt list entry " << i << "\n";
    }
    //move to beginning
    if(c[0] == 'b'){
        int i = stoi(c.substr(2));
        if(i >= (int)excerptlist.size() || i < 0){
            cerr << "b Index out of bounds";
            return;
        }
        int temp = excerptlist[i];
        excerptlist.erase(excerptlist.begin()+i);
        excerptlist.push_front(temp);
        cout << "Moved excerpt list entry " << i << "\n";
    }
    //move to end
    if(c[0] == 'e'){
        int i = stoi(c.substr(2));
        if(i >= (int)excerptlist.size() || i < 0){
            cerr << "e Index out of bounds";
            return;
        }
        int temp = excerptlist[i];
        excerptlist.erase(excerptlist.begin()+i);
        excerptlist.push_back(temp);
        cout << "Moved excerpt list entry " << i << "\n";
    }
    //sort excerpt list by timestamp
    if(c[0] == 's'){
        cout << "excerpt list sorted\n";
        int l = (int)excerptlist.size() - 1;
        if(l > -1){
            cout << "previous ordering:\n";
            cout << "0|" << master[excerptlist[0]].entryID << '|';
            printEntry(master[excerptlist[0]]);
            cout << "...\n";
            cout << l << '|' << master[excerptlist[l]].entryID << '|';
            printEntry(master[excerptlist[l]]);
            cout << "new ordering:\n";
            sort(excerptlist.begin(),excerptlist.end());
            cout << "0|" << master[excerptlist[0]].entryID << '|';
            printEntry(master[excerptlist[0]]);
            cout << "...\n";
            cout << l << '|' << master[excerptlist[l]].entryID << '|';
            printEntry(master[excerptlist[l]]);
        }
        else{
            cout << "(previously empty)\n";
        }
    }
    //clear excerpt list
    if(c[0] == 'l'){
        cout << "excerpt list cleared\n";
        int l = (int)excerptlist.size() - 1;
        if(l > -1){
            cout << "previous contents:\n";
            cout << "0|" << master[excerptlist[0]].entryID << '|';
            printEntry(master[excerptlist[0]]);
            cout << "...\n";
            cout << l << '|' << master[excerptlist[l]].entryID << '|';
            printEntry(master[excerptlist[l]]);
            excerptlist.clear();
        }
        else{
            cout << "(previously empty)\n";
        }
    }
}

void Logger::output(char c){
    //print most recent search
    if(c == 'g'){
        
        if(!searchOccurred){  
            cerr << "No recent search has occurred";
            return;
        }
        //sortRecentList(/*0,recentsearch.size()*/);
        for(int i : recentsearch){
            cout << master[i].entryID << '|';
            printEntry(master[i]);
        }
    }
    //print excerpt list
    if(c == 'p'){
        for(int i = 0; i < (int)excerptlist.size(); ++i){
            cout << i << '|' << master[excerptlist[i]].entryID << '|';
            printEntry(master[excerptlist[i]]);
        }
    }
}

bool Logger::misc(char c){
    if(c == 'q'){
        return false;
    }
    else{
        return true;
    }
}

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    try {
        Logger search;
        search.get_options(argc, argv);
        search.read_data();
        //search.printEntry(search.master[0]);
        string c;
        getline(cin,c);
        do{
            cout << "% ";
            if(!search.command(c)){
                break;
            }
            if (cin.fail()) {
                cerr << "cin entered fail state: exiting" << endl;
                exit(1);
            } // if
        } while(getline(cin,c));
    }
    catch (runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}