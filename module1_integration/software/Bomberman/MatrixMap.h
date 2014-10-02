/*
 * MatrixMap.h
 *
 *  Created on: 2014-09-26
 *      Author: Rayaan Choudri/ Lucas Gomes
 *      matrix representation of map, marks walkable pixels as x and nonwalkable as o
 */

#ifndef MATRIXMAP_H_
#define MATRIXMAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "VGA_Screen.h"

#define SIZE 11

#define PATH 'x'
#define BLOCK 'o' //indestructible
#define BOX 'a' //destructible
#define BOMB 'b'

class MatrixMap{//creates matrix representation of map
	private:

	public:

		char map[SIZE][SIZE];
		MatrixMap();
		MatrixMap(int nrows, int ncols);
		void gen_map();
		void print_matrix();
		void printrow_x();
		void printrow_y();
		char get_cord(int x, int y);
		void check_explosion(int x, int y, VGA_Screen& vga);
};

#endif /* MATRIXMAP_H_ */
