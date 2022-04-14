/*
 * AdjMat.h
 *
 */

#ifndef ADJMAT_H_
#define ADJMAT_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>//strncpy
#include <stdlib.h>//strtol

class AdjMat{
public:

	void setEdge(int row, int col);
	int getEdge(int row, int col); //Returns binary value on adjMatrix given a row and a col
	void init();
	void setN(int set);
	void setEdgesP(int* set);
private:
	int n;
	int* edgesP;
};



#endif /* ADJMAT_H_ */
