# Nybbles’ Project Report: Hunt the Wumpus

### Erica Lee & Emily Yeh

#### Goals

Our learning goals for this project are to gain a better understanding of C and to become more competent C programmers, especially with regards to using pointers and structs and following C coding conventions.

To achieve these goals, we create a version of a game in C called _Hunt the Wumpus_ with code that is object-oriented and memory- and runtime-efficient.

_Hunt the Wumpus_ is a game invented by Gregory Yob in 1975 in which a player wanders a map to find and hunt a monster called the Wumpus. There are three perils located randomly on the map: bats that will carry the player to another random location on the map, a bottomless pit that will trap the player forever, and of course, the Wumpus, which will eat the player if the player happens to cross paths with it. The original game was text-based, so there was no visual map - only textual cues that tell the player where they are in the map and what is near them. For example, if the Wumpus is one node away from the player, a text prompt such as “You smell a wumpus!” might appear.

Our rendition of _Hunt the Wumpus_ implements all of these behaviors and stays as true to the rules of the original game as possible. However, we also implement a few additional features in order to challenge ourselves and to make the game easier to play.

#### Implementation Details

In the header file `main.h`, we list macros and the declarations of global variables and functions, as well as two important structs: `Object` and `Map`.

```
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
```

The `Object` struct represents all the objects in the game: the player, the Wumpus, the bats, and the pit. The `Map` struct contains all of these objects, in addition to the properties of the map - its size and the number of arrows that are available to be shot by the player - as well as a two-dimensional integer array that represents the coordinates in the map.

The following is a sample of what our game looks like upon compiling and running it.

```
***************************
WELCOME TO HUNT THE WUMPUS!
Use lowercase wasd keys to move around the map.
Use uppercase WASD keys to shoot arrows. (You start out with 5.)
You have killed the Wumpus 0 times.
You have died 0 times.
Good luck!
***************************

You are at 3,2.
- - - - - 
- - - - - 
- - - O - 
- - - - - 
- - - - - 
```

Our minimum viable product is a game that includes a target enemy - the Wumpus, a mechanism by which the player can shoot arrows to defeat the Wumpus, and a map that is displayed in the terminal around which the player can move. We successfully implemented these features, as the above snippet demonstrates, then moved on to include more features.

A visual map was not a part of the original _Hunt the Wumpus_ game; however, we found that a map makes the game easier to play, since it allows the player to see where they are on the map. None of the other features (the Wumpus, the pit, or the bats) are visible on the map, so we decided that the map is a harmless addition that does not significantly affect the gameplay.

We want the player to be able to play the game as many times as possible, so we implemented this feature. We implement the game using signals; while `bool game_over` is not true, we use a signal handler to listen for keystrokes that indicate the direction the player would like to move or shoot; if the player tries to exit the program using `CTRL+C`, for example, instead of exiting the program instantly, we check to make sure the player really wants to quit using the following code.

```
void INThandler(int sig) {
    char  c;

    signal(sig, SIG_IGN);
    printf("\nAre you sure you want to quit? [y/n] ");
    c = getchar();
    if (c == 'y' || c == 'Y'){
        free_objects(); // free objects before map
        free_map();
        exit(0);
    }
    else{
        signal(SIGINT, INThandler);
    }
    getchar(); // Get new line character
}
```

This ensures that the player is able to continue playing for as long as they want. Since the player is able to play the game multiple times, we also decided to implement a way to keep track of the score in the game - every time the player defeats the Wumpus, the value of `int kills` increases, every time the player is defeated by the Wumpus, the value of `int deaths` increases, and every time the player falls down a bottomless pit, the value of `int deaths` increases again.

#### Reflection

In making our final product, we were able to meet all of our learning goals. We implemented structs and pointers, allocated and freed memory on the heap, and followed C coding conventions. We extended our MVP by adding the pit, bats, and finding random arrows that is in the original _Hunt the Wumpus_ game. 

#### Resources

We would like to thank Head First C by David and Dawn Griffiths for being a resource with regards to structs and pointers usages. We would also like to thank Stack Overflow for containing the answers to most of our questions. Last, but not least, we would like to thank the Software Systems teaching team (Allen and Serena) for supporting us in our endeavors.

