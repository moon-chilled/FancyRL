#ifndef TILE_H
#define TILE_H

typedef enum {
	Tile_Space,
	Tile_Rock,

	_Tile_max,
} TileType;

typedef struct {
	u32 glyph;
	bool blocks_traversal, blocks_light;
} Tile;

typedef struct {
	u32 width, height;
	Tile **tiles;
} Map;

extern Map new_map(u32 height, u32 width);
extern void delete_map(Map map);
extern Tile tile_specs[_Tile_max];

#endif //TILE_H
