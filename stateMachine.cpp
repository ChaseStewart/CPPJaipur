// stateMachine.cpp
// stateMachine member implementation

#include <sstream>
#include <string>
#include <iostream>
#include <climits>

#include "stateMachine.hpp"

using namespace std;

// initialize game state
stateMachine::stateMachine(string p1name, string p2name)
{
   players[0].init(0, p1name);
   players[1].init(1, p2name);
   board.reset();
   setState(GS_P0_ACK);
   for (int i=0; i<5; i++)
   {
      players[0].addCard(board.drawCard());
      players[1].addCard(board.drawCard());
   }
   winner = -1;
}

// take one step through the game state machine
// this is the main function that makes the game go
// to be called in a while loop until GS_TERMINATE
void stateMachine::step()
{
   string playAgain; // for GS_GAME_OVER

   switch (state)
   {
      case GS_INIT:
         reset();
         state = GS_P0_ACK;
         break;

      case GS_P0_ACK:
         getPlayerAck(0);
         state = GS_P0_TAKE_ACTION;
         break;

      case GS_P0_TAKE_ACTION:
         getPlayerAction(0);
         if (action != PA_NO_ACTION)
         {
            state = GS_P0_VALIDATE_ACTION;
         }
         break;

      case GS_P0_VALIDATE_ACTION:
         if (executePlayerAction(0))
         {
            action = PA_NO_ACTION;
            state = GS_P1_ACK;
         }
         else
         {
            action = PA_NO_ACTION;
            state = GS_P0_TAKE_ACTION;
         }
         break;

      case GS_P1_ACK:
         getPlayerAck(1);
         state = GS_P1_TAKE_ACTION;
         break;

      case GS_P1_TAKE_ACTION:
         getPlayerAction(1);
	 if (action != PA_NO_ACTION)
         {
            state = GS_P1_VALIDATE_ACTION;
         }
         break;

      case GS_P1_VALIDATE_ACTION:
         if (executePlayerAction(1))
         {
            action = PA_NO_ACTION;
            state = GS_P0_ACK;
         }
         else
         {
            action = PA_NO_ACTION;
            state = GS_P1_TAKE_ACTION;
         }
         break; 

      case GS_FINAL_SCORING:
         winner = calculateWinner();
         cout << endl << "Winner is: " << players[winner].getName() << "!" << endl;
         state = GS_GAME_OVER;

      case GS_GAME_OVER:
         state = GS_TERMINATE;
         // TODO implement play again
         //cout << "Would you like to play again?" << endl;
         //cout << "\tEnter \"yes\" to play again, anything else to quit:";
         //cin >> playAgain;
         //state = (playAgain == "yes") ? GS_INIT: GS_TERMINATE;
         break;

      case GS_TERMINATE:
         cout << "ERROR: should never get here!" << endl;
         break;
   };

   // always check for end condition
   if (isGameOver() && state != GS_GAME_OVER && state != GS_FINAL_SCORING && state != GS_TERMINATE)
   {
      cout << "*** GAME IS OVER ***" << endl;
      state = GS_FINAL_SCORING;
   }
}

// return which player in [0,1] won the game
int stateMachine::calculateWinner()
{
   // Give camels_token to player with largest herd
   // at end of the game 
   if (players[0].herdSize() > players[1].herdSize())
   {
      players[0].addToken(board.getToken(TOKEN_CAMELS));
   }
   else if (players[1].herdSize() > players[0].herdSize())
   {
      players[1].addToken(board.getToken(TOKEN_CAMELS));
   }

   cout << "\tPlayer 1 score: " << players[0].calculateScore() << endl;
   cout << "\tPlayer 2 score: " << players[1].calculateScore() << endl;
   return (players[0].calculateScore() > players[1].calculateScore()) ? 0 : 1;
}

// prompt the player to acknowledge that it is their turn
void stateMachine::getPlayerAck(int id)
{
   cout << players[id].getName()  << ", press any key to continue: ";
   getchar();
}

// receive and parse a choice of action from player[id]
void stateMachine::getPlayerAction(int id)
{
   const int STRLEN = 5;

   char actionStr[STRLEN];
   int actionInt = 0;
   cout << endl << "* " << players[id].getName() << ", choose an action:" << endl;
   cout << PA_TAKE_GOOD << ". Take a goods card" << endl;
   cout << PA_EXCHANGE_CARDS << ". Exchange cards" << endl;
   cout << PA_TAKE_ALL_CAMELS << ". Take all camels" << endl;
   cout << PA_SELL_GOODS << ". Sell goods cards" << endl;
   cout << PA_VIEW_BOARD_STATE << ". View board state" << endl;
   cout << PA_VIEW_MY_STATE << ". View my state" << endl;
   cin.getline(actionStr, STRLEN);
   if (cin.fail()) 
   {
       cin.clear();
       cin.ignore(INT_MAX, '\n');
   }

  try 
  {
    actionInt = stoi(actionStr);
  }
  catch (const invalid_argument& ia) 
  {
	  cout << "Invalid action: invalid action selected" << endl;
          action = PA_NO_ACTION;
          return;
  }

  switch (actionInt)
  {
     case PA_NO_ACTION:
        action = PA_NO_ACTION;
        break;
     case PA_TAKE_GOOD:
        action = PA_TAKE_GOOD;
        break;
     case PA_EXCHANGE_CARDS:
        action = PA_EXCHANGE_CARDS;
        break;
     case PA_TAKE_ALL_CAMELS:
        action = PA_TAKE_ALL_CAMELS;
        break;
     case PA_SELL_GOODS:
        action = PA_SELL_GOODS;
        break;
     case PA_VIEW_BOARD_STATE:
        action = PA_VIEW_BOARD_STATE;
        break;
     case PA_VIEW_MY_STATE:
        action = PA_VIEW_MY_STATE;
        break;
     default:
        action = PA_NO_ACTION;
        break;
  };
}

// route a selected action to appropriate function call
// if selected action is invalid or fails, next step
// will be to repeat player action
// if selected action succeeds, carry it out
// and prompt next player for ACK
bool stateMachine::executePlayerAction(int i)
{
   switch (action)
   {
      case PA_TAKE_GOOD:
         cout << "Action: Take a single good" << endl;
         return executeTakeGood(i);
      case PA_EXCHANGE_CARDS:
         return executeExchangeCards(i);
         cout << "Action: Exchange some cards" << endl;
         break;
      case PA_TAKE_ALL_CAMELS:
         cout << "Action: Take all camels" << endl;
         return executeTakeAllCamels(i);
         break;
      case PA_SELL_GOODS:
         cout << "Action: Sell some goods" << endl;
         return executeSellGoods(i);
         break;
      case PA_VIEW_BOARD_STATE:
         cout << "Action: View the board state" << endl;
         executeViewBoardState();
         return false;
      case PA_VIEW_MY_STATE:
         cout << "Action: View my player state" << endl;
         executeViewMyState(i);
         return false;
      case PA_NO_ACTION:
      default:
         cout << "Invalid Action selected" << endl;
         return false;
   };
   cout << "\tPlaceholder: should not get here! " << endl;
   return true;
}

// perform the take good action
// this can succeed or fail, only modify state if success
bool stateMachine::executeTakeGood(int playerId)
{
   if (players[playerId].handSize() >= players[playerId].HAND_LIMIT)
   {
      cout << "Invalid action: hand is full" << endl;
      return false;
   }
   board.printMarketState(false);
   int cardId;

   cout << "Your selection (0 to cancel): ";
   cin >> cardId;
   if (cardId > board.getMarketCardLen())
   {
      cardId = 0;
   }
   if (cardId == 0)
   {
      return false;
   }

   if (CARD_CAMELS == board.getMarketCardType(cardId - 1))
   {
      return false;
   }
   players[playerId].addCard(board.popMarketCard(cardId - 1, true));
   cout << "\t"<< players[playerId].getName() <<" took a " << players[playerId].getMostRecentCard() << " card" << endl;
   return true;
}

// perform the view game state action
// this always "fails" in the sense it doesn't end user's turn
// no error is printed  
void stateMachine::executeViewBoardState()
{
   board.printGameState();
}

// perform the view current player state action
// this always "fails" in the sense it doesn't end user's turn
// no error is printed  
void stateMachine::executeViewMyState(int id)
{
   players[id].printPlayerState();
}

// perform the take all camels action
// this can succeed or fail, only modify state if success
bool stateMachine::executeTakeAllCamels(int id)
{
   int camelCounter = 0;
   for (int i=board.getMarketCardLen() -1; i >= 0; i--)
   {
      if (CARD_CAMELS == board.getMarketCardType(i))
      {
         players[id].addCard(board.popMarketCard(i, true));
         camelCounter++;
      }
   }
   if (camelCounter > 0)
   {
      cout << "\t" << players[id].getName() << " received " << camelCounter << " camels" << endl;
      return true;
   }
   cout << "Invalid action: no camels available" << endl;
   return false;
}

// perform the exchange cards action
// this can succeed or fail, only modify state if success
// TODO this one needs cleanup 
bool stateMachine::executeExchangeCards(int id)
{
   string giveStr, recvStr, splitStr;
   vector<string> giveSplitStrs;
   vector<string> recvSplitStrs;
   vector<int> giveArray;
   vector<int> recvArray;
   int camelsToGive = 0;
   int cardsToRx = 0;

   players[id].printHand(false);
   players[id].printHerd();
   cout << "Enter up to 5 cards to exchange: " << endl;
   cout << "\tUse format: 1,4,c,c" << endl; 
   cin >> giveStr;

   stringstream giveStream(giveStr);
   while(getline(giveStream, splitStr, ','))
   {
      giveSplitStrs.push_back(splitStr);
   }

   if (giveSplitStrs.size() > board.getUnsignedMarketCardLen())
   {
      cout << "Invalid action: offering too many cards to exchange" << endl;
      giveArray.clear();
      return false;
   }
   else if (giveSplitStrs.size() <= 1)
   {
      cout << "Invalid action: must offer at least 2 cards to exchange" << endl;
      giveArray.clear();
      return false;
   }
   
   for (auto str: giveSplitStrs)
   {
      if (str == "c")
      {
         camelsToGive++;
         cardsToRx++;
      }
      else if (str == "1"){giveArray.push_back(1); cardsToRx++;}
      else if (str == "2"){giveArray.push_back(2); cardsToRx++;}
      else if (str == "3"){giveArray.push_back(3); cardsToRx++;}
      else if (str == "4"){giveArray.push_back(4); cardsToRx++;}
      else if (str == "5"){giveArray.push_back(5); cardsToRx++;}
      else if (str == "6"){giveArray.push_back(6); cardsToRx++;}
      else if (str == "7"){giveArray.push_back(7); cardsToRx++;}
      else
      {
         cout << "Invalid action: invalid hand index" << endl;
         return false;
      }
   }

   if (!validateCardIdxArray(giveArray))
   {
      cout << "Invalid action: invalid give array" << endl;
      giveArray.clear();
      return false;
   }
   if (camelsToGive + players[id].handSize() > players[id].HAND_LIMIT)
   {
      cout << "Invalid action: exchange would exceed hand limit" << endl;
      giveArray.clear();
      return false;
   }

   cout << "Give_Array: [";
   for (auto i: giveArray)
   {
      cout << i << ", ";
   }
   cout << "]";
   cout << " and " << camelsToGive << " camels"<< endl; 

   cout << "Now select " << cardsToRx << " cards from the market";
   cout << "\tUse format: 1,2,4,5" << endl; 
   board.printMarketState(false);
   cin >> recvStr;

   stringstream recvStream(recvStr);
   while(getline(recvStream, splitStr, ','))
   {
      recvSplitStrs.push_back(splitStr);
   }

   for (auto str: recvSplitStrs)
   {
      if (str == "1"){recvArray.push_back(1);}
      else if (str == "2"){recvArray.push_back(2);}
      else if (str == "3"){recvArray.push_back(3);}
      else if (str == "4"){recvArray.push_back(4);}
      else if (str == "5"){recvArray.push_back(5);}
      else
      {
         cout << "Invalid action: invalid market index" << endl;
         recvArray.clear();
         giveArray.clear();
         return false;
      }
   }

   if (giveArray.size() + camelsToGive != recvArray.size())
   {
      cout << "Invalid action: must take as many cards as you give" << endl;
      recvArray.clear();
      giveArray.clear();
      return false;
   }

   if (!validateCardIdxArray(recvArray))
   {
      cout << "Invalid action: invalid receive array" << endl;
      recvArray.clear();
      giveArray.clear();
      return false;
   }

   for (auto idx: recvArray)
   {
      if (CARD_CAMELS == board.getMarketCardType(idx -1))
      {
         cout << "Invalid action: cannot take camels in exchange" << endl;
         recvArray.clear();
         giveArray.clear();
         return false;
      }
   }


   cout << "Receive_Array: [";
   for (auto i: recvArray)
   {
      cout << i << ", ";
   }
   cout << "]" << endl;

   // do all validation before you start destructive modification
   for (int i=recvArray.size() - 1;  i >= 0; i--)
   {
      players[id].addCard(board.popMarketCard(recvArray[i] - 1, false));  
   }

   for (int i=giveArray.size() - 1;  i >= 0; i--)
   {
      board.addMarketCard(players[id].popCard(giveArray[i] - 1));
   }

   for (int i=0; i < camelsToGive; i++)
   {
      players[id].popCamel();
      board.addMarketCard(card(CARD_CAMELS));
   }

   cout << "\tResults:" << endl;
   players[id].printHand(true);
   players[id].printHerd();
   board.printMarketState(true);

   return true;
}

// perform the sell cards action
// this can succeed or fail, only modify state if success
bool stateMachine::executeSellGoods(int id)
{
   int selection;
   players[id].printHand(true);
   cout << "Select cards to sell (0 to cancel):" << endl;
   cout << CARD_DIAMONDS + 1<< ". Diamonds" << endl;
   cout << CARD_GOLD + 1<< ". Gold" << endl;
   cout << CARD_SILVER + 1<< ". Silver" << endl;
   cout << CARD_SPICES + 1<< ". Spices" << endl;
   cout << CARD_CLOTH + 1<< ". Cloth" << endl;
   cout << CARD_LEATHER + 1<< ". Leather" << endl;
   cin >> selection;

   if (selection == 0 || selection > CARD_LEATHER + 1)
   {
      return false;
   }

   int minSellCount =  (selection == CARD_DIAMONDS || selection == CARD_GOLD || selection == CARD_SILVER) ? 2 : 1;

   cardType cardSel = (cardType) (selection - 1);
   tokenType tokenSel = cardTypeToTokenType(cardSel);
   card nameCard = card(cardSel);

   int sellCount = players[id].countCardsByType(cardSel);

   if (sellCount < minSellCount)
   {
      cout << "Invalid Action: not enough " << nameCard << " to sell" << endl;
      return false;
   }

   // The Sale is now validated
   cout << "Selling " << sellCount << " copies of " << nameCard << endl;
   players[id].sellCardsByType(cardSel);

   for (int i=0; i < sellCount; i++)
   {
      players[id].addToken(board.getToken(tokenSel));
   }

   if (sellCount >= 5)
   {
      players[id].addToken(board.getToken(TOKEN_5_KIND));
   }
   else if (sellCount == 4)
   {
      players[id].addToken(board.getToken(TOKEN_4_KIND));
   }
   else if (sellCount == 3)
   {
      players[id].addToken(board.getToken(TOKEN_3_KIND));
   }
   return true;
}

// reset the game state machine and players and board
// this is destructive 
void stateMachine::reset()
{
   string p1name = players[0].getName();
   string p2name = players[1].getName();

   players[0].init(0, p1name);
   players[1].init(1, p2name);
   board.reset();
   setState(GS_P0_ACK);
   winner = -1;
}

// translate the provided goods cardType to its corresponding goods token
tokenType stateMachine::cardTypeToTokenType(cardType t)
{
   switch (t)
   {
      case CARD_DIAMONDS:
         return TOKEN_DIAMONDS;
      case CARD_GOLD:
         return TOKEN_GOLD;
      case CARD_SILVER:
         return TOKEN_SILVER;
      case CARD_SPICES:
         return TOKEN_SPICES;
      case CARD_CLOTH:
         return TOKEN_CLOTH;
      case CARD_LEATHER:
         return TOKEN_LEATHER;
      default:
         return TOKEN_INVALID;
   };
   return TOKEN_INVALID;
}

// return true if cardIdxArray is valid, else false
// this is a helper for the exchange action 
bool stateMachine::validateCardIdxArray(vector<int> v)
{
   sort(v.begin(), v.end());

   for (int i=0; i < (int) (v.size() - 1); i++)
   {
      if (v[i] == v[i+1])
      {
         return false;
      }
   }
   return true;
}
