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
        Game(int numInputs, char** inputs) {
            entry = inputs[0];
            string fileName = inputs[1];
            ifstream in(fileName);
            Pack pack(in);
            players.push_back(Player_factory(inputs[4], inputs[5]));
            players.push_back(Player_factory(inputs[6], inputs[7]));
            players.push_back(Player_factory(inputs[8], inputs[9]));
            players.push_back(Player_factory(inputs[10], inputs[11]));
            if (strcmp(inputs[2],"shuffle")) {
                shuffleCards = true;
            }
            if (strcmp(inputs[2],"noshuffle")) {
                shuffleCards = false;
            }
            pts = atoi(inputs[3]);
            trump = "";
            upcard = Card(Card::RANK_TWO,Card::SUIT_SPADES);
            round = 1;
            dealer = false;
        }
        void play() {
            int team1Pts = 0;
            int team2Pts = 0;
            int hand = 0;
            while (team1Pts < pts && team2Pts < pts) {
                cout << "Hand " << hand << endl;
                cout << players[0] << ""
            }
        }
    private:
        std::vector<Player*> players;
        Pack pack;
        bool shuffleCards;
        string entry;
        int pts;
        string trump;
        Card upcard;
        int round;
        bool dealer;

        void shuffle(){
            pack.shuffle();
        }

        void Dealxcards(Player *player, int numcards){
            for(int i=0; i<numcards; i++){
                player->add_card(pack.deal_one());
            }
        }

        void Dealcards(Player *player1, Player *player2, 
        Player *player3, Player *player4){
            Dealxcards(player1, 3);
            Dealxcards(player2, 2);
            Dealxcards(player3, 3);
            Dealxcards(player4, 2);

            Dealxcards(player1, 2);
            Dealxcards(player2, 3);
            Dealxcards(player3, 2);
            Dealxcards(player4, 3);
            upcard = pack.deal_one();
        }

        void MakeTrump(Player *player1){
            if(player1->make_trump(upcard, dealer, round, trump)){
                trump = upcard.get_suit();
                players[0]->add_and_discard(upcard);
            }
        }

        // card c0,1,2,3 corresponds to the order of players
        int TrickWinningPlayer(Card c0, Card c1, Card c2, Card c3, Card led){ 
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
        }

};

int main(int argc, char **argv) {
    // Read command line args and check for errors
    if(argc != 12){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    if(atoi(argv[3]) < 1 || atoi(argv[3]) > 100){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    if(!((strcmp(argv[2], "shuffle") == 0) || (strcmp(argv[2], "noshuffle") == 0))){
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
        << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;
        return 1;
    }
    if((!((strcmp(argv[5], "Simple") == 0) || (strcmp(argv[5], "Human") == 0))) ||
       (!((strcmp(argv[7], "Simple") == 0) || (strcmp(argv[7], "Human") == 0))) ||
       (!((strcmp(argv[9], "Simple") == 0) || (strcmp(argv[9], "Human") == 0))) ||
       (!((strcmp(argv[11], "Simple") == 0) || (strcmp(argv[11], "Human") == 0)))) {
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
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    } 
    cout << endl;
    Game game(argc,argv);
    game.play();

    /*for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    } */
}
