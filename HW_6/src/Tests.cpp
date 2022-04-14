/*
 * Tests.cpp
 *
 *  Created on: Oct 9, 2021
 *      Author: darth
 */

#include "Tests.h"


Tests::Tests() {
	// TODO Auto-generated constructor stub

}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

bool Tests::tests()
{
	bool answer = false;

	bool ok1 = testInitGameBoard();
	bool ok2 = testPrintGameBoard();
	bool ok3 = testPutShipOnGameBoard();

	answer = ok1 && ok2 && ok3;

	if(answer)
	{
		puts("All tests passed");
	}
	else
	{
		puts("Not all tests passed");
	}
	puts("\n\n\n");

	return answer;
}



bool Tests::testInitGameBoard(){
	bool ok = false;
	int i = 0, j = 0;
	Board board;
	Cell gameBoard[10][10];
	board.initializeGameBoard(gameBoard);

	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++) {
			if(
			gameBoard[i][j].symbol          == WATER &&
			gameBoard[i][j].position.row    == i &&
			gameBoard[i][j].position.column == j
			) ok = true;
			else {
				ok = false;
				break;
			}
		}


	if(ok)
	{
		puts("testInitGameBoard did pass");
	}
	else
	{
		puts("testInitGameBoard did not pass.");
	}
	return ok;
}

bool Tests::testPrintGameBoard(){
	bool ok = true;
	Board board;
	Cell gameBoard[10][10];
	board.initializeGameBoard(gameBoard);
	puts("Expected result");
	puts(" 0 1 2 3 4 5 6 7 8 9");
	puts("0 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
	puts("1 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
	puts("2 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
	puts("3 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
	puts("4 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
	puts("5 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
	puts("6 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
	puts("7 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
	puts("8 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
	puts("9 ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
	puts("Actual result");
	board.printGameBoard(gameBoard, true);


	if(ok)
	{
		puts("testprintGameBoard did pass");
	}
	else
	{
		puts("testrpintGameBoard did not pass.");
	}
	return ok;
}

bool Tests::testPutShipOnGameBoard()
{
	bool ok = true;
	Board board;
	Cell gameBoard[10][10];
	board.initializeGameBoard(gameBoard);
	WaterCraft ship[NUM_OF_SHIPS] = {{'c', 5, "Carrier"},
			                                 {'b', 4, "Battleship"},
			                                 {'r', 3, "Cruiser"},
			                                 {'s', 3, "Submarine"},
			                                 {'d', 2, "Destroyer"}};

	puts("Randomly Placed Ships");
	board.randomlyPlaceShipsOnGameBoard (gameBoard, ship);
	board.printGameBoard(gameBoard, true);

	if(ok)
	{
		puts("testPutShipOnGameBoard did pass");
	}
	else
	{
		puts("testPutShipOnGameBoard did not pass.");
	}
	return ok;
}


