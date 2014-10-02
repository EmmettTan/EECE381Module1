/*
 * VGA_Screen.h
 *
 *  Created on: Sep 29, 2014
 *      Author: Emmett
 */

#ifndef VGA_SCREEN_H_
#define VGA_SCREEN_H_
#define drawer_base (volatile int *) 0x2100

#include <stdio.h>
#include <string.h>
#include "io.h"
#include <stdlib.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"


class VGA_Screen {

public:
	// Public Methods
	VGA_Screen();

	// initializing methods
	void init();

	// drawing functions
	void draw_character(alt_up_char_buffer_dev* char_buffer);
	void draw_diagonal_line(alt_up_pixel_buffer_dma_dev* pixel_buffer);
	void draw_boxes(alt_up_pixel_buffer_dma_dev* pixel_buffer, int x_0, int x_1, int y_0, int y_1, int color);
	void draw_pattern(alt_up_pixel_buffer_dma_dev* pixel_buffer,int x_0, int y_0, int color);
	void draw_player(alt_up_pixel_buffer_dma_dev* pixel_buffer,int x_0,int y_0, int color);
	// blanking/painting screen
	void paint_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer);
	void clear_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer);

	// Drawing box from coordinate
	void draw_box_from_coordinate(int x, int y, char c);
	void erase_and_redraw_player(int old_x, int old_y, int new_x, int new_y);

	// MAP matrix stuff
	//void draw_map_from_array(MatrixMap& m_map);
	void draw_map_from_array(char m_map[11][11]);
	// buffer variables
	alt_up_pixel_buffer_dma_dev *pixel_buffer;
	alt_up_char_buffer_dev *char_buffer;


private:


	// Private Methods
	alt_up_pixel_buffer_dma_dev* init_pixel_buffer();
	alt_up_char_buffer_dev* init_char_buffer();

};

#endif /* VGA_SCREEN_H_ */
