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
	printMap();

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
	case 0:
		puts("Game Over...");
		game_over = 0;
		break;
	case 1:
		puts("YOU'VE WON!");
		game_over = 0;
		break;
	}
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
				if (map->player->y > map->wum->y &&
					map->player->x == map->wum->x){  endGame(1); }
				else if(map->player->y < map->wum->y &&
					map->player->x == map->wum->x){  wumpusMovement();  }
				break;
			case 'S':
				if(map->player->y > map->wum->y  &&
					map->player->x == map->wum->x){  wumpusMovement();  }
				else if(map->player->y < map->wum->y &&
					map->player->x == map->wum->x){  endGame(1); }
				break;
			case 'A':
				if(map->player->x > map->wum->x &&
					map->player->y == map->wum->y){  endGame(1); }
				else if(map->player->x < map->wum->x &&
					map->player->y == map->wum->y){  wumpusMovement();  }
				break;
			case 'D':
				if(map->player->x > map->wum->x &&
					map->player->y == map->wum->y){  wumpusMovement();  }
				else if(map->player->x < map->wum->x &&
					map->player->y == map->wum->y){  endGame(1); }
				break;
		}

		printf("You successfully shot an arrow in direction %c. Arrows remaining: %i.\n",
			direction, map->numArrows);

		if (map->numArrows == 0) {
			placeArrow();
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
	if((map->player->x==map->pit->x && map->player->y==map->pit->y) ||
		(map->player->x==map->wum->x && map->player->y==map->wum->y)){  endGame(0);  }
	else if(map->player->x==map->bat->x && map->player->y==map->bat->y){  batAbduction();  }
	else {
		if(map->player->x==map->wum->x || map->player->y==map->wum->y){
			puts("You smell a wumpus! Proceed with caution...");
		}
		if(map->player->x==map->pit->x || map->player->y==map->pit->y){
			puts("You feel a breeze nearby. Watch your step...");
		}
		if(map->player->x==map->bat->x || map->player->y==map->bat->y){
			puts("You hear flapping nearby. Wonder what's making that sound?");
		}
	}

	// default:
	// 	puts("I don't feel anything.");
	// }
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
			checkConsequences(map);
			whereisPlayer();
			printMap(map);
		} else {
			printf("You could not move in direction: %c. Please try again.\n", direction);
			printMap(map);
		}
	}
	map->coords[map->player->y][map->player->x] = PLAYER;
	if(game_over){
		checkConsequences(map);
	}
	printMap(map);
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
	signal(SIGINT, INThandler);
    while (1) {
        getKeyPress();
    }
}

int main() {
	game_over = 1;
	playGame();
	return 0;
}