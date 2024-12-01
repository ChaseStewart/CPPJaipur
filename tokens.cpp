// tokens.cpp
// token and tokenList member implementations

#include <iostream>
#include <random>
#include <algorithm>
#include "tokens.hpp"

using namespace std;

ostream& operator<<(ostream& os, const token& c)
{
   os << c.score;
   return os;
}

void tokenList:: shuffle()
{
   // Create a random number generator
   std::random_device rd;
   std::mt19937 g(rd());
   std::shuffle(tokens.begin(), tokens.end(), g); 
}

std::string token::typeToName(tokenType t)
{
   switch (t)
   {
      case TOKEN_DIAMONDS:
         return "Diamonds";
      case TOKEN_GOLD:
         return "Gold";
      case TOKEN_SILVER:
         return "Silver";
      case TOKEN_CLOTH:
         return "Cloth";
      case TOKEN_SPICES:
         return "Spices";
      case TOKEN_LEATHER:
         return "Leather";
      case TOKEN_3_KIND:
         return "Three-of-a-Kind";
      case TOKEN_4_KIND:
         return "Four-of-a-Kind";
      case TOKEN_5_KIND:
         return "Five-of-a-Kind";
      case TOKEN_CAMELS:
         return "Most-Camels";
      default:
         return "Invalid";
   };
}

