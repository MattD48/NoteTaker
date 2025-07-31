
#include "includes.hpp"

using namespace std;

namespace Files {

std::map<int, std::string> fileListMap; // Used to store names of files that are contained in a certain directory    

void writeToFile(string fileName, string text) {
    // Grab the default directory (where all files are stored)
    filesystem::path defaultDir = Secondary::getDefaultDirectory();

    // Define file path in default directory
    filesystem::path filePath = defaultDir / fileName;

    ofstream myFile(filePath, ios::app); // Always append, for now
    myFile << text;
    myFile.close();

}
void createFile(string fileName) { // Creates a brand new file
    // Grab the default directory (where all files are stored)
    filesystem::path defaultDir = Secondary::getDefaultDirectory();

    // Define file path in default directory
    filesystem::path filePath = defaultDir / fileName;

    ofstream myFile(filePath); 
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
    string response; int status = false; 
    cout << "Confirm deletion of " << fileName << "? (yes/no) ";

    while (!status) {
        cin >> response; 
        Secondary::normalizeInput(response); // convert to all lowercase

        if (response == "yes") {
            filesystem::path filePath = Secondary::getDefaultDirectory() / fileName; // creates an object that details the path to the target file
            status = filesystem::remove(filePath); // removes file based on filepath, returns TRUE if successful 
            if (!status) {
                cout << "Operation Failed" << endl;
                status = DelDONE;
            }

        }
        else {
            if (response == "no") {
                cout << "Operation Cancelled." << endl;
                status = DelDONE;
            }
            else {
                cout << "Invalid response, confirming deletion again...? (yes/no)" << endl;
            }
        }
    }
}

void listFiles(string path) {
    if (filesystem::exists(path) && filesystem::is_directory(path)) {
        int i = 0; 
        for (const auto& entry : filesystem::directory_iterator(path)) {

            // Store file in file map for easy selection
            fileListMap[i] = entry.path().filename().string(); 

            // Print file number and name for easy reference
            std::cout << i++ << ": " << entry.path().filename().string() << "   ";

        }
        cout << endl;
    }
    else {
        cout << "Directory does not exist: " << path << endl;
    }
}

}