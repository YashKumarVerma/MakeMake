/*
@author:YashKumarVerma
@desc:CPP-Template Makefile generator
*/
#include<iostream>
#include<filesystem>
#include<fstream>
#include<vector>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv){
    // to store moduleNames
    vector<string> headerNames;

    // open write stream to write makefile
    ofstream makeFile;
    makeFile.open("Makefile");
    
    // loop through the data and append to array
    for (const auto & entry : fs::directory_iterator("./includes")){
        // get filename
        string fileName = entry.path();
        fileName = fileName.substr(11, fileName.length());
        
        // push data into headerNames vector
        headerNames.push_back(fileName);
    }

    // write the header to makefile
    makeFile << "bin/build: bin/app.o ";
    for(int i=0; i<headerNames.size(); i++){

        // link all the object files of modules
        makeFile << " bin/" << headerNames[i] << ".o ";
    }

    // to write the #2, the cmd which runs if #1 is changed
    makeFile << "\n" << "\tg++ --std=c++17 bin/app.o ";
    for(int i=0; i<headerNames.size(); i++){
        makeFile << "bin/" << headerNames[i] << ".o "; 
    }
    makeFile << " -o bin/build";

    // the rule which directly works on app.cpp -> app.o
    makeFile << "\n\nbin/app.o: source/app.cpp\n\tg++ --std=c++17 -c source/app.cpp -o bin/app.o";

    // rule to check for changes in modules itself
    for(int i=0; i<headerNames.size(); i++){
        makeFile << "\n\nbin/" << headerNames[i] << ".o: includes/" << headerNames[i] << "/" << headerNames[i] << ".cpp includes/" << headerNames[i] << "/" << headerNames[i] << ".h\n";
        makeFile << "\tg++ --std=c++17 -c includes/"<< headerNames[i] << "/"<< headerNames[i] << ".cpp -o bin/"<< headerNames[i] <<".o"; 
    }

    // code the clean function
    makeFile << "\n\n" << "clean:\n\trm -rf bin/*.o\n";

    // close the file
    makeFile.close();
    return 0;
}
