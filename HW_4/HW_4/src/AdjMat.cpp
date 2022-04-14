///*
// * AdjMat.cpp
// *
// *  Created on: May 30, 2020
// *      Author: Owen Aguirre
// */
/*
 * AdjMat.c
 *
 *  Created on: Oct 24, 2019
 *      Author: Therese
 */

#include "AdjMat.h"
#include <stdio.h>

void AdjMat::init()
{
	int ncols = n;
	printf("In init with ncols = %d\n", ncols);
	//TODO need to malloc for the edges
	for(int row = 0; row<ncols; row++)
	{
		for(int col = 0; col<ncols; col++)
		{
			*((edgesP)+(row*ncols)+col)= 0;
		}
	}
}

void AdjMat::setEdge(int row, int col)
{

	int ncols = n;
	int* arrayBeginning = edgesP;
	*(arrayBeginning + (ncols*row) +col) = 1;
	*(arrayBeginning + (ncols*col) + row) = 1;
}

int AdjMat::getEdge(int row, int col)
{
	return *(edgesP + (n*row) +col);
}

void AdjMat::setN(int set)
{
	n = set;
}

void AdjMat::setEdgesP(int* set)
{
	edgesP = set;
}

