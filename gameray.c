#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <raylib.h>
#include "gameutils.h"

#define TITLE "snake"

void set_snake_intial_position(game_resource *game_res)
{
	game_res->is_map_loaded = MAP_NOT_LOADED;
	float start_x = 460, start_y = 300, end_x = 420, end_y = 300;
	for(int i=0; i<4; i++){
		game_res->snake.snake_block[i].start_pos = (Vector2){start_x, start_y};
		game_res->snake.snake_block[i].end_pos = (Vector2){end_x, end_y};
		game_res->snake.snake_block[i].block_direction = BLOCK_RIGHT;
		start_x -= 40;
		end_x -= 40;	
	}
}

int main(void)
{
	float fontsize = 50;
	char title_text[] = "Hello, How are you?";
	int title_text_len = strlen(title_text);
	printf("len of disp string:\t%d\n",title_text_len);
	

	Vector2 pos2, org2, line_start_pos, line_end_pos;
	// pos2.x = (float)SCREENWIDTH/2 - ((float)title_text_len * (float)fontsize)/4;
	pos2.x = (float)SCREENWIDTH/2 - 50;
	pos2.y = (float)SCREENHEIGHT/2;
	org2.x = 200;
	org2.y = 0;
	line_start_pos.x = 0;
	line_start_pos.y = SCREENHEIGHT;
    line_end_pos.x = SCREENWIDTH;
    line_end_pos.y = SCREENHEIGHT;

	InitWindow(SCREENWIDTH, SCREENHEIGHT, TITLE);

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------
	int rotation = 0;
	bool drawtext = true;
	float snake_start_pos_x = 300;
	Image map;
	game_resource game_res;
	set_snake_intial_position(&game_res);
	
	Color *map_colors;
	int pixel_index;
	bool keypressed = false;
	int update_speed=60;
	int inital_count = 0;
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		// rotation = (rotation + 10) % 360;
		if(drawtext){fontsize = fontsize + 0.1;}
		if(fontsize >= 60.0){drawtext=false;}
		pos2.x = pos2.x - 0.3;
	    // Draw
	    BeginDrawing();
	    ClearBackground(BLACK);
	    if (drawtext){DrawTextPro(GetFontDefault(),title_text, pos2, org2, rotation, fontsize, 10, MAROON);}
	    else{
	    	inital_count += 1;
	    	game_res.level = LEVEL_1;
	    	make_map(&game_res);
	    	if(game_res.is_map_loaded == MAP_NOT_LOADED){game_res.is_map_loaded = MAP_LOADED;}	    	
	    	// make_snake((Vector2){snake_start_pos_x, 300}, (Vector2){snake_start_pos_x + 160, 300}, RED);
	    	make_snake(&game_res, 0, RED);
	    	if(inital_count%60 ==0)
	    	{
	    		make_snake(&game_res, 40, RED);
	    		snake_start_pos_x += 40;
	    		inital_count = 0;
	    	}
	    	if(IsKeyPressed(KEY_UP))
	    	{
	    		printf("UP Key Pressed\n");
	    		make_keypress_node(KEY_UP, &game_res);
	    		traverse_keypress();
	    	}else if(IsKeyPressed(KEY_DOWN))
	    	{
	    		printf("Down Key Pressed\n");
	    		make_keypress_node(KEY_DOWN, &game_res);
	    		traverse_keypress();
	    	}else if(IsKeyPressed(KEY_RIGHT))
	    	{
	    		printf("Right Key Pressed\n");
	    		make_keypress_node(KEY_RIGHT, &game_res);
	    		traverse_keypress();
	    	}else if(IsKeyPressed(KEY_LEFT))
	    	{
	    		printf("Left Key Pressed\n");
	    		make_keypress_node(KEY_LEFT, &game_res);
	    		traverse_keypress();
	    	}
	    }
			    
	    EndDrawing();

	    if(game_res.is_map_loaded == MAP_LOADED)
	    {
	    	map = LoadImageFromScreen();	
	    	map_colors = LoadImageColors(map);
	    	game_res.is_map_loaded = MAP_LOADED_AND_SAVED;
	    }
	    if(game_res.is_map_loaded == MAP_LOADED_AND_SAVED)
	    {
	    	if((game_res.snake.snake_block[0].block_direction == BLOCK_LEFT) || (game_res.snake.snake_block[0].block_direction == BLOCK_RIGHT)){
	    		pixel_index = (map.width*game_res.snake.snake_block[0].start_pos.y) + game_res.snake.snake_block[0].start_pos.x;
	    		if(map_colors[pixel_index].r!=BLACK.r && map_colors[pixel_index].g!=BLACK.g || map_colors[pixel_index].b!=BLACK.b){
	    			printf("Index is:%d\t%u\t%u\t%u\n", pixel_index,map_colors[pixel_index].r, map_colors[pixel_index].g, map_colors[pixel_index].b);
	    			set_snake_intial_position(&game_res);
	    			delete_all_keypress_node();

	    		}
	    	}else{
	    		pixel_index = (map.width*game_res.snake.snake_block[0].start_pos.y) + game_res.snake.snake_block[0].start_pos.x;
	    		if(map_colors[pixel_index].r!=BLACK.r && map_colors[pixel_index].g!=BLACK.g || map_colors[pixel_index].b!=BLACK.b){
	    			printf("Index is:%d\t%u\t%u\t%u\n", pixel_index,map_colors[pixel_index].r, map_colors[pixel_index].g, map_colors[pixel_index].b);
	    			set_snake_intial_position(&game_res);
	    			delete_all_keypress_node();

	    		}
	    	}
	    	

	  	}
    	

	    //----------------------------------------------------------------------------------
	    
	}


	delete_all_keypress_node();
	UnloadImage(map);
	UnloadImageColors(map_colors);
	return 0;	
}