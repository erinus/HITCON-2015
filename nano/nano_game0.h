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
				Serial.print("Nano$ key is 457E1A295B9D1C48\n");
			} else {
				Serial.print("Nano$ wrong answer\n");
			}
			Serial.print("Nano$ finish\n");
		} else {
			answer += read;
		}
	}

}