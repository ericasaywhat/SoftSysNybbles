# Nybbles’ Project Update: Hunt the Wumpus

### Erica Lee & Emily Yeh

#### Our Goals

Our main goal for this project is to gain a better understanding of C, especially with regards to using pointers and various C libraries. To achieve this goal, we are building a game in C called Hunt the Wumpus with code that is object-oriented and memory- and runtime-efficient. We planned our minimum viable product to be a game that includes a target enemy (the Wumpus), a mechanism by which the player can shoot missiles to defeat the enemy, and a map that is displayed in the terminal around which the player can move. Some stretch goals we had were to include text prompts, movement mechanisms for the target and the player, and a “boundless” map where the player can move in any direction infinitely, and the map remains centered on the player.

#### Current Status

Currently, we have our MVP completed; we implemented a target enemy as a variable, a way for the player to shoot at the enemy via reading and parsing standard input, and a map that displays the current locations of all the elements of the game as a 2-dimensional array that is randomly generated at the start of the game. In addition, since the player is able to input a command to move around the map, we were able to implement a way for the player to input a similar command that shoots an arrow in the direction of their choosing.

Originally, text prompts were a stretch goal for us, because we were unsure how necessary they would be for the game. However, we eventually decided to implement prompts even before completing our MVP because we found that they are an important part of the Hunt the Wumpus game.

#### What's Next?
 
Currently, our MVP is complete. Our next steps are related to implementing more aspects of the original Hunt the Wumpus game and improving our code quality. First, we will implement movement of the enemy when arrows are shot near it; when this is completed, we will be able to observe the enemy changing positions on the map when an arrow is shot near it. Second, we will group some related variables into structs; when we have completed this task, there should not be any observable change to the behavior of the game, but the code quality will have improved. Third, we will use pointers to update variables; again, upon completing this task, there should not be any observable change to the game, but the code quality will have improved. Finally, we will separate useful functions in our code and move them into header files. After completing this task, the game will not have changed, but our code quality will have improved.

