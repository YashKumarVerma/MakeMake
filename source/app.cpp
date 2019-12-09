/*
@author:YashKumarVerma
@desc:CPP-Template Makefile generator
*/
#include<iostream>
#include<filesystem>
#include<vector>
#include"./../includes/rainbow/rainbow.h"

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv){

    // count the number of header files included
    int headerCounter = 0;
    for(const auto &n : fs::directory_iterator("./includes")){
        headerCounter++;
    }

    // array to store number of header files
    string *headerFileNames;

    // allocate memory 
    headerFileNames = (string*)malloc(headerCounter*sizeof(string));

    // loop through the data and append to array
    for (const auto & entry : fs::directory_iterator("./includes")){
        string fileName = entry.path();
        fileName = fileName.substr(11, fileName.length());
        cout << fileName << endl;
    }

    return 0;
}