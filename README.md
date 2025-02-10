SNAKE GAME

A simple console-based Snake game, where you can play either as a single player or multiplayer. Navigate through the grid to eat fruit and avoid obstacles or the other snake in multiplayer mode. The game keeps track of your high score and updates it when a new high score is reached. 
FEATURES
- Single Player: Play the classic Snake game with obstacles.
- Multiplayer: Play with a friend in a competitive mode.
- High Score Tracking: Your highest score is saved in a file, and updated if you beat it.
- Obstacles: Random obstacles to make the single-player experience more challenging.
- Snake Growth: The snake grows longer each time it eats a fruit.
- Keyboard Controls: Easy control via keyboard, with different keys for each player in multiplayer.

CONTROLS

Player 1 (Single Player):  
W- Move Up  
A - Move Left  
S - Move Down 
D - Move Right
  
Player 2 (Multiplayer):  

I- Move Up  
J- Move Left  
K - Move Down  
 L - Move Right

Quit:  
  -X - End the game

HOW TO PLAY
1. Choose between Single Player or Multiplayer mode.
2. Navigate your snake to collect the fruit (denoted by "F").
3. Avoid running into walls, your own tail, or obstacles (in single-player mode).
4. In multiplayer mode, avoid colliding with the other player's snake!
5. The game will display your score, and if you beat the high score, it will be saved.

HOW TO COMPILE AND RUN

1. Clone the repository or download the source files.
2. Open a terminal or command prompt.
3. Navigate to the directory where the files are located.
4. Compile using a C++ compiler. For example, using g++:

bash
   g++ -o SnakeGame SnakeGame.cpp
