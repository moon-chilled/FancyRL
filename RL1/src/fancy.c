#include <unistd.h>

#include "fancy.h"

#include "being.h"
#include "graphics.h"
#include "tile.h"


static bool playing = true;

u32 apply_action(Being *b, Action act, Map map) {
	u32 energy_consumed = 0;

	enum { None, Move, Wait, Other } act_type = None;
	i8 deltax = 0, deltay = 0;

	switch (act) {
		case Act_Movenorth: deltay = -1; act_type = Move; break;
		case Act_Movesouth: deltay = 1; act_type = Move; break;
		case Act_Moveeast: deltax = 1; act_type = Move; break;
		case Act_Movewest: deltax = -1; act_type = Move; break;
		case Act_Movenorthwest: deltax = -1; deltay = -1; act_type = Move; break;
		case Act_Movenortheast: deltax = 1; deltay = -1; act_type = Move; break;
		case Act_Movesouthwest: deltax = -1; deltay = 1; act_type = Move; break;
		case Act_Movesoutheast: deltax = 1; deltay = 1; act_type = Move; break;
		case Act_Quit: playing = false; act_type = Other; break;
		case Act_Wait: act_type = Wait; break;
		case Act_None: act_type = None; break;
	}
	switch (act_type) {
		case None: energy_consumed = 0; break;
		case Move: {
			bool move_successful = false;
			i32 newx = b->base.x + deltax;
			i32 newy = b->base.y + deltay;

			if (newx < 0 || newy < 0
				|| cast(u32)newx >= map.width || cast(u32)newy >= map.height
				|| map.tiles[newy][newx].blocks_traversal) {
				move_successful = false;
			} else {
				move_successful = true;
			}

			if (move_successful) {
				b->base.x = newx;
				b->base.y = newy;
				energy_consumed = 10;
			} else {
				energy_consumed = 0;
			}
			break;
		}
		case Wait: energy_consumed = 8; break;
		case Other: break;
	}

	return energy_consumed;
}

Action key_to_action(Key code) {
	// TODO: add key rebinding
	switch (code) {
		case Key_h: return Act_Movewest;
		case Key_j: return Act_Movesouth;
		case Key_k: return Act_Movenorth;
		case Key_l: return Act_Moveeast;
		case Key_y: return Act_Movenorthwest;
		case Key_u: return Act_Movenortheast;
		case Key_b: return Act_Movesouthwest;
		case Key_n: return Act_Movesoutheast;
		case Key_q: return Act_Quit;
		case Key_period: return Act_Wait;
		default: return Act_None;
	}
}
Action do_ai() {
	return rnb(Act_Quit);
}
typedef struct {
	Being *beings;
	usz num_beings;
} Beings;

void refresh(Windowprocs procs, Beings beings, Map map) {
	//terrain
	for (usz y = 0; y < 25; y++) {
		for (usz x = 0; x < 80; x++) {
			procs.write(map.tiles[y][x].glyph, y, x, 0xaaaaaa, map.tiles[y][x].blocks_light * 0x774400, map.tiles[y][x].blocks_traversal, false, false);
		}
	}

	//beings
	for (usz i = 0; i < beings.num_beings; i++) {
		Being b = beings.beings[i];
		procs.write(b.base.glyph, b.base.y, b.base.x, b.base.fg, b.base.bg, false, false, false);
	}

	procs.blit();
}


i32 main(void) {
	Windowprocs procs;
	if (0) {
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

	Beings beings = {
		.beings = new(Being, 2),
		.num_beings = 2,
	};

	beings.beings[0] = new_user(BeingSpec_DefaultUser);

	beings.beings[1] = new_mon(BeingSpec_Orc);
	beings.beings[1].base.x = beings.beings[1].base.y = 8;

	Map map = new_map(25, 80);
	for (usz y = 0; y < 25; y++) {
		for (usz x = 0; x < 80; x++) {
			if (rnb(3)) {
				map.tiles[y][x] = tile_specs[Tile_Space];
			} else {
				map.tiles[y][x] = tile_specs[Tile_Rock];
			}
		}
	}

	while (playing) {
		refresh(procs, beings, map);
		procs.clear();

		/// input/processing
		// Basic processing loop goes like this:
		// Give each monster as much energy as it has speed
		// Loop through all the monsters
		// Ask them to perform an action
		// If it didn't take any energy, ask them for another
		// Otherwise, decrement their total energy for the turn by the amount of energy it took and go on to the next monster
		// Loop through all the monsters over and over again until everyone has negative energy ('too exhausted to do anything more')

		// dole out energy
		for (usz i = 0; i < beings.num_beings; i++) {
			beings.beings[i].base.energy += beings.beings[i].base.speed;
		}


		bool any_monster_still_has_energy = true;
		while (any_monster_still_has_energy) {
			any_monster_still_has_energy = false;

			for (usz i = 0; i < beings.num_beings; i++) {
				if (beings.beings[i].base.energy <= 0) {
					continue;
				}

				u32 energy_spent = 0;

				while (energy_spent == 0) {
					Action act = (beings.beings[i].type == Being_User) ? key_to_action(procs.read()) : do_ai();
					if (act == Act_Quit) goto quit;
					energy_spent = apply_action(&beings.beings[i], act, map);
					beings.beings[i].base.energy -= energy_spent;

					refresh(procs, beings, map);
				}

				any_monster_still_has_energy = true;
			}
		}
	}

quit:

	procs.quit();

	for (usz i = 0; i < beings.num_beings; i++) delete_being(beings.beings[i]);
	free(beings.beings);
	delete_map(map);
}
