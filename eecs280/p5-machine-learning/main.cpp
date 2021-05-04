#include "csvstream.h"
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <cmath>

using namespace std;

class Classifier{
    public:
        Classifier(int nP, map<string, int> w,
        map<string, int> l, map<pair<string,string>, int> wL) : 
        numPosts(nP), words(w), labels(l),
        wordsAndLabels(wL) {}

        int numPosts;
        map<string, int> words;
        map<string, int> labels;
        map<pair<string,string>, int> wordsAndLabels;
};

// EFFECTS: Returns a set containing the unique "words" in the original
//          string, delimited by whitespace.
set<string> unique_words(const string &str) {
 // Fancy modern C++ and STL way to do it
 istringstream source{str};
 return {istream_iterator<string>{source},
         istream_iterator<string>{}};
}

pair<string,double> predictLabel(Classifier* data, set<string> testWords){
    double maxLPS = -1*__DBL_MAX__;
    string maxLPSLabel = "";
    for(auto &l:data->labels){
        double e = double(data->numPosts);
        double numPL = double(l.second);
        double logPrior = log(numPL/e);
        double logPS = logPrior;
        for(auto &s:testWords){
            if(data->wordsAndLabels.find({l.first,s}) != data->wordsAndLabels.end()){
                double countPair = data->wordsAndLabels.at({l.first,s});
                logPS += log(countPair/numPL);
            }
            else if(data->words.find(s) != data->words.end()){
                double countWords = data->words.at(s);
                logPS += log(countWords/e);
            }
            else{
                logPS += log(1/e);
            }
        }
        if(logPS > maxLPS){
            maxLPS = logPS;
            maxLPSLabel = l.first;
        }
    }
    return {maxLPSLabel,maxLPS};
}

void printTestOutput(Classifier* datasets, string filename){
    cout << "test data:" << endl;
    csvstream testData(filename);
    map<string, string> testrow;
    int numCorrect = 0;
    int numPosts = 0;
    while(testData >> testrow){
        numPosts++;
        pair<string,double> predicted = 
            predictLabel(datasets,unique_words(testrow.at("content")));
        cout << "  correct = " <<testrow.at("tag")<< ", predicted = " << predicted.first 
            << ", log-probability score = " << predicted.second << endl;
        cout << "  content = " << testrow.at("content") << endl << endl;
        if(predicted.first == testrow.at("tag")) numCorrect++;
    }
    cout << "performance: " << numCorrect << " / " << numPosts 
        << " predicted correctly" << endl;
}

pair<set<string>,set<string>> allStuff(map<int,map<string,string>> data){
    string allWords;
    string allLabels;
    for(auto i = data.begin(); i != data.end(); ++i){
        allWords += (*i).second.at("content") + " ";
        allLabels += (*i).second.at("tag") + " ";
    }
    set<string> vocab = unique_words(allWords);
    set<string> tags = unique_words(allLabels);

    return {vocab,tags};
}

int main(int argc, char *argv[]){
    bool debug = false;
    if(argc != 3) {if(argc == 4 && string(argv[3]) == "--debug") debug = true;
    else{
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return -1;
    }}
    
    cout.precision(3);
    csvstream trainData((argv[1]));
    map<string, string> row;
    map<int,map<string,string>> data;
    int i = 0;
    while(trainData >> row) data[++i] = row;
    pair<set<string>,set<string>> stuff = allStuff(data);
    set<string> vocab = stuff.first; set<string> tags =  stuff.second;
    
    map<string,int> labels;
    map<pair<string,string>,int> labelWordPosts;
    
    for(auto &l:tags){
        int numPostsWithLabel = 0;
        for(auto i = data.begin(); i != data.end(); ++i){
            if((*i).second.at("tag") == l){
                numPostsWithLabel++;
                set<string> wordsInPost = unique_words((*i).second.at("content"));
                for(auto &w:wordsInPost) labelWordPosts[{l,w}] += 1;
            }
        }
        labels[l] = numPostsWithLabel;
    }
    map<string,int> words;
    
    for(auto i = data.begin(); i != data.end(); ++i){
        set<string> wordsInPost = unique_words((*i).second.at("content"));
        for(auto &w:wordsInPost) words[w] += 1;
    }

    if(debug){
        cout << "training data:" << endl;
        for(auto i = data.begin(); i != data.end(); ++i){
            cout << "  label = " << (*i).second.at("tag") << ", "
                << "content = " << (*i).second.at("content") << endl;
        }
    }

    cout << "trained on " << data.size() << " examples" << endl;
    
    if(debug)
    cout << "vocabulary size = " << vocab.size() << endl;

    cout << endl;

    if(debug){
        cout << "classes:\n";
        for(auto &l:labels){
            double logPrior = log(double(l.second)/double(data.size()));
            cout << "  " << l.first << ", " << l.second 
                << " examples, log-prior = " << logPrior << endl;
        }
    }

    if(debug){
        cout << "classifier parementers:" << endl;
        for(auto &m:labelWordPosts){
            double logLikelihood = log(double(m.second)/double(labels.at(m.first.first)));
            cout << "  " << m.first.first << ":" << m.first.second << ", count = " 
                << m.second << ", log-likelihood = " << logLikelihood << endl;
        }
        cout << endl;
    }

    Classifier* datasets = new Classifier
        (double(data.size()),words,labels,labelWordPosts);

    printTestOutput(datasets,argv[2]);

    
    delete datasets;
    return 0;
}