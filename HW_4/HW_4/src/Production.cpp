/*
 * Production.cpp
 *
 *  Created on: Feb 1, 2020
 *      Author: Therese
 */

#include "Production.h"
#include <stdbool.h>
#include "AdjMat.h"
#include "Room.h"
#include "LinkedList.h"

Production::Production() {
	// TODO Auto-generated constructor stub

}

Production::~Production() {
	// TODO Auto-generated destructor stub
}

bool Production::prod(int argc, char* argv[])
{
	printf("Starting Production\n");
	bool answer = false;
	char filename[FILENAMELENGTHALLOWANCE];
	char* eptr=(char*) malloc(sizeof(char*));
	long aL=-1L;
	int maxRooms;
	float maxTreasure;
	double maxTreas;

	if(argc <=2) //no interesting information
	{
		puts("Didn't find any arguments.");
		fflush(stdout);
		maxRooms = getMaxRooms();
		maxTreasure = getMaxTreasure();
		for (int i= 0; i< FILENAMELENGTHALLOWANCE; i++)
			{
				filename[i]=0;
			}

			//this is filename
			printf("The length of the filename is %d.\n",(int)strlen(argv[1]));
			printf("The proposed filename is %s.\n", argv[1]);
			if(strlen(argv[1])>=FILENAMELENGTHALLOWANCE)
			{
				puts("Filename is too long.");
				fflush(stdout);
				answer = false;
			}
			else
			{
				strcpy(filename, argv[1]);
				printf("Filename was %s.\n", filename);
				fflush(stdout);
			}
	}
	else //there is interesting information
	{
		printf("Found %d interesting arguments.\n", argc-1);
		fflush(stdout);

		for(int i = 1; i<argc; i++) //don't want to read argv[0]
				{//argv[i] is a string

					switch(i)
					{
					case 1:
						//this is filename
						printf("The length of the filename is %d.\n",(int)strlen(argv[i]));
						printf("The proposed filename is %s.\n", argv[i]);
						if(strlen(argv[i])>=FILENAMELENGTHALLOWANCE)
						{
							puts("Filename is too long.");
							fflush(stdout);
							answer = false;
						}
						else
						{
							strcpy(filename, argv[i]);
							printf("Filename was %s.\n", filename);
							fflush(stdout);
						}
						break;
					case 2:
						//this is maximum number of rooms

						aL = strtol(argv[i], &eptr, 10);
						maxRooms = (int) aL;
						printf("Number of rooms is %d\n",maxRooms);fflush(stdout);
						break;
					case 3:
						//this is maximum amount of treasure

						maxTreas = atof(argv[i]);
						printf("Amount of  treasure is %f\n",maxTreas);fflush(stdout);
						maxTreasure = (float) maxTreas;
						break;

					default:
						puts("Unexpected argument count."); fflush(stdout);
						answer = false;
						break;
					}//end of switch
				}//end of for loop on argument count
				puts("after reading arguments"); fflush(stdout);
	}

		//we'll want to read the file
		int nrooms = -1;
		AdjMat* adjMP = (AdjMat*) malloc(sizeof(AdjMat));
		Room* theRoomPs[10];//addresses for 10 rooms

		puts("Before read file"); fflush(stdout);
		answer = readFile(filename, &nrooms, adjMP, theRoomPs); //read the file
		puts("Back from read file"); fflush(stdout);

		float totalTreasure = 0;
		int totalRoomsSearched = 0;

		LinkedList* lp = new LinkedList();
		//we'll want to conduct the search
		//for the search we'll need an empty search history
		LLNode2* historyP = lp->makeEmptyLinkedList2();
		//we'll need the Queue, into which we put rooms, and remove rooms
		LLNode* searchQ = lp->makeEmptyLinkedList();
		puts("starting search"); fflush(stdout);
		//we'll start searching with room 0
		bool done = false;
		int searchedRooms = 0;
		float foundTreasure = 0.0;
		Room* roomBeingSearchedP = theRoomPs[0];
		//we set its searched field to true, and take its treasure
		roomBeingSearchedP->searched = true;
		//we record it in the history
		SearchResults* srP = (SearchResults*) malloc(sizeof(SearchResults));
		srP->roomNumber= 0;
		srP->treasure = roomBeingSearchedP->treasure;
		if((srP->treasure <= maxTreas) && (maxRooms>0))
		{
			//we searched room 0, so it should be enqueued onto the history,
			//and not onto the "things-to-do" queue
			lp->savePayload2(historyP, srP);//here we are enqueueing room 0
			puts("Enqueuing room 0");
			foundTreasure = roomBeingSearchedP->treasure;
			searchedRooms = 1;
		}

		while(!done)
		{   //here we want to find all of the rooms adjacent to the roomBeingSearched,
			//so we look in the adj matrix
			for(int col = 0; (col<nrooms)&&!done; col++)
			{
				//we check whether this room is neighboring
				printf("checking rooms %d and %d.\n", roomBeingSearchedP->roomNumber, col); fflush(stdout);
				if(adjMP->getEdge(roomBeingSearchedP->roomNumber, col)==1)
				{
					puts("found an edge"); fflush(stdout);
					//if so, we check whether room has been searched
					if(!(theRoomPs[col]->searched))
					{//if it hasn't been searched
						printf("Room %d hasn't already been searched.\n", col);
						//we set it to searched
						theRoomPs[col]->searched=true;
						if(((foundTreasure + theRoomPs[col]->treasure)<= maxTreasure)&&(searchedRooms < maxRooms))
							//we check whether we can take the treasure vs. limit
							//we check whether we've hit the room limit
						{//we enqueue it for search
							foundTreasure += theRoomPs[col]->treasure;
							searchedRooms++;
							printf("found treasure updated to %f.\n", foundTreasure);
							printf("enqueuing room %d.\n", col); fflush(stdout);
							printf("Before enqueuing queue empty reports %d\n", lp->isEmpty(searchQ));
							lp->savePayload(searchQ, theRoomPs[col]);
							srP = (SearchResults*) malloc(sizeof(SearchResults));
							srP->roomNumber=theRoomPs[col]->roomNumber;
							srP->treasure = theRoomPs[col]->treasure;
							lp->savePayload2(historyP, srP);
							printf("After enqueuing, queue empty reports %d\n", lp->isEmpty(searchQ));
						}//check about search limits
					}//room can still be searched
				}//room is a neighbor

				if(foundTreasure >= maxTreasure)
				{
					done = true;
					puts("Done by treasure");
				}
				if (searchedRooms>=maxRooms)
				{
					done = true;
					puts("Done by rooms");
				}
			}//scan for all possible rooms to search from this room
			//time to get the next room
			if(lp->isEmpty(searchQ))
			{
				done=true;
				puts("Done by queue empty");
			}
			if(!done)
			{
				puts("Invoking  dequeuep");fflush(stdout);
				roomBeingSearchedP = lp->dequeueLIFO(searchQ);

			}
		}//while search is not done
		//search is now done, time to print the history
		lp->printHistory(historyP);



	return answer;
}

bool Production::readFile(char* filename, int* nrooms, AdjMat* adjMP, Room** theRoomPs)
{
	bool ok = false;
	//the file tells how many rooms there are
	FILE* fp = fopen(filename, "r"); //read the file

	if (fp == NULL)
	{
		puts("Error! opening file");

	}
	else
	{
		fscanf(fp,"%d", nrooms);
		int howManyRooms = *nrooms;
		printf("Found %d rooms.\n", howManyRooms);
		adjMP->setN(howManyRooms);

		adjMP->setEdgesP((int*) malloc(howManyRooms * howManyRooms *sizeof(int)));
		puts("Before init Adj Mat"); fflush(stdout);
		adjMP->init();
		puts("After init Adj Mat"); fflush(stdout);
		int temp = -1;
		for(int roomr = 1; roomr<*nrooms; roomr++)
		{
			printf("on row %d\n", roomr);fflush(stdout);
			for(int roomc = 0; roomc<roomr; roomc++)
			{
				fscanf(fp,"%d", &temp);
				printf("in column %d, read %d\n", roomc, temp);fflush(stdout);
				if(temp==1)
				{
					adjMP->setEdge(roomr, roomc);
				}

			}
		}

		float tempTreas = 2.9;
		for(int roomr = 0; roomr<*nrooms; roomr++)
		{
			fscanf(fp,"%f", &tempTreas);
			//make a room and set its treasure
			Room** aRoomP = theRoomPs;
			aRoomP = aRoomP+roomr;
			*aRoomP = (Room*) malloc(sizeof(Room));
			//now set the treasures
			(*aRoomP)->treasure = tempTreas;
			(*aRoomP)->roomNumber = roomr;
			(*aRoomP)->searched = false;
			printf("The treasure in room %d is %f\n", roomr, (*aRoomP)->treasure);
		}
		ok = true;
	}
	fclose(fp);

	return ok;
}

bool Production::getYesNo(char* query)
{
   bool answer = true; //so far
   char said = 'x';
   do
   {
	 printf("%s (y/n):",query);
     fflush(stdout);
     fflush(stdin);
     scanf("%c",&said);
   }while((said!= 'y')&&(said!='n'));
   if(said=='n')
   {
	   answer=false;
   }


   return answer;
}

int Production::getMaxRooms(){
	int ret_val=0;
	puts("Please enter the max amount of rooms");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &ret_val);
	return ret_val;
}

float Production::getMaxTreasure(){
	float ret_val = 0;
	puts("Please enter the max amount of treasure");
	fflush(stdout);
	fflush(stdin);
	scanf("%e", &ret_val);
	fflush(stdout);
	return ret_val;
}

