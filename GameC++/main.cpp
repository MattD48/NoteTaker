#include <main.hpp>




int main() {
    srand(time(0));    //Initialize the random seed, setup the random number generator
    printf("Welcome to Game. \nHere are the controls:\n");
    printf("w = UP       q = quit\na = LEFT\ns = DOWN\nd = RIGHT");
    printf("\nBuild Modes: n = normal, c = clear, b = build\n");

    command();
    return 0;
}

void command() {
    int c; char x;
    int loopVal = 1;
    int currentPos = 78; //Starting location (can be anywhere within 0-175)
    char avatar = 33;    //ASCII for '!'
    int buildMat = 1;    //Selected building material (default is normal mode, or ' ')

    printf("Select map size (1,2,or 3): ");
    c = getchar();

    system("cls");               //Running in the terminal, this clears the screen after each move
    mapSize(c);                           //Configure the map size
    initializeMap(currentPos,avatar);     //Load the array
    map[currentPos / horBound][currentPos % horBound] = avatar;     //Place the character
    printMap();                           //Print the array


    while (loopVal) {                 // Run until 'q'
        c = getchar();

        switch (c) {
            case 113: //q QUIT
                loopVal = 0;
                printf("Thanks for playing!");
                break;
            case 114: //r RESET
                currentPos = 78; buildMode = 0;
                initializeMap(currentPos,avatar);
                map[currentPos / horBound][currentPos % horBound] = avatar;
                printMap();
                break;
            case 119: //w UP
                buildMat = confirmMaterial(119, currentPos);
                if (!buildMat) { break;} //Illegal move was attempted

                x = mode(buildMode, buildMat);                //Determines what material to put into the array
                map[currentPos/horBound][currentPos%horBound] = x;   //Adds the returned material into the array

                currentPos -= horBound;   //Move up one whole row (subtract the length of one row)
                // Out of bounds? -------------
                if (currentPos < 0) {
                    currentPos += horBound;     //Move back to where you were before the attempted move
                    printf("Out of Bounds");
                    break;
                }
                //-----------------------------
                map[currentPos/horBound][currentPos%horBound] = avatar;
                system("cls");
                printMap();
                break;

            case 100: //d RIGHT
                c = confirmMaterial(100, currentPos);
                if (!c) { break;} //Illegal move was attempted

                x = mode(buildMode, c);        //Determines what material to put into the array
                map[currentPos/horBound][currentPos%horBound] = x; //Adds the returned material into the array

                currentPos += 1;
                // Out of bounds? -------------
                if ((currentPos - 1) % horBound == (horBound - 1)) {
                    currentPos -= 1;        //Move back to where you were before the attempted move
                    printf("Out of Bounds");
                    break;
                }
                //-----------------------------
                map[currentPos/horBound][currentPos%horBound] = avatar;
                system("cls");
                printMap();
                break;
            case 97: //a LEFT
                c = confirmMaterial(97, currentPos);
                if (!c) { break;} //Illegal move was attempted

                x = mode(buildMode,c);        //Determines what material to put into the array
                map[currentPos/horBound][currentPos%horBound] = x;  //Adds the returned material into the array

                currentPos -= 1;
                // Out of bounds? -------------
                if ((currentPos + 1) % horBound == 0) {
                    currentPos += 1;      //Move back to where you were before the attempted move
                    printf("Out of Bounds");
                    break;
                }
                //-----------------------------
                map[currentPos/horBound][currentPos%horBound] = avatar;
                system("cls");
                printMap();
                break;
            case 115: //s DOWN
                c = confirmMaterial(115, currentPos);
                if (!c) { break;} //Illegal move was attempted

                x = mode(buildMode,c);     //Determines what material to put into the array
                map[currentPos/horBound][currentPos%horBound] = x; //Adds the returned material into the array

                currentPos += horBound;   //Move down one whole row (add the length of one row)
                // Out of bounds? -------------
                if (currentPos > (horBound*vertBound) - 1) {
                    currentPos -= horBound;  //Move back to where you were before the attempted move
                    printf("Out of Bounds");
                    break;
                }
                //-----------------------------
                map[currentPos/horBound][currentPos%horBound] = avatar;
                system("cls");
                printMap();
                break;

                // Material Select ------------------------------
            case 110: //n NORMAL MODE
                buildMode = 0;
                //buildMat = 1; //Back to the default ' '
                break;
            case 99: //c CLEAR MODE
                buildMode = 1;
                break;
            case 98: //b BUILD MODE
                buildMode = 2;
                printf("Select your building material: ");
                //printf("")
                buildMat = getchar();
                break;

                // Map Size Select --------------------------------
            case 122: //z
                c = getchar();

                mapSize(c);
                initializeMap(currentPos,avatar);
                system("cls");
                printMap();

                break;

        }

        //-------------------
    }
}