#include <unistd.h>

#include "fancy.h"

#include "being.h"
#include "graphics.h"


static bool playing = true;

void apply_action(Being *b, Action act) {
	switch (act) {
		case Act_Movenorth: b->base.y--; break;
		case Act_Movesouth: b->base.y++; break;
		case Act_Moveeast: b->base.x++; break;
		case Act_Movewest: b->base.x--; break;
		case Act_Quit: playing = false; break;
		case Act_Wait: break;
		case Act_None: break;
	}
}

Action key_to_action(Key code) {
	// TODO: add key rebinding
	switch (code) {
		case Key_h: return Act_Movewest;
		case Key_j: return Act_Movesouth;
		case Key_k: return Act_Movenorth;
		case Key_l: return Act_Moveeast;
		case Key_q: return Act_Quit;
		//case _PERIOD: return Act_Wait;
		default: return Act_None;
	}
}
Action do_ai() {
	return rnb(Act_Quit);
}

i32 main(void) {
	Windowprocs procs;
	if (false) {
		procs = curses_windowprocs;
	} else {
		procs = blt_windowprocs;
	}

	seed_random(cast(u128)cast(usz)&seed_random, getpid());

	if (!procs.init()) {
		printf("Failed to open terminal!  Sorry...");
		return -1;
	}
	procs.blit();

	struct {
		Being *beings;
		usz num_beings;
	} beings = {
		.beings = alloc(sizeof(Being) * 2),
		.num_beings = 2,
	};

	beings.beings[0] = new_user(BeingSpec_DefaultUser);

	beings.beings[1] = new_mon(BeingSpec_Orc);
	beings.beings[1].base.x = beings.beings[1].base.y = 8;

	while (playing) {
		procs.clear();

		for (usz i = 0; i < beings.num_beings; i++) {
			if (beings.beings[i].type == Being_User) {
				apply_action(&beings.beings[i], key_to_action(procs.read()));
			} else {
				apply_action(&beings.beings[i], do_ai());
			}
		}

		for (usz i = 0; i < beings.num_beings; i++) {
			Being b = beings.beings[i];
			procs.write(b.base.glyph, b.base.y, b.base.x, b.base.fg, b.base.bg, false, false, false);
		}

		procs.blit();


	}


	procs.quit();
}
