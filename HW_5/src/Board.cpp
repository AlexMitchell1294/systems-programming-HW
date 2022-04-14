#include "Board.h"

Board::Board(int* intialBoard[64]) {
	m_gameHasEnded = false;
	m_redsTurn = true;
	board = new int[64];
	board = intialBoard[64];

	m_InPlayBPawns.SavePayload(new Pawn(62, false));
	m_InPlayBPawns.SavePayload(new Pawn(60, false));
	m_InPlayBPawns.SavePayload(new Pawn(58, false));
	m_InPlayBPawns.SavePayload(new Pawn(56, false));
	m_InPlayBPawns.SavePayload(new Pawn(55, false));
	m_InPlayBPawns.SavePayload(new Pawn(53, false));
	m_InPlayBPawns.SavePayload(new Pawn(51, false));
	m_InPlayBPawns.SavePayload(new Pawn(49, false));
	m_InPlayBPawns.SavePayload(new Pawn(46, false));
	m_InPlayBPawns.SavePayload(new Pawn(44, false));
	m_InPlayBPawns.SavePayload(new Pawn(42, false));
	m_InPlayBPawns.SavePayload(new Pawn(40, false));

	m_InPlayRPawns.SavePayload(new Pawn(1, true));
	m_InPlayRPawns.SavePayload(new Pawn(3, true));
	m_InPlayRPawns.SavePayload(new Pawn(5, true));
	m_InPlayRPawns.SavePayload(new Pawn(7, true));
	m_InPlayRPawns.SavePayload(new Pawn(8, true));
	m_InPlayRPawns.SavePayload(new Pawn(10, true));
	m_InPlayRPawns.SavePayload(new Pawn(12, true));
	m_InPlayRPawns.SavePayload(new Pawn(14, true));
	m_InPlayRPawns.SavePayload(new Pawn(17, true));
	m_InPlayRPawns.SavePayload(new Pawn(19, true));
	m_InPlayRPawns.SavePayload(new Pawn(21, true));
	m_InPlayRPawns.SavePayload(new Pawn(23, true));
}

Board::Board() {
	m_gameHasEnded = false;
		m_redsTurn = true;
		board = new int[64]{    0,1,0,1,0,1,0,1,
								1,0,1,0,1,0,1,0,
								0,1,0,1,0,1,0,1,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								2,0,2,0,2,0,2,0,
								0,2,0,2,0,2,0,2,
								2,0,2,0,2,0,2,0};

		m_InPlayBPawns.SavePayload(new Pawn(62, false));
		m_InPlayBPawns.SavePayload(new Pawn(60, false));
		m_InPlayBPawns.SavePayload(new Pawn(58, false));
		m_InPlayBPawns.SavePayload(new Pawn(56, false));
		m_InPlayBPawns.SavePayload(new Pawn(55, false));
		m_InPlayBPawns.SavePayload(new Pawn(53, false));
		m_InPlayBPawns.SavePayload(new Pawn(51, false));
		m_InPlayBPawns.SavePayload(new Pawn(49, false));
		m_InPlayBPawns.SavePayload(new Pawn(46, false));
		m_InPlayBPawns.SavePayload(new Pawn(44, false));
		m_InPlayBPawns.SavePayload(new Pawn(42, false));
		m_InPlayBPawns.SavePayload(new Pawn(40, false));

		m_InPlayRPawns.SavePayload(new Pawn(1, true));
		m_InPlayRPawns.SavePayload(new Pawn(3, true));
		m_InPlayRPawns.SavePayload(new Pawn(5, true));
		m_InPlayRPawns.SavePayload(new Pawn(7, true));
		m_InPlayRPawns.SavePayload(new Pawn(8, true));
		m_InPlayRPawns.SavePayload(new Pawn(10, true));
		m_InPlayRPawns.SavePayload(new Pawn(12, true));
		m_InPlayRPawns.SavePayload(new Pawn(14, true));
		m_InPlayRPawns.SavePayload(new Pawn(17, true));
		m_InPlayRPawns.SavePayload(new Pawn(19, true));
		m_InPlayRPawns.SavePayload(new Pawn(21, true));
		m_InPlayRPawns.SavePayload(new Pawn(23, true));

}

Board::~Board()
{
	delete board;
}

bool Board::getHasEnded() { return m_gameHasEnded;}
void Board::setHasEnded(bool state) {m_gameHasEnded = state;}
void Board::setInPlayRPawns(LLNode<Pawn> InPlayRPawns) {m_InPlayRPawns = InPlayRPawns;}
void Board::setInPlayBPawns(LLNode<Pawn> InPlayBPawns) {m_InPlayBPawns = InPlayBPawns;}
LLNode<Pawn>* Board::getInPlayBPawns() {return &m_InPlayBPawns;}
LLNode<Pawn>* Board::getInPlayRPawns() {return &m_InPlayRPawns;}


void Board::DisplayBoard(){
	for(int row = 0; row < BoardDimensions; row++){

		for(int col = 0; col < BoardDimensions; col++){

			printf("%d", board[row*BoardDimensions + col]);

			if(col < BoardDimensions-1){
				printf("| ");
			}
		}
		printf("\n");
	}
}

void Board::DisplayToFile(){

	FILE* Outp = fopen("Output.txt", "a");
	fprintf(Outp,"Board History:\n");
	fprintf(Outp,"_______________________\n");

	for(int row = 0; row < BoardDimensions; row++){

		for(int col = 0; col < BoardDimensions; col++){

			fprintf(Outp, "%d", board[row*BoardDimensions + col]);

			if(col < BoardDimensions-1){
				fprintf(Outp,"| ");
			}
		}
		fprintf(Outp,"\n");
	}
	fclose(Outp);
}

// Assume a piece is guaranteed to be at the given index
Pawn* Board::FindPieceAtLocal(int index) {
	LLNode<Pawn>* temp = &m_InPlayRPawns;

	if(temp->isEmpty()) {} // nothing to do

	else {
		while (temp){

			Pawn* currentPawn = temp->getElementP();
			if (currentPawn->GetIndex() == index)
			{
				return currentPawn;
			}

			temp = temp->getNextP();
		}
	}

	temp = &m_InPlayBPawns;

	if(temp->isEmpty()) {} // nothing to do

	else {
		while (temp){

			Pawn* currentPawn = temp->getElementP();
			if (currentPawn->GetIndex() == index)
			{
				return currentPawn;
			}

			temp = temp->getNextP();
		}
	}
}

void Board::RefreshBoard() {
	for (int i = 0; i<BoardDimensions*BoardDimensions;   ++i)
	{
		board[i] =0;
	}

	LLNode<Pawn>* temp = &m_InPlayRPawns;

	while(temp && !m_InPlayRPawns.isEmpty()){
		Pawn* pP = temp->getElementP();
		King* kP = dynamic_cast<King*> (pP);
		if(kP != (King*) 0){
			board[pP->GetIndex()] = 3;
			temp = temp->getNextP();
		}
		else {
			board[pP->GetIndex()] = 1;
			temp = temp->getNextP();
		}
	}

	temp = &m_InPlayBPawns;
	while(temp && !m_InPlayBPawns.isEmpty()){
		Pawn* pP = temp->getElementP();

		King* kP = dynamic_cast<King*> (temp->getElementP());
		if(kP != NULL){
			board[pP->GetIndex()] = 4;
			temp = temp->getNextP();
		} else {

			board[pP->GetIndex()] = 2;
			temp = temp->getNextP();
		}
	}
}
LLNode<Move>* Board::getMoves(LLNode<Pawn> activePawns) {
	LLNode<Move>* dummy = (LLNode<Move>*) 0;
}

void Board::Capture(Move* m){
	Pawn* pieceWhichMoves = m->m_pawnP;
	int indexToWhichItMoves = m->m_next;


	if(pieceWhichMoves->GetRed()){
		int indexOfPawnWhichWeAreRemoving = (pieceWhichMoves->GetIndex()+indexToWhichItMoves)/2;
		Pawn* pawnWhichWeAreRemoving = FindPieceAtLocal(indexOfPawnWhichWeAreRemoving);

		m_InPlayBPawns.removeItemFromLL(pawnWhichWeAreRemoving);

	}
	else {
		int indexOfPawnWhichWeAreRemoving = (pieceWhichMoves->GetIndex()+indexToWhichItMoves)/2;

		Pawn* pawnWhichWeAreRemoving = FindPieceAtLocal(indexOfPawnWhichWeAreRemoving);

		m_InPlayRPawns.removeItemFromLL(pawnWhichWeAreRemoving);

	}
	MakeMove(m);
}
void Board::MakeMove(Move* m){
	m->m_pawnP->SetIndex(m->m_next);
}

void Board::KingME(){
	//check if the pawn is the right color and correct position to be crowned king (also if it is not already a king)
	for(int i = 0; i<BoardDimensions; i++){
		if (board[i]) {
            Pawn* pP = FindPieceAtLocal(i);
            if (board[i] > 2) {} // if it is already a king nothing to do
            else if (!pP->GetRed())  //if it is red and in correct position
            {
                m_InPlayBPawns.SavePayload(new King (i, false));
                m_InPlayBPawns.removeItemFromLL(pP);
            }
		}
	}
	for(int i = BoardDimensions*BoardDimensions -1; i>=(BoardDimensions*BoardDimensions)-BoardDimensions; --i){
        if (board[i]) {

		Pawn* pP = FindPieceAtLocal(i);
		if (board[i] > 2) {} // if it is already a king nothing to do
		else if (pP->GetRed())  //if it is red and in correct position
		{
			m_InPlayRPawns.SavePayload(new King (i, true));
			m_InPlayRPawns.removeItemFromLL(pP);
		}
        }
	}
}

LLNode<Move>* Board::getAllMoves() {
	LLNode<Move>* returnList = new LLNode<Move>;
	LLNode<Pawn>* temp;

	if(m_redsTurn) {
		temp = &m_InPlayRPawns;
	} else {
		temp = &m_InPlayBPawns;
	}
	while(temp) {
		Pawn* pP = temp->getElementP();
		King* kP = dynamic_cast<King*> (pP);
		if(kP != (King*) 0){
			LLNode<Move>* currentMoves = kP->ListOfMoves(board);
			returnList->addLL(currentMoves);
			temp = temp ->getNextP();
		}
		else {
			LLNode<Move>* currentMoves = pP->ListOfMoves(board);
			returnList->addLL(currentMoves);
			temp = temp ->getNextP();
		}
	}

	return returnList;
}

LLNode<Move>* Board::getAllJumps() {
	LLNode<Move>* returnList = new LLNode<Move>;
	LLNode<Pawn>* temp;

	if(m_redsTurn) {
		temp = &m_InPlayRPawns;
	} else {
		temp = &m_InPlayBPawns;
	}
	while(temp) {
		Pawn* pP = temp->getElementP();
		LLNode<Move>* currentMoves = pP->ListOfJumps(board);
		returnList->addLL(currentMoves);
		temp = temp ->getNextP();
	}

	return returnList;
}

void Board::Begin() {
	FILE* Outp = fopen("Output.txt", "w");
	int numOfMoves = 0;
	setHasEnded(false);
	m_redsTurn = false;
	printf("___________________________________________________\n");
	fprintf(Outp,"___________________________________________________\n");
	LLNode<Pawn>* relevantPawns;

	while(!m_gameHasEnded && numOfMoves <= 1000) {
		printf("Currently On Move: %d\n", numOfMoves);

		RefreshBoard();


		DisplayBoard();
		DisplayToFile();

		if(m_redsTurn) {
			relevantPawns = &m_InPlayRPawns;}
		else {
			relevantPawns = &m_InPlayBPawns;
		}

		if (relevantPawns->isEmpty()) {
			printf("All pawns have been taken or kinged\n");
			fprintf(Outp,"All pawns have been taken or kinged\n");
			setHasEnded(true);
		}
		else {
			LLNode<Move>* jumpMoves = getAllJumps();
			if (!jumpMoves->isEmpty()) {
				while (!jumpMoves->isEmpty()) { // keep performing jumps
					printf("Number of legitimate jumps %d\n", jumpMoves->Length());
                    fprintf(Outp,"Number of possible valid jumps %d\n", jumpMoves->Length());

					Move* getRandomJump = jumpMoves->getRandom();
					int indexOfgetRandom = getRandomJump->m_pawnP->GetIndex();
					printf("The jump chosen was row %d and column %d to row %d and and column %d\n", (indexOfgetRandom / BoardDimensions) + 1, (indexOfgetRandom % BoardDimensions) + 1, (getRandomJump->m_next / BoardDimensions) + 1, (getRandomJump->m_next % BoardDimensions) + 1);
					fprintf(Outp, "The jump chosen was row %d and column %d to row %d and and column %d\n", (indexOfgetRandom / BoardDimensions) + 1, (indexOfgetRandom % BoardDimensions) + 1, (getRandomJump->m_next / BoardDimensions) + 1, (getRandomJump->m_next % BoardDimensions) + 1);
					Capture(getRandomJump);
					RefreshBoard();
					KingME();
					RefreshBoard();
					printf("___________________________________________________\n");
					fprintf(Outp,"___________________________________________________\n");
					printf("Currently On Move: %d \n", numOfMoves);
                    fprintf(Outp,"Currently On Move: %d\n", numOfMoves);
					DisplayBoard();
					DisplayToFile();
					jumpMoves = getAllJumps();
					++numOfMoves;
				}
			}
			else {
				LLNode<Move>* regularMoves = getAllMoves();
				if(regularMoves->isEmpty())
				{
					printf("No moves left\n");
					fprintf(Outp,"No moves left\n");

					setHasEnded(true);
				}
				else {
					printf("Valid Moves %d\n", regularMoves->Length());
                    fprintf(Outp,"Valid Moves %d\n", regularMoves->Length());
					Move* getRandomMove = regularMoves->getRandom();
					int indexOfgetRandom = getRandomMove->m_pawnP->GetIndex();
					printf("The jump chosen was row %d and column %d to row %d and column %d \n"   , (indexOfgetRandom / BoardDimensions + 1), (indexOfgetRandom % BoardDimensions + 1), (getRandomMove->m_next / BoardDimensions + 1), (getRandomMove->m_next % BoardDimensions + 1));
					fprintf(Outp,"The jump chosen was row %d and column %d to row %d and column %d\n", (indexOfgetRandom / BoardDimensions), (indexOfgetRandom % BoardDimensions + 1), (getRandomMove->m_next / BoardDimensions  + 1), (getRandomMove->m_next % BoardDimensions + 1));

					MakeMove(getRandomMove);
					RefreshBoard();
					KingME();
				}
			}
		}


		m_redsTurn = !m_redsTurn;
		++numOfMoves;
	}
	printf("___________________________________________________\n");
	fprintf(Outp,"___________________________________________________\n");
	DisplayBoard();
	printf("Game has ended!\n");
	fprintf(Outp,"Game has ended!\n");
	fclose(Outp);
}

