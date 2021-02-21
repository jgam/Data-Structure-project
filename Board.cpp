#include "Board.h"
#include "Square.h"
#include "Piece.h"
#include "Position.h"
#include "Move.h"

#include <iostream>

using namespace std;

void Board::display()//simple function that displays the board...
{
   display(true);
}
void Board::display(bool clearScreen){//header
   if (clearScreen && !this->isTestStyle())//simply adjusting the style of the board
      cout << "\E[H\E[2J";
   string space = "";
   if (!this->isTestStyle())
   {
      space = " ";//the first column of the board
   }
	cout << "  " <<  space << 
      "a" << space << space <<
   	"b" << space << space <<
   	"c" << space << space <<
   	"d" << space << space <<
   	"e" << space << space <<
   	"f" << space << space <<
   	"g" << space << space <<
   	"h" << space << 
      "\n";
   for (int i = 0; i < 8; i++){//this is a row header
      cout << 8 - i << " ";
      for (int j = 0; j < 8; j++){
         cout << squares[i][j];
      }
      if (!this->isTestStyle())//Row footer
         cout << " " << 8 - i;
      cout << endl;
   }
   if (!this->isTestStyle())//regular footer
	   cout << "  " << space << 
         "a" << space << space <<
      	"b" << space << space <<
      	"c" << space << space <<
      	"d" << space << space <<
      	"e" << space << space <<
      	"f" << space << space <<
      	"g" << space << space <<
      	"h" << space << space <<
         space << "\n";
}
void Board::reset(){//mostly setting the colors of the board
   for (int i = 0; i < 8; i++){
      for (int j = 0; j < 8; j++){
         squares[i][j] = new Square(this);
         if (((i * 8 + j) - i) % 2 == 0){
            squares[i][j]->setColor("red");
         }
         else{
            squares[i][j]->setColor("white");
         }
      }
   }
   for (int i = 0; i < 8; i++)//deleting the points of the board
      for (int j = 0; j < 8; j++)
         if (squares[i][j]->getPiece() != NULL)
            delete squares[i][j]->getPiece();

   //White side
   squares[0][0]->setPiece(new Bishop(this, 1));
   squares[0][1]->setPiece(new Knight(this, 1));
   squares[0][2]->setPiece(new Rook(this, 1));
   squares[0][3]->setPiece(new Queen(this, 1));
   squares[0][4]->setPiece(new King(this, 1));
   squares[0][5]->setPiece(new Rook(this, 1));
   squares[0][6]->setPiece(new Knight(this, 1));
   squares[0][7]->setPiece(new Bishop(this, 1));

   squares[1][0]->setPiece(new Pawn(this, 1));
   squares[1][1]->setPiece(new Pawn(this, 1));
   squares[1][2]->setPiece(new Pawn(this, 1));
   squares[1][3]->setPiece(new Pawn(this, 1));
   squares[1][4]->setPiece(new Pawn(this, 1));
   squares[1][5]->setPiece(new Pawn(this, 1));
   squares[1][6]->setPiece(new Pawn(this, 1));
   squares[1][7]->setPiece(new Pawn(this, 1));

   //represents Black side
   squares[6][0]->setPiece(new Pawn(this, 2));
   squares[6][1]->setPiece(new Pawn(this, 2));
   squares[6][2]->setPiece(new Pawn(this, 2));
   squares[6][3]->setPiece(new Pawn(this, 2));
   squares[6][4]->setPiece(new Pawn(this, 2));
   squares[6][5]->setPiece(new Pawn(this, 2));
   squares[6][6]->setPiece(new Pawn(this, 2));
   squares[6][7]->setPiece(new Pawn(this, 2));

   squares[7][0]->setPiece(new Bishop(this, 2));
   squares[7][1]->setPiece(new Knight(this, 2));
   squares[7][2]->setPiece(new Rook(this, 2));
   squares[7][3]->setPiece(new Queen(this, 2));
   squares[7][4]->setPiece(new King(this, 2));
   squares[7][5]->setPiece(new Rook(this, 2));
   squares[7][6]->setPiece(new Knight(this, 2));
   squares[7][7]->setPiece(new Bishop(this, 2));

   //The rest of the squares
   for (int i = 2; i <= 5; i++){
      for (int j = 0; j < 8; j++){
         //squares[i][j]->setPiece(new Pieces)
      }
   }
}
void Board::move(Move move) throw(string){//the piece to see the valid moves
   if (getSquare(move.src)->getPiece() != NULL){
      if(getSquare(move.src)->getPiece()->validMove(move)){
         getSquare(move.dest)->setPiece(getSquare(move.src)->getPiece());
         getSquare(move.src)->removePiece();
         getSquare(move.dest)->getPiece()->setHasMoved();
      }
      else
      {
         throw string("Invalid move for this piece");
      }
   }
   else
   {
      throw string("There is no piece on that square to move");
   }
}

Piece * Board::getPieceAtMove(const Move & move, const int & row, const int & col){
   Position pos = {move.src.row + row, move.src.col + col};
   Square * square = this->getSquare(pos);
   if (square == NULL)
      return NULL;
   return square->getPiece();
}
