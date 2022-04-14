#pragma once
#include "LinkedList.h"

class Move;

class Pawn{

public:
	Pawn();
	Pawn(int newIndex, bool newColorRed);
	virtual ~Pawn();
	void SetIndex(int i);
	void SetToRed(bool r);
	int GetIndex();
	bool GetRed();
	void makeMove(Move*);
	bool ValidLeftDown(int*);
	bool ValidLeftUp(int*);
	bool ValidRightDown(int*);
	bool ValidRightUp(int*);



	bool ValidLeftJumpDown(int*);
	bool ValidLeftJumpUp(int*);
	bool ValidRightJumpDown(int*);
	bool ValidRightJumpUp(int*);


	LLNode<Move>* ListOfMoves(int*);
	LLNode<Move>*ListOfJumps(int*);

private:
	int index;
	bool ColorRed;
};

class King : public Pawn{
public:
	King();
    King(int newIndex, bool newColorRed);

	virtual ~King();

	LLNode<Move>* ListOfMoves(int*);
	LLNode<Move>*ListOfJumps(int*);
};

class Move{
public:
    Move();
    Move(Pawn* pawnP, int next);
	Pawn* m_pawnP;
	int m_next;
	//for testing purposes
	void printMove();
};
