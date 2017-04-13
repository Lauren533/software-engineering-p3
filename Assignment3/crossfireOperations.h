/*
 * crossfireOperations.h
Author: Lauren Duffy
 */

#ifndef CROSSFIREOPERATIONS_H_
#define CROSSFIREOPERATIONS_H_



#endif /* CROSSFIREOPERATIONS_H_ */




struct slot **board;

/*
 * The slot template
 */
struct slot{
	//row number
	int row;
	//column number
	int column;

	// adjacent left slot
	struct slot *left;
	// adjacent right slot
	struct slot *right;
	// adjacent up slot
	struct slot *up;
	// adjacent down slot
	struct slot *down;
	char *slot_type; //to store the type of slot that the user has been placed in during init_slots
	int number;
	int num_players_in_slot;
	int player_slot[6];


}slot;

struct Players
{
    char name[15];
    char type[10];
    int luck;
    int magic_skills;
    int smartness;
    int dexterity;
    int strength;
    int life_points;
    int slot_index; //to store the slot position that the player is in
    int row,column;

};

//declaring all functions
void createBoard(int boardSize,int no_players);

void print_board (int boardSize, int no_players,struct slot **board);

void initialize(int no_players, struct Players * playerstruct);
void human (struct Players *structname);
void elf (struct Players *structname);
void ogre (struct Players *structname);
void wizard (struct Players *structname);

void assign_players_to_slots(int boardSize,struct Players players[], int no_players);
void moving_players (int boardSize,int current_player,struct Players playerstruct[], struct slot **board);
void can_move_2 (struct slot **board,int boardSize,int current_player, int current_slot,struct Players playerstruct[]);
void can_move_3 (struct slot **board,int boardSize,int current_player, int current_slot,struct Players playerstruct[]);
void can_move_4 (struct slot **board,int boardSize,int current_player, int current_slot,struct Players playerstruct[]);
void changing_caps(struct Players * pplayer, struct slot ** board, int current_player);
void set_slot_types(struct slot **board, int boardSize);
void current_player_capabilities(int no_players, struct Players * playerstruct);
void near_attack (struct Players players[], int attacker, int defender);
void distant_attack (struct Players players[], int attacker, int defender);
void magic_attack (struct Players playerstruct[], int attacker, int defender);
void implement_near_attack (struct Players playerstruct[],int boardSize,int current_player,int no_players);
void implement_distant_attack (struct Players playerstruct[],int boardSize,int current_player, int no_players);
void perform_near_attack(struct Players playerstruct[],int current_row,int current_column, int boardSize, int current_player,int no_players);

