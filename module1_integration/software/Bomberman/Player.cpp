/*
 * Player.c
 *
 *  Created on: 2014-09-26
 *  Author: Rayaan Choudri
 *
 *  Contains player movement functions and variables
 */
#include "Player.h"
#include "MatrixMap.h"

	Player::Player(){//constructor creates player

		 //initialises position and health
		 life = 3;
		 x_cord = 0;
		 y_cord = 0;

		 //initialises parallel port to read from direction from keys
		 parallel_port_dev = alt_up_parallel_port_open_dev("/dev/parallel_port_0");
			 if (parallel_port_dev == NULL)
					printf("Error: could not open Parallel Port device\n");
				 else
					printf("Opened Parallel Port device\n");
	}

	char Player::get_direction(){//returns the direction pressed
		unsigned int key;
		key = alt_up_parallel_port_read_data(parallel_port_dev);

			if (key != 0){
				switch(key){
					case 1:
						return RIGHT;
						break;
					case 2:
						return LEFT;
						break;
					case 4:
						return DOWN;
						break;
					case 8:
						return UP;
						break;
						}
					}
			return STAND;
		}

	void Player::move(char direction, MatrixMap& m){//moves in direction pressed if legal
		//checks matrix map for x's marked as legal areas
			x_old_cord = x_cord;
			y_old_cord = y_cord;
			if(direction == UP && m.get_cord(x_cord, y_cord-1)=='x' && y_cord>0)
					move_up();
			else if(direction == DOWN && m.get_cord(x_cord, y_cord+1)=='x' && y_cord<SIZE-1)
					move_down();
			else if(direction == RIGHT && m.get_cord(x_cord+1, y_cord)=='x' && x_cord<SIZE-1)
					move_right();
			else if(direction == LEFT && m.get_cord(x_cord-1, y_cord)=='x' && x_cord>0)
					move_left();
	}

	//move functions increment or decrement x or y coordinates
	void Player::move_right(){
			x_cord++;
	}
	void Player::move_left(){
			x_cord--;
	}
	void Player::move_up(){
			y_cord--;
	}
	void Player::move_down(){
			y_cord++;
	}

	//getters return x, y coordinates
	int Player::get_x_cord(){
		return x_cord;
	}
	int Player::get_y_cord(){
		return y_cord;
	}

	int Player::get_old_x_cord(){
		return x_old_cord;
	}

	int Player::get_old_y_cord(){
			return y_old_cord;
	}

	void Player::life_down(){
		life--;
		printf("LIFE DOWN!");
		if(life == 0){
			printf("PLAYER HAS DIED");
		}
	}

	void Player::check_damage(std::vector<int> &damaged_blocks){
		for (int i=0; i<damaged_blocks.size(); i+=2){
			if(x_cord == damaged_blocks[i] && y_cord == damaged_blocks[i+1]){
				this->life_down();
				printf("LIFE--");
			}
		}
	}

	void Player::place_bomb(MatrixMap& m){
		if ( IORD_8DIRECT(SWITCHES, 0)%2 == 1){
			bomb.place_bomb(x_cord, y_cord);
			m.map[x_cord][y_cord] = BOMB;
		}
	}

