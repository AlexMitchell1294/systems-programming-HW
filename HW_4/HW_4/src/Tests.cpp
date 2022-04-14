/*
 * Tests.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Tests.h"
#include <stdbool.h>

Tests::Tests() {
	// TODO Auto-generated constructor stub

}

Tests::~Tests() {
	// TODO Auto-generated destructor stub
}

bool Tests::tests()
{
	bool answer = true;

	bool ok1 = testReadFile();
	bool ok2 = testGotAdjacencyMatrix();
	bool ok3 = testMakeLList();
	bool ok4 = testEnqueue();
	//pedagogical bool ok5 = testRemoveFromList();
	bool ok6 = testPrintHistory();
	bool ok5 = testGetMaxRooms();
	bool ok7 = testGetMaxTreasure();
	answer = ok1 && ok2 && ok3 && ok4  && ok6 && ok5 && ok7;
	return answer;
}

bool Tests::testReadFile()
{
	puts("starting testReadFile"); fflush(stdout);
	bool ok = false;
	//the file tells how many rooms there are
	int answer = -1;
	int rightAnswer = 8;


	AdjMat* adjMP = new AdjMat();
	Room* theRoomPs[10];//addresses for 10 rooms

	Production* pP = new Production();
	char filename[] = "houseGraph.txt";

	ok = pP->readFile(filename, &answer, adjMP, theRoomPs); //read the file
	if(ok)
	{
		if(answer!=rightAnswer)
		{
			puts("test failed on number of rooms");
		}

	}
	puts("The adjacency matrix");
	for(int i = 0; i<answer; i++)
	{
		for(int j = 0; j<answer; j++)
		{
			printf("%d",adjMP->getEdge(i, j));

		}
		printf("\n");
	}
	puts("The treasure values");
	for(int i = 0; i<answer; i++)
	{
		printf("%f\n", theRoomPs[i]->treasure);
	}
	if(ok)
	{
		puts("testReadfile did pass");
	}
	else
	{
		puts("testReadfile did not pass.");
	}

	return ok;
}

bool Tests::testEnqueue()
{
	bool ok = false;
	AdjMat* adjMat = (AdjMat*) malloc(sizeof(AdjMat));
	LinkedList* lp = new LinkedList();
	LLNode* Q = lp->makeEmptyLinkedList();
	Room* room;
	room->treasure = 5.5;
	lp->savePayload(Q,room);
	if(lp->dequeueLIFO(Q)->treasure - 5.5 < 0.001)
	{
		puts("testEnqueue did pass");
		ok = true;
	}
	else
	{
		puts("testEnqueue did not pass.");
	}
	return ok;
}
bool Tests::testGotAdjacencyMatrix()
{
	bool ok = false;
	AdjMat* adjMat = (AdjMat*) malloc(sizeof(AdjMat));
	if(adjMat->getEdge(0, 0) == 0)
	{
		puts("testGotAdjacencyMatrix did pass");
	}
	else
	{
		puts("testGotAdjacencyMatrix did not pass.");
	}
	return ok;
}

bool Tests::testMakeLList()
{
	bool ok = false;
	LinkedList* lp = new LinkedList();
	LLNode2* ll = lp->makeEmptyLinkedList2();
	if(lp->isEmpty2(ll))
	{
		puts("testMakeLList did pass");
		ok = true;
	}
	else
	{
		puts("testMakeLList did not pass.");
	}
	return ok;
}
bool Tests::testPrintHistory()
{
	bool ok = false;
	LinkedList* ls = new LinkedList();
	LLNode2* ll = ls->makeEmptyLinkedList2();
	puts("Is linked list empty?");
	ls->printHistory(ll);
	fflush(stdout);
	fflush(stdin);
	char ans = 'n';
	scanf("%c", &ans);
	if(ans=='y')
	{
		puts("testPrintHistory did pass");
		ok = true;
	}
	else
	{
		puts("testPrintHistory did not pass.");
	}
	return ok;
}
bool Tests::testGetMaxRooms(){
	bool ok = false;
	puts("please enter 5");
	fflush(stdout);
	Production* pP = new Production();
	if(pP->getMaxRooms() == 5)
		{
			puts("testGetMaxRooms did pass");
			ok = true;
		}
		else
		{
			puts("testGetMaxRooms did not pass.");
		}
	return ok;
}

bool Tests::testGetMaxTreasure(){
	bool ok = false;
	puts("please enter 32.2");
	fflush(stdout);
	Production* pP = new Production();
	float maxTreasure = pP->getMaxTreasure();
	if(maxTreasure-32.2 < 0.001 && maxTreasure -32.2 > -0.001)
		{
			puts("testGetMaxTreasure did pass");
			ok = true;
		}
		else
		{
			puts("testGetMaxTreasure did not pass.");
		}

	return ok;
}



