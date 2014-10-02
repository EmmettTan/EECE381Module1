/*
 * Bomb.cpp
 *
 *  Created on: 2014-10-01
 *      Author: Lucas
 */

#include "Bomb.h"


Bomb::Bomb(){
	active = false;
	timer = 0;
}

void Bomb::place_bomb(int x_cord, int y_cord){
	if(!active){
		this->x_cord = x_cord;
		this->y_cord = y_cord;
		timer = 0;
		active = true;
		printf("BOMB PLACED\n");
	}
	else{
		printf("CAN'T PLACE BOMB\n");
	}
}

bool Bomb::check_explosion(VGA_Screen& vga){
	if(active){
		timer++;
		if (timer < TIME_TO_EXPLODE){
			return false;
		}
		else if (timer < TIME_TO_EXPLODE + EXPLOSION_DELAY){
			//vga.draw_explosion(x_cord, y_cord)
			printf("EXPLOSION!!");
			return false;
		}
		else{
			printf("CHECK EXPLOSION!!");
			active = false;
			return true;
		}
	}
	return false;
}

bool Bomb::isActive(){
	return active;
}

int Bomb::get_x_cord(){
	return x_cord;
}

int Bomb::get_y_cord(){
	return y_cord;
}

