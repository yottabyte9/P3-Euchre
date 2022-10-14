#include Card.h
#include Pack.h
#include Player.h
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <array>
#include <vector>

class Game {
    public:
        Game(/* game details */);
        void play();

    private:
        std::vector<Player*> players;
        Pack pack;
        // ...

        void shuffle();
        void deal(/* ... */);
        void make_trump(/* ... */);
        void play_hand(/* ... */);
        // ...
}

int main(int argc, char **argv) {
    // Read command line args and check for errors
    if(argc != 12){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    if(argv[3] < 1 || argv[3] > 100){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    if(argv[2] != "shuffle" && argv[2] != "noshuffle"){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    if((argv[5] != "Simple" && argv[5] != "Human") ||
       (argv[7] != "Simple" && argv[7] != "Human") ||
       (argv[9] != "Simple" && argv[9] != "Human") ||
       (argv[11] != "Simple" && argv[11] != "Human")){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    string inFile = argv[1];
    ifstream fin(inFile);
    if(!(fin.is_open())){
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }

    Game game(/* game details */);
    game.play();

    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}

