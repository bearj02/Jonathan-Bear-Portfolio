#include "csvstream.h"
#include <map> 
#include <string>
#include <iostream> 

using namespace std; 

int main(int argc, char *argv[]){
    csvstream train_file(argv[1]); 
    csvstream test_file(argv[2]); 

    bool debug; 
    if(argc == 3 ){
        debug == false; 
    }
    else if(argc == 4 && argv[3] == "--debug"){
        debug  == true; 
    }
    else
    {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;

    }




    




    //read posts from a csv file and then get data to put into classifier 
    // train the classifier with the data and store all the information 
    // classifier should compute the probability of a post to a given label 
    //choose the label that gives the highest probability score
    //read posts from a file again and then test, using classifier that was trained, predict 
    // a label x
    //take in train file and test file 

    csvstream csv_file(file); 
    std::map<std::string, std::string> row; 


    if(!csv_file){
        while(csv_file >> row){
            std::cout << "row" << std:: endl; 
            
            for(auto &col : row){
                const std::string &column_name = col.first; 
                const std::string &datum = col.second; 
                std::cout << " " << column_name << ": " << datum << std::endl; 
            }
        }
    }

}