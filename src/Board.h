/*
 * Board.h
 *
 *  Created on: Oct 9, 2021
 *      Author: darth
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <cstring>
#include <conio.h>

#include "Cell.h"
#include "Watercraft.h"
#include "Stats.h"

using namespace std;

#ifndef BOARD_H_
#define BOARD_H_

#define ROWS 10
#define COLS 10
#define LOG_FILE_NAME "battleship.log"

#define NUM_OF_SHIPS  5

#define HORIZONTAL    0
#define VERTICAL      1

#define PLAYER_ONE    0
#define PLAYER_TWO    1


#define WATER         '~'
#define HIT           '*'
#define MISS          'm'

#define CARRIER       'c'
#define BATTLESHIP    'b'
#define CRUISER       'r'
#define SUBMARINE     's'
#define DESTROYER     'd'

#define NORTH 0
#define SOUTH 1
#define WEST  2
#define EAST  3

class Board{
	public:
		Board();
		~Board();
		void welcomeScreen();
		void initializeGameBoard(Cell gameBoard[][COLS]);
		void printGameBoard(Cell gameBoard [][COLS], bool showPegs);
		void putShipOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship, Coordinate position, int direction);
		void manuallyPlaceShipsOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship[]);
		bool convertStringtoPosition (Coordinate position[], char *stringPosition, int length);
		void randomlyPlaceShipsOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship[]);
		bool isValidLocation (Cell gameBoard[][COLS], Coordinate position, int direction, int length);
		Coordinate generatePosition (int direction, int length);
		int getRandomNumber (int lowest, int highest);
		short checkShot (Cell gameBoard[][COLS], Coordinate target) ;
		Coordinate getTarget (void) ;
		void systemMessage (char *message) ;
		bool checkSunkShip (short sunkShip[][NUM_OF_SHIPS], short player, char shipSymbol, FILE *stream) ;
		bool isWinner (Stats players[], int player) ;
		void checkBoundsOfCardinal (bool cardinals[], int bound, int direction) ;
		void updateGameBoard (Cell gameBoard[][COLS], Coordinate target) ;

	private:
};



#endif /* BOARD_H_ */
