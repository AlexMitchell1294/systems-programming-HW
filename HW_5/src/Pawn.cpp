/*
 * Pawn.cpp
 *
 *  Created on: Oct 7, 2021
 *      Author: Alex mitchell
 */

#ifndef SRC_PAWN_CPP_
#define SRC_PAWN_CPP_

#include "Pawn.h"
#include "Board.h"

Move::Move() {}
Move::Move(Pawn* pawnP, int next) {m_pawnP = pawnP; m_next = next;}

void Move::printMove() {
	printf("%d", m_pawnP->GetIndex());
}


Pawn::Pawn(){
	index=-1;
}

Pawn::Pawn(int newIndex, bool newColorRed) {
    index = newIndex;
    ColorRed = newColorRed;
}

Pawn::~Pawn(){}
King::King(){}
King::~King(){}
King::King(int newIndex, bool newColorRed): Pawn{newIndex, newColorRed}
{

}


void Pawn::SetIndex(int i){
	if(i>=0 && i<Board::BoardDimensions*Board::BoardDimensions){
		index = i;
	}
}
void Pawn::SetToRed(bool r){ColorRed = r;}
int Pawn::GetIndex(){return index;}
bool Pawn::GetRed(){return ColorRed;}

bool Pawn::ValidLeftDown(int* board){
	bool ReturnValue = index % 8 != 0;
	ReturnValue &= index < 56;
	ReturnValue &= board[index + Board::BoardDimensions - 1] == 0; //not blocked

	return ReturnValue;
}
bool Pawn::ValidLeftUp(int* board){
	bool ReturnValue = index % 8 != 0;
	ReturnValue &= index >= 8;
	ReturnValue &= board[index - Board::BoardDimensions - 1] == 0;

	return ReturnValue;
}
bool Pawn::ValidRightDown(int* board){
	bool ReturnValue = index % 8 != 7;
	ReturnValue &= index < 56;
	ReturnValue &= board[index + Board::BoardDimensions + 1] == 0;

	return ReturnValue;
}
bool Pawn::ValidRightUp(int* board){

	bool ReturnValue = index % 8 != 7;
	ReturnValue &= index >= 8;
	ReturnValue &= board[index - Board::BoardDimensions + 1] == 0;

	return ReturnValue;
	return index%8 != 7 && board[index - Board::BoardDimensions + 1] == 0;
}

bool Pawn::ValidLeftJumpDown(int* board){

	bool ReturnValue = ((index % 8 != 0) && (index % 8 != 1));
	ReturnValue &= !(index >= 48);
	ReturnValue &=  board[index + Board::BoardDimensions - 1] != 0;
	ReturnValue &= ((board[index + Board::BoardDimensions - 1]) % 2) != (board[index]) % 2;
	ReturnValue &= !(board[index + 2* Board::BoardDimensions - 2]);
	return ReturnValue;
}
bool Pawn::ValidLeftJumpUp(int* board){
	bool ReturnValue = ((index % 8 != 0) && (index % 8 != 1));
	ReturnValue &= !(index < 16);
	ReturnValue &=  board[index - Board::BoardDimensions  - 1] != 0;
	ReturnValue &= ((board[index - Board::BoardDimensions - 1]) % 2) != (board[index]) % 2;
	ReturnValue &= !(board[index - 2* Board::BoardDimensions - 2]);
	return ReturnValue;
}

bool Pawn::ValidRightJumpDown(int* board){

	bool ReturnValue = ((index % 8 != 6) && (index % 8 != 7));
	ReturnValue &= !(index >= 48);
	ReturnValue &=  board[index + Board::BoardDimensions  + 1] != 0;
	ReturnValue &= ((board[index + Board::BoardDimensions + 1]) % 2) != (board[index]) % 2;
	ReturnValue &= !(board[index + 2* Board::BoardDimensions + 2]);
	return ReturnValue;

	if (!ReturnValue) {std::cout<<index<<" is where it fails"<<std::endl;}

}
bool Pawn::ValidRightJumpUp(int* board){

	bool ReturnValue = ((index % 8 != 6) && (index % 8 != 7));
	ReturnValue &= !(index < 16);
	ReturnValue &=  board[index - Board::BoardDimensions  + 1] != 0;
	ReturnValue &= ((board[index - Board::BoardDimensions + 1]) % 2) != (board[index]) % 2;
	ReturnValue &= !(board[index - 2* Board::BoardDimensions + 2]);
	return ReturnValue;

}

LLNode<Move>* Pawn::ListOfMoves(int* board){
	LLNode<Move>* lP = new LLNode<Move>();

	if (this->ColorRed) {
		if (this->ValidLeftDown(board)) {
			lP->SavePayload(new Move(this, this->GetIndex() + Board::BoardDimensions - 1));
		}
		if (this->ValidRightDown(board)) {
			lP->SavePayload(new Move(this, this->GetIndex() + Board::BoardDimensions + 1));
		}
	}
	else {
		if (this->ValidLeftUp(board)) {
			lP->SavePayload(new Move(this, this->GetIndex() - Board::BoardDimensions - 1));
		}
		if (this->ValidRightUp(board)) {
			lP->SavePayload(new Move(this, this->GetIndex() - Board::BoardDimensions + 1));
		}
	}

	return lP;
}

LLNode<Move>* Pawn::ListOfJumps(int* board){
	LLNode<Move>* lP = new LLNode<Move>();

	if (this->ColorRed) {
		if (this->ValidLeftJumpDown(board)) {
			lP->SavePayload(new Move(this, this->GetIndex() + 2*Board::BoardDimensions - 2));
		}
		if (this->ValidRightJumpDown(board)) {
			lP->SavePayload(new Move(this, this->GetIndex() + 2*Board::BoardDimensions + 2));
		}
	}
	else {
		if (this->ValidLeftJumpUp(board)) {
			lP->SavePayload(new Move(this, this->GetIndex() - 2*Board::BoardDimensions - 2));
		}
		if (this->ValidRightJumpUp(board)) {
			lP->SavePayload(new Move(this, this->GetIndex() - 2*Board::BoardDimensions + 2));
		}
	}

	return lP;
}


LLNode<Move>* King::ListOfMoves(int* board){
	LLNode<Move>* lP = new LLNode<Move>();

	if (this->ValidLeftDown(board)) {
		lP->SavePayload(new Move(this, this->GetIndex() + Board::BoardDimensions - 1));
	}
	if (this->ValidRightDown(board)) {
		lP->SavePayload(new Move(this, this->GetIndex() + Board::BoardDimensions + 1));
	}

	if (this->ValidLeftUp(board)) {
		lP->SavePayload(new Move(this, this->GetIndex() - Board::BoardDimensions - 1));
	}
	if (this->ValidRightUp(board)) {
		lP->SavePayload(new Move(this, this->GetIndex() - Board::BoardDimensions + 1));
	}
	return lP;
}
LLNode<Move>* King::ListOfJumps(int* board){
	LLNode<Move>* lP = new LLNode<Move>();
	if (this->ValidLeftJumpDown(board)) {
		lP->SavePayload(new Move(this, this->GetIndex() + 2*Board::BoardDimensions - 2));
	}
	if (this->ValidRightJumpDown(board)) {
		lP->SavePayload(new Move(this, this->GetIndex() + 2*Board::BoardDimensions + 2));
	}

	if (this->ValidLeftJumpUp(board)) {
		lP->SavePayload(new Move(this, this->GetIndex() - 2*Board::BoardDimensions - 2));
	}
	if (this->ValidRightJumpUp(board)) {
		lP->SavePayload(new Move(this, this->GetIndex() - 2*Board::BoardDimensions + 2));
	}
	return lP;
}




#endif /* SRC_PAWN_CPP_ */
