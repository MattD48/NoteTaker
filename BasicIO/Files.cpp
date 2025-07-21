
#include "includes.hpp"

using namespace std;

void writeToFile(string fileName, string text) {
    ofstream myFile(fileName, ios::app); // Always append, for now
    myFile << text;
    myFile.close();

}
void createFile(string fileName) { // Creates a brand new file
    ofstream myFile(fileName); 
    myFile.close();
    cout << "Done!" << endl;
}


// void combineFiles(string file1, string file2, string newFile) { // File 1 takes on File 2
//     ifstream fileOne(file1); // First file to write
//     ifstream fileTwo(file2); // Second file to write
//     ofstream combined(newFile); // combined file

//     string line; 
//     while(getline(fileOne, line)) {
//         combined << line << '\n'; 
//     }

//     while(getline(fileTwo, line)) {
//         combined << line << '\n'; 
//     }

//     cout << "## - Files Combined! - ##" << endl;
//     fileOne.close();
//     fileTwo.close();
//     combined.close();
// }

void deleteFile(string fileName) {
    string response; int status = 1; 
    cout << "Confirm deletion of " << fileName << "? (yes/no) ";

    while (status) {
        cin >> response; 
        Secondary::normalizeInput(response); // convert to all lowercase

        if (response == "yes") {
            status = remove(fileName.c_str()); // returns 0 if successful
            if (status) {
                cout << "Operation Failed" << endl;
                status = 0;
            }

        }
        else {
            if (response == "no") {
                cout << "Operation Cancelled." << endl;
                status = 0;
            }
            else {
                cout << "Invalid response, confirming deletion again...? (yes/no)" << endl;
            }
        }
    }
}