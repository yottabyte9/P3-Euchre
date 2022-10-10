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

TEST(test_make_trump){
    Player * alice = Player_factory("Alice", "Simple");
    Card c1(Card::RANK_NINE, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS); //left bower
    Card c3(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    string orderup = Card::SUIT_DIAMONDS;
    Card upcard1 = Card(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card upcard2 = Card(Card::RANK_TEN, Card::SUIT_SPADES);
    Card upcard3 = Card(Card::RANK_QUEEN, Card::SUIT_CLUBS);

    bool isDealer1 = false;
    bool isDealer2 = true;
    int round1 = 1;
    int round2 = 2;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    ASSERT_TRUE(alice->make_trump(upcard1, isDealer1, round1, orderup));
    ASSERT_TRUE(alice->make_trump(upcard2, isDealer1, round2, orderup));
    ASSERT_FALSE(alice->make_trump(upcard2, isDealer1, round1, orderup));
    ASSERT_TRUE(alice->make_trump(upcard1, isDealer1, round2, orderup));
    ASSERT_FALSE(alice->make_trump(upcard3, isDealer1, round1, orderup));
    ASSERT_FALSE(alice->make_trump(upcard3, isDealer1, round2, orderup));
    ASSERT_TRUE(alice->make_trump(upcard3, isDealer2, round2, orderup));
    ASSERT_FALSE(alice->make_trump(upcard3, isDealer2, round1, orderup));
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
    Card correct2(Card::RANK_KING, Card::SUIT_SPADES);
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
TEST_MAIN()
