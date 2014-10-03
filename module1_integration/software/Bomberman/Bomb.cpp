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

	in_explosion = false;
	explosion_animation_timer = 0;
}

void Bomb::place_bomb(int x_cord, int y_cord){
	if(!active){
		this->x_cord = x_cord;
		this->y_cord = y_cord;
		explosion_range = 1;
		timer = 0;
		active = true;
		printf("BOMB PLACED\n");
	}
	else{
		printf("CAN'T PLACE BOMB\n");
	}
}

bool Bomb::exploded(){
	if (timer == EXPLOSION_TIME && active){
		active = false;
		in_explosion = true;
		explosion_animation_timer = 0;
		return true;
	}
	else{
		return false;
	}
}

void Bomb::increment_timer(){
	if(active){
		timer++;
	}
}

bool Bomb::isExploding(){
	if(in_explosion && explosion_animation_timer < EXPLOSION_ANIMATION_DELAY){
		explosion_animation_timer++;
		return true;
	}
	else{
		return false;
	}
}

bool Bomb::finishedExploding(){
	if (in_explosion){
		in_explosion = false;
		return true;
	}
	else{
		return false;
	}
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

int Bomb::get_explosion_range(){
	return explosion_range;
}
