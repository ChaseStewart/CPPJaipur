// main.cpp

#include <iostream>

#include "stateMachine.hpp"
#include "gameboard.hpp"
#include "tokens.hpp"
#include "player.hpp"

using namespace std;

int main()
{
   string player1name, player2name;

   cout << "*** Jaipur in C++ ***" << endl;
   cout << "\tby Chase E. Stewart" << endl << endl;

   cout << "Enter player1 name: ";
   cin >> player1name;

   cout << endl << "Enter player2 name: ";
   cin >> player2name;

   cout << endl << "*** BEGIN ***" << endl;

   stateMachine *sm = new stateMachine(player1name, player2name);


   while (GS_TERMINATE != sm->getState())
   {
      sm->step();
   }

   cout << endl << "\t\tGoodbye!" << endl;
   return 0;
}
