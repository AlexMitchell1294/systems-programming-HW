/*
 * Tests.h
 *
 *  Created on: Oct 9, 2021
 *      Author: darth
 */

#ifndef TESTS_H_
#define TESTS_H_


#include "Production.h"
#include <stdio.h>
#include "Cell.h"
#include "Board.h"


class Tests {
public:
	Tests();
	virtual ~Tests();
	bool tests();


	bool testInitGameBoard();
	bool testPrintGameBoard();
	bool testPutShipOnGameBoard();
	bool testManuallyPlaceShip();
	bool testConvertStringToPosition();
	bool testRandomPlaceShip();
	bool testIsValid();
	bool testGenreatePosition();
	bool testRandomNumber();
	bool testShot();
	bool testWinner();
	bool testCheckShipSunk();

private:
	//For LinkedList

};


#endif /* TESTS_H_ */
