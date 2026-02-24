# Hex Game - Board Analyzer & Min-Max Solver

This project is an advanced algorithmic analyzer and solver for the classic board game **Hex**. Developed as part of a university programming contest, the application evaluates the state of a hexagonal board, checks for win conditions, and uses game theory algorithms to determine if a player can force a win within a specified number of moves against both naive and perfect opponents.


## Overview of Hex

The game is played by two players (Red and Blue) on a hexagonal grid (sizes varying from 1x1 up to 11x11). 
* **Red** is the starting player.
* Players take turns placing a single piece of their color on any unoccupied hexagon.
* The objective is to form a continuous, unbroken path of pieces connecting the two opposing sides of the board corresponding to the player's color.

<img width="1441" height="796" alt="image" src="https://github.com/user-attachments/assets/0fe31c0a-47a2-4eda-bf61-a1316f2fd215" />


## Key Features & Capabilities

The core of the project involves parsing a textual representation of the board and accurately answering a sequence of complex queries regarding the game state.

### 1. Board State Validation
* **`BOARD_SIZE`**: Determines the dimension of the board (from `1` to `11`).
* **`PAWNS_NUMBER`**: Counts the total pieces currently placed on the board.
* **`IS_BOARD_CORRECT`**: Validates the legality of the board state (ensuring the turn order is respected, meaning the difference between Red and Blue pawns is appropriate).
* **`IS_BOARD_POSSIBLE`**: A deeper validation to check if the current state could have been reached in a real game without overlooking an earlier win by either player.

### 2. End-Game Detection
* **`IS_GAME_OVER`**: Detects if the game has concluded and identifies the winner (`YES RED`, `YES BLUE`, or `NO`). This requires an efficient pathfinding algorithm (e.g., Depth-First Search or Union-Find) across the hexagonal grid to find continuous paths connecting the edges.

### 3. Predictive Analysis (Game Tree Search)
The application evaluates future moves to determine guaranteed winning strategies.
* **Naive Opponent Analysis (`CAN_..._WIN_IN_N_MOVE_WITH_NAIVE_OPPONENT`)**: Evaluates if a player can win in 1 or 2 moves assuming the opponent makes the worst possible choices.
* **Perfect Opponent Analysis (`CAN_..._WIN_IN_N_MOVE_WITH_PERFECT_OPPONENT`)**: Utilizes the **Min-Max algorithm** to determine if a player can force a win in 1 or 2 moves, assuming the opponent plays optimally to block them. 
    * The Min-Max tree generates all possible valid moves for the current player, followed by all optimal counter-moves by the opponent. 
    * The tree depth is dynamically constrained (up to 4 levels) to analyze these short-term forced wins efficiently.

## Example Board Representation

The board is provided via standard input as an ASCII-art hexagonal grid. `r` represents a Red pawn, `b` represents a Blue pawn, and an empty space is denoted by spaces between brackets `< >`.

```text
       ---
    --< r >--
 --< b >-<   >--
<   >-< b >-<   >
 --<   >-< r >--
    --< r >--
       ---
 ```
### 4. Setup & Compilation
To compile and run the project:

Ensure you have a standard C++ compiler installed (e.g., GCC or Clang).

Clone the repository to your local machine.

Compile the source code:

Bash
g++ HEX.cpp -o hex_solver -O3 -Wall
Run the program, feeding it the input test cases:

Bash
./hex_solver < input.txt
