#include "includes.hpp"


// Primary functions that make up the heart of the program
namespace Main {  
   
    string returnText; string returnName; string buff;
    vector<string> fileBuffer; // For commands with many files (to create, delete, etc.)

// Write to a File =================================================================================
/*
    User Command: "w {fileName}"
    Purpose: Writes to specified file or creates new file if not already existing

*/    
    void write() {
        cin >> returnName;

        // Clear cin buffer to prevent getline from reading newlines
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        cout << "Type now. When done, press '/' and enter." << endl;
        int status = 1; 

        // Automatically writes to file, line by line until user presses a single '/' and enters
        while (status) {
            cout << ">";
            std::getline(cin, returnText);
            if (returnText == "/") {
                status = 0;
                break; 
            }
            writeToFile(returnName, "\n" + returnText);
        }
    }

// QuickThought =================================================================================    
/*
    User Command: "qt"
    Purpose: Behaves similar to write function, but asks for fileName after the fact

*/
    void quickThought() {
        // Specify a default name in case the user doesn't know where to put it yet
        string defaultName = "QuickThought.txt"; 

        // Buffer for holding all lines of text entered
        vector<string> textBuff; 

        // Clear cin buffer to prevent getline from reading newlines
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        cout << "Type now. When done, press '/' and enter." << endl;
        int status = 1; 

        // Automatically stores to buffer, line by line until user presses a single '/' and enters
        while (status) {
            cout << ">";
            std::getline(cin, returnText);
            if (returnText == "/") {
                status = 0;
                break; 
            }
            textBuff.push_back(returnText);
        }

        cout << "Where do you want this to go? (Enter name of file or press enter again for default \"QuickThought.txt\")" << endl;
        std::getline(cin, returnText); 

        // If user presses enter, the default file is used. If not, use the file they specify
        returnName = (returnText.empty()) ? defaultName : returnText; 

        // Write lines to file after the user is done writing.
        for (auto t:textBuff) { 
            writeToFile(returnName, "\n" + t);
        }

    }

// Create a File =================================================================================    
/*
    User Command: "c {fileName}"
    Purpose: Creates a new file with the provided fileName

*/    
    void create() {
        cin >> returnText;
        cout << "Creating file: " << returnText << "...";
        createFile(returnText);
    }

// Quit Program =================================================================================    
/*
    User Command: "q"
    Purpose: End program

*/ 
    void quit() {
        cout << "Shutting down..." << endl;
    }

// Delete a File =================================================================================    
/*
    User Command: "d <m> {fileName}"
    Purpose: Deletes a file with the provided fileName. 
    Notes: <m> indicates the number of files to be deleted. If one file, this parameter can be left emptied
           If more than one file, set the parameter to that number of files and list all files with spaces between each

*/     
    void dlete() {
        int numofFiles; 

        // Plug next input after 'd' into buffer
        cin >> buff; 

    // Case 1: Multiple files to delete -----------------------------------------
        if (isdigit(buff[0])) {
            numofFiles = stoi(buff); // string to integer conversion

            // Store file names into buffer to access later 
            for (int i = 0; i < num; i++) {
                cin >> returnName; 
                fileBuffer.push_back(returnName);
            }

            // Access files from fileBuffer to delete 
            for (auto f:fileBuffer) {
                deleteFile(f);
            }
 
            // Reset file delete buffer
            fileBuffer.clear(); 
            buff.clear();

        }
    // Case 2: Only one file to delete -----------------------------------------   
        else { 
            deleteFile(buff);

            // Reset input buffer
            buff.clear(); 
        }

    }




    void printOptions() {
        
        cout << "Hello! How can I help you?" << endl;
        cout << "# Create a File, type \'c\', followed by the name of the file" << endl;
        cout << "# Write to a File, type \'w\', followed by the name of the file" << endl;
        cout << "# Delete a File, type \'d\', followed by the number of files, and all file names" << endl;
        cout << "# QuickThought, type \"qt\"" << endl;
        cout << "# Quit program, type \'q\'" << endl << endl;
    }


}


namespace Secondary { 

    using namespace Main;

    std::map<std::string, std::function<void()>> commandMap;  

// Normalize Input =================================================================================    
/*
    Purpose: Takes all user inputs and transforms them into either all lowercase or all uppercase. 
             This mitigates the effect of typos.

*/ 
    void normalizeInput(std::string& input) {
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    }


// Initialize Command Map =================================================================================    
/*
    Purpose: Sets up all command key-value pairs to accept user input and call appropriate function

*/ 
    void initCommands() {
        commandMap = {
        // This maps a user response to an appropriate command to run
        // Add commands here, with the key being the key to press and the value being the void function that will be run
            {"w", write},
            {"c", create},
            {"q", quit}, 
            {"p", printOptions},
            {"d", dlete},
            {"qt", quickThought}

        };
    }

}