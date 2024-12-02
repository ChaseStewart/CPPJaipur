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
      player(){id=-1; name="UNINITIALIZED";} // init with a playerId and a name
      void init(int i, string n){id=i; name=n;}
      void addCard(card c);
      card popCard(int idx);
      void addToken(token t);
      card popCamel();
      int countCardsByType(cardType t);
      void sellCardsByType(cardType t);
      int handSize(){return hand.size();}
      int herdSize(){return herd.size();}
      string getName(){return name;}
      void printHand(bool compressed);
      void printHerd(){cout << "Herd: " << herd.size() << " camels" << endl;}
      void printPlayerState(); // call printHand and printHerd
      card getMostRecentCard(){return hand.back();}
      int calculateScore();
};

#endif // __PLAYER_HPP_
