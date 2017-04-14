//Author: Lauren Duffy

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SLOT_NUMBER 20
#define MAX_SLOT_NAME 15
#define MAX_NAME_SIZE 15
#define MAX_PLAYER_ROLE_SIZE 10
#define MAX_CAPABILITIES 100
#include "crossfireOperations.h"




void createBoard(int boardSize, int no_players){

	//allocating memory, board previously made global variable
	board = malloc(boardSize * sizeof(struct slot *));



	for(int i =0; i< boardSize; i++){
		//allocating space for each of the slots
		board[i] = malloc(boardSize * sizeof(struct slot));

		//setting up a row and column number for each slot
		for(int j=0;j < boardSize; j++){
			board[i][j].row = i;
			board[i][j].column = j;
			board[i][j].num_players_in_slot=0;
			for(int c=0; c<no_players; c++){
				board[i][j].player_slot[c]=-1;
			}
		}
	}

	//for slots that are not at edge of the board there will be 4 adjacent slots for each
	//i.e. up, down, left and right
	for(int i =1; i< boardSize-1; i++){
		for(int j=1;j < boardSize-1; j++){
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].down = &board[i+1][j];
			board[i][j].left = &board[i][j-1];
		}
	}

	//for slots in first and last row
	//excluding slots in corners as they will only have two adjacent slots
	for(int j = 1; j < boardSize -1; j++){
		//in the first row there will be no row above them
		//i.e. no adjacent slot above
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];

		//slots in last row will have no row below
		board[boardSize - 1][j].right = &board[boardSize - 1][j+1];
		board[boardSize -1][j].left = &board[boardSize - 1][j-1];
		board[boardSize - 1][j].up = &board[boardSize - 2][j];
	}

	//for slots in first and last column
	//excluding corner slots as these will only have 2 adjacent slot options
	for(int i = 1; i < boardSize -1; i++){

		//for slots in first column there will be no slots to the left
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i-1][0];
		board[i][0].down = &board[i+1][0];

		//for slots in last column there wil be no slots to the right
		board[i][boardSize-1].left = &board[i][boardSize-2];
		board[i][boardSize -1].up = &board[i -1][boardSize-1];
		board[i][boardSize -1].down = &board[i+1][boardSize -1];
	}


	//for slot in corner position (0,0), only 2 adjacent slots options
	board[0][0].right = &board[0][1];
	board[0][0].down = &board[1][0];

	//for the slot in corner position (0,boardSize -1).
	board[0][boardSize-1].left = &board[0][boardSize-2];
	board[0][boardSize -1].down = &board[1][boardSize -1];

	//for slot at position (boardSize -1 ,0).
	//This only has only 2 adjacent slots: up and right
	board[boardSize -1][0].right = &board[boardSize -1][1];
	board[boardSize -1][0].up = &board[boardSize -2][0];

	//for slot at position (boarSize -1 ,boardSize-1).
	board[boardSize - 1][boardSize-1].up = &board[boardSize-2][boardSize-1];
	board[boardSize - 1][boardSize -1].left = &board[boardSize -1][boardSize -2];



	}


void print_board (int boardSize, int no_players,struct slot **board)
{
	int i,j,c;
	int counter=0;
	int count_players[6];

	for(i=0;i<boardSize;i++)
	{
		for(j=0;j<boardSize;j++)
		{

			for(c=0; c<no_players;c++)
			{
				if(board[i][j].player_slot[c] != -1)
				{
					count_players[counter]=board[i][j].player_slot[c];
					counter++;
				}

			}
			//different formats to print code depending on how many players are in the slot

			if(counter==0)
			{
				printf("(%s,( %d,%d))\t",board[i][j].slot_type,board[i][j].row,board[i][j].column);
			}
			else if(counter==1)
			{
				printf("(%s ,(%d,%d)->player %d)\t",board[i][j].slot_type, board[i][j].row,board[i][j].column,count_players[0]);
			}
			else if(counter==2)
			{
				printf("(%s,( %d,%d)->player %d,player %d)\t",board[i][j].slot_type,board[i][j].row,board[i][j].column,count_players[0],count_players[1]);
			}
			else if(counter==3)
			{
				printf("(%s,(%d,%d)->player %d,player %d, player %d,player %d)\t",board[i][j].slot_type,board[i][j].row,board[i][j].column,count_players[0],count_players[1],count_players[2],count_players[3]);
			}
			else if(counter==4)
			{
				printf("(%s,(%d,%d)->player %d,player %d, player %d,player %d, player %d)\t",board[i][j].slot_type,board[i][j].row,board[i][j].column,count_players[0],count_players[1],count_players[2],count_players[3],count_players[4]);
			}
			else if(counter==5)
			{
				printf("(%s,(%d,%d)->player %d,player %d, player %d,player %d, player %d,player %d)\t",board[i][j].slot_type,board[i][j].row,board[i][j].column,count_players[0],count_players[1],count_players[2],count_players[3],count_players[4],count_players[5]);
			}
			//setting counter back to zero in order to count players in next slot
			counter=0;
		}
		printf("\n\n");
	}
}

void initialize(int no_players, struct Players * playerstruct)
{
    //This function allows users to pick a player 'type' and name for the number of players they have entered
    //Within this function, we call 4 other functoins, one for each seperate character type in order to assign capabilities
    int type;
    int i;

    printf("To pick your player type, please use these corresponding numbers: \n"
        "Elf=1 \n"
        "Human=2 \n"
        "Ogre=3 \n"
        "Wizard=4 \n \n");

    //taking in users choice of character type
    for (i=0;i<no_players;i++)
    {
        printf(" \n Please enter corresponding number of player type: \n ");
        scanf("%d",&type);

            if (type==1)
            {
                strcpy(playerstruct[i].type,"Elf");
            }
            else if(type==2)
            {
                strcpy(playerstruct[i].type,"Human");
            }
            else if(type==3)
            {
                strcpy(playerstruct[i].type,"Ogre");
            }
            else if (type == 4)
            {
                strcpy(playerstruct[i].type,"Wizard");
            }

        printf("\n Please enter player name: \n");
        scanf("%s", playerstruct[i].name);
    }

     //calling in the 4 functions depending on user choice
    for (i=0;i<no_players;i++)
    {
        if (strcmp(playerstruct[i].type,"Elf")==0)
        {
            elf(&playerstruct[i]);
        }
        else if(strcmp(playerstruct[i].type,"Human")==0)
        {
            human(&playerstruct[i]);
        }
        else if(strcmp(playerstruct[i].type,"Ogre")==0)
        {
            ogre(&playerstruct[i]);
        }
        else if (strcmp(playerstruct[i].type,"Wizard")==0)
        {
            wizard(&playerstruct[i]);
        }
    }
     //printing user capabilities
    for(i=0; i<no_players; i++)
    {
        printf("Name of player %d is %s.\n", i+1, playerstruct[i].name);
        printf("Smartness: %d.\n", playerstruct[i].smartness);
        printf("Dexterity: %d.\n", playerstruct[i].dexterity);
        printf("Strength: %d.\n", playerstruct[i].strength);
        printf("Magic Skills: %d.\n", playerstruct[i].magic_skills);
        printf("Luck: %d.\n\n", playerstruct[i].luck);
        printf("Lifepoints: %d.\n\n", playerstruct[i].life_points);
    }
}

void human (struct Players *structname)
{
    int sum=301;
    //as the sum of all capabilities must be less than 300
   while (sum > 300)
    {
        int j=rand() %100 +1;
        (*structname).smartness= j;
        (*structname).luck=  rand() %100 +1;
        (*structname).dexterity=  rand() %100 +1;
        (*structname).strength=  rand() %100 +1;
        (*structname).magic_skills= rand() %100 +1;
        sum=0;
        sum=((*structname).luck+(*structname).dexterity+(*structname).smartness+(*structname).magic_skills+(*structname).strength);
    }
    (*structname).life_points=100;
}

void elf (struct Players *structname)
{
        (*structname).smartness= rand() %32 +69;
        (*structname).luck=  rand() %42 +59;
        (*structname).dexterity=  rand() %100 +1;
        (*structname).strength=  rand() %50 +1;
        (*structname).magic_skills= rand() %30 +50;

        (*structname).life_points=100;
}

void wizard (struct Players *structname)
{
        (*structname).smartness= rand() %12 +89;
        (*structname).luck=  rand() %52 + 49;
        (*structname).dexterity=  rand() %100 +1;
        (*structname).strength=  rand() %20 +1;
        (*structname).magic_skills= rand() %22+79;

        (*structname).life_points=100;
}

void ogre (struct Players *structname)
{
    int o_sum=51;
   //as sum of smartness and luck must be less than 50
    while (o_sum >=50)
    {
        (*structname).smartness= rand() %20+1;
        (*structname).luck=  rand() %49 + 1;
        o_sum=(*structname).luck + (*structname).smartness;
    }

        (*structname).dexterity=  rand() %22 +79;
        (*structname).strength=  rand() %22 +79;
        (*structname).magic_skills= 0;

        (*structname).life_points=100;
}

void assign_players_to_slots(int boardSize,struct Players playerstruct[], int no_players)
{
	int i=0,row,column;

	srand (time(NULL));

	while(i<no_players)
	{
		//to get a random row and column
		row=rand()%boardSize;
		column=rand()%boardSize;

		//formula to get a random slot for which to place players in
		board[row][column].player_slot[i]=i+1;
		board[row][column].num_players_in_slot+=1;
		playerstruct[i].row = row;
		playerstruct[i].column = column;
		i++;
	}

	for (i=0;i<no_players;i++)
	{
		//printing which slot each player is in
		printf("Player %d is in slot (%d,%d)\n",i+1,playerstruct[i].row,playerstruct[i].column);
	}
}

void moving_players (int boardSize,int current_player,struct Players playerstruct[], struct slot **board)
{
	//this will set the current slot that the player is to be a specific type in terms of how many directions the user is able to move in
	//there will always be at least 2 directions a player can move in, and this occurs when they are in a slot in one of the four corners of the board
	//otherwise there are 3/4 options depending on where the player currently is on the board
	int current_slot;

	if((playerstruct[current_player].row==0)&&(playerstruct[current_player].column==0))
	{
		printf("Player is in position (0,0),can only move down or right!");
		current_slot=1;
		//call two directions function
		can_move_2(board,boardSize,current_player,current_slot,playerstruct);
	}
	else if((playerstruct[current_player].row==boardSize-1)&&(playerstruct[current_player].column==0))
	{
		printf("Player is in position (6,0),can only move up or right!");
		current_slot=2;
		//call two directions function
		can_move_2(board,boardSize,current_player,current_slot,playerstruct);
	}
	else if((playerstruct[current_player].row==0)&&(playerstruct[current_player].column==boardSize-1))
	{
		printf("Player is in position (0,6), can only move down or left!");
		current_slot=3;
		//call two directions function
		can_move_2(board,boardSize,current_player,current_slot,playerstruct);
	}
	else if((playerstruct[current_player].row==boardSize-1)&&(playerstruct[current_player].column==boardSize-1))
	{
		printf("Player is in position (6,6),can only move up or left!");
		current_slot=4;
		//call two directions function
		can_move_2(board,boardSize,current_player,current_slot,playerstruct);
	}
	else if((playerstruct[current_player].row==boardSize-1))
	{
		printf("Player is in last row, can move left, right or up!");
		current_slot=5;
		//call three directions function
		can_move_3 (board,boardSize,current_player,current_slot, playerstruct);
	}
	else if((playerstruct[current_player].row==0))
	{
		printf("Player is in first row, can move left right or down!");
		current_slot=6;
		//call three directions function
		can_move_3 (board,boardSize,current_player,current_slot, playerstruct);
	}
	else if(playerstruct[current_player].column==boardSize-1)
	{
		printf("Player is in last column, can move up down or left!");
		current_slot=7;
		//call three direction function
		can_move_3 (board,boardSize,current_player,current_slot, playerstruct);
	}
	else if(playerstruct[current_player].column==0)
	{
		printf("Player is in first column, can move up down or left!");
		current_slot=8;
		//call three direction function
		can_move_3 (board,boardSize,current_player,current_slot, playerstruct);
	}
	else
	{
		printf("You can move in any direction!");
		current_slot=9;
		//call four direction function
		can_move_4 (board,boardSize,current_player, current_slot,playerstruct);
	}
}

void can_move_2 (struct slot **board,int boardSize,int current_player, int current_slot,struct Players playerstruct[])
{
	//this function will give the user options to choose from in terms of moving depending on which of the four corners they are in
	int direction,row,column;

	if(current_slot==1)
	{
		printf("\n\n1-right,\n\n3-down\n\n");
		scanf("%d",&direction);
	}
	else if(current_slot==2)
	{
		printf("\n\n1-right,\n\n4-up\n\n");
		scanf("%d",&direction);
	}
	else if(current_slot==3)
	{
		printf("\n\n2-left,\n\n3-down\n\n");
		scanf("%d",&direction);
	}
	else if(current_slot==4)
	{
		printf("\n\n2-left\n\n4-up");
	}

	column=playerstruct[current_player].column;
	row=playerstruct[current_player].row;
	//actually moving the players
	if(direction==1)
	{
		board[row][column].right->num_players_in_slot+=1;
		board[row][column].player_slot[current_player]=-1;
		board[row][column].right->player_slot[current_player]=current_player+1;
		board[row][column].num_players_in_slot-=1;


		playerstruct[current_player].column=playerstruct[current_player].column+1;
		//calling the function to change capabilities depending on which type of slot they move to
		changing_caps(playerstruct, board, current_player);

	}
	else if(direction==2)
	{
		board[row][column].left->num_players_in_slot+=1;
		board[row][column].player_slot[current_player]=-1;
		board[row][column].left->player_slot[current_player]=current_player+1;
		board[row][column].num_players_in_slot-=1;
		playerstruct[current_player].column=playerstruct[current_player].column-1;
		changing_caps(playerstruct, board, current_player);
	}
	else if (direction ==3)
	{
		board[row][column].down->num_players_in_slot+=1;
		board[row][column].player_slot[current_player]=-1;
		board[row][column].down->player_slot[current_player]=current_player+1;
		board[row][column].num_players_in_slot-=1;
		playerstruct[current_player].column=playerstruct[current_player].row+1;
		changing_caps(playerstruct, board, current_player);
	}
	else if (direction ==4)
	{
		board[row][column].up->num_players_in_slot+=1;
		board[row][column].player_slot[current_player]=-1;
		board[row][column].up->player_slot[current_player]=current_player+1;
		board[row][column].num_players_in_slot-=1;
		playerstruct[current_player].column=playerstruct[current_player].row-1;
		changing_caps(playerstruct, board, current_player);
	}

}

void can_move_3 (struct slot **board,int boardSize,int current_player, int current_slot,struct Players playerstruct[])
{
	//this function is used when players are not in the corner slots, but are on the first or last column or row of the board
	//this means they will each only have 3 directions that they can move in
	int direction,row,column;

	if(current_slot==5)
	{
		printf("\n\n1-right,\n\n2-left\n\n4-up\n\n");
		scanf("%d",&direction);
	}
	else if(current_slot==6)
	{
		printf("\n\n1-right,\n\n2-left\n\n3-down");
		scanf("%d",&direction);
	}
	else if(current_slot==7)
	{
		printf("\n\n2-left,\n\n3-down\n\n4-up\n\n");
		scanf("%d",&direction);
	}
	else if(current_slot==8)
	{
		printf("\n\n2-left\n\n3-down\n\n4-up");
	}

	column=playerstruct[current_player].column;
	row=playerstruct[current_player].row;

	//actually moving the players
	if(direction==1)
	{
		board[row][column].right->num_players_in_slot+=1;
		board[row][column].player_slot[current_player]=-1;
		board[row][column].right->player_slot[current_player]=current_player+1;
		board[row][column].num_players_in_slot-=1;


		playerstruct[current_player].column=playerstruct[current_player].column+1;
		//calling function to change the capabilities depending on which slot type the player has moved to
		changing_caps(playerstruct, board, current_player);

	}
	else if(direction==2)
	{
		board[row][column].left->num_players_in_slot+=1;
		board[row][column].player_slot[current_player]=-1;
		board[row][column].left->player_slot[current_player]=current_player+1;
		board[row][column].num_players_in_slot-=1;
		playerstruct[current_player].column=playerstruct[current_player].column-1;
		changing_caps(playerstruct, board, current_player);
	}
	else if (direction ==3)
	{
		board[row][column].down->num_players_in_slot+=1;
		board[row][column].player_slot[current_player]=-1;
		board[row][column].down->player_slot[current_player]=current_player+1;
		board[row][column].num_players_in_slot-=1;
		playerstruct[current_player].column=playerstruct[current_player].row+1;
		changing_caps(playerstruct, board, current_player);
	}
	else if (direction ==4)
	{
		board[row][column].up->num_players_in_slot+=1;
		board[row][column].player_slot[current_player]=-1;
		board[row][column].up->player_slot[current_player]=current_player+1;
		board[row][column].num_players_in_slot-=1;
		playerstruct[current_player].column=playerstruct[current_player].row-1;
		changing_caps(playerstruct, board, current_player);
	}

}

void can_move_4 (struct slot **board,int boardSize,int current_player, int current_slot,struct Players playerstruct[])
{
	//this function is called when the user is in a slot somewhere in the middle of the board
	//this means they can move to any of the adjacent slots
	int direction,row,column;

	printf("\n\n1-right,\n\n2-left,\n\n3-down,\n\n4-up\n\n");
	scanf("%d",&direction);
	column=playerstruct[current_player].column;
	row=playerstruct[current_player].row;

	//actually moving the players
	if(direction==1)
		{
			board[row][column].right->num_players_in_slot+=1;
			board[row][column].player_slot[current_player]=-1;
			board[row][column].right->player_slot[current_player]=current_player+1;
			board[row][column].num_players_in_slot-=1;



			playerstruct[current_player].column=playerstruct[current_player].column+1;
			//changing capability of current player depending on the slot type they have moved to
			changing_caps(playerstruct, board, current_player);
		}
		else if(direction==2)
		{
			board[row][column].left->num_players_in_slot+=1;
			board[row][column].player_slot[current_player]=-1;
			board[row][column].left->player_slot[current_player]=current_player+1;
			board[row][column].num_players_in_slot-=1;
			playerstruct[current_player].column=playerstruct[current_player].column-1;
			changing_caps(playerstruct, board, current_player);
		}
		else if (direction ==3)
		{
			board[row][column].down->num_players_in_slot+=1;
			board[row][column].player_slot[current_player]=-1;
			board[row][column].down->player_slot[current_player]=current_player+1;
			board[row][column].num_players_in_slot-=1;
			playerstruct[current_player].column=playerstruct[current_player].row+1;
			changing_caps(playerstruct, board, current_player);
		}
		else if (direction ==4)
		{
			board[row][column].up->num_players_in_slot+=1;
			board[row][column].player_slot[current_player]=-1;
			board[row][column].up->player_slot[current_player]=current_player+1;
			board[row][column].num_players_in_slot-=1;
			playerstruct[current_player].column=playerstruct[current_player].row-1;
			changing_caps(playerstruct, board, current_player);
		}



}

void set_slot_types(struct slot **board, int boardSize)
{
    int i = 0;
    int j=0;
    int slotslot_type;

    //iterating throughout board
    for (i = 0; i < boardSize; i++)
    {
    	for(j=0;j<boardSize;j++)
    	{
    		//randomly assigning one of three numbers to each of the slots
			slotslot_type = rand() % 3;
			board[i][j].number = i + 1;

			//depending on the number each slot has been assigned, they will be allocated a slot type
			if (slotslot_type == 0)
			{
				board[i][j].slot_type = "Hill";
			}
			else if (slotslot_type == 1)
			{
				board[i][j].slot_type = "City";
			}
			else if (slotslot_type == 2)
			{
				board[i][j].slot_type = "Level Ground";
			}

    	}
    }
}
void changing_caps(struct Players * pplayer, struct slot ** board, int current_player)
{

	int row = pplayer[current_player].row;
	int column = pplayer[current_player].column;
//function changes the capabilities of the players depending on which slot they
//move to, if they choose to move at all.
    if (strcmp (board[row][column].slot_type, "Hill") == 0)
    {
        if (pplayer->dexterity < 50)
        {
            pplayer->strength -= 10;
        }
        else if (pplayer->dexterity >= 60)
        {
            pplayer->strength += 10;
        }
    }
    else if (strcmp(board[row][column].slot_type, "City") == 0)
    {
        if (pplayer->smartness > 60)
        {
            pplayer->magic_skills += 10;
        }
        else if (pplayer->smartness <= 50)
        {
            pplayer->magic_skills -= 10;
        }
    }
}
void current_player_capabilities(int no_players, struct Players * playerstruct)
{
	//function to print out the name,capabilities and lifepoints of players
    int i;

    for(i=0; i<no_players; i++)
    {
    	printf("Name: %s.\n", playerstruct[i].name);
           printf("Smartness: %d.\n", playerstruct[i].smartness);
           printf("Dexterity: %d.\n", playerstruct[i].dexterity);
           printf("Strength: %d.\n", playerstruct[i].strength);
           printf("Magic Skills: %d.\n", playerstruct[i].magic_skills);
           printf("Luck: %d.\n\n", playerstruct[i].luck);
           printf("Lifepoints: %d.\n\n", playerstruct[i].life_points);
    }
}
void perform_near_attack(struct Players playerstruct[],int current_row,int current_column, int boardSize, int current_player,int no_players)
{
	int i,j;
	int player_slot_array[6];
	//to indicate if a player is found within acceptable range
	int found_near=0;
	int attack;

	for(i=0;i<no_players;i++)
	{
		//we will initially set the array to contain no players
		player_slot_array[i]=-1;
	}

	for(i=0;i<no_players;i++)
	{
		if(i!=current_player)
		{
			//firstly we will check if the slot that current player is on contains any more players in the same slot
			if((playerstruct[i].column==current_column)&&(playerstruct[i].row==current_row))
			{
				//if there is more than just current player in slot, i.e. more than 1
				if(board[current_column][current_row].num_players_in_slot>1)
				{
					//i+1 will be player number, put this in array which user then can use to select who to attack
					player_slot_array[i]=i+1;
				}
			}
			//check slot to the left
			else if((playerstruct[i].column==current_column-1)&&(playerstruct[i].row==current_row))
			{
				//this time check if any players at all in slot
				if(board[current_column][current_row].num_players_in_slot>0)
				{
					//put player number into array
					player_slot_array[i]=i+1;
				}
			}
			//check slot to the right
			else if((playerstruct[i].column==current_column+1)&&(playerstruct[i].row==current_row))
			{
				//this time check if any players at all in slot
				if(board[current_column][current_row].num_players_in_slot>0)
				{
					//put player number into array
					player_slot_array[i]=i+1;
				}
			}
			//check slot below
			else if((playerstruct[i].column==current_column)&&(playerstruct[i].row==current_row-1))
			{
				//this time check if any players at all in slot
				if(board[current_column][current_row].num_players_in_slot>0)
				{
					//put player number into array
					player_slot_array[i]=i+1;
				}
			}
			//check slot above
			else if((playerstruct[i].column==current_column)&&(playerstruct[i].row==current_row+1))
			{
				//this time check if any players at all in slot
				if(board[current_column][current_row].num_players_in_slot>0)
				{
					//put player number into array
					player_slot_array[i]=i+1;
				}
			}
		}
	}

	for(j=0;j<no_players;j++)
	{
		if(player_slot_array[j]>=1)
		{
			//set found near to 1 to indicate that user is able to perform near attack
			found_near=1;
		}
	}

	//if the user is able to perform attack
	if(found_near==1)
	{
		for(int k=0;k<no_players;k++)
		{
			printf("Please enter %d to attack player %d\n\n",player_slot_array[i],player_slot_array[i]);
		}
	}
	scanf("%d",&attack);
	//calling to change capabilities based on which player they decide to attack
				if(attack==1)
				{
					near_attack(playerstruct,current_player,attack);
				}
				else if(attack==2)
				{
					near_attack(playerstruct,current_player,attack);
				}
				else if(attack==3)
				{
					near_attack(playerstruct,current_player,attack);
				}
				else if(attack==4)
				{
					near_attack(playerstruct,current_player,attack);
				}
				else if(attack==5)
				{
					near_attack(playerstruct,current_player,attack);
				}
				else if(attack==6)
				{
					near_attack(playerstruct,current_player,attack);
				}


}
/*void implement_near_attack (struct Players playerstruct[],int boardSize,int current_player, int no_players)
{
	int i, j,  row, column;
	int attack;

	row = playerstruct[current_player].row;
	column = playerstruct[current_player].column;

	for(i=0; i<5; i++)
	{

		if(i==0)
		{
			if(board[row][column].up->num_players_in_slot > 0)
			{
				for(j=0; j<no_players; j++)
				{
					if(board[row][column].up->player_slot[j] != -1)
					{
						printf("Enter %d to Attack Player %d", board[row][column].up->player_slot[j], board[row][column].up->player_slot[j]);
						//near_attack (playerstruct, current_player, board[row][column].up->player_slot[j]);
					}
				}
			}
			else if(i==1)
			{

				if(board[row][column].down->num_players_in_slot > 0)
				{
					for(j=0; j<no_players; j++)
					{
						if(board[row][column].down->player_slot[j] != -1)
						{
							printf("Enter %d to Attack Player %d", board[row][column].down->player_slot[j], board[row][column].down->player_slot[j]);
							near_attack (playerstruct, current_player, board[row][column].up->player_slot[j]);
						}
					}
				}
			}
			else if(i==2)
			{
				if(board[row][column].left->num_players_in_slot > 0)
				{
					for(j=0; j<no_players; j++)
					{
						if(board[row][column].left->player_slot[j] != -1)
						{
							printf("Enter %d to Attack Player %d", board[row][column].left->player_slot[j], board[row][column].left->player_slot[j]);
						}
					}
				}
			}
			else if(i==3)
			{
				if(board[row][column].right->num_players_in_slot > 0)
				{
					for(j=0; j<no_players; j++)
					{
						if(board[row][column].right->player_slot[j] != -1)
						{
							printf("Enter %d to Attack Player %d", board[row][column].right->player_slot[j], board[row][column].right->player_slot[j]);
							//near_attack (playerstruct, current_player, board[row][column].up->player_slot[j]);
						}
					}
				}
			}
			else if(i==4)
			{
				if(board[row][column].num_players_in_slot > 1)
					{
						for(j=0; j<no_players; j++)
							{
								if(board[row][column].player_slot[j] != -1 && board[row][column].player_slot[j] != current_player)
									{
										printf("Enter %d to Attack Player %d", board[row][column].right->player_slot[j], board[row][column].right->player_slot[j]);
										//near_attack (playerstruct, current_player, board[row][column].up->player_slot[j]);
									}
							}
					}
			}


		}

	}

	scanf("%d",&attack);

			if(attack==1)
			{
				near_attack(playerstruct,current_player,attack);
			}
			else if(attack==2)
			{
				near_attack(playerstruct,current_player,attack);
			}
			else if(attack==3)
			{
				near_attack(playerstruct,current_player,attack);
			}
			else if(attack==4)
			{
				near_attack(playerstruct,current_player,attack);
			}
			else if(attack==5)
			{
				near_attack(playerstruct,current_player,attack);
			}
			else if(attack==6)
			{
				near_attack(playerstruct,current_player,attack);
			}


}
/*/
void implement_distant_attack (struct Players playerstruct[],int boardSize,int attacker, int no_players)
{
	int i,row,column;
	//to hold the distance the player is from current player
	int distance;
	//to hold the players that meet the conditions
	int available_to_attack[6];
	int attack;
	int found_near=0;

	row = playerstruct[attacker].row;
	column = playerstruct[attacker].column;



	for(i=0;i<no_players;i++)
	{
		if(board[row][column].player_slot[i] != attacker)
		{
			distance=abs(playerstruct[i].row)+abs(playerstruct[i].column);
			if (distance>1 && distance<5)
			{
				available_to_attack[i]=i+1;
			}
		}

	}
for(int j=0;j<no_players;j++)
	{
		if(available_to_attack[j]>=1)
		{
			//set found near to 1 to indicate that user is able to perform near attack
			found_near=1;
		}
	}

	//if the user is able to perform attack
	if(found_near==1)
	{
		for(int k=0;k<no_players;k++)
		{
			printf("Please enter %d to attack player %d\n\n",available_to_attack[i],available_to_attack[i]);
		}
	}
	scanf("%d",&attack);
	//calling to change capabilities based on which player they decide to attack
				if(attack==1)
				{
					distant_attack ( playerstruct, attacker,attack);
				}
				else if(attack==2)
				{
					distant_attack ( playerstruct, attacker,attack);
				}
				else if(attack==3)
				{
					distant_attack ( playerstruct, attacker,attack);
				}
				else if(attack==4)
				{
					distant_attack ( playerstruct, attacker,attack);
				}
				else if(attack==5)
				{
					distant_attack ( playerstruct, attacker,attack);
				}
				else if(attack==6)
				{
					distant_attack ( playerstruct, attacker,attack);
				}





}

void near_attack (struct Players playerstruct[], int attacker, int defender)
{
	defender-=1;
	 if (playerstruct[defender].strength <= 70)
    {//if the player being attacked has less than 71 strength points they lose life points equivalent to 1/2 their strength points.
        playerstruct[defender].life_points -= playerstruct[defender].strength/2;
    }
    else
    {//if the player being attacked has more than 70 strength points the attacking player loses 30% of their strength in life points.
        playerstruct[attacker].life_points -= 0.3 * playerstruct[defender].strength;
    }
}

void distant_attack (struct Players players[], int attacker, int defender)
{

	if (players[defender].dexterity < players[attacker].dexterity)
    {

        players[defender].life_points -= 0.3 * players[attacker].strength;
    }
}

void magic_attack (struct Players playerstruct[], int attacker, int defender)
{
	playerstruct[defender].life_points -= ((0.5 * playerstruct[attacker].magic_skills)+(0.2* playerstruct[attacker].smartness));
}
