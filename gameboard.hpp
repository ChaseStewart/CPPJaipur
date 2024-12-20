// gameboard.hpp
// gameboard class definitions

#include <string>
#include <vector>

#include "cards.hpp"
#include "tokens.hpp"

using namespace std;

#if !defined __GAMEBOARD_HPP_
#define __GAMEBOARD_HPP_

// all the objects on the game board
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
      // initialization
      gameBoard(){reset();} // always inits the same way
      void reset();

      // deck manipulation
      card drawCard(){return gameDeck.popCard();}
      bool deckIsEmpty(){return gameDeck.isEmpty();}

      // market manipulation
      card popMarketCard(int idx, bool redraw);
      void addMarketCard(card c) {marketCards.push_back(c);}
      cardType getMarketCardType(int idx);

      // tokenList manipulation
      token getToken(tokenType t);
      int sumEmptyTokenLists();

      // printing
      void printGameState();
      void printMarketState(bool compressed);
      void printTokenValues();

      // getters
      int getMarketCardLen(){return MARKET_CARD_LEN;}
      unsigned int getUnsignedMarketCardLen(){return (unsigned int) MARKET_CARD_LEN;}
      int deckSize(){return gameDeck.size();}
};

#endif // __GAMEBOARD_HPP_
