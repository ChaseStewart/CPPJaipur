// cards.cpp
// cards and deck member implementations

#include <string>
#include <algorithm>
#include <random>
#include <iostream>

#include "cards.hpp"

using namespace std;

// define printing a card as printing the name field
ostream& operator<<(ostream& os, const card& c)
{
    os << c.name;
    return os;
}

// return string name corresponding to cardType
string card::typeToName(cardType t)
{
   switch(t)
   {
      case CARD_DIAMONDS:
         return "Diamonds";
      case CARD_GOLD:
         return "Gold";
      case CARD_SILVER:
         return "Silver";
      case CARD_SPICES:
         return "Spices";
      case CARD_CLOTH:
         return "Cloth";
      case CARD_LEATHER:
         return "Leather";
      case CARD_CAMELS:
         return "Camels";
      default:
         return "INVALID!";
   };
}

// remove and return top card from deck
card deck::popCard()
{
   if (isEmpty())
   {
      return card(CARD_INVALID);
   }
   cardType retVal = cards.back().getType(); 
   cards.pop_back(); 
   return retVal;
}

// fill the deck with cards and shuffle
// also ensure the top 3 cards are camels
void deck::shuffle()
{
   // Create a random number generator
   random_device rd;
   mt19937 g(rd());
   std::shuffle(cards.begin(), cards.end(), g); 
}

void deck::init()
{
   cards.clear();


   // we take out 3 camels because they need to go in the market
   for (int i=0; i< NUM_CAMELS-3; i++) {
      card c(CARD_CAMELS);
      cards.push_back(c);
   }

   for (int i=0; i< NUM_DIAMONDS; i++) {
      card c(CARD_DIAMONDS);
      cards.push_back(c);
   }

   for (int i=0; i< NUM_GOLD; i++) {
      card c(CARD_GOLD);
      cards.push_back(c);
   }

   for (int i=0; i< NUM_SILVER; i++) {
      card c(CARD_SILVER);
      cards.push_back(c);
   }

   for (int i=0; i< NUM_CLOTH; i++) {
      card c(CARD_CLOTH);
      cards.push_back(c);
   }

   for (int i=0; i< NUM_SPICE; i++) {
      card c(CARD_SPICES);
      cards.push_back(c);
   }

   for (int i=0; i< NUM_LEATHER; i++) {
      card c(CARD_LEATHER);
      cards.push_back(c);
   }

   // ensures we will "pop" 3 camels into the market
   shuffle();
   cards.push_back(card(CARD_CAMELS));
   cards.push_back(card(CARD_CAMELS));
   cards.push_back(card(CARD_CAMELS));
}
