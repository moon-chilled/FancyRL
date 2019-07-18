#include "fancy.h"
#include "tile.h"

Map new_map(u32 height, u32 width) {
	Map ret;
	ret.width = width;
	ret.height = height;

	ret.tiles = new(Tile*, height);
	for (usz i = 0; i < height; i++) {
		ret.tiles[i] = new(Tile, width);
	}

	return ret;
}
void delete_map(Map map) {
	for (usz i = 0; i < map.height; i++) free(map.tiles[i]);
	free(map.tiles);
}

Tile tile_specs[_Tile_max] = {
	[Tile_Space] = {u' ', false, false},
	[Tile_Rock] = {u'#', true, true},
};
