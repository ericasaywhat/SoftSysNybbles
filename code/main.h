#include <assert.h>
#include <errno.h>  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <termios.h>  
#include <time.h>
#include <unistd.h>

#define WIDTH 5
#define HEIGHT 5

#define PIT 1
#define BAT 2
#define WUM 3
#define ARROW 4
#define PLAYER 5

#define PITDEATH 0
#define WUMDEATH 1
#define PLAYERWIN 2

int kills;
int deaths;
bool game_over;
bool want_to_play;

typedef struct {
	int x;
	int y;
} Object;

typedef struct {
	int width;
	int height;
	int numArrows;
	Object* player;
	Object* pit;
	Object* wum;
	Object* bat;
	int** coords;
} Map;

Map* map;

Object* make_object();
Map* make_map();
int** coords();
void playGame();
void INThandler(int);
void endGame(int condition);
void shoot(char direction);
void wumpusMovement();
void checkConsequences();
void playerMovement(char direction);
void printMap();
void placeObject(Object* object, int identity);
void free_objects();
void free_map();
void INThandler(int sig);
void getKeyPress();
void batAbduction();
void placeArrow();
void whereisPlayer();
void printMaskedMap();