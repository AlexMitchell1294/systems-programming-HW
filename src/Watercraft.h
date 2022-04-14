/*
 * Watercraft.h
 *
 *  Created on: Oct 9, 2021
 *      Author: darth
 */

#ifndef WATERCRAFT_H_
#define WATERCRAFT_H_



class WaterCraft{
public:
		char symbol;
		short length;
		char *name;
};

typedef enum {
	CARRIER_L    = 5,
	BATTLESHIP_L = 4,
	CRUISER_L    = 3,
	SUBMARINE_L  = 3,
	DESTROYER_L  = 2
} ShipType;

#endif /* WATERCRAFT_H_ */
