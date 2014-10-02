/*
 * Bomb.h
 *
 *  Created on: 2014-10-01
 *      Author: Lucas
 */

#ifndef BOMB_H_
#define BOMB_H_


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "VGA_Screen.h"

#define TIME_TO_EXPLODE 35
#define EXPLOSION_DELAY 5

class Bomb{
	private:
		bool active;
		int timer;
		int x_cord;
		int y_cord;
	public:
		Bomb();
		bool isActive();
		void place_bomb(int x_cord, int y_cord);
		bool check_explosion(VGA_Screen& vga); // increments timer and checks if it had exploded
		int get_x_cord();
		int get_y_cord();
};



#endif /* BOMB_H_ */
