#include "raylib.h"
#include <assert.h>
#include <stdbool.h>
#include "gameutils.h"
#include <stdio.h>
#include <stdlib.h>
key_press_q_t *key_q_head = NULL, *key_q_tail = NULL;

void make_keypress_node(KeyboardKey key, game_resource *game_res)
{
	
	if(key_q_tail == NULL && key_q_head == NULL)
	{
		if((game_res->snake.snake_block[0].block_direction == BLOCK_UP || game_res->snake.snake_block[0].block_direction == BLOCK_DOWN) && (key == KEY_RIGHT || key == KEY_LEFT)){
			printf("NULL condition\n");
			key_press_q_t *node = (key_press_q_t *)malloc(sizeof(key_press_q_t));
			key_q_tail = node;
			key_q_head = node;
			key_q_tail->key = key;
			key_q_tail->rc = game_res->snake.snake_len;
			key_q_tail->next = NULL;

		}else if((game_res->snake.snake_block[0].block_direction == BLOCK_LEFT || game_res->snake.snake_block[0].block_direction == BLOCK_RIGHT) && (key == KEY_UP || key == KEY_DOWN)){
			printf("NULL condition\n");
			key_press_q_t *node = (key_press_q_t *)malloc(sizeof(key_press_q_t));
			key_q_tail = node;
			key_q_head = node;
			key_q_tail->key = key;
			key_q_tail->rc = game_res->snake.snake_len;
			key_q_tail->next = NULL;
		}
		
	}else if((key_q_tail->key == KEY_UP || key_q_tail->key == KEY_DOWN) && (key == KEY_RIGHT || key == KEY_LEFT)){
			key_press_q_t *node = (key_press_q_t *)malloc(sizeof(key_press_q_t));
			printf("condition satisfied\n");
			key_q_tail->next = node;
			key_q_tail = key_q_tail->next;
			key_q_tail->key = key;
			key_q_tail->rc = game_res->snake.snake_len;
			key_q_tail->next = NULL;

	}else if((key_q_tail->key == KEY_LEFT || key_q_tail->key == KEY_RIGHT) && (key == KEY_UP || key == KEY_DOWN)){
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
	int moved_block[MAXLEN], moved_block_iter=0;
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
		for(int i=0; i<gr->snake.snake_len; i++){
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
			traverse_snake_block = &gr->snake.snake_block[gr->snake.snake_len - traverse_ptr->rc];
			bool already_moved = false;
			for(int k=0; k<moved_block_iter; k++){
				if((gr->snake.snake_len- traverse_ptr->rc) == moved_block[k]){
					already_moved = true;
				}
			}
			if(already_moved == false){
				moved_block[moved_block_iter] = gr->snake.snake_len - traverse_ptr->rc;
				moved_block_iter+=1;
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


        for(int i=0; i<gr->snake.snake_len; i++){
        	bool run_switch = true;
        	for (int j=0; j<moved_block_iter; j++){
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
	Vector2 temp_vec_start, temp_vec_end;

	//to make it a block rather than a line
	for(int i=0; i<gr->snake.snake_len;i++){

		if(gr->snake.snake_block[i].start_pos.x > gr->snake.snake_block[i].end_pos.x){
			temp_vec_start.x = gr->snake.snake_block[i].start_pos.x;
			temp_vec_end.x = gr->snake.snake_block[i].end_pos.x + 10;
			temp_vec_start.y = gr->snake.snake_block[i].start_pos.y;
			temp_vec_end.y = gr->snake.snake_block[i].end_pos.y;
		}else if(gr->snake.snake_block[i].start_pos.x < gr->snake.snake_block[i].end_pos.x){
			temp_vec_start.x = gr->snake.snake_block[i].start_pos.x;
			temp_vec_end.x = gr->snake.snake_block[i].end_pos.x - 10;
			temp_vec_start.y = gr->snake.snake_block[i].start_pos.y;
			temp_vec_end.y = gr->snake.snake_block[i].end_pos.y;
		}else if(gr->snake.snake_block[i].start_pos.y > gr->snake.snake_block[i].end_pos.y){
			temp_vec_start.y = gr->snake.snake_block[i].start_pos.y;
			temp_vec_end.y = gr->snake.snake_block[i].end_pos.y - 10;
			temp_vec_start.x = gr->snake.snake_block[i].start_pos.x;
			temp_vec_end.x = gr->snake.snake_block[i].end_pos.x;
		}else if(gr->snake.snake_block[i].start_pos.y > gr->snake.snake_block[i].end_pos.y){
			temp_vec_start.y = gr->snake.snake_block[i].start_pos.y;
			temp_vec_end.y = gr->snake.snake_block[i].end_pos.y + 10;
			temp_vec_start.x = gr->snake.snake_block[i].start_pos.x;
			temp_vec_end.x = gr->snake.snake_block[i].end_pos.x;
		}


		DrawLineEx(temp_vec_start, temp_vec_end, 30, color);
	}
}

bool check_collision(game_resource *game_res)
{
	int pixel_index;
	pixel_index = (game_res->image_map.width*game_res->snake.snake_block[0].start_pos.y) + game_res->snake.snake_block[0].start_pos.x;
	if(game_res->image_map_colors[pixel_index].r!=BLACK.r && game_res->image_map_colors[pixel_index].g!=BLACK.g || game_res->image_map_colors[pixel_index].b!=BLACK.b){
		printf("Index is:%d\t%u\t%u\t%u\n", pixel_index,game_res->image_map_colors[pixel_index].r, game_res->image_map_colors[pixel_index].g, game_res->image_map_colors[pixel_index].b);
		return true;
	}
	return false;
}