#include "includes.hpp"


using namespace Files;

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

        // Quick Reference detected
        if (returnName.find("^") != string::npos) { 
            string tempBuff = Secondary::trimQuickRefence(returnName);

            returnName = Secondary::quickReference(tempBuff);
        }

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

        // Go ahead and list files for convenience
        listFiles(Secondary::getDefaultDirectory().string()); 

        // Prompt user to specify a file location or use the default
        cout << "Where do you want this to go? (Enter name of file or press enter again for default \"QuickThought.txt\")" << endl;
        std::getline(cin, returnText); 

        // If user presses enter, the default file is used. If not, use the file they specify
        returnName = (returnText.empty()) ? defaultName : returnText; 

        // Quick Reference detected
        if (returnName.find("^") != string::npos) { 
            string tempBuff = Secondary::trimQuickRefence(returnName);
            returnName = Secondary::quickReference(tempBuff);
        }

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

// List all Files ===============================================================================
/*
    User Command: "ls"
    Purpose: List all files that are in the designated directory (default is current directory)

*/    
    void list() {
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::string pathStr; 

        cin >> returnText; 

        if (returnText == "fs") {
            pathStr = currentPath.string() + "\\FileStorage";
        }
        else {
            pathStr = returnText;
        }

        listFiles(pathStr);

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
            for (int i = 0; i < numofFiles; i++) {
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

            // Quick Reference detected
            if (buff.find("^") != string::npos) { 
                string tempBuff = Secondary::trimQuickRefence(buff);
                buff = Secondary::quickReference(tempBuff);
            }
                            
            deleteFile(buff);

            // Reset input buffer
            buff.clear(); 
        }

    }


// Print Menu =============================================
/*
    Purpose: Prints a welcome message and the most commonly used commands and syntax for each

*/
    void printMenu() {
        UI::UIprintMenu();
    }


}


namespace Secondary { 

    using namespace Main;

    std::map<std::string, std::function<void()>> commandMap;  

    string respBuff;

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
            {"p", printMenu},
            {"d", dlete},
            {"qt", quickThought},
            {"ls", list},
            {"asc", ASCIIArt}, 
            {"help", help}, 
            {"clr", clearScreen}

        };
    }


// Print available commands "help" ================================================================================
/*

    Purpose: Prints a reference to a specific (or ALL) command and a short description of what it does/how it works
    Syntax: help {command name} 
            help ALL

*/
    void help() {

        cin >> respBuff; // Read in the input from the user, should be the command to get help with or "ALL"

        Secondary::normalizeInput(respBuff); // Ensure a normalized string

        // User requested help with all commands 
        if (respBuff == "all") { 
            UI::UIprintHelp(respBuff); // Call function that will print help references
        }

        // User requested help with a specific command
        else {
            auto itr = Secondary::commandMap.find(respBuff);

            if (itr == Secondary::commandMap.end()) {
                cout << "Command Unknown" << endl; // iterator reached the end of the map, meaning entered character is not valid
            }
            else {
                UI::UIprintHelp(respBuff); 
            }
        }
    }




// Query Default Directory =================================================================================
/*
    Purpose: Creates (if not already existing) and returns the default directory that holds all note files

*/
    std::filesystem::path getDefaultDirectory() {
        // Get working directory
        filesystem::path currentPath = filesystem::current_path();

        // Define default directory to hold files
        filesystem::path defaultDir = currentPath / "FileStorage";

        // Create Directory if it doesn't exist already
        if (!filesystem::exists(defaultDir)) {
            filesystem::create_directory(defaultDir);
        }

        return defaultDir;
    }

// Print ASCII Art =========================================================================================
/*
    Purpose: Prints a simple ASCII art message 

*/    

    void ASCIIArt() {
    // Code example from Copilot - Heart    
        int n = 6; // Size of the heart 
        for (int i = n / 2; i <= n; i += 2) {
            for (int j = 1; j < n - i; j += 2) {
                cout << " ";
            }
            for (int j = 1; j <= i; ++j) {
                cout << "*";
            }
            for (int j = 1; j <= n - i; ++j) {
                cout << " ";
            }
            for (int j = 1; j <= i; ++j) {
                cout << "*";
            }
            cout << endl;
        }
        for (int i = n; i >= 1; --i) {
            for (int j = i; j < n; ++j) {
                cout << " ";
            }
            for (int j = 1; j <= (i * 2) - 1; ++j) {
                cout << "*";
            }
            cout << endl;
        }
        
    }

// Trim Functions =========================================================

/*
    Purpose: Trims config file text to ensure extra whitespace is ignored
    Use: Mainly used for help config file and storing data into helpConfigMap

*/
    // Code from Microsoft CoPilot


    std::string trimQuickRefence(const std::string& input) {
        std::string result;
        for (char ch : input) {
            if (std::isdigit(ch)) {
                result += ch;
            }
        }
        return result;
    }


// Quick Reference =============================================================

/*
    Purpose: Allows the user to select from a list of files printed by the "ls" command to write, quickthought, or delete
    Syntax: {command} ^{number of file}
    Example: w ^3
            *writes to file #3, as printed by the list command*
*/

    string quickReference(string numOfFile) {
        string returnString = numOfFile;
        string tempString; string selectionBuff;
        int index;

        bool quickRefDone = false;

        bool selection_confirmed = false;

        // Begin top level loop, runs until user confirms their choice
        while (!quickRefDone) {

            // Grab index, confirm it is within range
            index = stoi(numOfFile);
            if (index >= static_cast<int>(fileListMap.size())) {
                cout << "No such file. Enter valid index: ";
                cin >> numOfFile;
                numOfFile = Secondary::trimQuickRefence(numOfFile);
            }

            else {

                // Begin sub level loop, Prompt User for confirmation of selection
                while (!selection_confirmed) {

                    // Update tempstring
                    index = stoi(numOfFile);
                    tempString = Files::fileListMap[index];

                    // Ask user to confirm selection
                    cout << "Confirm Selection of " << tempString << "? (y/n) .....";
                    cin >> selectionBuff; 

                    normalizeInput(selectionBuff);

                    // User selected "y", confirming the quick reference file choice and returning the actual file name.
                    if (selectionBuff == "y") {
                        cout << "Selection Confirmed!" << endl;
                        
                        selection_confirmed = true;
                        quickRefDone = true;

                        returnString = tempString;

                    }

                    // User selected "n", rejecting the file choice and will be prompted for another index. 
                    else if (selectionBuff == "n") {
                        cout << "Enter valid index: ";
                        cin >> numOfFile;
                        numOfFile = Secondary::trimQuickRefence(numOfFile); // Trim function to ensure proper formatting
                    }   

                    else {
                        cout << "Invalid input."; 
                    }
                }
            }
        }

        return returnString;

    }

// Clear Screen ========================================================================
/*
    Purpose: Uses a special code to clear the console of all previous prompts and responses

*/   
    void clearScreen() {
        // ANSI escape code to clear screen and move cursor to top-left
        std::cout << "\033[2J\033[1;1H";
    }

}
