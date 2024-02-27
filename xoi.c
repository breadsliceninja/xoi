/*
XOI
Bodhi Tuladhar, November 2022

A variation of Naughts and Crosses played with three players.

Rules:
Take turns placing tokens. Create special patterns of tokens
to gain points. Patterns cannot share tokens. The game ends
when the board is full or no more points can be gained.

NOTE: The current point counting system is flawed and will
result in suboptimal point counts in certain situations.
When in doubt, count your own points!
*/

#include <stdio.h>

// Gameplay settings
// Default SIZE is 7
// Default TOKENS_PER_TURN is 1
#define SIZE 7
#define TOKENS_PER_TURN 2
#define FANCY_BOARD 0
#define POINTS_X 5
#define POINTS_O 3
#define POINTS_I 1
#define TOKEN_1 "X"
#define TOKEN_2 "O"
#define TOKEN_3 "I"

// Unmagic numbers
#define IN_PROGRESS 0
#define GAME_OVER 1
#define PATTERN_FOUND 1

void print_grid(int grid[SIZE][SIZE]);
int check_state(int grid[SIZE][SIZE]);
void print_patterns(void);
void count_points(int grid[SIZE][SIZE]);

int main(void) {

	int grid[SIZE][SIZE] = {0};
	int row;
	int col;
	int game_state = IN_PROGRESS;
	char* player_tokens[] = {" ", TOKEN_1, TOKEN_2, TOKEN_3};
	int current_player = 0;
	int tokens_placed = 0;

	printf("\nWelcome to XOI!\n\n");
	printf("Take turns placing tokens (%d per turn).\n", TOKENS_PER_TURN);
	printf("Create special patterns of tokens to gain points.\n");
	printf("Patterns can't share tokens.\n");
	printf("The game ends when the board is full.\n\n");
	printf("Here are the patterns:\n\n");
	print_patterns();
	printf("And here's the board (SIZE is set to %d):\n", SIZE);
	
	while (game_state == IN_PROGRESS) {
		print_grid(grid);
		
		printf("\n%s's turn. Choose a tile by entering <row> <col>:\n> ",
				player_tokens[current_player + 1]);

		if (scanf("%d %d", &row, &col) == EOF) {
			return 0;

		} else if (grid[row][col] == 0 && row < SIZE && col < SIZE) {
			grid[row][col] = current_player + 1;

			tokens_placed++;
			if (tokens_placed >= TOKENS_PER_TURN) {
				current_player++;

				if (current_player >= 3) {
					current_player = 0;
				}
				tokens_placed = 0;
			}

		} else {
			printf("\nInvalid input! Try again.\n");
		}

		// Test pattern, fills board with 'X's
		/*
		row = 0;
		while (row < SIZE) {
			col = 0;
			while (col < SIZE) {
				grid[row][col] = 1;
				col++;
			}
			row++;
		}
		*/

		game_state = check_state(grid);
	}

	print_grid(grid);
	//printf("\n- GAME OVER -\nCount your points!\n");
	//printf("Remember, patterns can't intersect.\n\n");
	//print_xoi();
	count_points(grid);
	printf("\nThanks for playing XOI!\n\n");

	return 0;
}

void print_grid(int grid[SIZE][SIZE]) {

	char* player_tokens[] = {" ", TOKEN_1, TOKEN_2, TOKEN_3};

	printf("\n    ");
	int i = 0;
	while (i < SIZE) {
		printf(" %d  ", i);
		i++;
	}
	printf("\n ");

	int row = 0;
	while (row < SIZE) {
		if (row == 0) {
			printf(" /");
		} else {
			printf(" |");
		}
		int i = 0;
		while (i < SIZE) {
			if (row == 0) {
				if (i == 0) {
					printf("/===");
				} else {
					printf("====");
				}

			} else if (i == 0) {
				printf("|---");

			} else if (FANCY_BOARD && row % 2 != 0) {
				if (i % 2 == 0) {
					printf("|---");
				} else {
					printf("----");
				}

			} else {
				if (FANCY_BOARD && i % 2 == 0) {
					printf("----");
				} else {
					printf("|---");
				}
			}
			i++;
		}
		if (row == 0) {
			printf("\\\\\n%d ||", row);
		} else {
			printf("||\n%d ||", row);
		}

		int col = 0;
		while (col < SIZE) {
			printf(" %s |", player_tokens[grid[row][col]]);
			col++;
		}
		printf("|\n ");
		row++;
	}

	printf(" \\\\===");
	i = 1;
	while (i < SIZE) {
		printf("====");
		i++;
	}
	printf("//\n");
}

int check_state(int grid[SIZE][SIZE]) {

	int i = 0;
	while (i < SIZE) {
		int j = 0;
		while (j < SIZE) {
			if (grid[i][j] == 0) {
				return IN_PROGRESS;
			}
			j++;
		}
		i++;
	}
	return GAME_OVER;
}

void print_patterns(void) {
	
	printf("|---|---|---|   |---|---|---|   |---|---|---|   |---|---|---|\n");
	printf("| X |   | X |   |   |   |   |   |   | I |   |   |   |   |   |\n");
	printf("|---|---|---|   |---|---|---|   |---|---|---|   |---|---|---|\n");
	printf("|   | X |   |   | O | O |   |   |   | I |   |   | I | I | I |\n");
	printf("|---|---|---|   |---|---|---|   |---|---|---|   |---|---|---|\n");
	printf("| X |   | X |   | O | O |   |   |   | I |   |   |   |   |   |\n");
	printf("|---|---|---|   |---|---|---|   |---|---|---|   |---|---|---|\n");
	printf("   %d points        %d points        %d point         %d point\n\n",
			POINTS_X, POINTS_O, POINTS_I, POINTS_I);
}

// Some edge cases appear, causing suboptimal points to be chosen.
// Eg. An 'X' with for 'O's on each corner will only award 5 points.
void count_points(int grid[SIZE][SIZE]) {

	char* player_tokens[] = {" ", TOKEN_1, TOKEN_2, TOKEN_3};
	int player = 0;
	while (player < 3) {

		int found_x = 0;
		int found_o = 0;
		int found_i = 0;
		int grid_patterns[SIZE][SIZE] = {0};

		// Check X
		int row = 0;
		while (row < SIZE - 2) {
			int col = 0;
			while (col < SIZE - 2) {
				//printf("Checking X at %d %d\n", row, col);
				if (grid[row][col] == player + 1 && 
					grid[row][col + 2] == player + 1 &&
					grid[row + 1][col + 1] == player + 1 && 
					grid[row + 2][col] == player + 1 && 
					grid[row + 2][col + 2]) {

					//printf("X found\n");
					found_x++;

					grid_patterns[row][col] = PATTERN_FOUND;
					grid_patterns[row + 2][col] = PATTERN_FOUND;
					grid_patterns[row + 1][col + 1] = PATTERN_FOUND;
					grid_patterns[row + 2][col] = PATTERN_FOUND;
					grid_patterns[row + 2][col + 2] = PATTERN_FOUND;
				}
				col++;
			}
			row++;
		}
		// Check O
		row = 0;
		while (row < SIZE - 1) {
			int col = 0;
			while (col < SIZE - 1) {
				//printf("Checking O at %d %d\n", row, col);
				if (grid_patterns[row][col] == 0 &&
					grid_patterns[row][col + 1] == 0 &&
					grid_patterns[row + 1][col] == 0 &&
					grid_patterns[row + 1][col + 1] == 0 &&

					grid[row][col] == player + 1 && 
					grid[row][col + 1] == player + 1 && 
					grid[row + 1][col] == player + 1 && 
					grid[row + 1][col + 1] == player + 1) {

					//printf("O found\n");
					found_o++;

					grid_patterns[row][col] = PATTERN_FOUND;
					grid_patterns[row][col + 1] = PATTERN_FOUND;
					grid_patterns[row + 1][col] = PATTERN_FOUND;
					grid_patterns[row + 1][col + 1] = PATTERN_FOUND;
				}
				col++;
			}
			row++;
		}
		// Check horizontal I
		row = 0;
		while (row < SIZE) {
			int col = 0;
			while (col < SIZE - 2) {
				//printf("Checking horizontal I at %d %d\n", row, col);
				if (grid_patterns[row][col] == 0 &&
					grid_patterns[row][col + 1] == 0 &&
					grid_patterns[row][col + 2] == 0 &&

					grid[row][col] == player + 1 && 
					grid[row][col + 1] == player + 1 && 
					grid[row][col + 2] == player + 1) {

					//printf("horizontal I found\n");
					found_i++;

					grid_patterns[row][col] = PATTERN_FOUND;
					grid_patterns[row][col + 1] = PATTERN_FOUND;
					grid_patterns[row][col + 2] = PATTERN_FOUND;
				}
				col++;
			}
			row++;
		}

		// Check vertical I
		row = 0;
		while (row < SIZE - 2) {
			int col = 0;
			while (col < SIZE) {
				//printf("Checking vertical I at %d %d\n", row, col);
				if (grid_patterns[row][col] == 0 &&
					grid_patterns[row + 1][col] == 0 &&
					grid_patterns[row + 2][col] == 0 &&

					grid[row][col] == player + 1 && 
					grid[row + 1][col] == player + 1 && 
					grid[row + 2][col] == player + 1) {

					//printf("vertical I found\n");
					found_i++;
				}
				col++;
			}
			row++;
		}

		printf("\nPlayer %s:\n", player_tokens[player + 1]);
		printf("  Xs found: %d\n", found_x);
		printf("  Os found: %d\n", found_o);
		printf("  Is found: %d\n", found_i);
		printf("  Total points: %d\n", 
				found_x * POINTS_X + found_o * POINTS_O + found_i * POINTS_I);

		player++;
	}

}
