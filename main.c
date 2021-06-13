#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define HAND_SIZE 13
//#define DECK_SIZE 52
//#define PLAYERS_SIZE 4


struct card_t
{
	char value;  //1, 2, 3, 4, 5, 6, 7, 8, 9, J (10), Q (12), K (15), A (20);
	char colour; //C (Clubs), D (Diamonds), H (Hearts), S (Spades);
};

struct player_t
{
	int size;
	struct card_t* hand;
};

struct game_t
{
	struct card_t* deck;
	struct player_t* players;
};


void write_deck(FILE* file, struct card_t* deck)
{
	char current;
	for(int i = 0; i < 52 && !feof(file); i++)
	{
		if((current = fgetc(file)) == ' ')
		{
			current = fgetc(file);
		}
		deck[i].value = current;
		
		if((current = fgetc(file)) == ' ')
		{
			current = fgetc(file);
		}
		deck[i].colour = current;
	}
}

void print_cards(struct card_t* cards, int size)
{
	for(int i = 0; i < size; i++)
	{
		printf("(%c, %c)\n", cards[i].value, cards[i].colour);
	}
}

void draw_card(struct card_t* deck, int i, struct player_t* player)
{
	player->hand[player->size] = deck[i];
	player->size++;
}

int check_hand(struct player_t* player)
{
	int count;
	for(int i = 0; i < player->size; i++)
	{
		count = 1;
		for(int j = i + 1; j < player->size; j++)
		{
			if(player->hand[i].value == player->hand[j].value)
			{
				count++;
			}
		}
		
		if(count == 4)
		{
			return 1;
		}
	}
	
	return 0;
}


struct game_t* init_game()
{
	struct game_t* game = malloc(sizeof(struct game_t));
	
	game->deck = malloc(sizeof(struct card_t) * 52);
	FILE* file = fopen("deck_1.txt", "r");
	write_deck(file, game->deck);
	//print_cards(game->deck, 52);
	fclose(file);
	
	game->players = malloc(sizeof(struct player_t) * 4);
	for(int i = 0; i < 4; i++)
	{
		game->players[i].size = 0;
		game->players[i].hand = malloc(sizeof(struct card_t) * 13);
	}
	
	return game;
}

void play_game(struct game_t* game)
{
	static int i = 0;
	for(int j = 0; j < 4; j++)
	{
		draw_card(game->deck, i++, &(game->players[j]));
		if(check_hand(&(game->players[j])))
		{
			printf("PLAYER %d WON:\n", j + 1);
			print_cards(game->players[j].hand, game->players[j].size);
			return;
		}
	}
	
	if(i >= 52)
	{
		printf("NOBODY WON");
		return;
	}
	
	play_game(game);
}

int main()
{
	struct game_t* game = init_game();
	play_game(game);
	return 0;
}