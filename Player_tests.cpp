// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include "Card.h"

#include <iostream>
#include <vector>

using namespace std;

TEST(test_player_get_name_empty) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;

    Player * empty = Player_factory("", "Simple");
    ASSERT_EQUAL("", empty->get_name());
    delete empty;

    Player * r = Player_factory("r", "Simple");
    ASSERT_EQUAL("r", r->get_name());
    delete r;
}

TEST(test_add_card){
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_JACK, Card::SUIT_CLUBS);
    alice->add_card(c1);
    //ASSERT_EQUAL(return_card(0,alice), c1);
    Card c2(Card::RANK_TEN, Card::SUIT_CLUBS);
    alice->add_card(c2);
    //ASSERT_EQUAL(return_card(1,alice), c2);
    alice->add_card(c2);
    alice->add_card(c2);
    alice->add_card(c1);
   // ASSERT_EQUAL(return_card(4,alice), c1);
    delete alice;
}

TEST(test_make_trump_1){
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); //left bower
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    string orderup;
    Card upcard1 = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);

    bool isDealer1 = false;
    int round1 = 1;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    ASSERT_TRUE(alice->make_trump(upcard1, isDealer1, round1, orderup));
    ASSERT_EQUAL(orderup, Card::SUIT_DIAMONDS);
    delete alice;
}

TEST(test_make_trump_2){
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); //left bower
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    string orderup;
    Card upcard2 = Card(Card::RANK_TEN, Card::SUIT_SPADES);

    bool isDealer1 = false;
    int round2 = 2;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    ASSERT_FALSE(alice->make_trump(upcard2, isDealer1, round2, orderup)); // change
    ASSERT_EQUAL(orderup, "");
    delete alice;
}

TEST(test_make_trump_3){
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); //left bower
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    string orderup;
    Card upcard2 = Card(Card::RANK_TEN, Card::SUIT_SPADES);

    bool isDealer1 = false;
    int round1 = 1;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    ASSERT_FALSE(alice->make_trump(upcard2, isDealer1, round1, orderup));
    ASSERT_EQUAL(orderup, "");
    delete alice;
}

TEST(test_make_trump_4){
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); //left bower
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    string orderup;
    Card upcard1 = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);

    bool isDealer1 = false;
    int round2 = 2;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    ASSERT_TRUE(alice->make_trump(upcard1, isDealer1, round2, orderup)); // change
    ASSERT_EQUAL(orderup, Card::SUIT_HEARTS);
    delete alice;
}

TEST(test_make_trump_5){
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); //left bower
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    string orderup;
    Card upcard3 = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);

    bool isDealer1 = false;
    int round1 = 1;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    ASSERT_FALSE(alice->make_trump(upcard3, isDealer1, round1, orderup));
    ASSERT_EQUAL(orderup, "");
    delete alice;
}

TEST(test_make_trump_6){
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); //left bower
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    string orderup;
    Card upcard3 = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);

    bool isDealer1 = false;
    int round2 = 2;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    ASSERT_TRUE(alice->make_trump(upcard3, isDealer1, round2, orderup)); // change
    ASSERT_EQUAL(orderup, Card::SUIT_SPADES);
    delete alice;
}

TEST(test_make_trump_7){
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); //left bower
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    string orderup;
    Card upcard3 = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);

    bool isDealer2 = true;
    int round2 = 2;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    ASSERT_TRUE(alice->make_trump(upcard3, isDealer2, round2, orderup));
    ASSERT_EQUAL(orderup, Card::SUIT_SPADES);
    delete alice;
}

TEST(test_make_trump_8){
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); //left bower
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    string orderup;
    Card upcard3 = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);

    bool isDealer2 = true;
    int round1 = 1;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    ASSERT_FALSE(alice->make_trump(upcard3, isDealer2, round1, orderup));
    ASSERT_EQUAL(orderup, "");
    delete alice;
}

TEST(test_add_and_discard_1) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); 
    Card c3(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    Card upcard1 = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    alice->add_and_discard(upcard1);
    Card send1 = alice->lead_card(Card::SUIT_DIAMONDS);
    Card correct1(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(send1, correct1);
    delete alice;
} 

TEST(test_add_and_discard_2) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); 
    Card c3(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_KING, Card::SUIT_SPADES);
    Card upcard2 = Card(Card::RANK_NINE, Card::SUIT_SPADES);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    alice->add_and_discard(upcard2);
    Card send2 = alice->lead_card(Card::SUIT_SPADES);
    Card correct2(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(send2, correct2);
    delete alice;
}

TEST(test_add_and_discard_3) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); 
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card upcard3 = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    alice->add_and_discard(upcard3);
    Card send3 = alice->lead_card(Card::SUIT_DIAMONDS);
    Card correct3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(send3, correct3);
    delete alice;
}



TEST(test_add_and_discard_4) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card upcard4 = Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);

    alice->add_card(c1);

    alice->add_and_discard(upcard4);
    Card send4 = alice->lead_card(Card::SUIT_DIAMONDS);
    Card correct4(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(send4, correct4);
    delete alice;
}

TEST(test_add_and_discard_5) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card upcard5 = Card(Card::RANK_NINE, Card::SUIT_CLUBS);

    alice->add_card(c1);

    alice->add_and_discard(upcard5);
    Card send5 = alice->lead_card(Card::SUIT_CLUBS);
    Card correct5(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(send5, correct5);
    delete alice;
}

TEST(test_add_and_discard_6) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); 
    Card c3(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card upcard6 = Card(Card::RANK_NINE, Card::SUIT_DIAMONDS);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    alice->add_and_discard(upcard6);
    Card send6 = alice->lead_card(Card::SUIT_DIAMONDS);
    Card correct6(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(send6, correct6);
    delete alice;
}

TEST(test_add_and_discard_7) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_TEN, Card::SUIT_DIAMONDS); 
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card upcard7 = Card(Card::RANK_ACE, Card::SUIT_DIAMONDS);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);

    alice->add_and_discard(upcard7);
    Card send7 = alice->lead_card(Card::SUIT_DIAMONDS);
    Card correct7(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(send7, correct7);
    delete alice;
}

TEST(test_play_card_1) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); 
    Card c3(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_KING, Card::SUIT_DIAMONDS);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);
    Card consider1(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card correct1(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(alice->play_card(consider1, "Diamonds"), correct1);
    delete alice;
}

TEST(test_play_card_2) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); 
    Card c3(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_KING, Card::SUIT_SPADES);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    Card consider2(Card::RANK_KING, Card::SUIT_CLUBS);
    Card correct2(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(alice->play_card(consider2, "Diamonds"), correct2);
    delete alice;
}

TEST(test_play_card_3) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); 
    Card c3(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c5(Card::RANK_KING, Card::SUIT_SPADES);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    Card consider3(Card::RANK_KING, Card::SUIT_CLUBS);
    Card correct3(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(alice->play_card(consider3, "Spades"), correct3);
    delete alice;
}

TEST(test_play_card_4) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c2(Card::RANK_ACE, Card::SUIT_SPADES); 
    Card c3(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c5(Card::RANK_KING, Card::SUIT_SPADES);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    Card consider4(Card::RANK_JACK, Card::SUIT_SPADES);
    Card correct4(Card::RANK_ACE, Card::SUIT_SPADES);
    ASSERT_EQUAL(alice->play_card(consider4, "Hearts"), correct4);
    delete alice;
}

TEST(test_play_card_5) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_SPADES);
    Card c2(Card::RANK_JACK, Card::SUIT_SPADES); 
    Card c3(Card::RANK_NINE, Card::SUIT_SPADES);
    Card c4(Card::RANK_TEN, Card::SUIT_SPADES);
    Card c5(Card::RANK_KING, Card::SUIT_SPADES);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    Card consider5(Card::RANK_ACE, Card::SUIT_SPADES);
    Card correct5(Card::RANK_JACK, Card::SUIT_SPADES);
    ASSERT_EQUAL(alice->play_card(consider5, "Spades"), correct5);
    delete alice;
}

TEST(test_play_card_6) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); 
    Card c3(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_NINE, Card::SUIT_HEARTS);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    Card consider6(Card::RANK_ACE, Card::SUIT_CLUBS);
    Card correct6(Card::RANK_NINE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(alice->play_card(consider6, "Spades"), correct6);
    delete alice;
}

TEST(test_play_card_7) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_QUEEN, Card::SUIT_HEARTS);

    alice->add_card(c1);

    Card consider7(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card correct7(Card::RANK_QUEEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(alice->play_card(consider7, "Spades"), correct7);
    delete alice;
}

TEST(test_play_card_8) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_TEN, Card::SUIT_CLUBS);

    alice->add_card(c1);

    Card consider8(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card correct8(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(alice->play_card(consider8, "Spades"), correct8);
    delete alice;
}

TEST(test_play_card_9) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS); 
    Card c3(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_NINE, Card::SUIT_HEARTS);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    Card consider9(Card::RANK_ACE, Card::SUIT_HEARTS);
    Card correct9(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(alice->play_card(consider9, "Hearts"), correct9);
    delete alice;
}

TEST(test_play_card_10) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_TEN, Card::SUIT_HEARTS);
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS); 
    Card c3(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c5(Card::RANK_NINE, Card::SUIT_HEARTS);

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    Card consider10(Card::RANK_ACE, Card::SUIT_DIAMONDS);
    Card correct10(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(alice->play_card(consider10, "Hearts"), correct10);
    delete alice;
}

TEST(test_play_card_11) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_TEN, Card::SUIT_DIAMONDS);
    Card c3(Card::RANK_NINE, Card::SUIT_SPADES);

    Card led1(Card::RANK_KING, Card::SUIT_DIAMONDS);
    string trump = Card::SUIT_HEARTS;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);

    alice->play_card(led1, trump); //will play c2 and remove c2 
    ASSERT_EQUAL(alice->play_card(led1, trump), c1); 

    delete alice;
}

TEST_MAIN()
