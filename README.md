# Snake Game - Syntax ke Shikar

## **Introduction**

This is a **classic Snake Game** implemented in **C++** with support for both **single-player and multiplayer modes**. The game is played on a **30x30 grid**, and the objective is to **eat the fruit** while avoiding collisions with the walls, obstacles, and yourself. In multiplayer mode, two players compete to achieve the highest score.

## **Features**

- **Single-player mode:** Navigate the snake, avoid obstacles, and achieve the highest score.
- **Multiplayer mode:** Two players control separate snakes and compete.
- **Dynamic obstacles:** Random obstacles appear in single-player mode.
- **High Score Tracking:** The game saves the highest score in a file.
- **Smooth Gameplay:** Uses `_kbhit()` for non-blocking input handling.

## **How to Play**

### **Controls**

#### *Single Player Mode:*

- Move **left**: `A`
- Move **right**: `D`
- Move **up**: `W`
- Move **down**: `S`

#### *Multiplayer Mode:*

- **Player 1 (Snake 1 - 'O')**

  - Move **left**: `A`
  - Move **right**: `D`
  - Move **up**: `W`
  - Move **down**: `S`

- **Player 2 (Snake 2 - 'X')**

  - Move **left**: `J`
  - Move **right**: `L`
  - Move **up**: `I`
  - Move **down**: `K`

- **Exit Game**: Press `X`

## **Game Rules**

- **The game ends** if you hit a wall, an obstacle, or yourself.
- In **multiplayer mode**, the game ends when both players are out.
- In **single-player mode**, the game tracks and updates the **high score**.
- **Winning Condition (Multiplayer):**
  - The player with the highest score at the end wins.
  - If scores are equal, the game results in a tie.

## **Installation & Running the Game**

1. **Compile the code** using a C++ compiler (MinGW, MSVC, etc.).
   ```sh
   g++ snakegame.cpp -o snakegame.exe
   ```
2. **Run the executable:**
   ```sh
   snakegame.exe
   ```

## **File Handling**

- The game maintains a **high score file (**`highscore.txt`**)**.
- If the current score is higher than the saved high score, it updates the file.

## **Future Improvements**

- Add **graphical interface** instead of console-based display.
- Introduce **power-ups** for more gameplay variations.
- Implement **levels with increasing difficulty**.

## **Author**

- Developed by **Grp-Syntax ke Shikar**

Enjoy playing the game! 🎮🐍

