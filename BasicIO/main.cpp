#include "includes.hpp"

using namespace std;

// void writeToFile(string fileName, string text) {
//     ofstream myFile;
//     myFile.open(fileName);
//     myFile << text;
//     myFile.close();

// }
// void createFile(string fileName){
//     ofstream myFile(fileName); 
//     myFile.close();
// }



int main () {

    Secondary::initCommands(); // Initialize commands provided in commands.cpp
    UI::UIprintMenu(); // Print user options

    string userResponse;

    while(true) {

        cout << "Command: "; 
        cin >> userResponse;
        Secondary::normalizeInput(userResponse);

        if (userResponse == "q") {
            Main::quit();
            return 0;
        }

        auto itr = Secondary::commandMap.find(userResponse);
        if (itr == Secondary::commandMap.end()) {
            cout << "Command Unknown" << endl; // iterator reached the end of the map, meaning entered character is not valid
        }
        else {
            itr->second(); // Call function that is connected to user request
        }

    }

    return 0; 
}