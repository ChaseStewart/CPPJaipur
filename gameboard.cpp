// gameboard.cpp 
// gameboard member implementations

#include <vector>
#include <iostream>

#include "cards.hpp"
#include "gameboard.hpp"
#include "tokens.hpp"

using namespace std;

// setup deck, market, tokens
gameBoard::gameBoard()
{
   reset();
}

// print all public info about game board 
void gameBoard::printGameState()
{
   cout << "Board State:" << endl;

   printMarketState(true);
   printTokenValues();
   cout << "Cards in deck: " << deckSize() << endl;
}

void gameBoard::reset()
{
   // setup deck
   gameDeck.init();

   // setup market by drawing 5 from the deck
   // because we stuck 3 camels at the end,
   // at least 3 camels in the market is guaranteed
   for (int i=0; i<MARKET_CARD_LEN; i++)
   {
      addMarketCard(gameDeck.popCard());
   }

   // TODO another candidate for temp struct and reduced logic

   // goods tokens are not shuffled
   vector<token> diamondsVec;
   diamondsVec.push_back(token(TOKEN_DIAMONDS, 5));
   diamondsVec.push_back(token(TOKEN_DIAMONDS, 5));
   diamondsVec.push_back(token(TOKEN_DIAMONDS, 5));
   diamondsVec.push_back(token(TOKEN_DIAMONDS, 7));
   diamondsVec.push_back(token(TOKEN_DIAMONDS, 7));
   diamondsTokens.init(diamondsVec);  

   vector<token> goldVec;
   goldVec.push_back(token(TOKEN_GOLD, 5));
   goldVec.push_back(token(TOKEN_GOLD, 5));
   goldVec.push_back(token(TOKEN_GOLD, 5));
   goldVec.push_back(token(TOKEN_GOLD, 6));
   goldVec.push_back(token(TOKEN_GOLD, 6));
   goldTokens.init(goldVec);  

   vector<token> silverVec;
   silverVec.push_back(token(TOKEN_SILVER, 5));
   silverVec.push_back(token(TOKEN_SILVER, 5));
   silverVec.push_back(token(TOKEN_SILVER, 5));
   silverVec.push_back(token(TOKEN_SILVER, 5));
   silverVec.push_back(token(TOKEN_SILVER, 5));
   silverTokens.init(silverVec);  

   vector<token> spicesVec;
   spicesVec.push_back(token(TOKEN_SPICES, 1));
   spicesVec.push_back(token(TOKEN_SPICES, 1));
   spicesVec.push_back(token(TOKEN_SPICES, 2));
   spicesVec.push_back(token(TOKEN_SPICES, 2));
   spicesVec.push_back(token(TOKEN_SPICES, 3));
   spicesVec.push_back(token(TOKEN_SPICES, 3));
   spicesVec.push_back(token(TOKEN_SPICES, 5));
   spicesTokens.init(spicesVec);  

   vector<token> clothVec;
   clothVec.push_back(token(TOKEN_CLOTH, 1));
   clothVec.push_back(token(TOKEN_CLOTH, 1));
   clothVec.push_back(token(TOKEN_CLOTH, 2));
   clothVec.push_back(token(TOKEN_CLOTH, 2));
   clothVec.push_back(token(TOKEN_CLOTH, 3));
   clothVec.push_back(token(TOKEN_CLOTH, 3));
   clothVec.push_back(token(TOKEN_CLOTH, 5));
   clothTokens.init(clothVec);  

   vector<token> leatherVec;
   leatherVec.push_back(token(TOKEN_LEATHER, 1));
   leatherVec.push_back(token(TOKEN_LEATHER, 1));
   leatherVec.push_back(token(TOKEN_LEATHER, 1));
   leatherVec.push_back(token(TOKEN_LEATHER, 1));
   leatherVec.push_back(token(TOKEN_LEATHER, 1));
   leatherVec.push_back(token(TOKEN_LEATHER, 1));
   leatherVec.push_back(token(TOKEN_LEATHER, 2));
   leatherVec.push_back(token(TOKEN_LEATHER, 3));
   leatherVec.push_back(token(TOKEN_LEATHER, 4));
   leatherTokens.init(leatherVec);
   
   vector<token> camelsVec;
   camelsVec.push_back(token(TOKEN_CAMELS, 5));
   camelsTokens.init(camelsVec);

   vector<token> threeKindVec;
   threeKindVec.push_back(token(TOKEN_3_KIND, 1));
   threeKindVec.push_back(token(TOKEN_3_KIND, 1));
   threeKindVec.push_back(token(TOKEN_3_KIND, 2));
   threeKindVec.push_back(token(TOKEN_3_KIND, 2));
   threeKindVec.push_back(token(TOKEN_3_KIND, 2));
   threeKindVec.push_back(token(TOKEN_3_KIND, 3));
   threeKindVec.push_back(token(TOKEN_3_KIND, 3));
   threeKindTokens.init(threeKindVec);
   threeKindTokens.shuffle();

   vector<token> fourKindVec;
   fourKindVec.push_back(token(TOKEN_4_KIND, 4));
   fourKindVec.push_back(token(TOKEN_4_KIND, 4));
   fourKindVec.push_back(token(TOKEN_4_KIND, 5));
   fourKindVec.push_back(token(TOKEN_4_KIND, 5));
   fourKindVec.push_back(token(TOKEN_4_KIND, 6));
   fourKindVec.push_back(token(TOKEN_4_KIND, 6));
   fourKindTokens.init(fourKindVec);
   fourKindTokens.shuffle();

   vector<token> fiveKindVec;
   fiveKindVec.push_back(token(TOKEN_5_KIND, 8));
   fiveKindVec.push_back(token(TOKEN_5_KIND, 8));
   fiveKindVec.push_back(token(TOKEN_5_KIND, 9));
   fiveKindVec.push_back(token(TOKEN_5_KIND, 10));
   fiveKindVec.push_back(token(TOKEN_5_KIND, 10));
   fiveKindTokens.init(fiveKindVec);
   fiveKindTokens.shuffle();
  
}

// pop the top token off the tokenList for provided tokenType
// caller should check for TOKEN_INVALID and not accept if received
token gameBoard::getToken(tokenType t)
{
   switch(t)
   {
      case TOKEN_DIAMONDS:
         return (diamondsTokens.isEmpty()) ? token(TOKEN_INVALID, -1) : diamondsTokens.popToken();
      case TOKEN_GOLD:
         return (goldTokens.isEmpty()) ? token(TOKEN_INVALID, -1) : goldTokens.popToken();
      case TOKEN_SILVER:
         return (silverTokens.isEmpty()) ? token(TOKEN_INVALID, -1) : silverTokens.popToken();
      case TOKEN_SPICES:
         return (spicesTokens.isEmpty()) ? token(TOKEN_INVALID, -1) : spicesTokens.popToken();
      case TOKEN_CLOTH:
         return (clothTokens.isEmpty()) ? token(TOKEN_INVALID, -1) : clothTokens.popToken();
      case TOKEN_LEATHER:
         return (leatherTokens.isEmpty()) ? token(TOKEN_INVALID, -1) : leatherTokens.popToken();
      case TOKEN_3_KIND:
         return (threeKindTokens.isEmpty()) ? token(TOKEN_INVALID, -1) : threeKindTokens.popToken();
      case TOKEN_4_KIND:
         return (fourKindTokens.isEmpty()) ? token(TOKEN_INVALID, -1) : fourKindTokens.popToken();
      case TOKEN_5_KIND:
         return (fiveKindTokens.isEmpty()) ? token(TOKEN_INVALID, -1) : fiveKindTokens.popToken();
      default:
         return token(TOKEN_INVALID, -1);
   };
}

// print just the market contents
// either in a compressed or multi-line format, per arg
void gameBoard::printMarketState(bool compressed)
{
   if (compressed)
   {
      cout << endl << "Market Cards: [";
      for (int i=0; i < MARKET_CARD_LEN; i++)
      {
         cout << marketCards[i] << ", ";
      }
      cout << "]" << endl;
   }
   else
   {
      cout << endl << "Market Cards:" << endl;
      for (int i=0; i < MARKET_CARD_LEN; i++)
      {
         cout << i + 1 << ":\t" << marketCards[i] << endl;
      }
   }
}

// print the public and hidden token values/counts
void gameBoard::printTokenValues()
{
   cout << endl << "Token_Values (taken from right):" << endl;
   
   // The "Mark B trick" again!
   struct printTokenStruct_t {
      string name;
      tokenList tokenlist;
   };

   printTokenStruct_t printTokenStruct[] = {
      { "Diamonds", diamondsTokens}, // take out 3 camels to add at end
      { "Gold", goldTokens},
      { "Silver", silverTokens},
      { "Spices", spicesTokens},
      { "Cloth", clothTokens},
      { "Leather", leatherTokens},
      { "Camels", camelsTokens}
   };

   for (auto item : printTokenStruct)
   {
      cout << "\t" << item.name << "_Tokens: [";
      for (auto token : item.tokenlist.getTokens())
      {
         cout << token << ", ";
      }
      cout << "]" << endl;

   }
   // End the "Mark B trick"

   cout << "\tThree_of_a_Kind_Tokens: " << threeKindTokens.size() << endl;
   cout << "\tFour_of_a_Kind_Tokens: " << fourKindTokens.size() << endl;
   cout << "\tFive_of_a_Kind_Tokens: " << fiveKindTokens.size() << endl;
}

// check how many tokenLists are empty
// this is an end-of-game condition to check
int gameBoard::sumEmptyTokenLists()
{
   int sum=0;
   if (diamondsTokens.isEmpty()) {sum++;}
   if (goldTokens.isEmpty()) {sum++;}
   if (silverTokens.isEmpty()) {sum++;}
   if (spicesTokens.isEmpty()) {sum++;}
   if (clothTokens.isEmpty()) {sum++;}
   if (leatherTokens.isEmpty()) {sum++;}
   return sum;
}

// take a card from the market at idx, and optionally
// draw a new one from the deck to replace the taken one
//
// re-draw is done for taking a single good or all camels
// but not done for exchanges
card gameBoard::popMarketCard(int idx, bool redraw)
{
   if (idx >= MARKET_CARD_LEN)
   {
      cout << "ERROR: failed to pull" << idx << endl;
      return card(CARD_INVALID);
   }

   card temp = marketCards[idx];
   marketCards.erase(marketCards.begin() + idx);
   if (redraw)
   {
      addMarketCard(drawCard());
   }
   return temp;
}

// return the type of market card at idx
cardType gameBoard::getMarketCardType(int idx)
{
   if (idx >= MARKET_CARD_LEN)
   {
      return CARD_INVALID;
   }
   return marketCards[idx].getType();
}
