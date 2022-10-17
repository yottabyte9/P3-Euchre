//Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include "Pack.h"
#include "Player.h"
    
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <array>
#include <vector>
using namespace std;

class Game {
    public:
        int partner1_pts;
        int partner2_pts;
        Game(Pack packc, int hand, int dealer_number, int round): hand(0), dealer_number(0), round(1){
            pack = packc;
        }
        void play();

        void shuffle(){
            pack.shuffle();
        }

        void Dealxcards(int playerindex, int numcards){
            for(int i=0; i<numcards; i++){
                players[playerindex] -> add_card(pack.deal_one());
            }
        }

        void Dealcards(){
            Dealxcards(0, 3);
            Dealxcards(1, 2);
            Dealxcards(2, 3);
            Dealxcards(3, 2);

            Dealxcards(0, 2);
            Dealxcards(1, 3);
            Dealxcards(2, 2);
            Dealxcards(3, 3);
            upcard = pack.deal_one();
        }

        void MakeTrump(){
            for(int i=0; i<4; i++){
                if(players[i]->make_trump(upcard, is_dealer, round, trump)){
                    trump = upcard.get_suit();
                    players[dealer_number]->add_and_discard(upcard);
                }
            }
        }

        // card c0,1,2,3 corresponds to the order of players
        int HandWinningPlayer(Card c0, Card c1, Card c2, Card c3, Card led){ 
            if(Card_less(c1,c0,led, trump)){ //true if c1<c0
                if(Card_less(c2, c0, led, trump)){ //true if c2<c0
                    if(Card_less(c3,c0, led, trump)){//true if c3<c0
                        return 0;
                    }
                }
            }
            if(Card_less(c0,c1,led, trump)){ //true if c0<c1
                if(Card_less(c2, c1, led, trump)){ //true if c2<c1
                    if(Card_less(c3,c1, led, trump)){//true if c3<c1
                        return 1;
                    }
                }
            }
            if(Card_less(c0,c2,led, trump)){ //true if c0<c2
                if(Card_less(c1, c2, led, trump)){ //true if c1<c2
                    if(Card_less(c3,c2, led, trump)){//true if c3<c2
                        return 2;
                    }
                }
            }
            if(Card_less(c0,c3,led, trump)){ //true if c0<c3
                if(Card_less(c1, c3, led, trump)){ //true if c1<c3
                    if(Card_less(c2,c3, led, trump)){//true if c2<c3
                        return 3;
                    }
                }
            }
            return -1;
        }

        void TrickTaking(){
            
        }

    private:
        std::vector<Player*> players;
        Pack pack;
        Card upcard;
        int hand;
        bool is_dealer;
        int dealer_number;
        std::string trump;
        int round;

};

int main(int argc, char **argv) {
    // Read command line args and check for errors
    if(argc != 12){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    if( atoi(argv[3]) < 1 || atoi(argv[3]) > 100){
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
        cout << "Error opening " << inFile << endl;
        return 1;
    }

    Game game(/* game details */);
    game.play();

    for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}

