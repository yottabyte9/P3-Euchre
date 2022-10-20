// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_card_get_suit) {
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    string trump = Card::SUIT_DIAMONDS;
    ASSERT_EQUAL(Card::SUIT_DIAMONDS, c.get_suit(trump));    
}

TEST(test_card_face_or_ace) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(c.is_face_or_ace(), true);
    Card c1(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c1.is_face_or_ace(), true);
    Card c2(Card::RANK_TEN, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c2.is_face_or_ace(), false);
    Card c3(Card::RANK_NINE, Card::SUIT_CLUBS);
    ASSERT_EQUAL(c3.is_face_or_ace(), false);
}

TEST(test_card_comprehensive) {
    string trump = Card::SUIT_DIAMONDS; 
    
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(false, c.is_right_bower(trump));
    ASSERT_EQUAL(true, c.is_left_bower(trump));
    ASSERT_EQUAL(true, c.is_trump(trump));

    Card c1(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(false, c1.is_right_bower(trump));
    ASSERT_EQUAL(false, c1.is_left_bower(trump));
    ASSERT_EQUAL(false, c1.is_trump(trump));

    Card c2(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(true, c2.is_right_bower(trump));  
    ASSERT_EQUAL(false, c2.is_left_bower(trump));  
    ASSERT_EQUAL(true, c2.is_trump(trump));

    Card c3(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_EQUAL(false, c3.is_right_bower(trump));
    ASSERT_EQUAL(false, c3.is_left_bower(trump));
    ASSERT_EQUAL(false, c3.is_trump(trump));

}

TEST(operators){
    string trump = Card::SUIT_DIAMONDS; //d > c > h > s
    Card c1(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_JACK, Card::SUIT_HEARTS);
    Card c3(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card c4(Card::RANK_TEN, Card::SUIT_CLUBS);
    Card c5(Card::RANK_ACE, Card::SUIT_SPADES);
    Card c6(Card::RANK_KING, Card::SUIT_HEARTS);
    Card c7(Card::RANK_KING, Card::SUIT_DIAMONDS);
    Card c8(Card::RANK_KING, Card::SUIT_DIAMONDS);

    ASSERT_TRUE( c1 > c2 );
    ASSERT_FALSE( c2 > c3 );
    ASSERT_FALSE( c3 < c4 );
    ASSERT_TRUE( c4 < c5 );
    ASSERT_TRUE( c6 < c7);
    ASSERT_TRUE( c7 == c8 );
    ASSERT_FALSE( c7 == c6 );
    ASSERT_TRUE( c7 >= c8 );
    ASSERT_FALSE( c6 >= c7);
    ASSERT_TRUE( c7 <= c8 );
    ASSERT_TRUE( c6 <= c7);
    ASSERT_FALSE( c7 != c8 );
    ASSERT_TRUE( c7 != c6 );
    
    ASSERT_TRUE( Card_less(c2, c1, trump) );
    ASSERT_TRUE( Card_less(c3, c1, trump) );
    ASSERT_FALSE( Card_less(c5, c4, trump) );
    ASSERT_TRUE( Card_less(c6, c7, trump) );

    Card led1 = Card(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card led2 = Card(Card::RANK_JACK, Card::SUIT_DIAMONDS);
    ASSERT_TRUE( Card_less( c2, c1, led1, trump));
    ASSERT_TRUE( Card_less( c3, c1, led1, trump));
    ASSERT_TRUE( Card_less( c5, c4, led1, trump));
    ASSERT_TRUE( Card_less( c6, c7, led1, trump));
    ASSERT_TRUE( Card_less( c4, c7, led2, trump));
    ASSERT_TRUE( Card_less( c6, c4, led1, trump));
    ASSERT_TRUE( Card_less( c5, c4, led1, trump));
}

TEST(test_cardless) {
    string trump = Card::SUIT_SPADES; 
    Card c1(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);
    Card c2(Card::RANK_NINE, Card::SUIT_CLUBS);
    Card led1(Card::RANK_JACK, Card::SUIT_CLUBS);
    ASSERT_TRUE(Card_less(c2, c1, led1, trump));
}

TEST(suit_next) {
    string trump1 = Card::SUIT_DIAMONDS; 
    string trump2 = Card::SUIT_CLUBS; 
    Card c(Card::RANK_JACK, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS), Card::SUIT_HEARTS);
    ASSERT_NOT_EQUAL(Suit_next(Card::SUIT_CLUBS), Card::SUIT_CLUBS);
}

TEST_MAIN()
