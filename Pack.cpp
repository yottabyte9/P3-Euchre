//Project UID 1d9f47bfc76643019cfbf037641defe1

#include <sstream>
#include "Pack.h"

using namespace std;
  
  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  Pack::Pack(){
    cards[0] = Card(Card::RANK_NINE, Card::SUIT_SPADES);
    cards[1] = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    cards[2] = Card(Card::RANK_JACK, Card::SUIT_SPADES);
    cards[3] = Card(Card::RANK_QUEEN, Card::SUIT_SPADES);
    cards[4] = Card(Card::RANK_KING, Card::SUIT_SPADES);
    cards[5] = Card(Card::RANK_ACE, Card::SUIT_SPADES);
    cards[6] = Card(Card::RANK_NINE, Card::SUIT_HEARTS);
    cards[7] = Card(Card::RANK_TEN, Card::SUIT_HEARTS);
    cards[8] = Card(Card::RANK_JACK, Card::SUIT_HEARTS);
    cards[9] = Card(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    cards[10] = Card(Card::RANK_KING, Card::SUIT_HEARTS);
    cards[11] = Card(Card::RANK_ACE, Card::SUIT_HEARTS);
    cards[12] = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    cards[13] = Card(Card::RANK_TEN, Card::SUIT_CLUBS);
    cards[14] = Card(Card::RANK_JACK, Card::SUIT_CLUBS);
    cards[15] = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);
    cards[16] = Card(Card::RANK_KING, Card::SUIT_CLUBS);
    cards[17] = Card(Card::RANK_ACE, Card::SUIT_CLUBS);
    cards[18] = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    cards[19] = Card(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    cards[20] = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    cards[21] = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    cards[22] = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    cards[23] = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    next = 0;
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input){
    for(int i = 0; i < PACK_SIZE; i++) {
      std::string rankI;
      pack_input >> rankI;
      std::string middle;
      pack_input >> middle;
      std::string suitI;
      pack_input >> suitI;
      cards[i] = Card(rankI, suitI);
    }

    next = 0;
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    next +=1;
    return cards[next-1];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
    for(int i=0; i<7; i++){ //iterates 7 times
      std::array<Card, PACK_SIZE/2> cards1;
      for(int j=0; j<PACK_SIZE/2; j++){
        cards1[j] = cards[j];
      }
      std::array<Card, PACK_SIZE/2> cards2;
      for(int j=0; j<PACK_SIZE/2; j++){
        cards2[j] = cards[j+PACK_SIZE/2];
      }
      //std::array<Card, PACK_SIZE> cardsf;
      int counter = 0;
      for(int k=0; k<PACK_SIZE-1; k+=2){
        cards[k] = cards2[counter];
        cards[k+1] = cards1[counter];
        cout << cards[k] << endl;
        cout << cards[k+1] << endl;
        counter ++;
      }
    }
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    return PACK_SIZE - next == 0;
  }
