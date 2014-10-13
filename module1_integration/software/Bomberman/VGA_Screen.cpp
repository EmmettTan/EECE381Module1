/*
 * VGA_Screen.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: Emmett
 */

#include "VGA_Screen.h"
#include "SD_Card.h"
#define path_color 0xFF4500
#define i_block_color 0xFF8F
#define player_color 0x0000
#define a_block_color 0x0234
#define bomb_color 0x6969
#define explosion_color 0xFF00



// Constructor
VGA_Screen::VGA_Screen() {
	printf("Constructing VGA Screen \n");
	this->pixel_buffer = init_pixel_buffer();
	this->char_buffer = init_char_buffer();
}

// Make sure you call this when creating a VGA_Screen object
void VGA_Screen::init(SD_Card sd_card_temp) {
	// Init Screen
	this->sd_card = sd_card_temp;

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
	alt_up_char_buffer_string(char_buffer, "Swag", 10, 120);
	alt_up_char_buffer_string(char_buffer, "Swag", 310, 120);
}

// Not sure if this will be useful or not, but kept it anyways
void VGA_Screen::draw_diagonal_line(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	printf("Drawing Diagonal Line \n");
	alt_up_pixel_buffer_dma_draw_line(pixel_buffer, 0, 0, 320, 240, 0x00ff, 0);
}

//
void VGA_Screen::draw_boxes(alt_up_pixel_buffer_dma_dev* pixel_buffer, int x_0,
		int x_1, int y_0, int y_1, int color) {

	//printf("Drawing Box \n");
	if (color == i_block_color) {
		this->draw_pattern(pixel_buffer, x_0, y_0, color);
//	} else if (color == player_color) {
//		this->draw_player(pixel_buffer, x_0, y_0, color);
	} else {
		IOWR_32DIRECT(drawer_base, 0, x_0);
		// Set x1
		IOWR_32DIRECT(drawer_base, 4, y_0);
		// Set y1
		IOWR_32DIRECT(drawer_base, 8, x_1);
		// Set x2
		IOWR_32DIRECT(drawer_base, 12, y_1);
		// Set y2
		IOWR_32DIRECT(drawer_base, 16, color);
		// Set colour
		IOWR_32DIRECT(drawer_base, 20, 1);
		// Start drawing
		while (IORD_32DIRECT(drawer_base, 20) == 0)
			; // wait until done
	}
}
//
void VGA_Screen::draw_player(alt_up_pixel_buffer_dma_dev* pixel_buffer, int x_0,
		int y_0, int color) {
	int x, y;
	for (x = x_0 + 10 - 7; x <= x_0 + 10 + 7; x++)
		for (y = y_0 + 10 - 7; y <= y_0 + 10 + 7; y++)
			if (((x * x) + (y * y)) < (7 * 7))
				alt_up_pixel_buffer_dma_draw(pixel_buffer, color, x, y);

}
//
void VGA_Screen::draw_pattern(alt_up_pixel_buffer_dma_dev* pixel_buffer,
		int x_0, int y_0, int color) {
	printf("drawing pattern \n");

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			IOWR_32DIRECT(drawer_base, 0, x_0 + (j * 5));
			// Set x1
			IOWR_32DIRECT(drawer_base, 4, y_0 + (i * 5));
			// Set y1
			IOWR_32DIRECT(drawer_base, 8, x_0 + (j * 5) + 5);
			// Set x2
			IOWR_32DIRECT(drawer_base, 12, y_0 + (i * 5) + 5);
			// Set y2
			if (i % 2 == 0) {
				if (j % 2 == 0) {
					IOWR_32DIRECT(drawer_base, 16, 0x0000);
					// Set colour
				} else {
					IOWR_32DIRECT(drawer_base, 16, 0xFFFF);
				}
			} else {
				if (j % 2 == 0) {
					IOWR_32DIRECT(drawer_base, 16, 0xFFFF);
					// Set colour
				} else {
					IOWR_32DIRECT(drawer_base, 16, 0x0000);
				}
			}
			IOWR_32DIRECT(drawer_base, 20, 1);
			// Start drawing
			while (IORD_32DIRECT(drawer_base, 20) == 0)
				;
			//color = color + 0x0823FF;
		}

	}

}
// paints screen black, you can change color in coding
void VGA_Screen::paint_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer,
		int color) {
	printf("Painting Screen White \n");
	IOWR_32DIRECT(drawer_base, 0, 0);
	// Set x1
	IOWR_32DIRECT(drawer_base, 4, 0);
	// Set y1
	IOWR_32DIRECT(drawer_base, 8, 320);
	// Set x2
	IOWR_32DIRECT(drawer_base, 12, 240);
	// Set y2
	IOWR_32DIRECT(drawer_base, 16, color);
	// Set colour
	IOWR_32DIRECT(drawer_base, 20, 1);
	// Start drawing
	while (IORD_32DIRECT(drawer_base, 20) == 0)
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

//high level drawing stuff

//taking in array
//void VGA_Screen::draw_map_from_array(MatrixMap& m_map) {
//	for (int i = 0; i < 11; i++) {
//		for (int j = 0; j < 11; j++) {
//			this->draw_box_from_coordinate(i,j,m_map.map[i][j]);
//		}
//	}
//}

void VGA_Screen::draw_map_from_array(char m_map[11][11]) {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			this->draw_box_from_coordinate(i, j, m_map[i][j]);
		}
	}
}

// Drawing 20x20 box: takes in top left coordinate of box
void VGA_Screen::draw_box_from_coordinate(int x, int y, char c) {
	int x_scaled = x * 20 + 50;
	int y_scaled = y * 20 + 10;
	int color;
	if (c == 'o') {
		color = i_block_color;
	} else if (c == 'x') {
		color = path_color;
	} else if (c == 'p') {
		color = player_color;
	} else if (c == 'a') {
		color = a_block_color;
	} else if (c == 'b') {
		color = bomb_color;
	} else if (c == 'e') {
		color = explosion_color;
	} else {
		printf("check your character array, something is wrong");
		return;
	}
	this->draw_boxes(this->pixel_buffer, x_scaled, x_scaled + 20, y_scaled,
			y_scaled + 20, color);
}

void VGA_Screen::erase_and_redraw_player(int old_x, int old_y, int new_x,
		int new_y) {
	if (!((old_x == new_x) && (old_y == new_y))) {
		this->draw_box_from_coordinate(old_x, old_y, 'x');
		this->draw_box_from_coordinate(new_x, new_y, 'p');
	}
}

void VGA_Screen::draw_bomb(int x, int y) {
	this->draw_box_from_coordinate(x, y, 'b');
}

void VGA_Screen::clear_bomb(int x, int y) {
	this->draw_box_from_coordinate(x, y, 'x');
}

void VGA_Screen::draw_flame(int x, int y){
	this->draw_bitmap(this->pixel_buffer, this->sd_card.flame_array, x*20+50, y*20+10 );
}

void VGA_Screen::draw_image_from_bitmap(int x, int y, short int bitmap[20][20]){
	this->draw_bitmap(this->pixel_buffer, bitmap, x*20+50, y*20+10 );
}

void VGA_Screen::draw_explosion(std::vector<int> &damaged_blocks,
		bool is_explosion) {
	if (is_explosion) {
		for (int i = 0; i < damaged_blocks.size(); i += 2) {
//			this->draw_box_from_coordinate(damaged_blocks[i],
//					damaged_blocks[i + 1], 'e');
			this->draw_flame(damaged_blocks[i], damaged_blocks[i+1]);
		}
	} else {
		for (int i = 0; i < damaged_blocks.size(); i += 2) {
			this->draw_box_from_coordinate(damaged_blocks[i],
					damaged_blocks[i + 1], 'x');
		}
	}
}

// Draws bitmap from bitmap array, specify top right pixel.
void VGA_Screen::draw_bitmap(alt_up_pixel_buffer_dma_dev* pixel_buffer,
		short int bitmap[20][20], int x_0, int y_0) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (bitmap[i][j] != -1) {
				alt_up_pixel_buffer_dma_draw(pixel_buffer, bitmap[i][j],
						x_0 + i, y_0 + j);
			}
		}
	}
}

