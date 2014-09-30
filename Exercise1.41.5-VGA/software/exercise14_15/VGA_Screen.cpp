/*
 * VGA_Screen.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: Emmett
 */

#include "VGA_Screen.h"

//Public Methods
VGA_Screen::VGA_Screen() {
	printf("Constructing VGA Screen \n");
	this->pixel_buffer = init_pixel_buffer();
}

void VGA_Screen::init() {
	printf("Initializing VGA Screen \n");
	if (pixel_buffer == 0) {
		printf("error initializing pixel buffer (check name in alt_up_pixel_buffer_dma_open_dev)\n");
		return;
	}
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,PIXEL_BUFFER_BASE);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
}

void VGA_Screen::draw_character(alt_up_char_buffer_dev* char_buffer) {
	printf("Drawing Character");
}

void VGA_Screen::draw_diagonal_line(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Drawing Diagonal Line");
}

void VGA_Screen::draw_boxes(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Drawing Boxes");
}

void VGA_Screen::clear_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Clearing Screen");
}

//Private Methods
alt_up_pixel_buffer_dma_dev* VGA_Screen::init_pixel_buffer() {
	printf("Initializing Pixel Buffer \n");
	alt_up_pixel_buffer_dma_dev* pixel_buffer_temp =
			alt_up_pixel_buffer_dma_open_dev("/dev/buffer_dma");
	return pixel_buffer_temp;
}

alt_up_char_buffer_dev* VGA_Screen::init_char_buffer() {
	printf("Initializing Char Buffer");

}
