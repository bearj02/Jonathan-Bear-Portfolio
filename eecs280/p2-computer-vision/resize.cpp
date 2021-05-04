#include "processing.h"
#include "Matrix.h"
#include "Image.h"
#include <fstream>
#include <iostream> 
#include <cstdlib> 
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    ifstream inputfile; 
    inputfile.open(argv[1]);

    ofstream outputfile; 
    outputfile.open(argv[2]);

    if(!inputfile.is_open() || !outputfile.is_open()){
        cout << "Open Failed" << endl; 
        return 1; 
    }

    Image* img = new Image; 
    Image_init(img, inputfile); 

    if(!(argc == 4 || argc == 5)){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1; 
    }

    int new_height = Image_height(img); 

    int new_width = atoi(argv[3]);

    if(argc == 5){
        new_height = atoi(argv[4]); 
    }

    if((new_width < 0 && new_width > Image_width(img))){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1; 
    }

    if((new_height < 0 && new_height > Image_height(img))){
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
     return 1; 
    }

    seam_carve(img, new_width, new_height);
    
    Image_print(img, outputfile);
    
    outputfile.close(); 
    inputfile.close();

    delete img; 

}