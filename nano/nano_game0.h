uint8_t game0_secret[] = { 0x45, 0x7E, 0x1A, 0x29, 0x5B, 0x9D, 0x1C, 0x48 };

void game0() {

	if (Serial.available()) {
		char read = Serial.read();
		if (read == '\n') {
			Serial.print("User$ my answer is " + answer + "\n");
			Serial.print("\n");
			Sha1.init();
			Sha1.print(answer);
			uint8_t *hash_result = Sha1.result();
			String hash_string;
			for (int index = 0; index < 20; index++) {
				hash_string += String(hash_result[index], HEX);
			}
			if (hash_string.equals("b347bae2bfcd1ef679aa3177d017f042e52dca2")) {
				for (int index = 0; index < 8; index++) {
					ticket += String(game0_secret[index] ^ team_token[index], HEX);
				}
				// Serial.print("Nano$ right answer (ticket is " + ticket + ")\n");
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