// tokens.hpp
// token and tokenList class definitions

#include <iostream>
#include <vector>

using namespace std;

#if !defined __TOKENS_HPP_
#define __TOKENS_HPP_

enum tokenType {TOKEN_DIAMONDS, TOKEN_GOLD, TOKEN_SILVER, TOKEN_SPICES, TOKEN_CLOTH, TOKEN_LEATHER, TOKEN_CAMELS, TOKEN_3_KIND, TOKEN_4_KIND, TOKEN_5_KIND, TOKEN_INVALID};

class token{
   private:
      tokenType type;
      string name;
      string typeToName(tokenType t);
      int score;
   public:
      token(tokenType t, int s){type = t; name = typeToName(t); score = s;}
      tokenType getType(){return type;}
      int getScore(){return score;}
      friend ostream& operator<<(ostream& os, const token& c);
};

class tokenList{
   protected:
      vector<token> tokens;
   public:
      tokenList(){tokens = {};}
      tokenList(vector<token> tList){init(tList);}
      void init(vector<token> tList){tokens.swap(tList);}
      token popToken(){token temp = tokens.back(); tokens.pop_back(); return temp;}
      void push_back(token t){tokens.push_back(t);}
      void reset();
      void shuffle();
      size_t size(){return tokens.size();}
      vector<token> getTokens(){return tokens;}
      bool isEmpty(){return (tokens.size() == 0);}
};

#endif // __TOKENS_HPP_
