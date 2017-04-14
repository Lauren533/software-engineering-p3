/*
 * main.c

 *
 * Author: Lauren Duffy
 */


#include <stdio.h>
#include "crossfireOperations.h"

//making board a global variable in order to call upon it in any function without referencing to struct
struct slot **board;

int main(){
    setbuf(stdout,NULL);
    //round is set to zero and will increment each time it enters into while loop
	int boardSize,no_players,user_input,input,round=0;
	//initialising magic to 0 in order to enter into while loop further down code
	int magic=-1;

	//prompting user to enter number of players they wish to enter into the game
	//there must initially be at least two players and no more than 6
	 printf("Please enter the number of players you wish to have (min 2,max 6) \n \n");
	 scanf("%d",&no_players);
	 //if users input does not meet game specifications, they are asked to re-enter number of players
	 if (no_players<2 ||no_players>6)
	 {
		 printf("Incorrect number of players entered, please enter a number of players between 2 and 6");
		 scanf("%d",&no_players);
	 }

	 //Initialise playerstruct of size no_players
	struct Players playerstruct[no_players];

	//Initialises player capabilities.
		 initialize(no_players, playerstruct);
	//board size is set to a constant of a 7 by 7 board
	boardSize=7;


	//Creates the board
	createBoard(boardSize, no_players);
	//giving each slot a randomly assigned slot type i.e. hill,city or level ground
	set_slot_types(board,boardSize);
	//this will randomly assign the players to a slot on the board
	//more than one player can be assigned to a slot
	assign_players_to_slots(boardSize,playerstruct,no_players);

	//rounds will continue until there is only one player left in game
	while (no_players>=2)
		{
	//printing initial board containing slots co-ordinates, types and the players in each
	print_board (boardSize,no_players,board);

		//incrementing rounds
		round++;
		printf("Round %d!",round);
		//give choice of moving or attacking to players currently in game
	    for(int i=0; i<no_players; i++){
	            printf("\n\nWhat would you like to do %s?\n", playerstruct[i].name);
	            printf("Enter 1 to move.\n");
	            printf("Enter 2 to attack.\n");
	            printf("Enter 3 to quit.\n");
	            scanf("%d", &user_input);

	            if(user_input == 1)
	            {
	            	//calling function to move players
	            	moving_players (boardSize,i ,playerstruct,board);

	            }
	            else if(user_input == 2)
	            {
	            	//giving user option for which attack they would like to implement
	                printf("Which attack would you like to implement %s\n",playerstruct[i].name);
	                printf("Enter 1 for near attack\n\n 2 for magic attack\n\n 3 for distance attack.\n\n");
	                scanf("%d",&input);

	                if(input==1)
	                {
	                	//calling the function for the near attack
	                	//implement_near_attack (playerstruct,boardSize,i,no_players);
	                	perform_near_attack(playerstruct,playerstruct[i].row,playerstruct[i].column,boardSize, i,no_players);
	                }

	                else if(input==2)
	                {
	                		//checking if current player has the required conditions in order to perform a magic attack
	                		if(((playerstruct[i].smartness+playerstruct[i].magic_skills)>150))
	                		{
	                			//if conditions are met, user can attack any player on board
	                			while (magic<1 || magic>no_players)
	                			{
	                				printf("Please enter player number you wish to attack\n\n player no: \n\n");
	                				scanf("%d",&magic);
	                			}
	                			magic_attack (playerstruct, i, magic);
	                		}

	                		//otherwise inform user that they do not have the capabilities necessary to perform their chosen attack
	                		else if(((playerstruct[i].smartness+playerstruct[i].magic_skills)<150))
	                		{
	                			printf("Do not have required capabilities for magic attack!\n\n");

	                		}
	                }
	                else if (input==3)
	                {
	                	implement_distant_attack (playerstruct,boardSize,i,no_players);
	                }
	            }
	            else if(input==3)
	            {
	            	//remove players from game
	            }
	            //print new board and capabilities
	            print_board (boardSize,no_players,board);
	            current_player_capabilities(no_players,playerstruct);

	        }
	}
	//when there are less than 2 players left in game, game will end
	if(no_players<2)
	{
		printf("Not enough players left in game, game has ended");
	}
	return 0;
}
