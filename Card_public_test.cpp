// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"
#include "Card.h"
#include "Pack.h"

#include <iostream>
#include <vector>

using namespace std;

TEST(test_player_get_name) {
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
    ASSERT_EQUAL(return_card(0,alice), c1);
    Card c2(Card::RANK_TEN, Card::SUIT_CLUBS);
    alice->add_card(c2);
    ASSERT_EQUAL(return_card(1,alice), c2);
    alice->add_card(c2);
    alice->add_card(c2);
    alice->add_card(c1);
    ASSERT_EQUAL(return_card(4,alice), c1);
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
    Card upcard1 = Card(Card::RANK_KING, CARD::SUIT_DIAMONDS);
    Card upcard2 = Card(Card::RANK_TEN, CARD::SUIT_SPADES);

    bool isDealer = false;
    int round1 = 1;
    int round2 = 2;

    alice->add_card(c1);
    alice->add_card(c2);
    alice->add_card(c3);
    alice->add_card(c4);
    alice->add_card(c5);

    ASSERT_TRUE(make_trump(upcard1, isdealer, round1, orderup));
    ASSERT_TRUE(make_trump(upcard2, isdealer, round2, orderup));
}

// Add more tests here

TEST_MAIN()
