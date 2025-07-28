#include <ncurses.h>
#include <random>
#include <vector>

struct Point {
    int y, x;
};

int generateRandomInt(int a, int b) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(a, b);
    return dist(gen);
}

int main() {
    initscr();            
    noecho();             
    cbreak();             
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    int ch;
	int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x); 

    std::vector<Point> snake = {{max_y / 2, max_x / 2}};
    Point food = {generateRandomInt(1, max_y - 2), generateRandomInt(1, max_x - 2)};
    int direction = KEY_RIGHT;
    int score = 0;
    bool game_over = false, pause = false, win = false, solidWalls;
	int difficulty = 0;

    nodelay(stdscr, FALSE); 
    echo();

    mvprintw(max_y / 2 - 1, (max_x - 20) / 2, "Solid walls:");
    mvprintw(max_y / 2, (max_x - 25) / 2, "1 - yes, 2 - no");
    mvprintw(max_y / 2 + 2, (max_x - 20) / 2, "Your choice: ");
    refresh();

    int input = getch();
    switch (input) {
        case '1':
            solidWalls = true;
            break;
        case '2':
            solidWalls = false;
            break;
        default:
            solidWalls = true; 
    }

    noecho();
    nodelay(stdscr, TRUE);
    clear();

    while((ch = getch()) != 'q') {
		if (ch == ' ') pause = !pause;

		if (!pause) {
			if (score == (max_x * max_y)) { win = true; break; }

			if (ch == KEY_UP && direction != KEY_DOWN) direction = KEY_UP;
			else if (ch == KEY_DOWN && direction != KEY_UP) direction = KEY_DOWN;
			else if (ch == KEY_LEFT && direction != KEY_RIGHT) direction = KEY_LEFT;
			else if (ch == KEY_RIGHT && direction != KEY_LEFT) direction = KEY_RIGHT;

			Point head = snake.front();
			switch (direction) {
				case KEY_UP: head.y--; break;
				case KEY_DOWN: head.y++; break;
				case KEY_LEFT: head.x--; break;
				case KEY_RIGHT: head.x++; break;
			}

            if (solidWalls) {
                if (head.x < 0 || head.x >= max_x || head.y < 0 || head.y >= max_y) {
                    game_over = true;
                    break;
                }
            } else {
                if (head.x < 0) head.x = max_x - 1;
                if (head.x >= max_x) head.x = 0;
                if (head.y < 0) head.y = max_y - 1;
                if (head.y >= max_y) head.y = 0;
            }

			for (const auto& segment : snake) {
				if (segment.x == head.x && segment.y == head.y) {
					game_over = true;
					break;
				}
			}
			if (game_over) break;

			snake.insert(snake.begin(), head);

			if (head.x == food.x && head.y == food.y) {
				score++;
				while (true) {
					food.y = generateRandomInt(1, max_y - 2);
					food.x = generateRandomInt(1, max_x - 2);
					bool on_snake = false;
					for (const auto& segment : snake) {
						if (segment.x == food.x && segment.y == food.y) {
							on_snake = true;
							break;
						}
					}
					if (!on_snake) break;
				}
				difficulty += 1;
			} else {
				snake.pop_back();
			}
			clear();
		}

		for (const auto& segment : snake) {
			mvaddch(segment.y, segment.x, 'O');
		}

		mvaddch(food.y, food.x, '*');

		if (pause) {
			mvprintw(0, 0, "Score: %d (PAUSE)", score);
		} else {
			mvprintw(0, 0, "Score: %d", score);
		}

        refresh();
		switch (direction) {
			case KEY_UP: napms(160 - difficulty); break;
			case KEY_DOWN: napms(160 - difficulty);; break;
			case KEY_LEFT: napms(100 - difficulty); break;
			case KEY_RIGHT: napms(100 - difficulty); break;
		}
    }

	clear();
	if (!win) mvprintw(max_y/2, (max_x - 9) / 2, "Game Over!");
	else mvprintw(max_y/2, (max_x - 8) / 2, "You Won!");
		
	mvprintw(max_y/2 + 1, (max_x - 15) / 2, "Final Score: %d", score);
	refresh();
	napms(3000);

    endwin();
    return 0;
}
