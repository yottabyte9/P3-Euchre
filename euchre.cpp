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
            team1score = 0;
            team2score = 0;
            orderedUp = 0;
            team1tricks = 0;
            team2tricks = 0;
        }
        void play() {
            int n;
            int i;
            while (team1score < pts && team2score < pts) {
                if (shuffleCards) {
                    pack.reset();
                    pack.shuffle();
                }
                else {
                    pack.reset();
                }
                cout << "Hand " << hand << endl;
                Dealcards(players[hand%4],players[(hand+1)%4],
                players[(hand+2)%4],players[(hand+3)%4]);
                n = 1;
                i = (hand+n)%4;
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
                orderedUp = (hand+n-1)%4;
                round = 1;
                dealer = false;
                PlayHand();
                ScoreUpdate();
            }
            EndGame();
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
        int team1score;
        int team2score;
        int orderedUp;
        int team1tricks;
        int team2tricks;

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
            Card lead;
            Card play1;
            Card play2;
            Card play3;
            ostringstream current; 
            int start = (hand+1)%4;
            for (int j = 0; j < 5; j++) {
                lead = players[start]->lead_card(trump);
                current << lead;
                cout << current.str() << " led by " << 
                players[start]->get_name() << endl;
                play1 = players[(start+1)%4]->play_card(lead,trump);
                current.str("");;
                current << play1;
                cout << current.str() << " played by " << 
                players[(start+1)%4]->get_name() << endl;
                play2 = players[(start+2)%4]->play_card(lead,trump);
                current.str("");
                current << play2;
                cout << current.str() << " played by " << 
                players[(start+2)%4]->get_name() << endl;
                play3 = players[(start+3)%4]->play_card(lead,trump);
                current.str("");
                current << play3;
                cout << current.str() << " played by " << 
                players[(start+3)%4]->get_name() << endl;
                int trickWinner = TrickWinningPlayer(lead,play1,play2,play3);
                current.str("");
                cout << players[(start+trickWinner)%4]->get_name() 
                << " takes the trick" << endl;
                cout << endl;
                if ((start+trickWinner)%4 == 0 || (start+trickWinner)%4 == 2) {
                    team1tricks++;
                }
                if ((start+trickWinner)%4 == 1 || (start+trickWinner)%4 == 3) {
                    team2tricks++;
                }
                start = (start+trickWinner)%4;
            }
        }

        void ScoreUpdate() {
            if (team1tricks >= 3) {
                cout << players[0]->get_name() << " and " << 
                players[2]->get_name() << " win the hand" << endl;
                if ((team1tricks == 3 || team1tricks == 4) && (orderedUp % 2 == 0)) {
                    team1score = team1score + 1;
                }
                else if (team1tricks == 5 && orderedUp % 2 == 0) {
                    team1score = team1score + 2;
                    cout << "march!" << endl;
                }
                else {
                    team1score = team1score + 2;
                    cout << "euchred!" << endl;
                }
            }
            else {
                cout << players[1]->get_name() << " and " << 
                players[3]->get_name() << " win the hand" << endl;
                if ((team2tricks == 3 || team2tricks == 4) && (orderedUp % 2 == 1)) {
                    team2score = team2score + 1;
                }
                else if (team2tricks == 5 && orderedUp % 2 == 1) {
                    team2score = team2score + 2;
                    cout << "march!" << endl;
                }
                else {
                    team2score = team2score + 2;
                    cout << "euchred!" << endl;
                }
            }
            cout << players[0]->get_name() << " and " << 
            players[2]->get_name() << " have " << team1score << " points" << endl;
            cout << players[1]->get_name() << " and " << 
            players[3]->get_name() << " have " << team2score << " points" << endl;
            cout << endl;
            trumpMade = false;
            hand++;
            team1tricks = 0;
            team2tricks = 0;
        }

        void EndGame() {
            if (team1score >= pts) {
                cout << players[0]->get_name() << " and " 
                << players[2]->get_name() << " win!" << endl;;
            }
            else {
                cout << players[1]->get_name() << " and " 
                << players[3]->get_name() << " win!" << endl;
            }
            for (size_t i = 0; i < players.size(); ++i) {
                delete players[i];
            } 
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
            return 3;
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
}
