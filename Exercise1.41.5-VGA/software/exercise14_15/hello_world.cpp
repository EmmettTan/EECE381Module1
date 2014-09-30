#include <stdio.h>
#include <string.h>
#include "io.h"
#include <stdlib.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "VGA_Screen.h"

#define drawer_base (volatile int *) 0x2100
alt_up_pixel_buffer_dma_dev* init_pixel_buffer();
void draw_character(alt_up_char_buffer_dev* char_buffer);
void draw_diagonal_line(alt_up_pixel_buffer_dma_dev* pixel_buffer);
void draw_boxes(alt_up_pixel_buffer_dma_dev* pixel_buffer);
void clear_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer);
alt_up_char_buffer_dev* init_char_buffer();
void ex4();
void ex5();

void ex4() {
	alt_up_pixel_buffer_dma_dev* pixel_buffer;
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/buffer_dma");
	if (pixel_buffer == 0) {
		printf(
				"error initializing pixel buffer (check name in alt_up_pixel_buffer_dma_open_dev)\n");
	}
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
			PIXEL_BUFFER_BASE);
	// Swap background and foreground buffers
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);

	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
		;
	// Clear the screen
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	draw_diagonal_line(pixel_buffer);
	alt_up_char_buffer_dev* char_buffer = init_char_buffer();
	//clear_screen(pixel_buffer);
	draw_character(char_buffer);
}

alt_up_pixel_buffer_dma_dev* init_pixel_buffer() {
	alt_up_pixel_buffer_dma_dev* pixel_buffer;
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/buffer_dma");
	return pixel_buffer;
}

alt_up_char_buffer_dev* init_char_buffer() {
	alt_up_char_buffer_dev* char_buffer;
	char_buffer = alt_up_char_buffer_open_dev(
			"/dev/video_character_buffer_with_dma_0");
	alt_up_char_buffer_init(char_buffer);
	return char_buffer;
}

void clear_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
}

void draw_character(alt_up_char_buffer_dev *char_buffer) {

	alt_up_char_buffer_string(char_buffer, "eece381", 40, 30);

}

void draw_diagonal_line(alt_up_pixel_buffer_dma_dev* pixel_buffer) {

	// Draw a white line to the foreground buffer
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 0, 0, 320, 240, 0x00ff, 0);
}

void draw_boxes(alt_up_pixel_buffer_dma_dev* pixel_buffer) {

	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
			PIXEL_BUFFER_BASE);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
		;
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	int hw = 0;
	if (hw) {
		printf("test");
		IOWR_32DIRECT(drawer_base, 0, 10);
		// Set x1
		IOWR_32DIRECT(drawer_base, 4, 20);
		// Set y1
		IOWR_32DIRECT(drawer_base, 8, 50);
		// Set x2
		IOWR_32DIRECT(drawer_base, 12, 60);
		// Set y2
		IOWR_32DIRECT(drawer_base, 16, 0x0110);
		// Set colour
		IOWR_32DIRECT(drawer_base, 20, 1);
		// Start drawing
		while (IORD_32DIRECT(drawer_base,20) == 0)
			; // wait until done
	} else {
		printf("test2");
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 10, 20, 50, 60, 0x0101,
				0);
	}
}

void ex5() {

	alt_up_pixel_buffer_dma_dev *pixel_buffer = init_pixel_buffer();
	if (pixel_buffer == 0) {
		printf(
				"error initializing pixel buffer (check name in alt_up_pixel_buffer_dma_open_dev)\n");
	}
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
			PIXEL_BUFFER_BASE);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
		;
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

	int hw = 1;
	while (1) {
		if (hw) {

			IOWR_32DIRECT(drawer_base, 0, rand()%320);
			// Set x1
			IOWR_32DIRECT(drawer_base, 4, rand()%240);
			// Set y1
			IOWR_32DIRECT(drawer_base, 8, rand()%320);
			// Set x2
			IOWR_32DIRECT(drawer_base, 12, rand()%320);
			// Set y2
			IOWR_32DIRECT(drawer_base, 16, rand()%0x10000);
			// Set colour
			IOWR_32DIRECT(drawer_base, 20, 1);
			// Start drawing
			while (IORD_32DIRECT(drawer_base,20) == 0)
				; // wait until done
		} else {
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer, rand() % 320,
					rand() % 240, rand() % 320, rand() % 320, rand() % 0x10000,
					0);
		}
	}

}

int main() {
	VGA_Screen vga_screen;
	vga_screen.init();
}

void junkcode(){
	printf("eclipse is a bitch");
		alt_up_pixel_buffer_dma_dev *pixel_buffer = init_pixel_buffer();
		if (pixel_buffer == 0) {
			printf(
					"error initializing pixel buffer (check name in alt_up_pixel_buffer_dma_open_dev)\n");
		}
		alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
				PIXEL_BUFFER_BASE);
		alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
		while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
			;
		alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
}

//Error: character_lcd_0_avalon_lcd_slave_translator.avalon_anti_slave_0: Cannot connect character_lcd_0_avalon_lcd_slave_translator.reset because character_lcd_0.clock_reset_reset is not connected

