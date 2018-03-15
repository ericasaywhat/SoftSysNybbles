#include "main.h"

/*
 * Allocates space to an Object and returns a pointer to the Object.
 * 
 * return: pointer to newly created Object
 */
Object* make_object(){
	Object* obj = malloc(sizeof(Object));
	return obj;
}

/*
 * Creates the game Map, including placing Objects on the Map.
 * Initializes locations of the player, the pit, the Wumpus, and the bats.
 * 
 * return: pointer to newly created Map
 */
Map* make_map(){
	map = malloc(sizeof(Map));
	map->width = 5;
	map->height = 5;
	map->numArrows = 5;
	map->coords = coords();
	Object* player = make_object();
	Object* pit = make_object();
	Object* wum = make_object();
	Object* bat = make_object();

	map->player = player;
	map->pit = pit;
	map->wum = wum;
	map->bat = bat;

	placeObject(map->pit, PIT);
	placeObject(map->bat, BAT);
	placeObject(map->wum, WUM);
	placeObject(map->player, PLAYER);
	whereisPlayer();

	return map;
}

/*
 * Prints the location of the player.
 * Player location goes left to right and top to bottom.
 */
void whereisPlayer() {
	printf("You are at %i,%i.\n", map->player->x, map->player->y);
}

/*
 * Generates an empty 2D array for a Map to populate.
 * 
 * return: pointer to pointer to 2D array
 */
int** coords() {
	int i, j;
	int** coords = malloc(HEIGHT * WIDTH * sizeof(int*));

	for(i=0; i<HEIGHT; i++) {
		int* values = calloc(WIDTH*HEIGHT, sizeof(int));
		coords[i] = values;
	}
	return coords;
}

/*
 * Ends the game and prints the appropriate statement.
 * 
 * condition: 0 if player lost, 1 if player won
 */
void endGame(int condition){
    char c;

	switch (condition){
	case WUMDEATH:
		puts("Game Over... The Wumpus got you.");
		deaths++;
		break;
	case PITDEATH:
		puts("Game Over... You fell down a pit!");
		deaths++;
		break;
	case PLAYERWIN:
		puts("You killed the Wumpus! Congratulations!");
		kills++;
		break;
	}

	game_over = true;
}

/*
 * Shoots an arrow in the direction inputted by the user.
 * 
 * direction: char direction to shoot in ('WASD')
 */
void shoot(char direction){
	if (map->numArrows == 0) {
		puts("You are out of arrows! Try walking around to find more.");
	} else {
		map->numArrows--;

		switch(direction) {
			case 'W':
			if (map->player->y < map->wum->y &&
				map->player->x == map->wum->x) { 
				wumpusMovement();
			} else if (map->player->y > map->wum->y &&
				map->player->x == map->wum->x) { 
				endGame(PLAYERWIN);
			}
			break;
			case 'S':
			if(map->player->y > map->wum->y &&
				map->player->x == map->wum->x){ 
				wumpusMovement();
			} else if(map->player->y < map->wum->y &&
				map->player->x == map->wum->x){
				endGame(PLAYERWIN);
			}
			break;
			case 'A':
			if(map->player->x < map->wum->x &&
				map->player->y == map->wum->y){ 
				wumpusMovement(); 
			} else if (map->player->x > map->wum->x &&
				map->player->y == map->wum->y) { 
				endGame(PLAYERWIN);
			}
			break;
			case 'D':
			if(map->player->x > map->wum->x &&
				map->player->y == map->wum->y){ 
				wumpusMovement();
			} else if(map->player->x < map->wum->x &&
				map->player->y == map->wum->y){
				endGame(PLAYERWIN);
			}
			break;
		}

		if (!endGame) {
			printf("You successfully shot an arrow in direction %c. Arrows remaining: %i.\n",
			direction, map->numArrows);

			if (map->numArrows == 0) {
				placeArrow();
			}
		}
	}
}

void placeArrow() {
	time_t t;
	srand((unsigned) time(&t));

	int x = rand()%map->width;
	int y = rand()%map->height;
	while (map->coords[y][x] != 0) {
		x = rand()%map->width;
		y = rand()%map->height;
	}

	map->coords[y][x] = ARROW;
}

/*
 * Moves the wumpus in a random direction.
 */
void wumpusMovement() {
	map->coords[map->wum->y][map->wum->x] = 0;
	placeObject(map->wum, WUM);
}

void checkConsequences(){
	int playerx = map->player->x;
	int playery = map->player->y;
	int pitx = map->pit->x;
	int pity = map->pit->y;
	int wumx = map->wum->x;
	int wumy = map->wum->y;
	int batx = map->bat->x;
	int baty = map->bat->y;

	if ((playerx == pitx &&
		playery == pity) ||
		(playerx == pitx &&
		playery == pity)) { 
		endGame(PITDEATH); 
	} else if (playerx == batx &&
		playery == baty) {
		batAbduction();
	} else if (playerx == wumx &&
		playery == wumy) {
		endGame(WUMDEATH);
	} else {
		if ((playerx + 1 == wumx && playery == wumy) ||
			(playerx - 1 == wumx && playery == wumy) || 
			(playery + 1 == wumy && playerx == wumx) ||
			(playery - 1 == wumy && playerx == wumx)) {
			puts("You smell a wumpus! Proceed with caution...");
		}
		if ((playerx + 1 == pitx && playery == pity) ||
			(playerx - 1 == pitx && playery == pity) || 
			(playery + 1 == pity && playerx == pitx) ||
			(playery - 1 == pity && playerx == pitx)) {
			puts("You feel a breeze nearby. Watch your step...");
		}
		if ((playerx + 1 == batx && playery == baty) ||
			(playerx - 1 == batx && playery == baty) || 
			(playery + 1 == baty && playerx == batx) ||
			(playery - 1 == baty && playerx == batx)) {
			puts("You hear flapping nearby. Wonder what's making that sound?");
		}
	}
}

bool playerCanMove(char direction) {
	if ((direction == 'a' && map->player->x == 0) ||
		(direction == 'd' && map->player->x == WIDTH-1) ||
		(direction == 's' && map->player->y == HEIGHT-1) |
		(direction == 'w' && map->player->y == 0) ||
		(direction != 'a' && direction != 'w' &&
			direction != 's' && direction != 'd')) {
		return false;
	} else {
		return true;
	}
}

bool moveSuccessful(char direction) {
	map->coords[map->player->y][map->player->x] = 0;
	switch (direction) {
		case 'w':
			map->player->y--;
			break;
		case 'a':
			map->player->x--;
			break;
		case 's':
			map->player->y++;
			break;
		case 'd':
			map->player->x++;
			break;
		default:
			return false;
	}
	return true;
}

void playerMovement(char direction){
	switch(direction) {
	//player shooting
	case 'W':
	case 'A':
	case 'S':
	case 'D':
		shoot(direction);
		break;
	default:
		if (playerCanMove(direction) && moveSuccessful(direction)) {
			if (map->coords[map->player->y][map->player->x] == ARROW) {
				map->numArrows++;
				printf("You found an arrow! Arrows remaining: %i.\n", map->numArrows);
			}
			map->coords[map->player->y][map->player->x] = PLAYER;
			checkConsequences();
			if (!game_over) {
				whereisPlayer();
			}
		} else {
			printf("You could not move in direction: %c. Please try again.\n", direction);
		}
	}
}

void printMap() {
	int i, j;

	for (i=0; i<5; i++){
		for (j=0; j<5; j++) {
			printf("%i ", map->coords[i][j]);
		}
		puts("\n");
	}
}

void placeObject(Object* object, int identity) {
	time_t t;
	srand((unsigned) time(&t));

	int x = rand()%map->width;
	int y = rand()%map->height;
	while (map->coords[y][x] != 0) {
		x = rand()%map->width;
		y = rand()%map->height;
	}

	object->x = x;
	object->y = y;

	map->coords[y][x] = identity;
}



void free_objects(){
	free(map->player);
	free(map->bat);
	free(map->pit);
	free(map->wum);
}

void free_map(){
	free(map);
}

void INThandler(int sig) {
     char  c;

     signal(sig, SIG_IGN);
     printf("\nAre you sure you want to quit? [y/n] ");
     c = getchar();
     if (c == 'y' || c == 'Y'){
          exit(0);
     }
     else{
          signal(SIGINT, INThandler);
     }
     getchar(); // Get new line character
}

void getKeyPress() {
	char s;
	int i;
	char valid_directions[] = "wasdWASD";

	s = getchar();

	for (i = 0; i < strlen(valid_directions); i++) {
		if (s == valid_directions[i]) {
			playerMovement(s);
		}
	}
}

/*
 * Abducts the player and moves them to a new blok.
 */
void batAbduction() {
	map->coords[map->player->y][map->player->x] = 0;
	placeObject(map->player, PLAYER);
}

void playGame(){
	make_map();
	game_over = false;

	while (!game_over) {
		signal(SIGINT, INThandler);
	    getKeyPress();
	}
}

int main() {
	char response[2];
	want_to_play = true;
	kills = 0;
	deaths = 0;
	while (want_to_play) {
		puts("***************************");
		puts("WELCOME TO HUNT THE WUMPUS!");
		printf("You have killed the Wumpus %i times.\n",
			kills);
		printf("You have died %i times.\n",
			deaths);
		puts("Good luck!");
		puts("***************************\n");
		playGame();
		printf("Would you like to play again? [y/n] ");
		scanf("%s", response);
		if (response[0] == 'n') {
			puts("Exiting...");
			want_to_play = false;
		} else {
			puts("Great, let's play another round!\n");
		}
		free_map();
		free_objects();
	}
	return 0;
}