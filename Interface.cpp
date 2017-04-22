#include "Move.h"
#include "Position.h"
#include "Board.h"
#include "Square.h"
#include "Interface.h"
#include <iostream>
#include <fstream>
#include <vector>

void Interface::saveFile(string filename){//this function saves file if you want to save the file
   ofstream myfile(filename.c_str());
   if (myfile.is_open()){
      for (int i = 0; i < this->moves.size(); i++){
         myfile << this->moves.at(i);//it saves the game.
         if ((i - 1) % 2 == 0 && i > 0){
            myfile << endl;
         }
         else{
            myfile << " ";
         }
      }
   }
   else{
      cout << "ERROR: could not open file" << filename << endl;
   }
}

void Interface::beginMenuCapture(){//takes turns with the players.
   this->board->display(false);
   string input;
  for (playerTurn = 1;;playerTurn++){//this loop takes the turn of the player.
    Player * playerThisTurn;
    if (playerTurn % 2 == 0){
      playerThisTurn = this->players[0];
    }
    else{
      playerThisTurn = this->players[1];
    }
    input = getInput(playerThisTurn);
    if (input.compare("quit") == 0){//what quit does.
      break;
    }
    else if (input.compare("?") == 0 || input.compare("help") == 0){//help and ? are the samething. This simply tells the program.
      this->displayMenu();
      playerTurn--;
    }
    else if (input.compare("read") == 0){//reads in any saved files.
      try{
         this->read();
         this->board->display();
      }
      catch(string msg){
         cout << msg << endl;
         playerTurn--;
      }
    }
    else if (input.compare("test") == 0){//tests the movement
      this->board->setTestStyle(true);
      this->board->display();
      playerTurn--;
    }
    else if (validateInput(input)){//if invalid input then do the following.
      try{
         Move move = this->parseToMove(input);
         Piece * piece = this->board->getPieceAtMove(move, 0, 0);
         if (piece != NULL){
            if(piece->getPlayer() == playerThisTurn->getId()){
               this->board->move(move);
               this->moves.push_back(input);
               this->board->display();
            }
            else{
               throw string("Not your piece, make sure to check which side you play for.");
            }
         }
         else{
            throw string("A blank square...think again!");
         }
      }
      catch(string msg){
         cout << msg << endl;
         playerTurn--;
      }
    }
    else{
       cout << "ERROR MESSAGE\n";
       playerTurn--;
    }
  }
  this->saveFileOnQuit();
}

void Interface::read()throw(string){//reads in the filename.
   cout << "Filename:";
   string filename;
   cin >> filename;

   string line;//set up variables to be used when reading
   string playerOneMove;
   string playerTwoMove;
   size_t spaceT;

   Board * newBoard = new Board();
   newBoard->reset();
   try{
      ifstream myfile(filename.c_str());
      if (myfile.is_open()){
         int turn = 0;
         while ( getline (myfile,line) ){
            spaceT = line.find(" ");//this splits up line by spaces
            playerOneMove = line.substr(0, spaceT);
            playerTwoMove = line.substr(spaceT + 1);
            if (playerOneMove.compare("") != 0){
               newBoard->move(this->parseToMove(playerOneMove));
               turn++;
            }
            if (playerTwoMove.compare("") != 0 && playerTwoMove.compare(playerOneMove) != 0){//checking to see if the move is blank or not
               Move move = this->parseToMove(playerTwoMove);
               newBoard->move(move);
               turn++;
            }
         }
         myfile.close();
         newBoard->setTestStyle(this->board->isTestStyle());
         delete this->board;
         this->board = newBoard;
         this->playerTurn = turn;
      }
      else{
         throw string("Error while reading file");
      }
   }
   catch(string msg){
      throw string(msg);
   }
}

Move Interface::parseToMove(string & input) throw (string){
   int srcRow;
   int srcCol;
   int destRow;
   int destCol;
   Position coord[2];
   Move move;
   for (int i = 0, j = 0; i <= 3; i += 2, j++){//valid moves
      if (input[i] >= 'a' && input[i] <= 'h'){
         srcCol = input[i] - 'a';
      }
      else if (input[i] >= 'A' && input[i] <= 'H'){
         srcCol = input[i] - 'A';
      }
      else {
         throw string("Invalid format of ") + string((i >= 2 ? "destination" : "source")) + string(" coordinates");
      }
      if (input[i + 1] >= '1' && input[i + 1] <= '8'){//the board is 8 through 1, and needs to reverse it.
         srcRow = 7 - (input[i + 1] - '1');
      }
       else {
         throw string("Invalid format of ") + string((i >= 2 ? "destination" : "source")) + string(" coordinates");
      }
      if (!(input[4] == 'p'//this checks 5th letter command.
         || input[4] == 'n'
         || input[4] == 'b'
         || input[4] == 'r'
         || input[4] == 'q'
         || input[4] == 'k'
         || input[4] == 'c'
         || input[4] == 'C'
         || input[4] == 'E'
         || input[4] == 'N'
         || input[4] == 'B'
         || input[4] == 'R'
         || input[4] == 'Q'
         || !input[4]
         ))
      {
         throw string("Unknown promotion piece specification");
      }
      coord[j].col = srcCol;
      coord[j].row = srcRow;
   }
   move.src = coord[0];
   move.dest = coord[1];
   return move;
}
