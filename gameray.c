#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include "gameutils.h"

#define TITLE "snake"

void set_snake_intial_position(game_resource *game_res)
{
	game_res->is_map_loaded = MAP_NOT_LOADED;
	
	float start_x = 450, start_y = 300, end_x = 420, end_y = 300;
	for(int i=game_res->snake.snake_len-1; i>=0; i--){
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
	char title_text[] = "---SNAKE---";
	int title_text_len = strlen(title_text);
	printf("len of disp string:\t%d\n",title_text_len);
	

	Vector2 pos2, org2, line_start_pos, line_end_pos;
	// pos2.x = (float)SCREENWIDTH/2 - ((float)title_text_len * (float)fontsize)/4;
	pos2.x = (float)SCREENWIDTH/2 ;
	pos2.y = (float)SCREENHEIGHT/2;
	org2.x = 200;
	org2.y = 0;
	line_start_pos.x = 0;
	line_start_pos.y = SCREENHEIGHT;
    line_end_pos.x = SCREENWIDTH;
    line_end_pos.y = SCREENHEIGHT;


              
	int rotation = 0;
	bool drawtext = true;
	float snake_start_pos_x = 300;
	game_resource game_res;

	game_res.map.start_pos = (Vector2 *)malloc(10*sizeof(Vector2));
	game_res.map.end_pos = (Vector2 *)malloc(10*sizeof(Vector2));
	game_res.map.color = (Color *)malloc(10*sizeof(Color));
	game_res.map.thickness = (float *)malloc(10*sizeof(float));
	game_res.level = LEVEL_1;
	game_res.snake.snake_len = 4;
	game_res.coin.block_center = (Vector2){700, 400};
	set_map(&game_res);
	set_snake_intial_position(&game_res);

	int pixel_index;
	bool keypressed = false;
	int update_frame=30;
	int inital_count = 0;
	bool collision=false;
	bool collision_coin = false;

	InitWindow(SCREENWIDTH, SCREENHEIGHT, TITLE);
	SetTargetFPS(60); 
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
	    	make_map(&game_res);
	    	if(game_res.is_map_loaded == MAP_NOT_LOADED){game_res.is_map_loaded = MAP_LOADED;}	    	
	    	if(game_res.is_map_loaded == MAP_LOADED_AND_SAVED){
	    		make_snake(&game_res, 0, RED);
	    		make_coin(&game_res, collision_coin);
	    		if(collision_coin == true){
	    			if(update_frame > 2){
	    				update_frame = update_frame - 1;
	    			}
	    			
	    			collision_coin = false;
	    		}

	    		if(inital_count%update_frame ==0)
	    		{
	    			printf(" update_frame %d\n",update_frame);
	    			make_snake(&game_res, 40, RED);
	    			snake_start_pos_x += 40;
	    			inital_count = 0;
	    		}
	    		if(IsKeyPressed(KEY_UP))
	    		{
	    			printf("Up Key Pressed\n");
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
	    	
	    }
			    
	    EndDrawing();

	    if(game_res.is_map_loaded == MAP_LOADED)
	    {
	    	game_res.image_map = LoadImageFromScreen();	
	    	game_res.image_map_colors = LoadImageColors(game_res.image_map);
	    	game_res.is_map_loaded = MAP_LOADED_AND_SAVED;
	    }
	    if(game_res.is_map_loaded == MAP_LOADED_AND_SAVED)
	    {	
	    	switch(game_res.snake.snake_block[game_res.snake.snake_len-1].block_direction){

                case BLOCK_UP:{
                	// printf("\nhello up %f\t%f\t%f\t%f\n",game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.x, game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.y - 15, game_res.coin.block_center.x - 15, game_res.coin.block_center.y - 15);
                	collision_coin = CheckCollisionRecs((Rectangle){game_res.snake.snake_block[game_res.snake.snake_len - 1].start_pos.x - 30, game_res.snake.snake_block[game_res.snake.snake_len - 1].start_pos.y, 35, 35},(Rectangle){game_res.coin.block_center.x - 15, game_res.coin.block_center.y - 15, 40, 40});
                	break;
                }
                case BLOCK_DOWN:{
                	// printf("\nhello down %f\t%f\t%f\t%f\n",game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.x, game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.y - 15, game_res.coin.block_center.x - 15, game_res.coin.block_center.y - 15);
                	collision_coin = CheckCollisionRecs((Rectangle){game_res.snake.snake_block[game_res.snake.snake_len - 1].start_pos.x - 30, game_res.snake.snake_block[game_res.snake.snake_len - 1].start_pos.y, 35, 35},(Rectangle){game_res.coin.block_center.x - 15, game_res.coin.block_center.y - 15, 40, 40});
                	break;
                }
                case BLOCK_RIGHT:{
                	// printf("\nhello right %f\t%f\t%f\t%f\n",game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.x, game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.y - 15, game_res.coin.block_center.x - 15, game_res.coin.block_center.y - 15);
                	collision_coin = CheckCollisionRecs((Rectangle){game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.x, game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.y - 15, 35, 35},(Rectangle){game_res.coin.block_center.x - 15, game_res.coin.block_center.y - 15, 40, 40});
                	break;
                }
                case BLOCK_LEFT:{
                	// printf("\nhello left %f\t%f\t%f\t%f\n",game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.x, game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.y - 15, game_res.coin.block_center.x - 15, game_res.coin.block_center.y - 15);
                	collision_coin = CheckCollisionRecs((Rectangle){game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.x, game_res.snake.snake_block[game_res.snake.snake_len - 1].end_pos.y - 15, 35, 35},(Rectangle){game_res.coin.block_center.x - 15, game_res.coin.block_center.y - 15, 40, 40});
                	break;
               	}
                
            }
            if(collision_coin){
            	printf("collision detected\n");
            }
            if(collision_coin == true){
            	switch(game_res.snake.snake_block[game_res.snake.snake_len -1].block_direction){

                	case BLOCK_UP:{
                		int old_snake_len = game_res.snake.snake_len;
                		int new_snake_len = game_res.snake.snake_len + 1;
                		game_res.snake.snake_block[new_snake_len - 1].start_pos.y = game_res.snake.snake_block[old_snake_len - 1].end_pos.y - 40;
                		game_res.snake.snake_block[new_snake_len - 1].end_pos.y = game_res.snake.snake_block[new_snake_len - 1].start_pos.y;
                		game_res.snake.snake_block[new_snake_len - 1].start_pos.x = game_res.snake.snake_block[old_snake_len - 1].start_pos.x;
                		game_res.snake.snake_block[new_snake_len - 1].end_pos.x = game_res.snake.snake_block[old_snake_len - 1].end_pos.x;
                		game_res.snake.snake_block[new_snake_len - 1].block_direction = BLOCK_UP;

                		game_res.snake.snake_len +=1;

                		break;
                	}
                	case BLOCK_DOWN:{
                		int old_snake_len = game_res.snake.snake_len;
                		int new_snake_len = game_res.snake.snake_len + 1;
                		game_res.snake.snake_block[new_snake_len - 1].start_pos.y = game_res.snake.snake_block[old_snake_len - 1].end_pos.y + 40;
                		game_res.snake.snake_block[new_snake_len - 1].end_pos.y = game_res.snake.snake_block[new_snake_len - 1].start_pos.y;
                		game_res.snake.snake_block[new_snake_len - 1].start_pos.x = game_res.snake.snake_block[old_snake_len - 1].start_pos.x;
                		game_res.snake.snake_block[new_snake_len - 1].end_pos.x = game_res.snake.snake_block[old_snake_len - 1].end_pos.x;
                		game_res.snake.snake_block[new_snake_len - 1].block_direction = BLOCK_DOWN;

                		game_res.snake.snake_len +=1;

                		break;
                	}
                	case BLOCK_RIGHT:{
                		int old_snake_len = game_res.snake.snake_len;
                		int new_snake_len = game_res.snake.snake_len + 1;
                		game_res.snake.snake_block[new_snake_len - 1].end_pos.x = game_res.snake.snake_block[old_snake_len - 1].start_pos.x + 10;
                		game_res.snake.snake_block[new_snake_len - 1].start_pos.x = game_res.snake.snake_block[new_snake_len - 1].end_pos.x + 30;
                		game_res.snake.snake_block[new_snake_len - 1].start_pos.y = game_res.snake.snake_block[old_snake_len - 1].end_pos.y;
                		game_res.snake.snake_block[new_snake_len - 1].end_pos.y = game_res.snake.snake_block[old_snake_len - 1].end_pos.y;
                		game_res.snake.snake_block[new_snake_len - 1].block_direction = BLOCK_RIGHT;

                		game_res.snake.snake_len +=1;
                		break;
                	}
                	case BLOCK_LEFT:{
                		int old_snake_len = game_res.snake.snake_len;
                		int new_snake_len = game_res.snake.snake_len + 1;
                		game_res.snake.snake_block[new_snake_len - 1].start_pos.x = game_res.snake.snake_block[old_snake_len - 1].end_pos.x - 10;
                		game_res.snake.snake_block[new_snake_len - 1].end_pos.x = game_res.snake.snake_block[new_snake_len - 1].start_pos.x - 30;
                		game_res.snake.snake_block[new_snake_len - 1].start_pos.y = game_res.snake.snake_block[old_snake_len - 1].end_pos.y;
                		game_res.snake.snake_block[new_snake_len - 1].end_pos.y = game_res.snake.snake_block[old_snake_len - 1].end_pos.y;
                		game_res.snake.snake_block[new_snake_len - 1].block_direction = BLOCK_LEFT;

                		game_res.snake.snake_len +=1;
                		break;
                	}
                  	default:{break;}
                }
            }

	    	collision = check_collision(&game_res);
	    	if(collision == true){
	    		update_frame=30;
	    		set_snake_intial_position(&game_res);
	    		delete_all_keypress_node();
	    		UnloadImage(game_res.image_map);
	    		UnloadImageColors(game_res.image_map_colors);
	    	}
	    	
	  	}
    	

	    //----------------------------------------------------------------------------------
	    
	}


	//free used memory
	delete_all_keypress_node();
	UnloadImage(game_res.image_map);
	UnloadImageColors(game_res.image_map_colors);
	free(game_res.map.start_pos);
	free(game_res.map.end_pos);
	free(game_res.map.color);
	free(game_res.map.thickness);
	return 0;	
}