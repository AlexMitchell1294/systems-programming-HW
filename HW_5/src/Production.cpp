#include "Production.h"




Production::Production() {


}


bool Production::prod(int argc, char* argv[])
{
	bool answer = true;
	if(argc <=1) //no interesting information
			{
				puts("Didn't find any arguments.");
				fflush(stdout);
				answer = false;
			}
			else //there is interesting information
			{
				printf("Found %d interesting arguments.\n", argc-1);
				fflush(stdout);
				char filename[FILENAMELENGTH];
				for(int i = 1; i<argc; i++) //don't want to read argv[0]
				{
					switch(i)
					{
					case 1:
						//this is filename
						printf("The length of the filename is %d.\n",(int)strlen(argv[i]));
						printf("The proposed filename is %s.\n", argv[i]);
						if(strlen(argv[i])>=FILENAMELENGTH)
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
							bool player1st = true;
						break;
					}
				}
			}


	std::fstream myfile("C:\\Board.txt", std::ios_base::in);
	int TheBoard[64];
	int temp;
	int cntr = 0;

	while(myfile >> temp)
	{
		TheBoard[cntr] = temp;
		cntr++;
	}

	printf("\n");
	printf("\n");

	for(int row = 0; row < 8; row++){

		for(int col = 0; col < 8; col++){

				printf("%d", TheBoard[row * 8 + col]);
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");


	//Board TheBoard = readFile(filename);
	Board board;
    board.Begin();

    return true;
}
