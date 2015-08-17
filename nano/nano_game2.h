#include "TrueRandom.h"

uint8_t game2_secret[] = { 0x27, 0x3A, 0x9C, 0x1E, 0x2D, 0x38, 0x0B, 0x48 };

int game2_total = 0;

void game2_init() {

	randomSeed(analogRead(0));
	String expr = "";
	for (int index = 0; index < 3; index++) {
		int mode = 0;
		if (index != 0) {
			mode = TrueRandom.random(3) + 1;
			switch (mode) {
				case 1:
					expr = expr + " + ";
					break;
				case 2:
					expr = expr + " - ";
					break;
				case 3:
					expr = expr + " * ";
					break;
			}
		}
		int num1 = 0;
		int num2 = 0;
		switch (TrueRandom.random(2)) {
			case 0:
				num1 = TrueRandom.random(10);
				num2 = TrueRandom.random(10);
				switch (mode) {
					case 0:
						game2_total = num1 * num2;
						break;
					case 1:
						game2_total = game2_total + num1 * num2;
						break;
					case 2:
						game2_total = game2_total - num1 * num2;
						break;
					case 3:
						game2_total = game2_total * num1 * num2;
						break;
				}
				expr = expr + String(num1) + " * " + String(num2);
				break;
			case 1:
				num1 = TrueRandom.random(10);
				switch (mode) {
					case 0:
						game2_total = num1;
						break;
					case 1:
						game2_total = game2_total + num1;
						break;
					case 2:
						game2_total = game2_total - num1;
						break;
					case 3:
						game2_total = game2_total * num1;
						break;
				}
				expr = expr + String(num1);
				break;
		}
	}
	Serial.print("Nano$ " + expr + " = " + String(game2_total) + "\n");

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