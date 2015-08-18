#include "TrueRandom.h"

uint8_t game2_secret[] = { 0x27, 0x3A, 0x9C, 0x1E, 0x2D, 0x38, 0x0B, 0x48 };

int game2_total = 0;

void game2_init() {

	String expr = "";
	int num0;
	int num1;
	int num2;
	for (int index = 0; index < 5; index++) {
		if (index == 0) {
			switch (TrueRandom.random(2)) {
				case 0:
					num1 = TrueRandom.random(10) + 1;
					num2 = TrueRandom.random(10) + 1;
					game2_total = num1 * num2;
					expr = expr + String(num1) + " * " + String(num2);
					break;
				case 1:
					num0 = TrueRandom.random(10) + 1;
					game2_total = num0;
					expr = expr + String(num0);
					break;
			}
			continue;
		}
		num0 = TrueRandom.random(20) + 1;
		switch (TrueRandom.random(2)) {
			case 1:
				game2_total = game2_total + num0;
				expr = expr + " + " + String(num0);
				break;
			case 2:
				game2_total = game2_total - num0;
				expr = expr + " - " + String(num0);
				break;
		}
	}
	Serial.print("Nano$ " + String(game2_total) + "\n");
	Serial.print("Nano$ " + expr + " = ?\n");

}

void game2() {

	if (Serial.available()) {
		char read = Serial.read();
		if (read == '\n') {
			Serial.print("User$ my answer is " + answer + "\n");
			Serial.print("\n");
			if (answer.toInt() == game2_total) {
				for (int index = 0; index < 8; index++) {
					ticket += String(game2_secret[index] ^ team_token[index], HEX);
				}
				Serial.print("Nano$ ticket is " + ticket + "\n");
			} else {
				Serial.print("Nano$ wrong answer\n");
			}
			Serial.print("Nano$ finish\n");
		} else {
			answer += read;
		}
	}

}