#include "TrueRandom.h"

#include "sha1.h"

#include "nano.h"

#include "nano_game0.h"
#include "nano_game1.h"
#include "nano_game2.h"

int scene_id = 0;

int timestamp = 0;

void setup() {

	randomSeed(analogRead(0));
	Serial.begin(115200);

	Serial.print("HITCON 2015 NANO GAME\n");
	Serial.print("\n");
	Serial.print("Nano$ enter your team token:\n");
	Serial.print("\n");

}

void loop() {

	switch (scene_id) {

		case 0:
			if (Serial.available()) {
				char read = Serial.read();
				if (read == '\n') {
					Serial.print("User$ my team token is " + team_token + "\n");
					Serial.print("\n");
					scene_id = 1;
				} else {
					team_token += read;
				}
			}
			break;

		case 1:
			Serial.print("Nano$ [0] Morse\n");
			Serial.print("Nano$ [1] Maze\n");
			Serial.print("Nano$ [2] Calculator\n");
			Serial.print("Nano$ enter your choice:\n");
			Serial.print("\n");
			scene_id = 2;
			break;

		case 2:
			if (Serial.available()) {
				char read = Serial.read();
				if (read == '\n') {
					read = answer.charAt(0);
					answer = "";
					if (read == '0') {
						Serial.print("User$ choice [0] Morse\n");
						Serial.print("\n");
						scene_id = 100 + 0;
					}
					if (read == '1') {
						Serial.print("User$ choice [1] Maze\n");
						Serial.print("\n");
						scene_id = 100 + 1;
					}
					if (read == '2') {
						Serial.print("User$ choice [2] Calculator\n");
						Serial.print("\n");
						scene_id = 100 + 2;
					}
				} else {
					answer += read;
				}
			}
			break;

		case 100 + 0:
			Serial.print("Nano$ activate Morse\n");
			Serial.print("Nano$ .... .. - -.-. --- -. -. .- -. --- --. .- -- . -- --- .-. ... .\n");
			Serial.print("Nano$ enter your answer:\n");
			Serial.print("\n");
			scene_id = 1000 + 0;
			break;

		case 100 + 1:
			Serial.print("Nano$ activate Maze\n");
			Serial.print("\n");
			game1_init();
			timestamp = millis();
			scene_id = 1000 + 1;
			break;

		case 100 + 2:
			Serial.print("Nano$ activate Calculator\n");
			game2_init();
			timestamp = millis();
			Serial.print("Nano$ enter your answer:\n");
			Serial.print("\n");
			scene_id = 1000 + 2;
			break;

		case 1000 + 0:
			game0();
			break;

		case 1000 + 1:
			if (millis() - timestamp > 9 * 1000) {
				Serial.print("Nano$ timeout (9 seconds)\n");
				Serial.print("Nano$ finish\n");
				scene_id = 9999;
				break;
			}
			game1();
			break;

		case 1000 + 2:
			if (millis() - timestamp > 1 * 1000) {
				Serial.print("Nano$ timeout (1 seconds)\n");
				Serial.print("Nano$ finish\n");
				scene_id = 9999;
				break;
			}
			game2();
			break;

		case 9999:
			Serial.end();
			break;

	}
}