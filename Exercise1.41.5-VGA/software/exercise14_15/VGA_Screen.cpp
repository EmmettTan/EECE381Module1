/*
 * VGA_Screen.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: Emmett
 */

#include "VGA_Screen.h"

// Constructor
VGA_Screen::VGA_Screen() {
	printf("Constructing VGA Screen \n");
	this->pixel_buffer = init_pixel_buffer();
	this->char_buffer = init_char_buffer();
}

// Make sure you call this when creating a VGA_Screen object
void VGA_Screen::init() {
	printf("Initializing VGA Screen \n");
	if (this->pixel_buffer == 0) {
		printf(
				"error initializing pixel buffer (check name in alt_up_pixel_buffer_dma_open_dev)\n");
		return;
	}
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
			PIXEL_BUFFER_BASE);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
		;
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
}


// TODO Draw a character, needs to take in input
void VGA_Screen::draw_character(alt_up_char_buffer_dev* char_buffer) {
	printf("Drawing Character \n");
	alt_up_char_buffer_string(char_buffer, "eece381", 40, 30);
}

// Not sure if this will be useful or not, but kept it anyways
void VGA_Screen::draw_diagonal_line(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Drawing Diagonal Line \n");
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 0, 0, 320, 240, 0x00ff, 0);
}

// TODO take coordinate and draw box to appropriate place
void VGA_Screen::draw_boxes(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Drawing Boxes \n");
	IOWR_32DIRECT(drawer_base, 0, 0);
	// Set x1
	IOWR_32DIRECT(drawer_base, 4, 0);
	// Set y1
	IOWR_32DIRECT(drawer_base, 8, 20);
	// Set x2
	IOWR_32DIRECT(drawer_base, 12, 20);
	// Set y2
	IOWR_32DIRECT(drawer_base, 16, 0x00FF);
	// Set colour
	IOWR_32DIRECT(drawer_base, 20, 1);
	// Start drawing
	while (IORD_32DIRECT(drawer_base,20) == 0)
		; // wait until done
}

// paints screen black, you can change color in coding
void VGA_Screen::paint_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Painting Screen White \n");
	IOWR_32DIRECT(drawer_base, 0, 0);
	// Set x1
	IOWR_32DIRECT(drawer_base, 4, 0);
	// Set y1
	IOWR_32DIRECT(drawer_base, 8, 320);
	// Set x2
	IOWR_32DIRECT(drawer_base, 12, 240);
	// Set y2
	IOWR_32DIRECT(drawer_base, 16, 0x0000);
	// Set colour
	IOWR_32DIRECT(drawer_base, 20, 1);
	// Start drawing
	while (IORD_32DIRECT(drawer_base,20) == 0)
		; // wait until done
}

// Clears screen. Can't clear characters, needs to be checked out
void VGA_Screen::clear_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Clearing Screen \n");
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

}

//Private Methods. Does not need to be changed, called by the init() function
alt_up_pixel_buffer_dma_dev* VGA_Screen::init_pixel_buffer() {
	printf("Initializing Pixel Buffer \n");
	alt_up_pixel_buffer_dma_dev* pixel_buffer_temp =
			alt_up_pixel_buffer_dma_open_dev("/dev/buffer_dma");
	return pixel_buffer_temp;
}

alt_up_char_buffer_dev* VGA_Screen::init_char_buffer() {
	printf("Initializing Char Buffer \n");
	alt_up_char_buffer_dev* char_buffer;
	char_buffer = alt_up_char_buffer_open_dev(
			"/dev/video_character_buffer_with_dma_0");
	alt_up_char_buffer_init(char_buffer);
	return char_buffer;

}
