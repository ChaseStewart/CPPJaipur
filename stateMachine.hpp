// stateMachine.hpp
// stateMachine class definitions

#include <vector>
#include <string>

#include "gameboard.hpp"
#include "player.hpp"

using namespace std;

#if !defined __STATEMACHINE_HPP_
#define __STATEMACHINE_HPP_

// states to model the flow of gameplay
enum gameStates {GS_INIT,
                 GS_P0_ACK, 
                 GS_P0_TAKE_ACTION, 
                 GS_P0_VALIDATE_ACTION, 
                 GS_P1_ACK, 
                 GS_P1_TAKE_ACTION, 
                 GS_P1_VALIDATE_ACTION,
                 GS_FINAL_SCORING,
                 GS_GAME_OVER,
                 GS_TERMINATE};

// the different actions a player can choose, or NO_ACTION
enum playerActions {PA_NO_ACTION,
                    PA_TAKE_GOOD,
                    PA_EXCHANGE_CARDS,
                    PA_TAKE_ALL_CAMELS,
                    PA_SELL_GOODS,
                    PA_VIEW_BOARD_STATE,
                    PA_VIEW_MY_STATE};

// the game state and related methods
class stateMachine
{
   private:

      // mostly for static array init
      enum player_count {PLAYER_0 = 0, PLAYER_1 = 1, NUM_PLAYERS = 2};
 
      // class variables
      int wins[NUM_PLAYERS];
      player players[NUM_PLAYERS];
      playerActions action = PA_NO_ACTION;
      gameStates state = GS_INIT;
      gameBoard board;
      int winner;

      // internal helper functions
      tokenType cardTypeToTokenType(cardType t);
      bool validateCardIdxArray(vector<int> v);
      bool isGameOver(){return (board.deckIsEmpty() || board.sumEmptyTokenLists() >= 3);}
      int calculateWinner();

   public:
      // initialization
      stateMachine(string p1Name, string p2Name);
      ~stateMachine();
      void reset();

      // state manipulation
      gameStates getState() {return state;}
      void setState(gameStates g){state = g;}

      // state flow steps
      void step();
      void getPlayerAction(int id);
      void getPlayerAck(int id);
      bool executePlayerAction(int id);

      // processing specific commands
      bool executeTakeGood(int id);
      bool executeExchangeCards(int id);
      bool executeSellGoods(int id);
      void executeViewBoardState();
      void executeViewMyState(int id);
      bool executeTakeAllCamels(int id);
};

#endif // __STATEMACHINE_HPP_
