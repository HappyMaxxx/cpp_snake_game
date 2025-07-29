# Snake Game

This is a classic Snake game implemented in C++ using the ncurses library for a terminal-based interface.

## Features
- Control the snake using arrow keys to collect food (`*`) and grow longer.
- Toggle between solid walls (game over on collision) or wrap-around walls (snake reappears on the opposite side).
- Pause the game with the spacebar.
- Dynamic difficulty: game speed increases as the snake collects food.
- Displays score and game status (paused, game over, or win).
- Win condition: fill the entire screen with the snake.

## Prerequisites
- A C++ compiler (e.g., g++).
- The ncurses library installed on your system:
  - On Ubuntu/Debian: `sudo apt-get install libncurses5-dev libncursesw5-dev`
  - On macOS: `brew install ncurses`
  - On Windows: Use a Unix-like environment (e.g., WSL or MinGW) with ncurses.

## Installation
1. Clone or download the repository.
2. Ensure the ncurses library is installed.
3. Compile the game:
   ```bash
   g++ -o snake main.cpp -lncurses
   ```
4. Run the game:
   ```bash
   ./snake
   ```

## How to Play
1. At the start, choose wall behavior:
   - Press `1` for solid walls (collision ends the game).
   - Press `2` for wrap-around walls (snake wraps to the opposite side).
2. Use the arrow keys to control the snake's direction.
3. Collect food (`*`) to increase your score and the snake's length.
4. Press the spacebar to pause/unpause the game.
5. Press `q` to quit the game.
6. Win by filling the entire screen with the snake, or lose by hitting yourself or (with solid walls) the screen boundaries.

## Controls
- **Arrow Keys**: Change the snake's direction (Up, Down, Left, Right).
- **Spacebar**: Pause or resume the game.
- **q**: Quit the game.

## Notes
- The game speed increases with each food collected, making it progressively harder.
- The snake cannot reverse directly into itself (e.g., from right to left).
- The game uses the terminal's dimensions, so resizing the terminal may affect gameplay.

## License
This project is licensed under the MIT License.