/*
 * Production.h
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_
#include <stdio.h>
#include <stdbool.h>
#include <string.h>//strncpy
#include <stdlib.h>//strtol
#include "Room.h"
#include "AdjMat.h"
#include "LinkedList.h"

#define FILENAMELENGTHALLOWANCE 50

class Production {
public:
	Production();
	virtual ~Production();
	bool prod(int argc, char* argv[]);
	bool readFile(char*, int*, AdjMat*, Room**);
	bool getYesNo(char* query);
	int getMaxRooms();
	float getMaxTreasure();

private:

};

#endif /* PRODUCTION_H_ */
