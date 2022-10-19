//Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include "Pack.h"
#include "Player.h"
    
#include <iostream>
#include <sstream>
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
            if (strcmp(inputs[2],"shuffle") == 0) {
                shuffleCards = true;
            }
            if (strcmp(inputs[2],"noshuffle") == 0) {
                shuffleCards = false;
            }
            pts = atoi(inputs[3]);
            trump = "";
            upcard = Card(Card::RANK_TWO,Card::SUIT_SPADES);
            round = 1;
            trumpMade = false;
            hand = 0;
            dealer = false;
        }
        void play() {
            //int team1Pts = 0;
            //int team2Pts = 0;
            //int team1Tricks = 0;
            //int team2Tricks = 0;
            //while (team1Pts < pts && team2Pts < pts) {
                if (shuffleCards) {
                    pack.shuffle();
                }
                else {
                    pack.reset();
                }
                cout << "Hand " << hand << endl;
                Dealcards(players[hand%4],players[(hand+1)%4],players[(hand+2)%4],players[(hand+3)%4]);
                int n = 1;
                int i = (hand+n)%4;
                while (!trumpMade && n <= 8) {
                    if (i == hand%4 && n > 4) {
                        round = 2;
                        dealer = true;
                        MakeTrump(players[i]);
                    }
                    else if (n > 4) {
                        round = 2;
                        dealer = false;
                        MakeTrump(players[i]);
                    }
                    else if (i == hand%4 && n <= 4) {
                        round = 1;
                        dealer = true;
                        MakeTrump(players[i]);
                    }
                    else {
                        round = 1;
                        dealer = false;
                        MakeTrump(players[i]);
                    }
                    n++;
                    i = (hand+n)%4;
                }
                round = 1;
                dealer = false;

          //  }
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
        bool trumpMade;
        bool dealer;
        int hand;

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
            cout << players[hand%4]->get_name() << " deals" << endl;
            Dealxcards(player2, 3);
            Dealxcards(player3, 2);
            Dealxcards(player4, 3);
            Dealxcards(player1, 2);

            Dealxcards(player2, 2);
            Dealxcards(player3, 3);
            Dealxcards(player4, 2);
            Dealxcards(player1, 3);
            upcard = pack.deal_one();
            ostringstream up;
            up << upcard;
            cout << up.str() << " turned up" << endl;
        }

        void MakeTrump(Player *player1){
            if(player1->make_trump(upcard, dealer, round, trump)){
                cout << player1->get_name() << " orders up " << trump << endl;
                cout << endl;
                trumpMade = true;
                if (round == 1) {
                    players[hand%4]->add_and_discard(upcard);
                }
            }
            else {
                cout << player1->get_name() << " passes" << endl;
            }
        }

        void PlayHand() {

        }

        void ScoreUpdate(){ // updates the score per hand.
            int team1tricks = 0;
            int team2tricks = 0;
            Card c0;
            Card c1;
            Card c2;
            Card c3;
            for(int i=0; i<5; i++){//5 cards played
                Card led = players[(dealer+1)%dealer]->lead_card(trump);
                c0 = players[(dealer+1)%dealer]->play_card(led, trump);
                c1 = players[(dealer+2)%dealer]->play_card(led, trump);
                c2 = players[(dealer+3)%dealer]->play_card(led, trump);
                c3 = players[dealer]->play_card(led, trump);
            
                int playerwon = TrickWinningPlayer(c0, c1, c2, c3);
                if(playerwon % 2 == 0){
                    team1tricks += 1;
                    cout << players[0]->get_name() << " and " << players[2]->get_name() << " takes the trick" << endl;
                }
                if(playerwon % 2 == 1){
                    team2tricks += 1;
                    cout << players[1]->get_name() << " and " << players[3]->get_name() << " takes the trick" << endl;
                }
            }

            if(team1tricks > team2tricks){
                cout << players[0]->get_name() << " and " << players[2]->get_name() << " win the hand" << endl;
                if(orderup){
                    if(team1tricks == 3 || team1tricks == 4){
                        team1score += 1;
                    }
                    if(team1tricks == 5){
                        team1score += 2;
                        cout << "march!" << endl;
                    }
                }
                if(!orderup){
                    team1score += 2;
                    cout << "euchred!" << endl;
                }
            }
            if(team2tricks > team1tricks){
                cout << players[1]->get_name() << " and " << players[3]->get_name() << " win the hand" << endl;
                if(orderup){
                    if(team2tricks == 3 || team2tricks == 4){
                        team2score += 1;
                    }
                    if(team2tricks == 5){
                        team2score += 2;
                        cout << "march!" << endl;
                    }
                }
                if(!orderup){
                    team2score += 2;
                    cout << "euchred!" << endl;
                }                  
            }
            cout << players[0]->get_name() << " and " << players[2]->get_name() << " have " << team1score << " points" << endl; 
            cout << players[1]->get_name() << " and " << players[3]->get_name() << " have " << team1score << " points" << endl; 
        }

       int TrickWinningPlayer(Card c0, Card c1, Card c2, Card c3){ 
            Card led = c0; //led card is the first card that is played
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
