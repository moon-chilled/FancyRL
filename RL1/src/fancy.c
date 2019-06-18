#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include <BearLibTerminal.h>

typedef struct {
	uint32_t glyph;
	uint32_t y, x;
} Being;

typedef enum {
	Movenorth,
	Movesouth,
	Moveeast,
	Movewest,
	Quit,
	Wait,
	None,
} Action;

Action key_to_action(int code) {
	// TODO
	switch (code) {
		case TK_H: return Movewest;
		case TK_J: return Movesouth;
		case TK_K: return Movenorth;
		case TK_L: return Moveeast;
		case TK_Q: return Quit;
		case TK_PERIOD: return Wait;
		default: return None;
	}
}

int main(void) {
	if (!terminal_open()) {
		printf("Failed to open terminal!  Sorry...");
		return -1;
	}
	terminal_set("input.cursor-blink-rate=2147483647");
	terminal_set("input.cursor-symbol=0x2588");
	terminal_set("font: dvsm.ttf, use-box-drawing=false, use-block-elements=false, size=12x24");

	bool playing = true;
	Being player = {'@', 0, 0};

	while (playing) {
		terminal_clear();

		switch (key_to_action(terminal_read())) {
			case Movenorth: player.y--; break;
			case Movesouth: player.y++; break;
			case Moveeast: player.x++; break;
			case Movewest: player.x--; break;
			case Quit: playing = false; break;
			case Wait: break;
			case None: break;
		}

		terminal_put(player.x, player.y, player.glyph);

		
		terminal_refresh();
	}


	terminal_close();
}
