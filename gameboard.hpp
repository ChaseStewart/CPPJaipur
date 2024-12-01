// gameboard.hpp
// gameboard class definitions

#include <string>
#include <vector>
#include "cards.hpp"
#include "tokens.hpp"

using namespace std;

#if !defined __GAMEBOARD_HPP_
#define __GAMEBOARD_HPP_

class gameBoard
{
   private:
      deck gameDeck;
      static const int MARKET_CARD_LEN = 5;
      vector<card> marketCards;
 
      tokenList  clothTokens;
      tokenList  leatherTokens;
      tokenList  goldTokens;
      tokenList  diamondsTokens;
      tokenList  silverTokens;
      tokenList  spicesTokens;
      tokenList  camelsTokens;
      tokenList  threeKindTokens;
      tokenList  fourKindTokens;
      tokenList  fiveKindTokens;

   public:
      gameBoard();
      void reset();
      void printGameState();
      int deckSize(){return gameDeck.size();}
      bool deckIsEmpty(){return gameDeck.isEmpty();}
      card drawCard(){return gameDeck.popCard();}
      card popMarketCard(int idx, bool redraw);
      void addMarketCard(card c) {marketCards.push_back(c);}
      cardType getMarketCardType(int idx);
      token getToken(tokenType t);
      void printMarketState(bool compressed);
      void printTokenCounts();
      void printTokenValues();
      int getMarketCardLen(){return MARKET_CARD_LEN;}
      unsigned int getUnsignedMarketCardLen(){return (unsigned int) MARKET_CARD_LEN;}
      int sumEmptyTokenLists();
};

#endif // __GAMEBOARD_HPP_
