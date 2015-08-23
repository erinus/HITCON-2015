#include "TrueRandom.h"

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
			case 0:
				game2_total = game2_total + num0;
				expr = expr + " + " + String(num0);
				break;
			case 1:
				game2_total = game2_total - num0;
				expr = expr + " - " + String(num0);
				break;
		}
	}
	Serial.print("Nano$ " + expr + " = ?\n");

}

void game2() {

	if (Serial.available()) {
		char read = Serial.read();
		if (read == '\n') {
			Serial.print("User$ my answer is " + answer + "\n");
			Serial.print("\n");
			if (answer.toInt() == game2_total) {
				Serial.print("Nano$ key is 273A9C1E2D380B48\n");
			} else {
				Serial.print("Nano$ wrong answer\n");
			}
			Serial.print("Nano$ finish\n");
		} else {
			answer += read;
		}
	}

}