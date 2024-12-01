// cards.hpp
// cards and deck class definitions

#include <vector>
#include <string>
#include <iostream>

using namespace std;

#if !defined __CARDS_HPP_
#define __CARDS_HPP_

enum cardType {CARD_DIAMONDS, CARD_GOLD, CARD_SILVER,
                 CARD_SPICES, CARD_CLOTH, CARD_LEATHER, 
                 CARD_CAMELS, CARD_INVALID};

class card {
   private:
      cardType type;
      string name;
      string typeToName(cardType t);
   public:
      card(cardType t){type = t; name = typeToName(t);}
      cardType getType(){return type;}
      void setType(cardType t){type = t; name = typeToName(t);}
      friend ostream& operator<<(ostream& os, const card& c);
};

class deck {
   private:
      const int NUM_DIAMONDS = 6;
      const int NUM_GOLD = 6;
      const int NUM_SILVER = 6;
      const int NUM_CLOTH = 8;
      const int NUM_SPICE = 8;
      const int NUM_LEATHER = 10;
      const int NUM_CAMELS = 11;
      const int NUM_CARDS = NUM_DIAMONDS + NUM_GOLD + \
                            NUM_SILVER + NUM_CLOTH + \
                            NUM_SPICE + NUM_LEATHER + NUM_CAMELS; // empirically 55
 
      std::vector<card> cards;

   public:
     deck() {init();}
     ~deck() {cards.clear();}
     void init();
     void shuffle();
     card popCard();
     int size(){return cards.size();}
     bool isEmpty() {return cards.size() == 0;}
};

#endif // __CARDS_HPP_
