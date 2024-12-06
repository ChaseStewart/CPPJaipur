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

// an individual card
class card {
   private:
      cardType type;
      string name;
      string typeToName(cardType t);

   public:
      // initialization
      card(cardType t){type = t; name = typeToName(t);} // provide a cardType to init

      // getters
      cardType getType(){return type;}

      // custom print operator for cards
      friend ostream& operator<<(ostream& os, const card& c);
};

// a deck of cards for the game Jaipur
class deck {
   private:
      // private card counts
      const int NUM_DIAMONDS = 6;
      const int NUM_GOLD = 6;
      const int NUM_SILVER = 6;
      const int NUM_CLOTH = 8;
      const int NUM_SPICES = 8;
      const int NUM_LEATHER = 10;
      const int NUM_CAMELS = 11;
      const int NUM_CARDS = NUM_DIAMONDS + NUM_GOLD + \
                            NUM_SILVER + NUM_CLOTH + \
                            NUM_SPICES + NUM_LEATHER + NUM_CAMELS; // empirically 55
 
      std::vector<card> cards;
      void shuffle(); // scoped to deck, not std::shuffle()

   public:
      // initialization
      deck() {init();} // always inits to same state, no args
      ~deck() {cards.clear();}
      void init();

      // card manipulation
      card popCard();

      // getters
      int size(){return cards.size();}
      bool isEmpty() {return cards.size() == 0;}
};

#endif // __CARDS_HPP_
