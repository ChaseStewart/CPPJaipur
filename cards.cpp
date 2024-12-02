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

   // deconflict with the name of this function
   std::shuffle(cards.begin(), cards.end(), g); 
}

void deck::init()
{
   cards.clear();


   // The "Mark B trick" - thanks, Mark!
   struct cardInitStruct_t {
      int repetitions;
      cardType type;
   };

   cardInitStruct_t cardInitStruct[] = {
      {NUM_CAMELS - 3, CARD_CAMELS}, // take out 3 camels to add at end
      {NUM_DIAMONDS, CARD_DIAMONDS},
      {NUM_GOLD, CARD_GOLD},
      {NUM_SILVER, CARD_SILVER},
      {NUM_SPICES, CARD_SPICES},
      {NUM_CLOTH, CARD_CLOTH},
      {NUM_LEATHER, CARD_LEATHER}
   };

   for (auto item : cardInitStruct)
   {
      for (int i=0; i< item.repetitions; i++)
      {
         card c(item.type);
         cards.push_back(c);
      }
   }
   // End the "Mark B trick"

   shuffle();

   // lastly, add the 3 CAMELS cards we held back
   // this ensures we will "pop" 3 camels into the market
   cards.push_back(card(CARD_CAMELS));
   cards.push_back(card(CARD_CAMELS));
   cards.push_back(card(CARD_CAMELS));
}
