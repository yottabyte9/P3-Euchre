//Project UID 1d9f47bfc76643019cfbf037641defe1
#include <sstream>
#include "unit_test_framework.h"
#include "Pack.h"
#include "Card.h"
#include "Player.h"
using namespace std;

#include <string>
#include <vector>
#include <cassert>

class SimplePlayer: public Player{
    private:
        string namep;
        vector<Card> cardsp;
    public: 

    SimplePlayer(string name) : namep(name){};

    const std::string & get_name() const{
        return namep;
    }

    void add_card(const Card &c){
        if(cardsp.size() < MAX_HAND_SIZE){
            cardsp.push_back(c);
        }
    }

    bool make_trump(const Card &upcard, bool is_dealer, int round, std::string &order_up_suit) const {

        int num_suit_hand = 0;
        for(int i=0; i<cardsp.size(); i++){
            if(cardsp[i].is_face_or_ace() && cardsp[i].get_suit(upcard.get_suit()) == upcard.get_suit()){
                num_suit_hand += 1;
            }
        }
        
        if(round == 1){
            if(num_suit_hand >= 2){
                order_up_suit = upcard.get_suit();
                return true;
            }
            return false;
        }
        else if(round == 2){
            if(is_dealer){
                order_up_suit = Suit_next(upcard.get_suit());
                return true;
            }
            
            if(num_suit_hand >= 1){
                order_up_suit = upcard.get_suit();
                return true;
            }
            return false;        
        }
    }


    void add_and_discard(const Card &upcard){
        cardsp.push_back(upcard);
        int min_index = 0;
        for(int i=0; i<cardsp.size(); i++){
            if(cardsp[i] < cardsp[min_index]){
                min_index = i;
            }
        }
        cardsp.erase(cardsp.begin()+min_index);
    }

    Card lead_card(const std::string &trump){
        int max_index;
        int trump_counter = 0;
        for(int i=0; i<cardsp.size(); i++){
            if(cardsp[i].get_suit(trump) == trump){
                trump_counter ++;
            }
            if(cardsp[i].get_suit(trump) != trump){
                max_index = i;
            }
        }
        int max_index = 0;
        for(int i=0; i<cardsp.size(); i++){
            if(Card_less(cardsp[i], cardsp[max_index], trump)){
                max_index = i;
            }
        }
        if(trump_counter == MAX_HAND_SIZE){
            Card tempcard = cardsp[max_index];
            cardsp.erase(cardsp.begin() + max_index);
            return tempcard;
        }
        
        for(int i=0; i<cardsp.size(); i++){
            if(cardsp[i] > cardsp[max_index] && cardsp[i].get_suit(trump) != trump){
                max_index = i;
            }
        }
        Card tempcard = cardsp[max_index];
        cardsp.erase(cardsp.begin() + max_index);
        return tempcard;
    }

    Card play_card(const Card &led_card, const std::string &trump){
        int followIndex = 0;
        int lowIndex = 0;
        int countLed = 0;
        for (int i = 0; i < cardsp.size(); i++) {
            if (cardsp[i].get_suit(trump) == led_card.get_suit(trump)) {
                countLed++;
                followIndex = i;
            }
            if (Card_less(cardsp[i], cardsp[lowIndex], led_card, trump)) {
                lowIndex = i;
            }
        }
        if (countLed == 0) {
            Card tempcard = cardsp[lowIndex];
            cardsp.erase(cardsp.begin() + lowIndex);
            return tempcard;
        }
        else if (countLed == 1) {
            Card tempcard = cardsp[followIndex];
            cardsp.erase(cardsp.begin() + followIndex);
            return tempcard;
        }
        else {
            for (int j = 0; j < cardsp.size(); j++) {
                if (cardsp[j].get_suit(trump) == led_card.get_suit(trump)) {
                    if (Card_less(cardsp[followIndex], cardsp[j], trump)) {
                        followIndex = j;
                    }
                }
            }
            Card tempcard = cardsp[followIndex];
            cardsp.erase(cardsp.begin() + followIndex);
            return tempcard;
        }
    }

    static const int MAX_HAND_SIZE = 5;

    ~SimplePlayer() {}

    Player * Player_factory(const std::string &name, const std::string &strategy){
        if(strategy == "Simple"){
            return new SimplePlayer(name);
        }
        if(strategy == "Human"){
            return new HumanPlayer(name);
        }
        assert(false);
        return nullptr;
    }

    std::ostream & operator<<(std::ostream &os, const Player &p){
        os << p.get_name() << endl;
        return os;
    }

    Card return_card(int index, SimplePlayer *a){
        return a->cardsp[index];
    }

    class HumanPlayer: public Player{
    private:
        string nameh;
        vector<Card> cardsh;
    public:

        HumanPlayer(string name) : nameh(name){};

        virtual const std::string & get_name() const{
            return nameh;
        }

        void add_card(const Card &c){
            if(cardsh.size() < MAX_HAND_SIZE){
                cardsh.push_back(c);
            }
        }

        //REQUIRES round is 1 or 2
        //MODIFIES order_up_suit
        //EFFECTS If Player wishes to order up a trump suit then return true and
        //  change order_up_suit to desired suit.  If Player wishes to pass, then do
        //  not modify order_up_suit and return false.
        bool make_trump(const Card &upcard, bool is_dealer,
                                int round, std::string &order_up_suit) const{
            print_hand();
            cout << "Human player " << nameh << ", please enter a suit, or \"pass\":\n";
            string suit_in;
            cin >> suit_in;
            if(suit_in != "pass"){
                order_up_suit = suit_in;
                return true;
            }
            return false;
        }

        void print_hand() const {
            for (size_t i=0; i < cardsh.size(); ++i) {
                cout << "Human player " << nameh << "'s hand: "
                << "[" << i << "] " << cardsh[i] << "\n";
            }
        }

        //REQUIRES Player has at least one card
        //EFFECTS  Player adds one card to hand and removes one card from hand.
        void add_and_discard(const Card &upcard){
            print_hand();
            cout << "Discard upcard: [-1]\n";
            cout << "Human player " << nameh << ", please select a card to discard:\n";
            int discard_num;
            cin >> discard_num;
            if(discard_num != -1){
                cardsh.erase(cardsh.begin() + discard_num);
                cardsh.push_back(upcard);
                std::sort(cardsh.begin(), cardsh.end());
            }
            std::sort(cardsh.begin(), cardsh.end());
        }

        //REQUIRES Player has at least one card, trump is a valid suit
        //EFFECTS  Leads one Card from Player's hand according to their strategy
        //  "Lead" means to play the first Card in a trick.  The card
        //  is removed the player's hand.
        Card lead_card(const std::string &trump){
            print_hand();
            cout << "Human player " << nameh << ", please select a card:\n";
            int play_num;
            cin >> play_num;
            Card tempcard = cardsh[play_num];
            cardsh.erase(cardsh.begin() + play_num);
            return tempcard;
        }

        //REQUIRES Player has at least one card, trump is a valid suit
        //EFFECTS  Plays one Card from Player's hand according to their strategy.
        //  The card is removed from the player's hand.
        Card play_card(const Card &led_card, const std::string &trump){
            lead_card(trump);
        }

        // Maximum number of cards in a player's hand
        static const int MAX_HAND_SIZE = 5;

        // Needed to avoid some compiler errors
        ~HumanPlayer() {}

        //EFFECTS: Prints player's name to os
        std::ostream & operator<<(std::ostream &os, const Player &p){
            os << p.get_name() << endl;
            return os;
        }
    }
}
