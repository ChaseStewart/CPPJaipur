// player.hpp
// player class definitions

#include <vector>
#include <string>

#include "cards.hpp"
#include "tokens.hpp"

using namespace std;

#if !defined __PLAYER_HPP_
#define __PLAYER_HPP_

// player state and actions
class player
{
   private:
      int id;
      string name;

      vector<card> hand;
      vector<card> herd;

      // these start empty and then are summed
      // for the final score
      tokenList  diamondsTokens;
      tokenList  goldTokens;
      tokenList  silverTokens;
      tokenList  spicesTokens;
      tokenList  clothTokens;
      tokenList  leatherTokens;
      tokenList  threeKindTokens;
      tokenList  fourKindTokens;
      tokenList  fiveKindTokens;
      tokenList  camelsTokens;
  
   public:
      static const int HAND_LIMIT = 7;

      // initialization
      player(){id=-1; name="UNINITIALIZED";} // init with a playerId and a name
      void init(int i, string n){id=i; name=n;}

      // goods card manipulation (the hand)
      void addCard(card c);
      card popCard(int idx);
      int countGoodsCardsByType(cardType t);
      void sellGoodsCardsByType(cardType t);
      card getMostRecentCard(){return hand.back();}
      int handSize(){return hand.size();}

      // camel card manipulation (the herd)
      card popCamel(); // separate command, camels are stored separately
      int herdSize(){return herd.size();}

      // token manipulation
      void addToken(token t);

      // printing
      void printHand(bool compressed);
      void printHerd(){cout << "Herd: " << herd.size() << " camels" << endl;}
      void printPlayerState(); // call printHand and printHerd

      // getters
      int calculateScore();
      string getName(){return name;}
};

#endif // __PLAYER_HPP_
