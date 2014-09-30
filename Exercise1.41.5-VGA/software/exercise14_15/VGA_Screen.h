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
	void init();
	void draw_character(alt_up_char_buffer_dev* char_buffer);
	void draw_diagonal_line(alt_up_pixel_buffer_dma_dev* pixel_buffer);
	void draw_boxes(alt_up_pixel_buffer_dma_dev* pixel_buffer);
	void paint_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer);
	void clear_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer);

	alt_up_pixel_buffer_dma_dev *pixel_buffer;
	alt_up_char_buffer_dev *char_buffer;
private:


	// Private Methods
	alt_up_pixel_buffer_dma_dev* init_pixel_buffer();
	alt_up_char_buffer_dev* init_char_buffer();
};

#endif /* VGA_SCREEN_H_ */
