#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "funcs.h"

// #define HAND_SIZE 13
// #define DECK_SIZE 52
// #define PLAYERS_SIZE 4



struct game_t* init_game(FILE* file) // Initiates the game.
{
	struct game_t* game = malloc(sizeof(struct game_t));
	
	game->deck = malloc(sizeof(struct card_t) * 52);
	write_deck(file, game->deck);
	// print_cards(game->deck, 52);
	
	game->players = malloc(sizeof(struct player_t) * 4);
	for(int i = 0; i < 4; i++)
	{
		game->players[i].num = i + 1;
		game->players[i].used = 0;
		game->players[i].hand = malloc(sizeof(struct card_t) * 13);
	}
	
	return game;
}

void play_game(struct game_t* game) // Automatically progresses, i.e. plays, the game.
{
	static int i = 0;
	
	for(int j = 0; j < 4; j++)
	{
		draw_card(game->deck, i++, &(game->players[j]));
		if(check_fours(game->players[j]))
		{
			print_player(game->players[j]);
			i = 0;
			return;
		}
	}
	
	if(i >= 52)
	{
		struct player_t* player = check_points(game->players);
		
		if(player != NULL)
		{
			print_player(*player);
			i = 0;
			return;
		}
		
		printf("NOBODY WON\n"); // It's a draw.
		i = 0;
		return;
	}
	
	play_game(game);
}



int main() // Demonstrates a game of cards.
{
	char* fname = malloc(sizeof(char) * 11); // "deck_1.txt" || "deck_2.txt"
	printf("ENTER FILENAME:\n");
	fgets(fname, 11, stdin);
	// strtok(fname, "\n");
	
	printf("\n");
	
	FILE* deck = fopen(fname, "r");
	struct game_t* game = init_game(deck);
	play_game(game);
	
	free(fname);
	fname = NULL;
	fclose(deck);
	free(game);
	game = NULL;
	
	return 0;
}
