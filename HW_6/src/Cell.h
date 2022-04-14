/*
 * Cell.h
 *
 *  Created on: Oct 9, 2021
 *      Author: darth
 */

#ifndef CELL_H_
#define CELL_H_

class Coordinate{
public:
	int row;
	int column;
};


class Cell{
public:
	char symbol;
	Coordinate position;
};


#endif /* CELL_H_ */
