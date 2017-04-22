#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Interface.h"

using namespace std;
//it contains classes both public and private.
class Game{
public://aceesbile
   Game() : board(new Board()){
      this->players[0] = new Player("Black");//two players
      this->players[1] = new Player("White");
      this->interface = new Interface(this->board, this->players);
   }
   ~Game() {}
   void createGame(){
      board->reset();
      interface->beginMenuCapture();
   }
private://the priates needs to be declared so that .cpp file can solely access these variables.
   Board * board;
   Player * players[2];
   Interface * interface;
};

#endif
