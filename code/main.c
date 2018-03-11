#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
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

void INThandler(int);

/*
void shoot()
	if no hit wumpus then wumpus movement
	if hit wumpus win
void wumpusMovement()
void batAbduction()

<<<<<<< HEAD
=======

wasd keys is movement
WASD keys is shooting
void gameOver()
void win()
>>>>>>> 5d7484ae8e0fa6ff1d0f6d232126605473a0974d
*/
void wumpusMovement(){

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
	switch(direction){
	case 'W':
		if(playery < wumy){  endGame(1);  }
		else if(playery > wumy){  wumpusMovement();  }
	case 'S':
		if(playery < wumy){  wumpusMovement();  }
		else if(playery > wumy){  endGame(1);  }
	case 'A':
		if(playerx < wumx){  endGame(1);  }
		else if(playerx > wumx){  wumpusMovement();  }
	case 'D':
		if(playerx < wumx){  wumpusMovement();  }
		else if(playerx > wumx){  endGame(1);  }

	}
}

void batAbduction(){

}


void checkConsequences(){
	if((playerx==pitx && playery==pity) || (playerx==wumx && playery==wumy)){  endGame(0);  }
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

void  INThandler(int sig) {
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
			checkConsequences();
		}
	}
}

int main() {
	int** arr = map();

	shoot('W');
	signal(SIGINT, INThandler);
    while (1) {
        getKeyPress();
    }
    return 0;

	free(*arr);
	free(arr);
	return 0;
}