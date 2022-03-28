#include "Game.h"
int main(int argc, char** argv) {

    Game g;
    int mode;
    if (!argv[1])
        mode = SIMPLE;
    else if (strcmp(argv[1], "-load")==0)
        mode = LOAD;
    else if (strcmp(argv[1], "-save")==0)
        mode = SAVE;
    else {
        cout << "Wrong input" << endl;
        return 0;
    }
    if (mode == LOAD) {
        if ((argv[2])) {
            if (strcmp(argv[2], "-silent")==0)
                mode = SILENCE;
            else {
                cout << "Wrong input" << endl;
                return 0;
            }
        }
    }
    g.startGame(mode);
    return 0;
}