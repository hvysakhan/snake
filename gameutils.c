#include "raylib.h"
#include <assert.h>
#include <stdbool.h>
#include "gameutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
key_press_q_t *key_q_head = NULL, *key_q_tail = NULL;

void make_keypress_node(KeyboardKey key, game_resource *game_res)
{
	
	if(key_q_tail == NULL && key_q_head == NULL)
	{
		if((game_res->snake.snake_block[game_res->snake.snake_len - 1].block_direction == BLOCK_UP || game_res->snake.snake_block[game_res->snake.snake_len - 1].block_direction == BLOCK_DOWN) && (key == KEY_RIGHT || key == KEY_LEFT)){
			printf("NULL condition\n");
			key_press_q_t *node = (key_press_q_t *)malloc(sizeof(key_press_q_t));
			key_q_tail = node;
			key_q_head = node;
			key_q_tail->key = key;
			key_q_tail->rc = game_res->snake.snake_len;
			key_q_tail->next = NULL;

		}else if((game_res->snake.snake_block[game_res->snake.snake_len - 1].block_direction == BLOCK_LEFT || game_res->snake.snake_block[game_res->snake.snake_len - 1].block_direction == BLOCK_RIGHT) && (key == KEY_UP || key == KEY_DOWN)){
			printf("NULL condition\n");
			key_press_q_t *node = (key_press_q_t *)malloc(sizeof(key_press_q_t));
			key_q_tail = node;
			key_q_head = node;
			key_q_tail->key = key;
			key_q_tail->rc = game_res->snake.snake_len;
			key_q_tail->next = NULL;
		}
		
	}else if((game_res->snake.snake_block[game_res->snake.snake_len - 1].block_direction == BLOCK_UP || game_res->snake.snake_block[game_res->snake.snake_len - 1].block_direction == BLOCK_DOWN) && (key == KEY_RIGHT || key == KEY_LEFT)){
			key_press_q_t *node = (key_press_q_t *)malloc(sizeof(key_press_q_t));
			printf("condition satisfied\n");
			key_q_tail->next = node;
			key_q_tail = key_q_tail->next;
			key_q_tail->key = key;
			key_q_tail->rc = game_res->snake.snake_len;
			key_q_tail->next = NULL;

	}else if((game_res->snake.snake_block[game_res->snake.snake_len - 1].block_direction == BLOCK_LEFT || game_res->snake.snake_block[game_res->snake.snake_len - 1].block_direction == BLOCK_RIGHT) && (key == KEY_UP || key == KEY_DOWN)){
			key_press_q_t *node = (key_press_q_t *)malloc(sizeof(key_press_q_t));
			printf("condition satisfied\n");
			key_q_tail->next = node;
			key_q_tail = key_q_tail->next;
			key_q_tail->key = key;
			key_q_tail->rc = game_res->snake.snake_len;
			key_q_tail->next = NULL;
	}
		
}

void delete_keypress_node(void)
{
	key_press_q_t *node = key_q_head;
	if(node != NULL)
	{
		key_q_head = key_q_head->next;
		free(node);
	}
	else
	{
		printf("queue already empty\n");
	}
	
}

void delete_all_keypress_node(void)
{
	key_press_q_t *delete_ptr;
	while (key_q_head != NULL)
	{
		delete_ptr = key_q_head;
		key_q_head = key_q_head->next;
		free(delete_ptr);
	}
	key_q_tail = NULL;
	delete_ptr = NULL;
}

void traverse_keypress(void)
{
	key_press_q_t *traverse_ptr = key_q_head;
	while(traverse_ptr!=NULL)
	{
		printf("%d\t", traverse_ptr->key);
		traverse_ptr = traverse_ptr->next;
	}
	printf("\n");
}

void make_block_line(Vector2 start_pos, Vector2 end_pos, int block_length, int block_gap, float thickness, Color color)
{
	assert(((start_pos.x != end_pos.x) && (start_pos.y == end_pos.y)) || ((start_pos.y != end_pos.y) && (start_pos.x == end_pos.x)));
	assert(block_length>0);
	Vector2 temp;
	if((start_pos.x > end_pos.x) || (start_pos.y > end_pos.y)){
		temp = start_pos;
		start_pos = end_pos;
		end_pos = temp;
	}
	if(start_pos.x != end_pos.x)
	{
		
		int num_blocks = (start_pos.x - end_pos.x)/block_length*-1;
		if(block_length*num_blocks < end_pos.x - start_pos.x){num_blocks = num_blocks + 1;}
		Vector2 line_start_pos;
		Vector2 line_end_pos;
		line_start_pos.y = start_pos.y;
		line_end_pos.y = end_pos.y;
		float block_start_x = start_pos.x;
		for (int i=0; i< num_blocks; i++)
		{
			line_start_pos.x = block_start_x;
			line_end_pos.x = block_start_x + block_length - block_gap;
			DrawLineEx(line_end_pos, line_start_pos, thickness, color);
			block_start_x = line_end_pos.x + block_gap;
		}
	}
	else if(start_pos.y != end_pos.y)
	{
		int num_blocks = (start_pos.y - end_pos.y)/block_length* -1;
		// block_length = (start_pos.y - end_pos.y)/num_blocks* -1;
		
		if(block_length*num_blocks < end_pos.y - start_pos.y){num_blocks = num_blocks + 1;}
		Vector2 line_start_pos;
		Vector2 line_end_pos;
		line_start_pos.x = start_pos.x;
		line_end_pos.x = end_pos.x;
		float block_start_y = start_pos.y;
		for (int i=0; i< num_blocks; i++)
		{
			line_start_pos.y = block_start_y;
			line_end_pos.y = block_start_y + block_length - block_gap;
			DrawLineEx(line_start_pos, line_end_pos, thickness, color);
			block_start_y = line_end_pos.y + block_gap;
		}
	}
	
}

void set_map(game_resource *game_res){
	if(game_res->level == LEVEL_1){
		game_res->map.start_pos[0].x = 15;
		game_res->map.start_pos[0].y = 0;
		game_res->map.end_pos[0].x = 15;
		game_res->map.end_pos[0].y = SCREENHEIGHT;

		game_res->map.start_pos[1].x = SCREENWIDTH - 25;
		game_res->map.start_pos[1].y = 0;
		game_res->map.end_pos[1].x = SCREENWIDTH - 25;
		game_res->map.end_pos[1].y = SCREENHEIGHT;

		game_res->map.start_pos[2].x = 0;
		game_res->map.start_pos[2].y = 15;
		game_res->map.end_pos[2].x = SCREENWIDTH;
		game_res->map.end_pos[2].y = 15;

		game_res->map.start_pos[3].x = 0;
		game_res->map.start_pos[3].y = SCREENHEIGHT - 25;
		game_res->map.end_pos[3].x = SCREENWIDTH;
		game_res->map.end_pos[3].y = SCREENHEIGHT - 25;
		
	}
}

void make_map(game_resource *game_res)
{		
	for(int i=0; i<4; i++){
		make_block_line(game_res->map.start_pos[i], game_res->map.end_pos[i], 40, 10, 30, BEIGE);	
	}

}


void make_snake(game_resource *gr, int velocity, Color color)
{
	int snake_len = gr->snake.snake_len;
	int moved_block[MAXLEN], moved_block_iter=MAXLEN - 1;
	for(int i=0;i<MAXLEN;i++){
		moved_block[i] = -1;
	}

	key_press_q_t *traverse_ptr = key_q_head;
	key_press_q_t *delete_ptr = NULL;

	//clean up all used nodes
	while (traverse_ptr != NULL){
		if(traverse_ptr->rc == 0){
			delete_ptr = traverse_ptr;
			traverse_ptr = traverse_ptr->next;
			free(delete_ptr);
		}else{
			break;
		}
	}
	key_q_head = traverse_ptr;
	delete_ptr = NULL;

	if(key_q_head == NULL){
		key_q_tail = NULL;
		for(int i=snake_len-1; i>=0; i--){
			if(gr->snake.snake_block[i].block_direction == BLOCK_RIGHT){
				gr->snake.snake_block[i].start_pos.x +=(float)velocity;
				gr->snake.snake_block[i].end_pos.x += (float)velocity;
			}else if(gr->snake.snake_block[i].block_direction == BLOCK_UP){
				gr->snake.snake_block[i].start_pos.y -=(float)velocity;
				gr->snake.snake_block[i].end_pos.y -= (float)velocity;
			}else if(gr->snake.snake_block[i].block_direction == BLOCK_DOWN){
				gr->snake.snake_block[i].start_pos.y +=(float)velocity;
				gr->snake.snake_block[i].end_pos.y += (float)velocity;
			}else if(gr->snake.snake_block[i].block_direction == BLOCK_LEFT){
				gr->snake.snake_block[i].start_pos.x -=(float)velocity;
				gr->snake.snake_block[i].end_pos.x -= (float)velocity;
			}
		}		
	}else if(velocity > 0){
		while (traverse_ptr != NULL){
			sb *traverse_snake_block;
			printf("traverse_ptr rc is %d \n", traverse_ptr->rc);
			traverse_snake_block = &gr->snake.snake_block[traverse_ptr->rc - 1];
			bool already_moved = false;
			for(int k= MAXLEN -1; k > (MAXLEN-1) - snake_len; k--){
				if((traverse_ptr->rc - 1) == moved_block[k]){
					already_moved = true;
				}
			}
			if(already_moved == false){
				moved_block[moved_block_iter] = traverse_ptr->rc - 1;
				moved_block_iter-=1;
				if(traverse_ptr->key == KEY_RIGHT){
					traverse_snake_block->block_direction = BLOCK_RIGHT;
				}else if(traverse_ptr->key == KEY_LEFT){
					traverse_snake_block->block_direction = BLOCK_LEFT;
				}else if(traverse_ptr->key == KEY_UP){
					traverse_snake_block->block_direction = BLOCK_UP;
				}else if(traverse_ptr->key == KEY_DOWN){
					traverse_snake_block->block_direction = BLOCK_DOWN;
				}

				switch (traverse_snake_block->block_direction){
					float temp;
	                case BLOCK_UP:{
	                	traverse_snake_block->start_pos.y -= (float)velocity;
	                	traverse_snake_block->end_pos.y -= (float)velocity;
	                	break;

	                }
	                case BLOCK_DOWN:{
	                	traverse_snake_block->start_pos.y +=(float)velocity;
	                	traverse_snake_block->end_pos.y += (float)velocity;
	                	break;
	                }
	                case BLOCK_RIGHT:{
	                	traverse_snake_block->start_pos.x +=(float)velocity;
	                	traverse_snake_block->end_pos.x += (float)velocity;
	                	break;
	                }
	                case BLOCK_LEFT:{
	                 	traverse_snake_block->start_pos.x -=(float) velocity;
	                 	traverse_snake_block->end_pos.x -= (float)velocity;
	                 	break;
	                }
	            	default:{
	            		break;
	            	}
	            }
	            traverse_ptr->rc = traverse_ptr->rc - 1;
			}
			            
			traverse_ptr = traverse_ptr->next;
		}


        for(int i=snake_len-1; i>=0; i--){
        	bool run_switch = true;
        	for (int j=MAXLEN -1; j>moved_block_iter; j--){
        		if (moved_block[j] == i){
        			run_switch = false;
        		}
        	}
        	if(run_switch == true){
        		switch (gr->snake.snake_block[i].block_direction){
					float temp;
	                case BLOCK_UP:{
	                	gr->snake.snake_block[i].start_pos.y -= (float)velocity;
	                	gr->snake.snake_block[i].end_pos.y -= (float)velocity;
	                	break;

	                }
	                case BLOCK_DOWN:{
	                	gr->snake.snake_block[i].start_pos.y +=(float)velocity;
	                	gr->snake.snake_block[i].end_pos.y += (float)velocity;
	                	break;
	                }
	                case BLOCK_RIGHT:{
	                	gr->snake.snake_block[i].start_pos.x +=(float)velocity;
	                	gr->snake.snake_block[i].end_pos.x += (float)velocity;
	                	break;
	                }
	                case BLOCK_LEFT:{
	                 	gr->snake.snake_block[i].start_pos.x -=(float) velocity;
	                 	gr->snake.snake_block[i].end_pos.x -= (float)velocity;
	                 	break;
	                }
	            	default:{
	            		break;
	            	}
            	}	
        	}
			
        	
        }

	}
	traverse_ptr = key_q_head;

	for(int i=snake_len -1; i>=0 ;i--){
		DrawLineEx(gr->snake.snake_block[i].start_pos, gr->snake.snake_block[i].end_pos, 30, color);
	}
}

bool check_collision(game_resource *game_res)
{
	int pixel_index;
	pixel_index = (game_res->image_map.width*game_res->snake.snake_block[game_res->snake.snake_len -1].start_pos.y) + game_res->snake.snake_block[game_res->snake.snake_len -1].start_pos.x;
	if(game_res->image_map_colors[pixel_index].r!=BLACK.r && game_res->image_map_colors[pixel_index].g!=BLACK.g || game_res->image_map_colors[pixel_index].b!=BLACK.b){
		printf("Index is:%d\t%u\t%u\t%u\n", pixel_index,game_res->image_map_colors[pixel_index].r, game_res->image_map_colors[pixel_index].g, game_res->image_map_colors[pixel_index].b);
		return true;
	}
	return false;
}

void make_coin(game_resource *game_res, bool collision){
	if(collision == true){
		SetRandomSeed(time(NULL));
		game_res->coin.block_center.x = GetRandomValue(100, SCREENWIDTH - 100);
		game_res->coin.block_center.y = GetRandomValue(100, SCREENHEIGHT - 100);
	}
	
	DrawLineEx((Vector2){game_res->coin.block_center.x-15, game_res->coin.block_center.y},(Vector2){game_res->coin.block_center.x+15, game_res->coin.block_center.y}, 30, VIOLET);

}

bool check_collision_coin(game_resource *game_res){
	int collision_coin = false;
	switch(game_res->snake.snake_block[game_res->snake.snake_len-1].block_direction){

        case BLOCK_UP:{
       
        	collision_coin = CheckCollisionRecs((Rectangle){game_res->snake.snake_block[game_res->snake.snake_len - 1].start_pos.x - 30, game_res->snake.snake_block[game_res->snake.snake_len - 1].start_pos.y, 35, 35},(Rectangle){game_res->coin.block_center.x - 15, game_res->coin.block_center.y - 15, 40, 40});
        	break;
        }
        case BLOCK_DOWN:{
        	
        	collision_coin = CheckCollisionRecs((Rectangle){game_res->snake.snake_block[game_res->snake.snake_len - 1].start_pos.x - 30, game_res->snake.snake_block[game_res->snake.snake_len - 1].start_pos.y, 35, 35},(Rectangle){game_res->coin.block_center.x - 15, game_res->coin.block_center.y - 15, 40, 40});
        	break;
        }
        case BLOCK_RIGHT:{
        	
        	collision_coin = CheckCollisionRecs((Rectangle){game_res->snake.snake_block[game_res->snake.snake_len - 1].end_pos.x, game_res->snake.snake_block[game_res->snake.snake_len - 1].end_pos.y - 15, 35, 35},(Rectangle){game_res->coin.block_center.x - 15, game_res->coin.block_center.y - 15, 40, 40});
        	break;
        }
        case BLOCK_LEFT:{
        	
        	collision_coin = CheckCollisionRecs((Rectangle){game_res->snake.snake_block[game_res->snake.snake_len - 1].end_pos.x, game_res->snake.snake_block[game_res->snake.snake_len - 1].end_pos.y - 15, 35, 35},(Rectangle){game_res->coin.block_center.x - 15, game_res->coin.block_center.y - 15, 40, 40});
        	break;
       	}
        
    }
    return collision_coin;
}

void add_snake_block(game_resource *game_res){
		switch(game_res->snake.snake_block[game_res->snake.snake_len -1].block_direction){

	    	case BLOCK_UP:{
	    		int old_snake_len = game_res->snake.snake_len;
	    		int new_snake_len = game_res->snake.snake_len + 1;
	    		game_res->snake.snake_block[new_snake_len - 1].start_pos.y = game_res->snake.snake_block[old_snake_len - 1].end_pos.y - 40;
	    		game_res->snake.snake_block[new_snake_len - 1].end_pos.y = game_res->snake.snake_block[new_snake_len - 1].start_pos.y;
	    		game_res->snake.snake_block[new_snake_len - 1].start_pos.x = game_res->snake.snake_block[old_snake_len - 1].start_pos.x;
	    		game_res->snake.snake_block[new_snake_len - 1].end_pos.x = game_res->snake.snake_block[old_snake_len - 1].end_pos.x;
	    		game_res->snake.snake_block[new_snake_len - 1].block_direction = BLOCK_UP;

	    		game_res->snake.snake_len +=1;

	    		break;
	    	}
	    	case BLOCK_DOWN:{
	    		int old_snake_len = game_res->snake.snake_len;
	    		int new_snake_len = game_res->snake.snake_len + 1;
	    		game_res->snake.snake_block[new_snake_len - 1].start_pos.y = game_res->snake.snake_block[old_snake_len - 1].end_pos.y + 40;
	    		game_res->snake.snake_block[new_snake_len - 1].end_pos.y = game_res->snake.snake_block[new_snake_len - 1].start_pos.y;
	    		game_res->snake.snake_block[new_snake_len - 1].start_pos.x = game_res->snake.snake_block[old_snake_len - 1].start_pos.x;
	    		game_res->snake.snake_block[new_snake_len - 1].end_pos.x = game_res->snake.snake_block[old_snake_len - 1].end_pos.x;
	    		game_res->snake.snake_block[new_snake_len - 1].block_direction = BLOCK_DOWN;

	    		game_res->snake.snake_len +=1;

	    		break;
	    	}
	    	case BLOCK_RIGHT:{
	    		int old_snake_len = game_res->snake.snake_len;
	    		int new_snake_len = game_res->snake.snake_len + 1;
	    		game_res->snake.snake_block[new_snake_len - 1].end_pos.x = game_res->snake.snake_block[old_snake_len - 1].start_pos.x + 10;
	    		game_res->snake.snake_block[new_snake_len - 1].start_pos.x = game_res->snake.snake_block[new_snake_len - 1].end_pos.x + 30;
	    		game_res->snake.snake_block[new_snake_len - 1].start_pos.y = game_res->snake.snake_block[old_snake_len - 1].end_pos.y;
	    		game_res->snake.snake_block[new_snake_len - 1].end_pos.y = game_res->snake.snake_block[old_snake_len - 1].end_pos.y;
	    		game_res->snake.snake_block[new_snake_len - 1].block_direction = BLOCK_RIGHT;

	    		game_res->snake.snake_len +=1;
	    		break;
	    	}
	    	case BLOCK_LEFT:{
	    		int old_snake_len = game_res->snake.snake_len;
	    		int new_snake_len = game_res->snake.snake_len + 1;
	    		game_res->snake.snake_block[new_snake_len - 1].start_pos.x = game_res->snake.snake_block[old_snake_len - 1].end_pos.x - 10;
	    		game_res->snake.snake_block[new_snake_len - 1].end_pos.x = game_res->snake.snake_block[new_snake_len - 1].start_pos.x - 30;
	    		game_res->snake.snake_block[new_snake_len - 1].start_pos.y = game_res->snake.snake_block[old_snake_len - 1].end_pos.y;
	    		game_res->snake.snake_block[new_snake_len - 1].end_pos.y = game_res->snake.snake_block[old_snake_len - 1].end_pos.y;
	    		game_res->snake.snake_block[new_snake_len - 1].block_direction = BLOCK_LEFT;

	    		game_res->snake.snake_len +=1;
	    		break;
	    	}
	      	default:{
	      		break;
	      	}
	    }
}