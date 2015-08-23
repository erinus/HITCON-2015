#include "TrueRandom.h"

int game1_maze_myposx = 0;
int game1_maze_myposy = 0;

int game1_maze_myansx = 14;
int game1_maze_myansy = 14;

char game1_maze_square[15][15] = {
	{ '.', '+', '+', '+', '+', '+', '+' ,'+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' },
	{ '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+' ,'+', '+' }
};

void game1_maze_create() {
	Serial.print("Nano$ I WANT TO PLAY A GAME !\n");
	Serial.print("Nano$ now, you are in (0,0) of an unknown maze.\n");
	Serial.print("Nano$ you must reach (14, 14) of this maze.\n");
	Serial.print("Nano$ you have ten seconds to reach it.\n");
	Serial.print("Nano$ the 'O' is where you are.\n");
	Serial.print("Nano$ the '.' mark is road.\n");
	Serial.print("Nano$ the '+' mark is wall.\n");
	Serial.print("Nano$ send [w] to move up\n");
	Serial.print("Nano$ send [d] to move right\n");
	Serial.print("Nano$ send [s] to move down\n");
	Serial.print("Nano$ send [a] to move left\n");
	int count = 0;
	int herex = 0;
	int herey = 0;
	int limit = 0;
	int x = 0;
	int y = 0;
	start:
	game1_maze_myposx = 0;
	game1_maze_myposy = 0;
	for (y = 0; y <= 14; y++) {
		for (x = 0; x <= 14; x++) {
			if (x == 0 && y == 0) {
				game1_maze_square[y][x] = '.';
				continue;
			}
			game1_maze_square[y][x] = '+';
		}
	}
	for (count = 0; count < 10000; count++) {
		if (herex == game1_maze_myansx && herey == game1_maze_myansy) {
			break;
		}
		if (limit > 8) {
			limit = 0;
			int y = TrueRandom.random(14) + 1;
			switch (TrueRandom.random(4)) {
				case 0:
					for (x = 14; x >= 0; x--) {
						if (game1_maze_square[y][x] == '.') {
							herex = x;
							herey = y;
							goto again;
						}
					}
					break;
				case 1:
					for (x = 0; x <= 14; x++) {
						if (game1_maze_square[y][x] == '.') {
							herex = x;
							herey = y;
							goto again;
						}
					}
					break;
			}
		}
		again:
		switch (TrueRandom.random(4)) {
			// UP
			case 0:
				if (herey == 0) {
					limit++;
					continue;
				}
				if (herey >= 2 && game1_maze_square[herey - 2][herex] == '.') {
					limit++;
					continue;
				}
				if (herex >= 1 && herex <= 13) {
					if (game1_maze_square[herey - 1][herex + 1] == '.' ||
						game1_maze_square[herey - 1][herex - 1] == '.') {
						limit++;
						continue;
					}
				} else {
					if (herex == 0 &&
						game1_maze_square[herey - 1][herex + 1] == '.') {
						limit++;
						continue;
					}
					if (herex == 14 &&
						game1_maze_square[herey - 1][herex + 1] == '.') {
						limit++;
						continue;
					}
				}
				herey--;
				break;
			// RIGHT
			case 1:
				if (herex == 14) {
					limit++;
					continue;
				}
				if (herex <= 12 && game1_maze_square[herey][herex + 2] == '.') {
					limit++;
					continue;
				}
				if (herey >= 1 && herey <= 13) {
					if (game1_maze_square[herey + 1][herex + 1] == '.' ||
						game1_maze_square[herey - 1][herex + 1] == '.') {
						limit++;
						continue;
					}
				} else {
					if (herey == 0 &&
						game1_maze_square[herey + 1][herex + 1] == '.') {
						limit++;
						continue;
					}
					if (herey == 14 &&
						game1_maze_square[herey - 1][herex + 1] == '.') {
						limit++;
						continue;
					}
				}
				herex++;
				break;
			// DOWN
			case 2:
				if (herey == 14) {
					limit++;
					continue;
				}
				if (herey <= 12 && game1_maze_square[herey + 2][herex] == '.') {
					limit++;
					continue;
				}
				if (herex >= 1 && herex <= 13) {
					if (game1_maze_square[herey + 1][herex + 1] == '.' ||
						game1_maze_square[herey + 1][herex - 1] == '.') {
						limit++;
						continue;
					}
				} else {
					if (herex == 0 &&
						game1_maze_square[herey + 1][herex + 1] == '.') {
						limit++;
						continue;
					}
					if (herex == 14 &&
						game1_maze_square[herey + 1][herex + 1] == '.') {
						limit++;
						continue;
					}
				}
				herey++;
				break;
			// LEFT
			case 3:
				if (herex == 0) {
					limit++;
					continue;
				}
				if (herex >= 2 && game1_maze_square[herey][herex - 2] == '.') {
					limit++;
					continue;
				}
				if (herey >= 1 && herey <= 13) {
					if (game1_maze_square[herey + 1][herex - 1] == '.' ||
						game1_maze_square[herey - 1][herex - 1] == '.') {
						limit++;
						continue;
					}
				} else {
					if (herey == 0 &&
						game1_maze_square[herey + 1][herex - 1] == '.') {
						limit++;
						continue;
					}
					if (herey == 14 &&
						game1_maze_square[herey - 1][herex - 1] == '.') {
						limit++;
						continue;
					}
				}
				herex--;
				break;
		}
		game1_maze_square[herey][herex] = '.';
		// maze_output();
	}
	if (count == 10000) {
		goto start;
	}
	for (y = 0; y <= 12; y++) {
		for (x = 0; x <= 12; x++) {
			if (game1_maze_square[y + 0][x + 0] == '+' && game1_maze_square[y + 0][x + 1] == '+' && game1_maze_square[y + 0][x + 2] == '+' &&
				game1_maze_square[y + 1][x + 0] == '+' && game1_maze_square[y + 1][x + 1] == '+' && game1_maze_square[y + 1][x + 2] == '+' &&
				game1_maze_square[y + 2][x + 0] == '+' && game1_maze_square[y + 2][x + 1] == '+' && game1_maze_square[y + 2][x + 2] == '+') {
				if (game1_maze_square[y + 0][x - 1] == '.') {
					game1_maze_square[y + 0][x + 0] = '.';
					herex = x;
					herey = y;
					goto again;
				}
				if (game1_maze_square[y + 1][x - 1] == '.') {
					game1_maze_square[y + 1][x + 0] = '.';
					herex = x;
					herey = y;
					goto again;
				}
				if (game1_maze_square[y + 2][x - 1] == '.') {
					game1_maze_square[y + 2][x + 0] = '.';
					herex = x;
					herey = y;
					goto again;
				}
			}
		}
	}
}

void game1_maze_output() {
	// display partial maze (3 X 3)
	// /*
	int begx = game1_maze_myposx;
	int begy = game1_maze_myposy;
	if (begx == 0) {
		begx += 1;
	}
	if (begx == 14) {
		begx -= 1;
	}
	begx -= 1;
	if (begy == 0) {
		begy += 1;
	}
	if (begy == 14) {
		begy -= 1;
	}
	begy -= 1;
	for (int y = begy; y < begy + 3; y++) {
		for (int x = begx; x < begx + 3; x++) {
			if (x == game1_maze_myposx && y == game1_maze_myposy) {
				Serial.print('O');
				continue;
			}
			if (x == game1_maze_myansx && y == game1_maze_myansy) {
				Serial.print('X');
				continue;
			}
			Serial.print(game1_maze_square[y][x]);
		}
		Serial.print("\n");
	}
	// */

	// display full maze
	/*
	for (int y = 0; y <= 14; y++) {
		for (int x = 0; x <= 14; x++) {
			if (x == game1_maze_myposx && y == game1_maze_myposy) {
				Serial.print('O');
				continue;
			}
			Serial.print(game1_maze_square[y][x]);
		}
		Serial.print('\n');
	}
	*/

	Serial.print("Nano$ show map\n");
	Serial.print("\n");
}

void game1_init() {

	game1_maze_create();
	game1_maze_output();

}

void game1() {

	if (Serial.available()) {
		char read = Serial.read();
		if (read == '\n') {
			read = answer.charAt(0);
			answer = "";
			Serial.print("User$ send [" + String(read) + "]\n");
			Serial.print("\n");
			switch (read) {
				// UP
				case 'w':
					if (game1_maze_myposy != 0) {
						if (game1_maze_square[game1_maze_myposy - 1][game1_maze_myposx] != '+') {
							game1_maze_myposy -= 1;
						}
					}
					if (game1_maze_myposx == game1_maze_myansx && game1_maze_myposy == game1_maze_myansy) {
						Serial.print("Nano$ key is 3D52CB746F9E6C83\n");
						break;
					}
					game1_maze_output();
					break;

				// DOWN
				case 's':
					if (game1_maze_myposy != 14) {
						if (game1_maze_square[game1_maze_myposy + 1][game1_maze_myposx] != '+') {
							game1_maze_myposy += 1;
						}
					}
					if (game1_maze_myposx == game1_maze_myansx && game1_maze_myposy == game1_maze_myansy) {
						Serial.print("Nano$ key is 3D52CB746F9E6C83\n");
						break;
					}
					game1_maze_output();
					break;

				// LEFT
				case 'a':
					if (game1_maze_myposx != 0) {
						if (game1_maze_square[game1_maze_myposy][game1_maze_myposx - 1] != '+') {
							game1_maze_myposx -= 1;
						}
					}
					if (game1_maze_myposx == game1_maze_myansx && game1_maze_myposy == game1_maze_myansy) {
						Serial.print("Nano$ key is 3D52CB746F9E6C83\n");
						break;
					}
					game1_maze_output();
					break;

				// RIGHT
				case 'd':
					if (game1_maze_myposx != 14) {
						if (game1_maze_square[game1_maze_myposy][game1_maze_myposx + 1] != '+') {
							game1_maze_myposx += 1;
						}
					}
					if (game1_maze_myposx == game1_maze_myansx && game1_maze_myposy == game1_maze_myansy) {
						Serial.print("Nano$ key is 3D52CB746F9E6C83\n");
						break;
					}
					game1_maze_output();
					break;

			}
		} else {
			answer += read;
		}
	}

}
