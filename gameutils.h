#ifndef GAMEUTILS_H
#define GAMEUTILS_H
#include <raylib.h>

#ifndef SCREENWIDTH
	#define SCREENWIDTH 1280
#endif

#ifndef SCREENHEIGHT
	#define SCREENHEIGHT  720
#endif

#ifndef MAXLEN
	#define MAXLEN 100
#endif

typedef enum{
	MAP_NOT_LOADED,
	MAP_LOADED,
	MAP_LOADED_AND_SAVED
}is_map_loaded;

typedef enum{
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,
	LEVEL_5
}game_level;

typedef enum{
	BLOCK_UP,
	BLOCK_DOWN,
	BLOCK_RIGHT,
	BLOCK_LEFT
}bd;

typedef struct key_press_q_s{
	KeyboardKey key;
	int rc;
	struct key_press_q_s *next;
}key_press_q_t;

typedef struct{
	Vector2 start_pos;
	Vector2 end_pos;
	bd block_direction;
}sb;

typedef struct{
	sb snake_block[MAXLEN];	
	int snake_len;
}snake;

typedef  struct {
	Vector2 *start_pos;
	Vector2 *end_pos;
	Color *color;
	float *thickness;
}map;

typedef struct{
	Vector2 block_center;
	Color color;
}coin;

typedef struct {
	game_level level;
	is_map_loaded is_map_loaded;
	snake snake;
	map map;
	coin coin;
	Image image_map;
	Color *image_map_colors;
}game_resource;



void make_map(game_resource *game_res);
void set_map(game_resource *game_res);
void make_snake(game_resource *gr, int velocity, Color color);
void make_block_line(Vector2 start_pos, Vector2 end_pos, int block_length, int block_gap, float thickness,  Color color);
void make_keypress_node(KeyboardKey key, game_resource *game_res);
void traverse_keypress(void);
void delete_all_keypress_node(void);
bool check_collision(game_resource *game_res);
void make_coin(game_resource *game_res, bool collision);

#endif