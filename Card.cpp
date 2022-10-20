// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;


Card::Card(){
    suit = Card::SUIT_SPADES;
    rank = Card::RANK_TWO;
}

Card::Card(const string &rank_in, const string &suit_in){
    suit = suit_in;
    rank = rank_in;
}

string Card::get_rank() const{
    return rank;
}

string Card::get_suit() const{
    return suit;
}

string Card::get_suit(const string &trump) const{
    Card lbower = Card("Jack", Suit_next(trump));
    if(lbower == Card(rank, suit)){ 
        return trump;
    }
    return suit;
}

bool Card::is_face_or_ace() const{
    if( rank == RANK_JACK || rank == RANK_QUEEN || 
    rank == RANK_KING || rank == RANK_ACE ){
        return true;
    }
    return false;
    
}
bool Card::is_right_bower(const string &trump) const{
    return Card("Jack", trump) == Card(rank, suit);
}
bool Card::is_left_bower(const string &trump) const{
    return Card("Jack", Suit_next(trump)) == Card(rank, suit);
}
bool Card::is_trump(const string &trump) const{
    return (get_suit(trump) == trump);
}

bool operator<(const Card &lhs, const Card &rhs){
    double ranknuml = 9.0;
    if(lhs.get_rank().compare(Card::RANK_ACE)==0){
        ranknuml = 14;
    }
    if(lhs.get_rank().compare(Card::RANK_KING)==0){
        ranknuml = 13;
    }
    if(lhs.get_rank().compare(Card::RANK_QUEEN)==0){
        ranknuml = 12;
    }
    if(lhs.get_rank().compare(Card::RANK_JACK)==0){
        ranknuml = 11;
    }
    if(lhs.get_rank().compare(Card::RANK_TEN)==0){
        ranknuml = 10;
    }

    if(lhs.get_suit().compare(Card::SUIT_SPADES) == 0){
        ranknuml +=0.1;
    }
    if(lhs.get_suit().compare(Card::SUIT_HEARTS) == 0){
        ranknuml +=0.2;
    }
    if(lhs.get_suit().compare(Card::SUIT_CLUBS) == 0){
        ranknuml +=0.3;
    }
    if(lhs.get_suit().compare(Card::SUIT_DIAMONDS) == 0){
        ranknuml +=0.4;
    }

    double ranknumr = 9.0;
    if(rhs.get_rank().compare(Card::RANK_ACE)==0){
        ranknumr = 14;
    }
    if(rhs.get_rank().compare(Card::RANK_KING)==0){
        ranknumr = 13;
    }
    if(rhs.get_rank().compare(Card::RANK_QUEEN)==0){
        ranknumr = 12;
    }
    if(rhs.get_rank().compare(Card::RANK_JACK)==0){
        ranknumr = 11;
    }
    if(rhs.get_rank().compare(Card::RANK_TEN)==0){
        ranknumr = 10;
    }

    if(rhs.get_suit().compare(Card::SUIT_SPADES) == 0){
        ranknumr +=0.1;
    }
    if(rhs.get_suit().compare(Card::SUIT_HEARTS) == 0){
        ranknumr +=0.2;
    }
    if(rhs.get_suit().compare(Card::SUIT_CLUBS) == 0){
        ranknumr +=0.3;
    }
    if(rhs.get_suit().compare(Card::SUIT_DIAMONDS) == 0){ //test case suit different
        ranknumr +=0.4;
    }

    return( ranknuml < ranknumr );
}

bool operator<=(const Card &lhs, const Card &rhs){
    return (lhs < rhs || lhs == rhs);
}

bool operator>(const Card &lhs, const Card &rhs){
    return !(lhs <= rhs);
}

bool operator>=(const Card &lhs, const Card &rhs) {
    return !(lhs < rhs);
}

bool operator==(const Card &lhs, const Card &rhs) {
    if (lhs.get_rank() == rhs.get_rank()) {
        if (lhs.get_suit() == rhs.get_suit()) {
            return true;
        }
    }
    return false;
}

bool operator!=(const Card &lhs, const Card &rhs) {
    return !(lhs == rhs);
}

std::string Suit_next(const std::string &suit){
    if(suit.compare(Card::SUIT_DIAMONDS) == 0){
        return Card::SUIT_HEARTS;
    }
    if(suit.compare(Card::SUIT_HEARTS) == 0){
        return Card::SUIT_DIAMONDS;
    }
    if(suit.compare(Card::SUIT_CLUBS) == 0){
        return Card::SUIT_SPADES;
    }
    return Card::SUIT_CLUBS;
}

std::ostream & operator<<(std::ostream &os, const Card &card){
    os << card.get_rank() << " of " << card.get_suit();
    return os;
}

bool Card_less(const Card &a, const Card &b, const std::string &trump){
    if(a.is_trump(trump) && !b.is_trump(trump)){
        return false;
    }
    else if(!a.is_trump(trump) && b.is_trump(trump)){
        return true;
    }
    else if(a.is_trump(trump) && b.is_trump(trump)){
        if(a.is_right_bower(trump)){
            return false;
        }
        if(b.is_right_bower(trump)){
            return true;
        }
        if(a.is_left_bower(trump)){
            return false;
        }
        if(b.is_left_bower(trump)){
            return true;
        }
    }
    if(a >= b){
        return false;
    }
    return true;
}

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    if(a.is_trump(trump) && b.is_trump(trump)){ // if they are both trumps
        return Card_less(a, b, trump);
    }
    if(a.is_trump(trump) && !b.is_trump(trump)){ // if only a is trump
        return false;
    }
    if(!a.is_trump(trump) && b.is_trump(trump)){ // if only b is trump
        return true;
    }
    if(a.get_suit(trump) == led_card.get_suit(trump) && 
    b.get_suit() == led_card.get_suit()){ // if both are led suit
        return a<b;
    }
    if(a.get_suit(trump) == led_card.get_suit(trump) && 
    !(b.get_suit() == led_card.get_suit())){ // if a is led suit
        return false;
    }
    if(!(a.get_suit(trump) == led_card.get_suit(trump))&& 
    b.get_suit() == led_card.get_suit()){ // if b is led suit
        return true;
    }
    return a<b;
}
