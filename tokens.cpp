// tokens.cpp
// token and tokenList member implementations

#include <iostream>
#include <random>
#include <algorithm>
#include "tokens.hpp"

using namespace std;

// define printing tokens to be printing the score
ostream& operator<<(ostream& os, const token& c)
{
   os << c.score;
   return os;
}

// shuffle the tokens in the tokenList
// this is destructive
void tokenList:: shuffle()
{
   // Create a random number generator
   random_device rd;
   mt19937 g(rd());
   std::shuffle(tokens.begin(), tokens.end(), g); 
}

// return a string name for provided tokenType 
string token::typeToName(tokenType t)
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

