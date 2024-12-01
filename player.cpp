// player.cpp

#include <vector>

#include "cards.hpp"
#include "player.hpp"

using namespace std;

// add a card to the hand
// since this only happens in controlled actions
// there is no check for hand limit in this function
// it was messing up the way exchange was implemented
void player::addCard(card c)
{ 
   if (CARD_CAMELS != c.getType())
   { 
      hand.push_back(c);
   }
   else
   {
      herd.push_back(c);
   }
}

// add a token to the appropriate tokenList
void player::addToken(token t)
{
   tokenType type = t.getType(); 
   if( type == TOKEN_INVALID)
   {
      return;
   }

   switch (type)
   {
      case TOKEN_DIAMONDS:
         cout << "\t" << name << " got a Diamond token" << endl;
         diamondsTokens.push_back(t);
         break;
      case TOKEN_GOLD:
         cout << "\t" << name << " got a Gold token" << endl;
         goldTokens.push_back(t);
         break;
      case TOKEN_SILVER:
         cout << "\t" << name << " got a Silver token" << endl;
         silverTokens.push_back(t);
         break;
      case TOKEN_SPICES:
         cout << "\t" << name << " got a Spices token" << endl;
         spicesTokens.push_back(t);
         break;
      case TOKEN_CLOTH:
         cout << "\t" << name << " got a Cloth token" << endl;
         clothTokens.push_back(t);
         break;
      case TOKEN_LEATHER:
         cout << "\t" << name << " got a Leather token" << endl;
         leatherTokens.push_back(t);
         break;
      case TOKEN_3_KIND:
         cout << "\t" << name << " got a 3-of-a-Kind token" << endl;
         threeKindTokens.push_back(t);
         break;
      case TOKEN_4_KIND:
         cout << "\t" << name << " got a 4-of-a-Kind token" << endl;
         fourKindTokens.push_back(t);
         break;
      case TOKEN_5_KIND:
         cout << "\t" << name << " got a 5-of-a-Kind token" << endl;
         fiveKindTokens.push_back(t);
         break;
      case TOKEN_CAMELS:
         cout << name << " got a Camels token" << endl;
         camelsTokens.push_back(t);
         break;
      default: // TOKEN_INVALID
         break;
   };
}

// remove and return card at idx from player's hand
card player::popCard(int idx)
{
   if (idx >= HAND_LIMIT || handSize() == 0)
   {
      return card(CARD_INVALID);
   }
   card temp = hand[idx];
   hand.erase(hand.begin() + idx);
   return temp;
}

// remove and return card from player's camel "herd" 
card player::popCamel()
{
   if (handSize() == 0)
   {
      return card(CARD_INVALID);
   }
   herd.pop_back();
   return card(CARD_CAMELS);
}

// calculate player's current score from tokens
int player::calculateScore()
{
   int score = 0;
   for (auto t: diamondsTokens.getTokens())
   {
      score += t.getScore();
   }
   for (auto t: goldTokens.getTokens())
   {
      score += t.getScore();
   }
   for (auto t: silverTokens.getTokens())
   {
      score += t.getScore();
   } 
   for (auto t: spicesTokens.getTokens())
   {
      score += t.getScore();
   } 
   for (auto t: clothTokens.getTokens())
   {
      score += t.getScore();
   } 
   for (auto t: leatherTokens.getTokens())
   {
      score += t.getScore();
   } 
   for (auto t: threeKindTokens.getTokens())
   {
      score += t.getScore();
   } 
   for (auto t: fourKindTokens.getTokens())
   {
      score += t.getScore();
   } 
   for (auto t: fiveKindTokens.getTokens())
   {
      score += t.getScore();
   } 
   for (auto t: camelsTokens.getTokens())
   {
      score += t.getScore();
   }
   return score; 
}

// print player's hand and herd state
void player::printPlayerState()
{
   printHand(true);
   printHerd();
   cout << "Score: " << calculateScore();   
}


// print the cards in the player's hand
// either in a compressed or indexed format
void player::printHand(bool compressed)
{
   if (compressed)
   {
      cout << endl << "Hand Cards: [";
      for (int i=0; i < handSize(); i++)
      {
         cout << hand[i] << ", ";
      }
      cout << "]" << endl;
   }
   else
   {
      cout << endl << "Hand Cards:" << endl;
      for (int i=0; i < handSize(); i++)
      {
         cout << i + 1 << ":\t" << hand[i] << endl;
      }
   }
}

// count all cards of provided cardType
int player::countCardsByType(cardType t)
{
   int sum = 0;
   for (int i=handSize() -1; i >= 0; i--)
   {
      if (hand[i].getType() == t)
      {
         sum++;
      }
   }

   return sum;
}

// remove all cards of provided cardType
// obviously this is destructive
void player::sellCardsByType(cardType t)
{
   for (int i=handSize() -1; i >= 0; i--)
   {
      if (hand[i].getType() == t)
      {
         hand.erase(hand.begin() + i);
      }
   }
}
