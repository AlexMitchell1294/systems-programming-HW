/*
 * Production.h
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include <stdlib.h>
#include <stdbool.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include "Board.h"
#include "LinkedList.h"

using namespace std;

#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#define FILENAMELENGTH (50)


class Production {
private:

public:
	Production();
    bool prod(int argc, char* argv[]);
};

#endif
