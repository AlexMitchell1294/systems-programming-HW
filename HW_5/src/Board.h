#pragma once
#include "LinkedList.h"
#include "Pawn.h"
#include <fstream>


#ifndef BOARD_H_
#define BOARD_H_



class Board {
private:
    bool m_gameHasEnded;
    LLNode<Pawn> m_InPlayRPawns;
    LLNode<Pawn> m_InPlayBPawns;
    int* board;

public:

    // these are fields
    bool m_redsTurn;

    //these are constructors/destructors
     Board();
     Board(int* intialBoard[64]);

    ~Board();

    //these are member functions
    //setters / getters
    bool getHasEnded();
    void setHasEnded(bool);
    void setInPlayRPawns(LLNode<Pawn> InPlayRPawns);
    void setInPlayBPawns(LLNode<Pawn> InPlayBPawns);
    LLNode<Pawn>* getInPlayBPawns();
    LLNode<Pawn>* getInPlayRPawns();



    void DisplayBoard();
    void DisplayToFile();
    Pawn* FindPieceAtLocal(int index);
    void RefreshBoard();
    LLNode<Move>* getMoves(LLNode<Pawn> activePawns);
    void Begin();
    void MakeMove(Move* moveToMake);
    void Capture(Move* jumoToMake);
    void KingME();
    LLNode<Move>* getAllMoves();
    LLNode<Move>* getAllJumps();


	static const int BoardDimensions = 8;
};

#endif
