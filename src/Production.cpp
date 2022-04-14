/*
 * Production.cpp
 *
 *  Created on: Oct 9, 2021
 *      Author: darth
 */
#include "Production.h"
#include "Board.h"

Production::Production(){

}

bool Production::prod(int argc, char* argv[]){
	/**
		 * Two boards exist within the game. Hint: each board should be
		 * implemented as a 2-dimensional array. Each 2-dimensional array
		 * should be 10 X 10. One represents Player1's board and one represents
		 * Player2's board.
		 */

		Board board;
		Stats players[2] = {{0, 0, 0, 0.0}, {0, 0, 0, 0.0}};

		Cell playerOneGameBoard[ROWS][COLS];       /* Player one game board */
		Cell playerTwoGameBoard[ROWS][COLS];       /* Player two game board */

		Coordinate target;             /* x, y value of a target */
		Coordinate targetTemp;         /* x, y value that holds a temporary value*/
		Coordinate targetOrigin;       /* x, y value of the original target */
		Coordinate targetAI;           /* x, y value of the targets using AI technique */

		WaterCraft ship[NUM_OF_SHIPS] = {{'c', 5, "Carrier"},
		                                 {'b', 4, "Battleship"},
		                                 {'r', 3, "Cruiser"},
		                                 {'s', 3, "Submarine"},
		                                 {'d', 2, "Destroyer"}};

		bool    huntMode       = true;                     /* mode of randomly selecting a target */
		bool    targetMode     = false;                    /* mode when there is a hit */
		bool    flipper        = true;	                  /* flips values of boolean */
		bool    cardinals[4]   = {true, true, true, true}; /* represents the 4 cardinals, N, S, W, E */
		bool    hasAShipSunked = false;                    /* if a ship has sank */

		short sunkShip[2][NUM_OF_SHIPS] = {{5, 4, 3, 3, 2},
		                                   {5, 4, 3, 3, 2}};  /* tracks parts of the ship destroyed */

		short player  = 0;	           /* 0 -> player1, 1 -> player2 */
		short shot    = 0;             /* holds temp value if ship has been shot */
		int   option  = 0;             /* option for player to place ship manually or randomly */
		int   north   = 0,             /* holds change of value when going north */
			  south   = 0,             /* holds change of value when going south */
			  east    = 0,             /* holds change of value when going east */
			  west    = 0;             /* holds change of value when going west */
		int   i       = 0,
			  counter = 1;             /* i and counter are used as counters */

		char  shipSymbol = '\0';       /* temporary value to save character symbol of the ship */

		FILE *outStream = NULL;        /* stream to output file battleship.log */

		/* Start of Program */
		outStream = fopen (LOG_FILE_NAME, "w");

		srand ((unsigned int) time (NULL));

		/**
		 * Print welcome screen
		 */
		board.welcomeScreen ();
		board.systemMessage ("Hit <ENTER> to continue!\n");

		system ("cls");

		/**
		 * Each Player's game board should be initialized to all '~' indicating
		 * no ships hachar ch = '\0';ve been placed on either board.
		 */
		board.initializeGameBoard (playerOneGameBoard);
		board.initializeGameBoard (playerTwoGameBoard);

		/**
		 * Both players' fleets consist of 5 ships that are hidden from the enemy.
		 * Each ship may be differentiated by its "size" (besides the Cruiser and
		 * Submarine) or number of cells it expands on the game board.
		 *      The Carrier has 5 cells,
		 *      Battleship has 4 cells,
		 *      Cruiser has 3 cells,
		 *      Submarine has 3 cells, and
		 *      the Destroyer has 2 cells.
		 */

		/**
		 * The program should be built such that the user is Player1 and the
		 * computer is Player2.
		 */

		/**
		 * Before the game starts, Player1 should have the option to either
		 * manually place each of the 5 ships in his/her fleet or to have them
		 * randomly placed on the board. If Player1 decides to place the ships
		 * manually, then he/she should be prompted to place the Carrier first,
		 * Battleship second, Cruiser third, Submarine fourth, and the Destroyer
		 * last.
		 */
		printf ("> Please select from the following menu:\n");
		printf ("> [1] Manually\n");
		printf ("> [2] Randomly\n");
		printf ("> Enter Option: ");
		fflush(stdout);
		scanf ("%d", &option);
		fflush(stdin);

		switch (option) {
			case 1: board.manuallyPlaceShipsOnGameBoard (playerOneGameBoard, ship);
		            break;
			case 2: board.randomlyPlaceShipsOnGameBoard (playerOneGameBoard, ship);
					break;
		}

		/**
		 * Note that ships cannot be placed diagonally on the board, they can
		 * only be placed vertically or horizontally. You program must check to
		 * see if the user tries to place a ship outside the boundaries of the
		 * board or on top of a ship that has already been placed. Each cell on
		 * the board that contains part of the ship must be indicated by 'c' for
		 * Carrier, 'b' for Battleship, 'r' for Cruiser, 's' for Submarine, or
		 * 'd' for Destroyer.
		 */

		/**
		 * Player2's ships must be randomly placed. Note that the placement of
		 * Player2's ships must be unknown. Thus, Player2's board will only
		 * display '~' in each cell after the placement of each ship.
		 */
		board.randomlyPlaceShipsOnGameBoard (playerTwoGameBoard, ship);
		printf ("> Player 2 (Computer's) board has been generated.\n");

		/**
		 * The program should randomly select Player1 or Player2 to go first.
		 */
		player = board.getRandomNumber (0, 1);
		printf ("> Player %d has been randomly selected to go first.\n", player + 1);
		board.systemMessage ("> Hit <ENTER> to continue!\n");
		fflush(stdout);
		system ("cls");

		/**
		 * Once it has been decided on which player goes first, the game starts.
		 * Whenever it's Player1's turn, a prompt should be displayed asking for
		 * a position to target (specifying where to "shoot") on the enemy's
		 * (Player2's) board (2-dimensional array). The position should be
		 * specified in terms of a row and a column on the board. The row and
		 * column should always be displayed along with the board. If the
		 * position specified happens to hit a ship, then a '*' should replace
		 * the '-' on Player2's board. If the positioned specified misses any
		 * one of the ships in the fleet, then a 'm' should replace the '-' on
		 * Player2's board. Note that from turn-to-turn each player should NOT
		 * be allowed to enter the same position. Also, between turns clear the
		 * screen (system("cls")). In one turn, a player can only take one shot
		 * at the enemy's (other player's) fleet. When Player2 takes a shot at
		 * Player1's board, each hit should be specified with a '*' and each
		 * miss with a 'm' on Player1's board. The game is over win Player1 or
		 * Player2 has sunk all of the ships in the fleet of the enemy.
		 */

		/**
		 * For each move made by Player1 and Player2, the results should be
		 * echoed to a file called "battleship.log". In this file, you should
		 * log the targeted position by each player on each move and whether it
		 * was a hit on one of the ships in the fleet. Also, if one of the ships
		 * happens to sink, then note this in the log file.
		 */
		while (true) {

			/* Write to battleship.log */
			fprintf (outStream, "Player %d's turn.\n", player + 1);

			/* switches back and forth between player 1 and player 2 */
			switch (player) {

				case PLAYER_ONE:
					/* Print player 2's game board*/
					printf ("> Player 2's Board:\n");
					board.printGameBoard (playerTwoGameBoard, false);
					printf ("> PLAYER 1'S TURN\n");
					fflush(stdout);

					/* Prompts user to enter target */
					do {
						target = board.getTarget ();
						shot = board.checkShot (playerTwoGameBoard, target);
						fflush(stdout);

						/* prompts user that input is invalid or either a hit or miss cell */
						if (shot == -1)
							printf ("> Try inputting another target!\n");
						fflush(stdout);
					} while (shot == -1);

					/* saves the character of the targeted cell */
					shipSymbol = playerTwoGameBoard[target.row][target.column].symbol;
					fflush(stdout);
					break;

				case PLAYER_TWO:

					/**** IMPLEMENTATION OF ARTIFICIAL INTELLIGENCE ****/

					/* Print player 1's game board */
					printf ("> Player 1's Board:\n");
					board.printGameBoard (playerOneGameBoard, true);
					printf ("> COMPUTER'S TURN\n");

					/**
					 * check from a previous cycle if a ship has sunk,
					 * if yes, it reinitializes values to go back to hunt mode
					 */
					if (hasAShipSunked) {
						hasAShipSunked = false;
						targetMode = false;
						huntMode = true;
					}

					/**
					 * TARGET MODE
					 * This mode is true when the computer randomly selects a target,
					 * and it happens to be a hit, this mode is set to true.
					 */
					if (targetMode) {
						/* retains value of targetAI */
						target = targetAI;

						do {
							if (cardinals[NORTH]) {        /* NORTH */
								target.row = north;
							} else if (cardinals[SOUTH]) { /* SOUTH */
								target.row = south;
							} else if (cardinals[WEST]) {  /* WEST */
								target.column = west;
							} else if (cardinals[EAST]) {  /* EAST */
								target.column = east;
							} else if (!cardinals[NORTH] && !cardinals[SOUTH] &&
							           !cardinals[WEST]  && !cardinals[EAST]  &&
									   !hasAShipSunked) {
								/* All cardinals are false but has not sunk a ship */

								/* reinitiliazes target to the original target value */
								target = targetOrigin;
								targetTemp = target;

								/**
								 * Counter increments by one, when the loop cycles again and
								 * all cardinals are still false. This ensures that we are checking
								 * one cell over the adjacent cells
								 */
								north = target.row - counter;
								targetTemp.row = north;

								/* checks if the value NORTH of the target is a hit or miss */
								if (board.checkShot (playerOneGameBoard, targetTemp) != -1 && north >= 0) {
									cardinals[NORTH] = true;
								}

								targetTemp = target;
								south = target.row + counter;
								targetTemp.row = south;

								/* checks if the value SOUTH of the target is a hit or miss */
								if (board.checkShot (playerOneGameBoard, targetTemp) != -1 && south <= 9) {
									cardinals[SOUTH] = true;
								}

								targetTemp = target;
								west = target.column - counter;
								targetTemp.column = west;

								/* checks if the value WEST of the target is a hit or miss */
								if (board.checkShot (playerOneGameBoard, targetTemp) != -1 && west >= 0) {
									cardinals[WEST] = true;
								}

								targetTemp = target;
								east = target.column + counter;
								targetTemp.column = east;

								/* checks if the value EAST of the target is a hit or miss */
								if (board.checkShot (playerOneGameBoard, targetTemp) != -1 && east <= 9) {
									cardinals[EAST] = true;
								}

								/**
								 * increments counter every cycle, serves as a addend to how
								 * many cells to check from the target cell
								 */
								counter++;

							} else  {
								/* when all conditions are not met, it reverts back to Hunt mode */
								targetMode = false;
								huntMode = true;
								break;
							}

							/* checks if the shot is a hit or miss */
							shot = board.checkShot (playerOneGameBoard, target);

						} while (shot == -1 && targetMode == true);

						/**
						 * this loop flips the values of the cardinals when it is not needed
						 * takes the cardinal off the stack for directions to check
						 */
						if (shot == 1 && huntMode == false) {
							for (i = 0; i < 4; i++) {
								if (flipper == false)
									cardinals[i] = false;

								if (cardinals[i] == flipper)
									flipper = false;
							}
						} else {
							for (i = 0; i < 4; i++) {
								if (flipper == true && cardinals[i] != false) {
									cardinals[i] = false;
									break;
								}
							}
						}

						/* reinitializes the value of flipper */
						flipper = true;
					}

					/**
					 * HUNT MODE
					 * This is starting mode of Player 2's turn. This pertains to the
					 * computer randomly selecting cells as targets and checking if they are
					 * just plain water. When a cell equates to a Hit, then hunt mode is
					 * set to false and target mode is set to true
					 */
					if (huntMode) {

						/* reinitializes important values */
						counter = 1;
						flipper = true;
						for (i = 0; i < 4; i++)
							cardinals[i] = true;

						/* loop that gets a random number of a cell as target */
						do {
							target.row = board.getRandomNumber (0, 9);
							target.column = board.getRandomNumber (0, 9);

							/* checks target if it is a miss or hit cell */
							shot = board.checkShot (playerOneGameBoard, target);
						} while (shot == -1);

						/* if it is a Hit, this saves the value of the original target */
						if (shot == 1) targetOrigin = target;
					}

					/**
					 * shot values (1 means craft is hit, 0 means missed and -1 means
					 * it is already a hit or miss cell
					 */
					if (shot == 1) {

						/**
						 * if all cardinals are false and no ship was sunk,
						 * reintializes target from value of original target
						 */
						if (!cardinals[NORTH] && !cardinals[SOUTH] &&
							!cardinals[WEST]  && !cardinals[EAST]  &&
							!hasAShipSunked) { target = targetOrigin; }

						/* hunt mode is false during a target mode */
						huntMode = false;
						targetMode = true;
						targetAI = target;

						/**
						 * get values of adjacent cells and ensuring that
						 * that it is withing the bounds of gameboard for
						 * NORTH, SOUTH, WEST & EAST
						 */
						if (cardinals[NORTH] == true) {  /* NORTH */
							north = (targetAI.row - 1);
							board.checkBoundsOfCardinal (cardinals, north, NORTH);
							targetTemp = target;
							targetTemp.row = north;
							if (board.checkShot (playerOneGameBoard, targetTemp) == -1)
								cardinals[NORTH] = false;
						}

						if (cardinals[SOUTH] == true) {  /* SOUTH */
							south = targetAI.row + 1;
							board.checkBoundsOfCardinal (cardinals, south, SOUTH);
							targetTemp = target;
							targetTemp.row = south;
							if (board.checkShot (playerOneGameBoard, targetTemp) == -1)
								cardinals[SOUTH] = false;
						}

						if (cardinals[WEST] == true) {   /* WEST */
							west  = targetAI.column - 1;
							board.checkBoundsOfCardinal (cardinals, west, WEST);
							targetTemp = target;
							targetTemp.column = west;
							if (board.checkShot (playerOneGameBoard, targetTemp) == -1)
								cardinals[WEST] = false;
						}

						if (cardinals[EAST] == true) {   /* EAST */
							east  = targetAI.column + 1;
							board.checkBoundsOfCardinal (cardinals, east, EAST);
							targetTemp = target;
							targetTemp.column = east;
							if (board.checkShot (playerOneGameBoard, targetTemp) == -1)
								cardinals[EAST] = false;
						}
					}

					/* saves the character of the targeted cell */
					shipSymbol = playerOneGameBoard[target.row][target.column].symbol;
					break;
			}

			/**
			 * Prompts player if it's a hit or miss
			 */
			if (shot == 1) { /* HIT */
				printf ("> %d, %d is a hit!\n", target.row, target.column);

				/* Write to battleship.log */
				fprintf (outStream, "%d, %d is a hit!\n", target.row, target.column);

				/* Keeps track so number of hits for stats */
				players[player].numHits++;

				/* Checks if the ship has sank */
				if (player == 1)
					hasAShipSunked = board.checkSunkShip (sunkShip, !player, shipSymbol, outStream);
				else
					board.checkSunkShip (sunkShip, !player, shipSymbol, outStream);

			} else {        /* MISS */
				printf ("> %d, %d is a miss!\n", target.row, target.column);

				/* Write to battleship.log */
				fprintf (outStream, "%d, %d is a miss!\n", target.row, target.column);
				players[player].numMisses++;
			}
			fflush(stdout);

			if (player == 0) /* If Player 1 then update player 2's gameboard */
				board.updateGameBoard (playerTwoGameBoard, target);
			else             /* If Player 2 then update player 1's gameboard */
				board.updateGameBoard (playerOneGameBoard, target);

			/* Determins if there is a winner based on number of hits */
			if (board.isWinner (players, player)) {
				printf ("\n> Player %d wins!\n", player + 1);

				/* Write to battleship.log */
				fprintf (outStream, "\n>>>>> Player %d wins! <<<<<\n", player + 1);
				break;
			}
			fflush(stdout);
			board.systemMessage ("Hit <ENTER> to continue!\n");
			fflush(stdout);

			/* switches from player 1 to player 2 */
			player = !player;

			system ("cls");
		}

		/**
		 * At the end of the game, Player1's and Player2's statistics should be
		 * written to "battleship.log". The stats include total number of hits,
		 * total number of misses, total number of shots, hits to misses ratio
		 * (as a percentage), and won or lost the game. Note that the statistics
		 * should be placed into a structure called Stats. You need two variables
		 * of type Stats, one for Player1 and one for Player2. Once the game has
		 * ended you should write the contents of each struct variable to the
		 * "battleship.log" file.
		 */
		players[0].totalShots = players[0].numHits + players[0].numMisses;
		players[0].hitMissRatio = ((double) players[0].numHits/(double) players[0].numMisses) * 100;
		players[1].totalShots = players[1].numHits + players[1].numMisses;
		players[1].hitMissRatio = ((double) players[1].numHits/(double) players[1].numMisses) * 100;
		fprintf (outStream, "+===================================================\n");
		fprintf (outStream, "|                    PLAYER STATS                   \n");
		fprintf (outStream, "+---------------------------------------------------\n");
		fprintf (outStream, "| PLAYER 1 : %d hits                                \n", players[0].numHits);
		fprintf (outStream, "|            %d misses                              \n", players[0].numMisses);
		fprintf (outStream, "|            %d total shots                         \n", players[0].totalShots);
		fprintf (outStream, "|            %.2lf%% hit/miss ratio                 \n", players[0].hitMissRatio);
		fprintf (outStream, "| PLAYER 2 : %d hits                                \n", players[1].numHits);
		fprintf (outStream, "|            %d misses                              \n", players[1].numMisses);
		fprintf (outStream, "|            %d total shots                         \n", players[1].totalShots);
		fprintf (outStream, "|            %.2lf%% hit/miss ratio                 \n", players[1].hitMissRatio);
		fprintf (outStream, "+===================================================");

		fclose (outStream);
		return 0;
}
