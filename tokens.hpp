// tokens.hpp
// token and tokenList class definitions

#include <iostream>
#include <vector>

using namespace std;

#if !defined __TOKENS_HPP_
#define __TOKENS_HPP_

enum tokenType {TOKEN_DIAMONDS, TOKEN_GOLD, TOKEN_SILVER, TOKEN_SPICES,
                TOKEN_CLOTH, TOKEN_LEATHER, TOKEN_CAMELS, TOKEN_3_KIND,
                TOKEN_4_KIND, TOKEN_5_KIND, TOKEN_INVALID};

// an individual token
class token{
   private:
      tokenType type;
      string name;
      int score;

      // getters
      string typeToName(tokenType t);

   public:
      // initialization
      token(tokenType t, int s){type = t; name = typeToName(t); score = s;}

      // getters
      tokenType getType(){return type;}
      int getScore(){return score;}

      // print definition
      friend ostream& operator<<(ostream& os, const token& c);
};

// a LIFO of tokens, order matters here
class tokenList{
   private:
      vector<token> tokens;

   public:

      // initialization and reset
      tokenList(){tokens = {};}
      tokenList(vector<token> &tList){init(tList);}
      void init(vector<token> &tList){tokens.swap(tList);}
      void reset();

      // token manipulation
      token popToken(){token temp = tokens.back(); tokens.pop_back(); return temp;}
      vector<token> getTokens(){return tokens;}
      void push_back(token t){tokens.push_back(t);}
      void shuffle(); // destructive, of course

      // getters
      size_t size(){return tokens.size();}
      bool isEmpty(){return (tokens.size() == 0);}
};

#endif // __TOKENS_HPP_
