/*
 * Tests.h
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#ifndef TESTS_H_
#define TESTS_H_
#include "Production.h"
#include <stdio.h>


class Tests {
public:
	Tests();
	virtual ~Tests();
	bool tests();

private:
	//For LinkedList
	bool testSavePayload();
	bool testIsEmpty();
	bool testIsEmpty2();
	bool testRemoveSingleNode();
	bool testSearchList();
	bool testLength();
	bool testaddLL();

	//For Pawn
	bool testSetIndexAndTestGetIndex();
	bool testValidLeftDown();
	bool testValidLeftUp();
	bool testValidRightDown();
	bool testValidRightUp();

	//jump moves
	bool testValidJumpRight();
	bool testValidJumpLeft();
	//list construction
	bool testListOfMovesPawn();
	bool testListOfJumpsPawn();

	//For Board
	bool testDisplayBoard();
	bool testMakeMove();
	bool testCapture();

};

#endif /* TESTS_H_ */
