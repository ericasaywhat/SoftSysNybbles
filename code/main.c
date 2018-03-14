#include "main.h"

Object* make_object(){
	Object* obj = malloc(sizeof(Object));
	return obj;
}

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
	printMap();

	return map;
}

int** coords() {
	int i, j;

	int** coords = malloc(HEIGHT * WIDTH * sizeof(int*));

	for(i=0; i<HEIGHT; i++) {
		int* values = calloc(WIDTH*HEIGHT, sizeof(int));
		coords[i] = values;
	}


	return coords;
}

void endGame(int condition){
	switch (condition){
	case 0:
		puts("Game Over...");
		break;
	case 1:
		puts("YOU'VE WON!");
		break;

	}
	//TODO: restart game?
}

void shoot(char direction){
	if (map->numArrows == 0) {
		puts("You are out of arrows! Try walking around to find more.");
	} else {
		map->numArrows--;

		switch(direction) {
			case 'W':
				if(map->player->y < map->wum->y){  endGame(1); puts("WAH"); }
				else if(map->player->y > map->wum->y){  wumpusMovement();  }
				break;
			case 'S':
				if(map->player->y < map->wum->y){  wumpusMovement();  }
				else if(map->player->y > map->wum->y){  endGame(1); puts("NYA"); }
				break;
			case 'A':
				if(map->player->x < map->wum->x){  endGame(1); puts("KWA");  }
				else if(map->player->x > map->wum->x){  wumpusMovement();  }
				break;
			case 'D':
				if(map->player->x < map->wum->x){  wumpusMovement();  }
				else if(map->player->x > map->wum->x){  endGame(1); puts("FWA"); }
				break;
		}

		printf("Successfully shot an arrow in direction %c. Arrows remaining: %i\n", direction, map->numArrows);
	}
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
			puts("I hear the wumpus!");
		}
		if(map->player->x==map->pit->x || map->player->y==map->pit->y){
			puts("There is imminent danger...");
		}
		if(map->player->x==map->bat->x || map->player->y==map->bat->y){
			puts("I hear the flapping of wings");
		}
	}

	// default:
	// 	puts("I don't feel anything.");
	// }
}

void playerMovement(char direction){
	map->coords[map->player->y][map->player->x] = 0;

	switch(direction) {
	//player shooting
	case 'W':
	case 'A':
	case 'S':
	case 'D':
		shoot(direction);
		break;
	//player movements
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
		puts("do not understand direction given");
	}
	map->coords[map->player->y][map->player->x] = PLAYER;
	checkConsequences(map);
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
     if (c == 'y' || c == 'Y')
          exit(0);
     else
          signal(SIGINT, INThandler);
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

int main() {
	make_map();
	// int** arr = coords();

	signal(SIGINT, INThandler);
    while (1) {
        getKeyPress();
    }

	// free(*arr);
	// free(arr);
	return 0;
}