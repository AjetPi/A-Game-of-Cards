#ifndef FUNCS_H
#define FUNCS_H



void write_deck(FILE* file, struct card_t* deck) // Writes the game's deck from a file.
{
	char cur;
	
	for(int i = 0; i < 52 /*&& !feof(file)*/ ; i++)
	{
		if((cur = fgetc(file)) == ' ')
		{
			cur = fgetc(file);
		}
		deck[i].value = cur;
		
		if((cur = fgetc(file)) == ' ')
		{
			cur = fgetc(file);
		}
		deck[i].colour = cur;
	}
}

void draw_card(struct card_t* deck, int i, struct player_t* player) // Draws a card from the game's deck and adds it to a player's hand.
{
	player->hand[player->used] = deck[i];
	player->used++;
}


int get_value(struct card_t card) // Converts a card's value into an integer.
{
	int val;
	
	switch(card.value)
	{
		case 'J':
			val = 10;
			break;
		case 'Q':
			val = 12;
			break;
		case 'K':
			val = 15;
			break;
		case 'A':
			val = 20;
			break;
		default: // '1' - '9'
			val = card.value - 49;
	}
	
	return val;
}

int get_colour(struct card_t card) // Converts a card's colour into an integer.
{
	int val;
	
	switch(card.colour)
	{
		case 'C':
			val = 1;
			break;
		case 'D':
			val = 2;
			break;
		case 'H':
			val = 3;
			break;
		case 'S':
			val = 4;
			break;
	}
	
	return val;
}

int sum_values(struct player_t player) // Sums the card values in a player's hand.
{
	int sum = 0;
	
	for(int i = 0; i < player.used; i++)
	{
		sum += get_value(player.hand[i]);
	}
	
	return sum;
}

int sum_colours(struct player_t player) // Sums the card colours in a player's hand.
{
	int sum = 0;
	
	for(int i = 0; i < player.used; i++)
	{
		sum += get_colour(player.hand[i]);
	}
	
	return sum;
}


int check_fours(struct player_t player) // Checks whether the player has four of a kind or not.
{
	int count;
	
	for(int i = 0; i < player.used; i++)
	{
		count = 1;
		for(int j = i + 1; j < player.used; j++)
		{
			if(player.hand[i].value == player.hand[j].value)
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

struct player_t* check_points(struct player_t* players) // Returns the player with the most points or NULL if there are multiple.
{
	int max = sum_values(players[0]);
	struct player_t* player = &(players[0]);
	
	for(int j = 1; j < 4; j++)
	{
		int cur = sum_values(players[j]);
		
		if(cur > max)
		{
			max = cur;
			player = &(players[j]);
		}
		
		else if(cur == max)
		{
			max = sum_colours(*player);
			cur = sum_colours(players[j]);
			
			if(cur > max)
			{
				player = &(players[j]);
			}
			
			else if(cur == max)
			{
				return NULL;
			}
			
			max = sum_values(*player);
		}
	}
	
	return player;
}


void sort_cards(struct card_t* cards, int size) // Sorts an array of cards, e.g. a player's hand, in descending order.
{
	for(int i = 0; i < size - 1; i++)
	{
		struct card_t* max = &(cards[i]);
		
		for(int j = i + 1; j < size; j++)
		{
			if(get_value(cards[j]) > get_value(*max))
			{
				max = &(cards[j]);
			}
			
			else if(cards[j].value == max->value)
			{
				if(cards[j].colour > max->colour)
				{
					max = &(cards[j]);
				}
			}
		}
		
		struct card_t tmp = cards[i];
		cards[i] = *max;
		*max = tmp;
	}
}

void print_cards(struct card_t* cards, int size) // Prints an array of cards, e.g. the game's deck or a player's hand.
{
	for(int i = 0; i < size; i++)
	{
		printf("(%c, %c)\n", cards[i].value, cards[i].colour);
	}
}

void print_player(struct player_t player) // Prints the winner and his hand's cards in ascending order.
{
	printf("PLAYER %d WON:\n", player.num);
	sort_cards(player.hand, player.used);
	print_cards(player.hand, player.used);
}



#endif
