#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define WIDTH 5
#define HEIGHT 5

#define PIT 1
#define BAT 2
#define WUM 3
#define PLAYER 5

int playerx, playery;
int pitx, pity;
int wumx, wumy;
int batx, baty;

/*

1) implement get user input in main

======timeless================

void playerMovement()
	if hit by wumpus game over
	if abduct by bat rando movement
	if fall in pit game over
void shoot()
	if no hit wumpus then wumpus movement
	if hit wumpus win
void wumpusMovement()
void batAbduction()


ctrl + arrow/ wasd keys is movement
alt + arrow/ wasd keys is shooting
void gameOver()
void win()
*/

void shoot(){

}
void gameOver(){
	puts("Game Over!");
	//TODO: the stuff in main maybe move out the map to global
}

void batAbduction(){

}

void checkConsequences(){
	if((playerx==pitx && playery==pity) || (playerx==wumx && playery==wumy)){  gameOver();  }
	else if(playerx==batx && playery==baty){  batAbduction();  }
	else {
		if(playerx==wumx || playery==wumy){
			puts("I hear the wumpus!");
		}
		if(playerx==pitx || playery==pity){
			puts("There is imminent danger...");
		}
		if(playerx==batx || playery==baty){
			puts("I hear the flapping of wings");
		}
	}

	// default:
	// 	puts("I don't feel anything.");
	// }
}

void playerMovement(char direction){
	switch(direction){
	//player shooting
	case 'W':
	case 'A':
	case 'S':
	case 'D':
		shoot(direction);
		break;
	//player movements
	case 'w':
		playery--;
		break;
	case 'a':
		playerx--;
		break;
	case 's':
		playery++;
		break;
	case 'd':
		playerx++;
		break;
	default:
		puts("do not understand direction given");

	}
	checkConsequences();
}



void printMap(int** map) {
	int i, j;

	for (i=0; i<5; i++){
		for (j=0; j<5; j++) {
			printf("%i ", map[i][j]);
		}
		puts("\n");
	}
}

void placeObject(int** map, int object) {
	int x = rand()%WIDTH;
	int y = rand()%HEIGHT;
	while (map[y][x] != 0) {
		puts("repetition");
		x = rand()%WIDTH;
		y = rand()%HEIGHT;
	}

	switch(object) {
	case PLAYER:
		playerx = x;
		playery = y;
		break;
	case BAT:
		batx = x;
		baty = y;
		break;
	case PIT:
		pitx = x;
		pity = y;
		break;
	case WUM:
		wumx = x;
		wumy = y;
		break;
	default:
		puts("do not recognize object to be placed");
	}

	map[y][x] = object;
}

int** map() {
	int i, j;

	int** map = malloc(HEIGHT * sizeof(int*));

	for(i=0; i<WIDTH; i++) {
		int* values = calloc(WIDTH*HEIGHT, sizeof(int));
		map[i] = values;
	}

	time_t t;
	srand((unsigned) time(&t));

	placeObject(map, PIT);
	placeObject(map, BAT);
	placeObject(map, WUM);
	placeObject(map, PLAYER);
	printMap(map);

	return map;
}

int main() {
	int** arr = map();
	// checkConsequences();
	free(*arr);
	free(arr);
	return 0;
}