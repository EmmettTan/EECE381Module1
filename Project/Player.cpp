/*
 * Player.c
 *
 *  Created on: 2014-09-26
 *  Author: Rayaan Choudri
 *
 *  Contains player movement functions and variables
 */
#include "Player.h"

Player::Player(){//constructor creates player object with position at top left of screen
	 health = 3;
	 x_cord = 0;
	 y_cord = 0;
	 parallel_port_dev = alt_up_parallel_port_open_dev("/dev/parallel_port_0");
	 if (parallel_port_dev == NULL)
	 		printf("Error: could not open Parallel Port device\n");

	 	else
	 		printf("Opened Parallel Port device\n");
}

char Player::get_direction(){
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
bool Player::validate_next_move(char direction){
	//if
	return true;
}
void Player::move(){
	if(get_direction()==UP)
		move_up();
	else if(get_direction()==DOWN)
		move_down();
	else if(get_direction()==RIGHT)
		move_right();
	else if(get_direction()==LEFT)
		move_left();
}
void Player::move_right(){
		printf("Moving right...");
		x_cord++;
}
void Player::move_left(){
		printf("Moving left...");
		x_cord--;
}
void Player::move_up(){
		printf("Moving up...");
		y_cord--;
}
void Player::move_down(){
		printf("Moving down...");
		y_cord++;
}
int Player::get_x_cord(){
	return x_cord;
}
int Player::get_y_cord(){
	return y_cord;
}


