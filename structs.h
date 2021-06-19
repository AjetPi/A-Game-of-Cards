#ifndef STRUCTS_H
#define STRUCTS_H



struct card_t
{
	char value;   // 1, 2, 3, 4, 5, 6, 7, 8, 9, J (10), Q (12), K (15), A (20);
	char colour; // C (Clubs), D (Diamonds), H (Hearts), S (Spades);
};

struct player_t
{
	int num;
	int used;
	struct card_t* hand;
};

struct game_t
{
	struct card_t* deck;
	struct player_t* players;
};



#endif
