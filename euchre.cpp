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
        Game(string exec,std::istream& use,string shuffleC,
        int pts,string n1,string t1,string n2,string t2,
        string n3,string t3,string n4,string t4) {
            entry = exec;
            Pack pack(use);
            p1 = Player_factory(n1, t1);
            p2 = Player_factory(n2, t2);
            p3 = Player_factory(n3, t3);
            p4 = Player_factory(n4, t4);
            players.push_back(p1);
            players.push_back(p2);
            players.push_back(p3);
            players.push_back(p4);
            if (shuffleC == "shuffle") {
                shuffleCards = true;
            }
            if (shuffleC == "noshuffle") {
                shuffleCards = false;
            }
        }
        void play() {
            
        }
    private:
        std::vector<Player*> players;
        Pack pack;
        Player *p1;
        Player *p2;
        Player *p3;
        Player *p4;
        bool shuffleCards;
        string entry;
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
    if( atoi(argv[3]) < 1 || atoi(argv[3]) > 100){
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
    string executable = argv[0];
    string shuffle = argv[2];
    int points = atoi(argv[3]);
    string name1 = argv[4];
    string type1 = argv[5];
    string name2 = argv[6];
    string type2 = argv[7];
    string name3 = argv[8];
    string type3 = argv[9];
    string name4 = argv[10];
    string type4 = argv[11];
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    Game game(executable,fin,shuffle,points,name1,
    type1,name2,type2,name3,type3,name4,type4);
    game.play();

    /*for (size_t i = 0; i < players.size(); ++i) {
        delete players[i];
    } */
}
