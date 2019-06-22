//#include <BearLibTerminal.h>

#include "fancy.h"
#include "graphics.h"

typedef struct {
	u32 glyph;
	u32 y, x;
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

Action key_to_action(Key code) {
	// TODO: add key rebinding
	switch (code) {
		case Key_h: return Movewest;
		case Key_j: return Movesouth;
		case Key_k: return Movenorth;
		case Key_l: return Moveeast;
		case Key_q: return Quit;
		//case _PERIOD: return Wait;
		default: return None;
	}
}

i32 main(void) {
	Windowprocs procs;
	if (true) {
		procs = curses_windowprocs;
	} else {
		//procs = blt_windowprocs;
	}

	if (!procs.init()) {
		printf("Failed to open terminal!  Sorry...");
		return -1;
	}
	/*
	terminal_set("input.cursor-blink-rate=2147483647");
	terminal_set("input.cursor-symbol=0x2588");
	terminal_set("font: dvsm.ttf, use-box-drawing=false, use-block-elements=false, size=12x24");
	*/

	bool playing = true;
	Being player = {'@', 0, 0};

	while (playing) {
		switch (key_to_action(procs.read())) {
			case Movenorth: player.y--; break;
			case Movesouth: player.y++; break;
			case Moveeast: player.x++; break;
			case Movewest: player.x--; break;
			case Quit: playing = false; break;
			case Wait: break;
			case None: break;
		}
		procs.clear();

		procs.write(player.glyph, player.y, player.x, false, false, false);

		procs.blit();
	}


	procs.quit();
}
