#include "fancy.h"
#include "tile.h"

Map new_map(u32 height, u32 width) {

	Map ret;
	ret.width = width;
	ret.height = height;

	ret.tiles = alloc(sizeof(Tile*) * height);
	for (usz i = 0; i < height; i++) {
		ret.tiles[i] = alloc(sizeof(Tile) * width);
	}

	return ret;
}

Tile tile_specs[_Tile_max] = {
	[Tile_Space] = {u' ', false, false},
	[Tile_Rock] = {u'#', true, true},
};
