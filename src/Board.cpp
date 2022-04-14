/*
 * Board.cpp
 *
 *  Created on: Oct 9, 2021
 *      Author: darth
 */

#include "Board.h"

Board::Board(){

}
Board::~Board(){

}

void Board::welcomeScreen() {
	printf("XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXX\n");
	printf ("XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX\n");
	printf ("XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXX\n");
	printf ("XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX\n");
	printf ("XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX\n");
	printf ("\n\n");
	printf ("RULES OF THE GAME:\n");
	printf ("1. This is a two player game.\n");
	printf ("2. Player 1 is you and Player 2 is the computer.\n");
	printf ("3. Player 1 will be prompted if user wants to manually input coordinates\n");
	printf ("   for the game board or have the computer randomly generate a game board\n");
	printf ("4. There are five types of ships to be placed by longest length to the\n");
	printf ("   shortest; [c] Carrier has 5 cells, [b] Battleship has 4 cells, [r] Cruiser\n");
	printf ("   has 3 cells, [s] Submarine has 3 cells, [d] Destroyer has 2 cells\n");
	printf ("5. The computer randomly selects which player goes first\n");
	printf ("6. The game begins as each player tries to guess the location of the ships\n");
	printf ("   of the opposing player's game board; [*] hit and [m] miss\n");
	printf ("7. First player to guess the location of all ships wins\n\n");
}

void Board::initializeGameBoard (Cell gameBoard[][COLS]) {
	int i = 0, j = 0;

	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++) {
			gameBoard[i][j].symbol          = WATER;
			gameBoard[i][j].position.row    = i;
			gameBoard[i][j].position.column = j;
		}
}

void Board::printGameBoard (Cell gameBoard [][COLS], bool showPegs) {
	int i = 0, j = 0;

	printf ("  0 1 2 3 4 5 6 7 8 9\n");

	for (i = 0; i < ROWS; i++) {
		printf ("%d ", i);

		for (j = 0; j < COLS; j++) {
			if (showPegs == true)
				printf ("%c ", gameBoard [i][j].symbol);
			else {
				switch (gameBoard [i][j].symbol) {
					case HIT:   printf ("%c ", HIT);   break;
					case MISS:  printf ("%c ", MISS);  break;
					case WATER:
					default:    printf ("%c ", WATER); break;
				}
			}
		}

		putchar ('\n');
	}
}

void Board::putShipOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship,
	                     Coordinate position, int direction) {
	int i = ship.length - 1;

	for (i = 0; i < ship.length; i++) {
		if (direction == HORIZONTAL)
			gameBoard [position.row][position.column + i].symbol = ship.symbol;
		else /* VERTICAL */
			gameBoard [position.row + i][position.column].symbol = ship.symbol;
	}
}

void Board::manuallyPlaceShipsOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship[]) {
	char       stringPosition[11] = "";
	int        i = 0, j = 0;

	Coordinate position[5];
	bool    isValid = false;

	fflush (stdin);

	for (i = 0; i < NUM_OF_SHIPS; i++) {

		while (1) {
			system ("cls");
			printGameBoard(gameBoard, true);
			printf ("> Please enter the %d cells to place the %s across (no spaces):\n", ship[i].length, ship[i].name);
			printf ("> ");
			scanf ("%s", stringPosition);

			/* convertStringtoPosition returns false if unsuccessful */
			if (convertStringtoPosition (position, stringPosition, ship[i].length)) {

				isValid = true;

				for (j = 0; j < ship[i].length; j++) {

					if (gameBoard[position[j].row][position[j].column].symbol == WATER) {
						gameBoard[position[j].row][position[j].column].symbol = ship[i].symbol;
					} else {
						isValid = false;
						printf ("> Invalid input!\n");

						if (j != 0)
							while (j >= 0) {
								gameBoard[position[j].row][position[j].column].symbol = WATER;
								j--;
							}

						break;
					}
				}
			} else {
				isValid = false;
				printf ("> Invalid input!\n");
			}

			if (isValid == true) break;
		}

	}
}

bool Board::convertStringtoPosition (Coordinate position[], char *stringPosition, int length) {
	bool flag = true;
	int i = 0, j = 0, k = 1;

	/* checks if length of input is good */
	if (strlen (stringPosition)/2 == length) {
		/* loops through the length of the ship */
		for (i = 0; i < length && flag; i++) {
			/* checks if each cell is a digit */
			if (isdigit (stringPosition[j]) && isdigit (stringPosition[k])) {
				position[i].row    = stringPosition[j] - '0';
				position[i].column = stringPosition[k] - '0';

				j += 2;
				k += 2;
			} else {
				flag = false;
			}
		}
	} else {
		flag = false;
	}

	return flag;
}

void Board::randomlyPlaceShipsOnGameBoard (Cell gameBoard[][COLS], WaterCraft ship[]) {
	Coordinate position;
	int direction = -1;
	int i = 0;

	for (i = 0; i < NUM_OF_SHIPS; i++) {
		while (true) {
			direction = getRandomNumber (0, 1); /* 0 -> horizontal, 1 -> vertical */
			position = generatePosition (direction, ship[i].length);

			if (isValidLocation (gameBoard, position, direction, ship[i].length)) break;
		}

		putShipOnGameBoard (gameBoard, ship[i], position, direction);
	}
}

bool Board::isValidLocation (Cell gameBoard[][COLS], Coordinate position,
				         int direction, int length) {
	int i = length - 1;
	bool isValid = true;

	for (i = 0; isValid && i < length; i++) {
		if (direction == HORIZONTAL) {
			if (gameBoard [position.row][position.column + i].symbol != WATER &&
				(position.column + i) < COLS)
				isValid = false;
		} else { /* VERTICAL */
			if (gameBoard [position.row + i][position.column].symbol != WATER &&
				(position.row + i) < ROWS)
				isValid = false;
		}
	}

	return isValid;
}

Coordinate Board::generatePosition (int direction, int length) {
	Coordinate position;

	if (direction == HORIZONTAL) {
		position.row    = getRandomNumber (0, ROWS);
		position.column = getRandomNumber (0, COLS - length);
	} else { /* VERTICAL */
		position.row    = getRandomNumber (0, ROWS - length);
		position.column = getRandomNumber (0, COLS);
	}

	return position;
}

int Board::getRandomNumber (int lowest, int highest) {
	if (lowest == 0)
		return rand () % ++highest;

	if (lowest > 0)
		return rand () % ++highest + lowest;
}

short Board::checkShot (Cell gameBoard[][COLS], Coordinate target) {
	int hit = -2;

	switch (gameBoard[target.row][target.column].symbol) {
		/* miss */
		case WATER:
			hit = 0;
			break;

		/* hit */
		case CARRIER:
		case BATTLESHIP:
		case CRUISER:
		case SUBMARINE:
		case DESTROYER:
			hit = 1;
			break;

		case HIT:
		case MISS:
		default:
			hit = -1;
			break;
	}

	return hit;
}

Coordinate Board::getTarget (void) {
	Coordinate target;

	fflush (stdin);

	printf ("> Enter Target (ex. > 3 4):\n");
	printf ("> ");
	fflush(stdout);
	scanf ("%d %d", &target.row, &target.column);
	fflush(stdin);

	return target;
}

bool Board::isWinner (Stats players[], int player) {
	bool isWin = false;

	if (players[player].numHits == 17)
		isWin = true;

	return isWin;
}

bool Board::checkSunkShip (short sunkShip[][NUM_OF_SHIPS], short player, char shipSymbol, FILE *stream) {
	bool sunked = false;

	switch (shipSymbol) {
		case CARRIER:
			if (--sunkShip[player][0] == 0) {
				printf ("> Player %d's Carrier sunked!\n", player + 1);

				/* Write to battleship.log */
				fprintf (stream, "Player %d's Carrier sunked!\n", player + 1);

				sunked = true;
			}
			break;

		case BATTLESHIP:
			if (--sunkShip[player][1] == 0) {
				printf ("> Player %d's Battleship sunked!\n", player + 1);

				/* Write to battleship.log */
				fprintf (stream, "Player %d's Battleship sunked!\n", player + 1);

				sunked = true;
			}
			break;

		case CRUISER:
			if (--sunkShip[player][2] == 0) {
				printf ("> Player %d's Cruiser sunked!\n", player + 1);

				/* Write to battleship.log */
				fprintf (stream, "Player %d's Cruiser sunked!\n", player + 1);

				sunked = true;
			}
			break;

		case SUBMARINE:
			if (--sunkShip[player][3] == 0) {
				printf ("> Player %d's Submarine sunked!\n", player + 1);

				/* Write to battleship.log */
				fprintf (stream, "Player %d's Submarine sunked!\n", player + 1);

				sunked = true;
			}
			break;

		case DESTROYER:
			if (--sunkShip[player][4] == 0) {
				printf ("> Player %d's Destroyer sunked!\n", player + 1);

				/* Write to battleship.log */
				fprintf (stream, "Player %d's Destroyer sunked!\n", player + 1);

				sunked = true;
			}
			break;
	}

	return sunked;
}

void Board::systemMessage (char *message) {
	char ch = '\0';
	char option[] = "1";
	printf ("%s", message);
	fflush(stdout);
	while(1){
		if(cin.get() == '\n') break;
	}
}

void Board::checkBoundsOfCardinal (bool cardinals[], int bound, int direction) {
	switch (direction) {
		case NORTH:
			if (bound < 0)
				cardinals[0] = false;
			else
				cardinals[0] = true;
			break;

		case SOUTH:
			if (bound > 9)
				cardinals[1] = false;
			else
				cardinals[1] = true;
			break;

		case WEST:
			if (bound < 0)
				cardinals[2] = false;
			else
				cardinals[2] = true;
			break;

		case EAST:
			if (bound > 9)
				cardinals[3] = false;
			else
				cardinals[3] = true;
			break;
	}
}

void Board::updateGameBoard (Cell gameBoard[][COLS], Coordinate target) {
	switch (gameBoard[target.row][target.column].symbol) {
		/* miss */
		case WATER:
			gameBoard[target.row][target.column].symbol = MISS;
			break;

		/* hit */
		case CARRIER:
		case BATTLESHIP:
		case CRUISER:
		case SUBMARINE:
		case DESTROYER:
			gameBoard[target.row][target.column].symbol = HIT;
			break;

		case HIT:
		case MISS:
		default:
			break;
	}
}
