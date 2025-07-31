
#include "includes.hpp"

using namespace std;


namespace UI {

    std::map<std::string, std::string> helpConfigMap; // Constainer to store helpConfig data from helpConfig.txt

// Print Menu =============================================================================
/*
    Purpose: Prints initial greeting and menu of available commands

*/

    void UIprintMenu() {

        ifstream fileOne("menuConfig.txt"); // create input stream of menuConfig.txt file

        string line; char startPrint = 0;

        while(getline(fileOne, line)) {
            if (line == "###") {
                startPrint = 1;
            }

            if (startPrint) {
                cout << line << endl;
            }    
        }

        startPrint = 0; // Reset for next call

        fileOne.close(); // Close file

       // cout << "Hello! Welcome to NoteTaker!" << endl;
        // cout << "# Create a File, type \'c\', followed by the name of the file" << endl;
        // cout << "# List files, type \'ls\', followed by \"fs\" for File Storage or any other path you want" << endl;
        // cout << "# Write to a File, type \'w\', followed by the name of the file" << endl;
        // cout << "# Delete a File, type \'d\', followed by the number of files, and all file names" << endl;
        // cout << "# QuickThought, type \"qt\"" << endl;
        // cout << "# Quit program, type \'q\'" << endl << endl;
        
    }



    void UIinitHelpConfig() {

        ifstream fileOne("helpConfig.txt"); // create input stream of helpConfig.txt file

        string line; char storeCommand = 0; char storeDescription = 0;
        string currCommand, currDescription;

        while(getline(fileOne, line)) {

            // Detect new command
            if (line == "###") {
                storeCommand = 1; 
                // If storeDescription = 1, we just read a command config, so we need to store it.
                if (storeDescription) {
                    storeDescription = 0; // Reset for next run
                    helpConfigMap[currCommand] = currDescription; // Store command description in map

                    // Reset strings to store the next command in config file
                    currCommand.clear();
                    currDescription.clear();
                }
            } 

            // Store Command
            else if (storeCommand) {
                currCommand = line; 
                storeCommand = 0; 
                storeDescription = 1;
            }

            // Store Description
            else if (storeDescription) {
                currDescription += line + "\n";
            }
        }

        fileOne.close(); // Close file

    }

    void UIprintHelp(string command) {
        cout << "Help requested with command: " << command << std::endl;

        // User requested references on all commands
        if (command == "all") {
            for (auto s : helpConfigMap) {
                cout << s.second;
            }
        }

        // User requested reference for specific command
        else {
            cout << helpConfigMap[command];
        }

    }






};

