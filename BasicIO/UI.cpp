
#include "includes.hpp"

using namespace std;


namespace UI {

    void UIprintMenu() {

        cout << "Hello! How can I help you?" << endl;
        cout << "# Create a File, type \'c\', followed by the name of the file" << endl;
        cout << "# List files, type \'ls\', followed by \"fs\" for File Storage or any other path you want" << endl;
        cout << "# Write to a File, type \'w\', followed by the name of the file" << endl;
        cout << "# Delete a File, type \'d\', followed by the number of files, and all file names" << endl;
        cout << "# QuickThought, type \"qt\"" << endl;
        cout << "# Quit program, type \'q\'" << endl << endl;
    }

    void UIprintHelp(string command) {
        cout << "Help requested with command: " << command << std::endl;
    }


};

