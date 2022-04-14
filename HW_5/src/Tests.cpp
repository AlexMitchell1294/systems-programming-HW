/*
 * Tests.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Tests.h"
#include <stdbool.h>

Tests::Tests() {
	// TODO Auto-generated constructor stub

}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

bool Tests::tests()
{
	bool answer = true;

	bool ok1 = testSavePayload();
	bool ok2 = testIsEmpty();
	bool ok8 = testIsEmpty2();
	bool ok3 = testRemoveSingleNode();
	bool ok4 = testSearchList();
	bool ok5 = testLength();
	bool ok6 = testaddLL();
	bool ok7 = testDisplayBoard();
	bool ok9 = testMakeMove();
	bool ok91 = testCapture();
	bool ok10 = testSetIndexAndTestGetIndex();
	bool ok11 = testValidLeftDown();
	bool ok13 = testValidLeftUp();
	bool ok14 = testValidRightDown();
	bool ok16 = testValidRightUp();
	bool ok20 = testValidJumpLeft();
	bool ok21 = testValidJumpRight();
	bool ok22 = testListOfMovesPawn();
	answer = ok1 && ok2 && ok8 && ok3 && ok4 && ok5 && ok8&& ok9 && ok10 && ok11 && ok13&&ok14&&ok16&&ok20&&ok21&&ok22;// && ok3  && ok4 && ok5 && ok6 && ok7;
	return answer;
}

bool Tests::testSavePayload() {
	int first = 123;
	int second = 2454;
	int third = 219;

	LLNode<int> ll;

	ll.SavePayload(&first);
	ll.SavePayload(&second);
	ll.SavePayload(&third);


	LLNode<int>* middle = ll.getNextP();

	LLNode<int>* leaf = middle->getNextP();

	bool ok = (ll.getElementP() == &first);
	ok &= (middle->getElementP() == &second);
	ok &= (leaf->getElementP() == &third);


	if(ok) {
		printf("savePayload passed \n");
	}
	else {
		printf("savePayload did not pass \n");
	}

	return ok;
}

bool Tests::testIsEmpty() {
	bool ok = false;
	int first = 123;

	LLNode<int> ll(&first);

	ok = !ll.isEmpty();

	if(ok) {
		printf("testIsEmpty passed \n");
	}
	else {
		printf("testIsEmpty did not pass \n");
	}

	return ok;
}

bool Tests::testIsEmpty2() {
	bool ok = false;

	LLNode<int> ll;

	ok = ll.isEmpty();

	if(ok) {
		printf("testIsEmpty2 passed \n");
	}
	else {
		printf("testIsEmpty2 did not pass \n");
	}

	return ok;
}

bool Tests::testRemoveSingleNode() {
	LLNode<int> ll;
	int first = 123;
	ll.SavePayload(&first);
	ll.removeItemFromLL(&first);
	bool ok = ll.isEmpty();

	if(ok) {
		printf("testRemoveSingleNode passed \n");
	}
	else {
		printf("testRemoveSingleNode did not pass \n");
	}

	return ok;
}

bool Tests::testSearchList() {

	LLNode<int> ll;
	int first = 1;
	int second = 20000;
	int third = 3000;
	int fourth = 400;

	ll.SavePayload(&first);
	ll.SavePayload(&second);
	ll.SavePayload(&third);
	ll.SavePayload(&fourth);

	bool ok = true;
	ok &= ll.SearchList(&first);
	ok &= ll.SearchList(&third);


	if(ok) {
		printf("testSearchList passed \n");
	}
	else {
		printf("testSearchList did not pass \n");
	}

	return ok;

}

bool Tests::testLength() {
	int first = 1;
	int second = 20000;
	int third = 3000;
	int fourth = 400;
	bool ok = false;

	LLNode<int> ll;
	ok = ll.Length() == 0;

	ll.SavePayload(&first);
	ok &= ll.Length() == 1;

	ll.SavePayload(&second);
	ll.SavePayload(&third);
	ll.SavePayload(&fourth);
	ok &= ll.Length() == 4;

	ll.removeItemFromLL(&fourth);
	ok &= ll.Length() == 3;

	if(ok) {
		printf("testLength passed \n");
	}
	else {
		printf("testLength did not pass \n");
	}

	return ok;

}

bool Tests::testaddLL() {
	int first = 1;
	int second = 20000;
	int third = 3000;
	int fourth = 400;
	bool ok = true;

	LLNode<int> ll1;
	ll1.SavePayload(&second);
	ll1.SavePayload(&third);

	LLNode<int> ll2;
	ll2.SavePayload(&first);
	ll2.SavePayload(&fourth);

	ll1.addLL(&ll2);

	ok &= ll1.SearchList(&first);
	ok &= ll1.SearchList(&fourth);


	if(ok) {
		printf("testaddLL passed \n");
	}
	else {
		printf("testaddLL did not pass \n");
	}

	return ok;


}

bool Tests::testDisplayBoard(){
	Board* board = new Board();
	printf("Board should look like:\n");
    printf("0| 1| 0| 1| 0| 1| 0| 1\n");
	printf("1| 0| 1| 0| 1| 0| 1| 0\n");
	printf("0| 1| 0| 1| 0| 1| 0| 1\n");
	printf("0| 0| 0| 0| 0| 0| 0| 0\n");
	printf("0| 0| 0| 0| 0| 0| 0| 0\n");
	printf("2| 0| 2| 0| 2| 0| 2| 0\n");
	printf("0| 2| 0| 2| 0| 2| 0| 2\n");
	printf("2| 0| 2| 0| 2| 0| 2| 0\n");
	printf("Actual board:\n");
	board->DisplayBoard();
}


bool Tests::testMakeMove() {
	Board board;

	Move myMove(board.FindPieceAtLocal(40), 33);
	board.MakeMove(&myMove);
	board.RefreshBoard();
	printf("Expected board is: \n");
	printf("0| 1| 0| 1| 0| 1| 0| 1\n");
	printf("1| 0| 1| 0| 1| 0| 1| 0\n");
	printf("0| 1| 0| 1| 0| 1| 0| 1\n");
	printf("0| 0| 0| 0| 0| 0| 0| 0\n");
	printf("0| 2| 0| 0| 0| 0| 0| 0\n");
	printf("0| 0| 2| 0| 2| 0| 0| 2\n");
	printf("0| 2| 0| 2| 0| 2| 0| 2\n");
	printf("2| 0| 2| 0| 2| 0| 2| 0\n");

	printf("Actual Board Is:\n");
	board.DisplayBoard();
}


bool Tests::testCapture() {

	Board board;

	Pawn* pieceP = new Pawn(35, true);
	board.getInPlayRPawns()->SavePayload(pieceP);
	board.RefreshBoard();

    Pawn* jumperP = board.FindPieceAtLocal(42);
	Move myJump(jumperP, 28);

	board.Capture(&myJump);
	board.RefreshBoard();
	printf("Expected board is: ");
	printf("0| 1| 0| 1| 0| 1| 0| 1\n");
	printf("1| 0| 1| 0| 1| 0| 1| 0\n");
	printf("0| 1| 0| 1| 0| 1| 0| 1\n");
	printf("0| 0| 0| 0| 2| 0| 0| 0\n");
	printf("0| 0| 0| 0| 0| 0| 0| 0\n");
	printf("2| 0| 0| 0| 2| 0| 2| 0\n");
	printf("0| 2| 0| 2| 0| 2| 0| 2\n");
	printf("2| 0| 2| 0| 2| 0| 2| 0\n");

	printf("Actual Board Is:\n");
	board.DisplayBoard();
}

bool Tests::testSetIndexAndTestGetIndex(){
	bool ok = true;

	Pawn* pP = new Pawn();
	pP->SetIndex(1);
	if(pP->GetIndex()!=1){ok = false;}

	pP->SetIndex((Board::BoardDimensions)*(Board::BoardDimensions)-1);
	if(pP->GetIndex()!=((Board::BoardDimensions)*(Board::BoardDimensions)-1)){ok = false;}

	pP->SetIndex((Board::BoardDimensions)*(Board::BoardDimensions)+1);
	if(pP->GetIndex()!=((Board::BoardDimensions)*(Board::BoardDimensions)-1)){ok = false;}

	if(ok) {
		printf("testSetIndexndexAndTestGetIndexndex passed \n");
	}
	else {
		printf("testSetIndexndexAndTestGetIndexndex did not pass \n");
	}
	return ok;
}



bool Tests::testValidLeftDown(){

	bool ok = true;

	int board[] = { 0,1,0,1,0,0,0,0,
			1,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,1,0,0,0,0,0};

	Pawn* pP = new Pawn();
	pP -> SetIndex(3);          //should be able to move
	if(!(pP -> ValidLeftDown(board))){
		ok = false;
	}
	pP -> SetIndex(8);        // cannot move off the board horizontally
	if(pP -> ValidLeftDown(board)){
		ok = false;
	}

	pP -> SetIndex(58);        // cannot move off the board vertically
	if(pP -> ValidLeftDown(board)){
		ok = false;
	}

	pP -> SetIndex(1);        // cannot move when blocked by another piece
	if(pP -> ValidLeftDown(board)){
		ok = false;
	}

	if(ok) {
		printf("testValidLeftDown passed \n");
	}
	else {
		printf("testValidLeftDown did not pass \n");
	}

	return ok;
}
bool Tests::testValidLeftUp(){

	bool ok = true;
	int board[] = { 0,1,0,0,0,0,0,0,
			1,0,1,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,1,0,0,0,0,0};

	Pawn* pP = new Pawn();
	pP -> SetIndex(58);          //should be able to move
	if(!(pP -> ValidLeftUp(board))){
		ok = false;
	}
	pP -> SetIndex(8);        // cannot move off the board horizontally
	if(pP -> ValidLeftUp(board)){
		ok = false;
	}

	pP -> SetIndex(1);        // cannot move off the board vertically
	if(pP -> ValidLeftUp(board)){
		ok = false;
	}

	pP -> SetIndex(10);        // cannot move when blocked by another piece
	if(pP -> ValidLeftUp(board)){
		ok = false;
	}

	if(ok) {
		printf("testValidLeftUp passed \n");
	}
	else {
		printf("testValidLeftUp did not pass \n");
	}

	return ok;
}
bool Tests::testValidRightDown(){

	bool ok = true;

	int board[] = { 0,1,0,0,0,0,0,0,
			0,0,1,0,0,0,0,1,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,1,0,0,0,0,0};

	Pawn* pP = new Pawn();
	pP -> SetIndex(10);          //should be able to move
	if(!(pP -> ValidRightDown(board))){
		ok = false;
	}
	pP -> SetIndex(15);        // cannot move off the board horizontally
	if(pP -> ValidRightDown(board)){
		ok = false;
	}

	pP -> SetIndex(58);        // cannot move off the board vertically
	if(pP -> ValidRightDown(board)){
		ok = false;
	}

	pP -> SetIndex(1);        // cannot move when blocked by another piece
	if(pP -> ValidRightDown(board)){
		ok = false;
	}

	if(ok) {
		printf("testValidRightDown passed \n");
	}
	else {
		printf("testValidRightDown did not pass \n");
	}

	return ok;
}
bool Tests::testValidRightUp(){

	bool ok = true;

	int board[] = { 0,1,0,1,0,0,0,0,
			1,0,0,0,0,0,0,1,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			0,0,1,0,0,0,0,0};

	Pawn* pP = new Pawn();
	pP -> SetIndex(58);          //should be able to move
	if(!(pP -> ValidRightUp(board))){
		ok = false;
	}
	pP -> SetIndex(15);        // cannot move off the board horizontally
	if(pP -> ValidRightUp(board)){
		ok = false;
	}

	pP -> SetIndex(1);        // cannot move off the board vertically
	if(pP -> ValidRightUp(board)){
		ok = false;
	}

	pP -> SetIndex(8);        // cannot move when blocked by another piece
	if(pP -> ValidRightUp(board)){
		ok = false;
	}
	if(ok) {
		printf("testValidRightDown passed \n");
	}
	else {
		printf("testValidRightDown did not pass \n");
	}

	return ok;
}


bool Tests::testValidJumpLeft(){
	bool ok = true;

	int board[] = { 1,0,1,0,1,0,1,0,
			0,1,0,1,0,1,0,1,
			0,0,2,0,2,0,0,0,
			0,0,0,2,0,0,0,0,
			0,1,0,0,0,0,0,0,
			2,0,0,0,0,0,0,0,
			2,0,2,1,2,0,2,0,
			0,2,2,2,0,2,0,2};

	Pawn* pP = new Pawn();
	pP -> SetIndex(11);             //should be able to jump
	if(!(pP -> ValidLeftJumpDown(board))){
		ok = false;
	}

	pP -> SetIndex(13);             //should not jump 2 pieces
	if(pP -> ValidLeftJumpDown(board)){
		ok = false;
	}

	pP -> SetIndex(2);              // should not jump own piece
	if(pP -> ValidLeftJumpDown(board)){
		ok = false;
	}

	pP -> SetIndex(33);             // should not jump off the board to the left
	if(pP -> ValidLeftJumpDown(board)){
		ok = false;
	}

	pP ->SetIndex(51);          //should not jump off the board down
	if(pP -> ValidLeftJumpDown(board)){
		ok = false;
	}


	if(ok) {
		printf("testValidLeftJump passed \n");
	}
	else {
		printf("testValidLeftJump did not pass \n");
	}

	return ok;
}

bool Tests::testValidJumpRight(){
	bool ok = true;

	int board[] = { 1,0,1,0,1,0,1,0,
			0,1,0,1,0,1,0,1,
			0,0,2,0,2,0,0,0,
			0,0,0,0,0,2,0,0,
			0,0,0,0,0,0,1,0,
			0,0,0,0,0,0,0,2,
			2,0,2,0,1,0,2,0,
			0,2,0,2,0,2,0,2};

	Pawn* pP = new Pawn();
	pP -> SetIndex(9);
	if(!(pP -> ValidRightJumpDown(board))){
		ok = false;
	}

	pP -> SetIndex(11);
	if(pP -> ValidRightJumpDown(board)){
		ok = false;
	}

	pP -> SetIndex(4);
	if(pP -> ValidRightJumpDown(board)){
		ok = false;
	}

	pP -> SetIndex(38);
	if(pP -> ValidRightJumpDown(board)){
		ok = false;
	}

	pP ->SetIndex(52);          //should not jump off the board down
	if(pP -> ValidRightJumpUp(board)){
		ok = false;
	}

	if(ok) {
		printf("testValidRightJump passed \n");
	}
	else {
		printf("testValidRightJump did not pass \n");
	}

	return ok;
}


bool Tests::testListOfMovesPawn() {
	bool ok = true;

	int board[] = { 0,1,0,0,0,0,0,2,
			0,0,1,0,0,0,0,0,
			0,0,0,0,0,0,0,0,
			1,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,2,
			0,0,0,0,0,0,0,0,
			0,0,0,0,0,2,0,0,
			1,0,0,0,0,0,2,0};

	Pawn* pP = new Pawn();
	int length = 0;

	// Red Pawns
	pP -> SetToRed(true);
	//First pawn
	{
		pP -> SetIndex(56);             //should not be able to move
		printf("Expected moves for pawn 1 are:");
		printf("None. ");
		LLNode<Move>* moves1 = pP->ListOfMoves(board);
		length = moves1->Length();
		printf("Actual moves for pawn 1 are:");
		printf("(");
		LLNode<Move>* temp = moves1;
		for (int i = 0; i < length; ++i) {
			Move* m = temp->getElementP();
			m->printMove();
			temp->getNextP();
		}
		printf(" )");
	}

	//Second Pawn
	{
		pP -> SetIndex(1);             //should be able to move left down only
		printf("Expected moves for pawn 2 are:");
		printf("1,");
		LLNode<Move>* moves1 = pP->ListOfMoves(board);
		length = moves1->Length();
		printf("Actual moves for pawn 2 are:");
		printf("( ");
		LLNode<Move>* temp = moves1;
		for (int i = 0; i < length; ++i) {
			Move* m = temp->getElementP();
			m->printMove();
			temp->getNextP();
		}
		printf(" )\n");
	}
	return ok;
}
