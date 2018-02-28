#include <stdio.h>
#include <stdlib.h>
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

void playerMovement(){

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


	while (map[x][y] != 0) {
		x = rand()%WIDTH;
		y = rand()%HEIGHT;
	}

	printf("%i, %i\n", x, y);

	switch(object) {
	case PLAYER:
		playerx = x;
		playery = y;
	case BAT:
		batx = x;
		baty = y;
	case PIT:
		pitx = x;
		pity = y;
	case WUM:
		wumx = x;
		wumy = y;
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
	free(*arr);
	free(arr);
	return 0;
}