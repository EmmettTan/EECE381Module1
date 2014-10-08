#include <stdio.h>
#include <string.h>
#include "io.h"
#include <stdlib.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include <time.h>
#include "sys/alt_timestamp.h"
#include <iostream>
#include "MatrixMap.h"
#include "VGA_Screen.h"
#include "Player.h"
#include "unistd.h"
#include "altera_up_sd_card_avalon_interface.h"
#include "SD_Card.h"

void game_logic(Player &player1, MatrixMap &matrix_map, VGA_Screen &vga_screen);
void game_drawing(Player &player1, MatrixMap &matrix_map,
		VGA_Screen &vga_screen);

int main() {

	Player player1;
	MatrixMap matrix_map;
	VGA_Screen vga_screen;
	SD_Card sd_card;

	if (sd_card.init()) {
		short int file_handle = alt_up_sd_card_fopen(Bomberman_Forward_Bitmap, false);
		alt_up_sd_card_read(file_handle);
	}

	vga_screen.init();
	vga_screen.clear_screen(vga_screen.pixel_buffer);
	vga_screen.paint_screen(vga_screen.pixel_buffer, 0xF000);
	vga_screen.draw_map_from_array(matrix_map.map);
	vga_screen.draw_box_from_coordinate(0, 0, 'p');

	while (1) {
		game_logic(player1, matrix_map, vga_screen);
		game_drawing(player1, matrix_map, vga_screen);
		usleep(30000);
	}

	return 0;
}

void game_logic(Player &player1, MatrixMap &matrix_map,
		VGA_Screen &vga_screen) {
	player1.move(player1.get_direction(), matrix_map);
	player1.place_bomb(matrix_map);

	player1.bomb.increment_timer();
	if (player1.bomb.exploded()) {
		matrix_map.check_damaged_blocks(player1.bomb.get_x_cord(),
				player1.bomb.get_y_cord(), player1.bomb.get_explosion_range(),
				player1.bomb.damaged_blocks);
		player1.check_damage(player1.bomb.damaged_blocks);
	}
}

void game_drawing(Player &player1, MatrixMap &matrix_map,
		VGA_Screen &vga_screen) {
	vga_screen.erase_and_redraw_player(player1.get_old_x_cord(),
			player1.get_old_y_cord(), player1.get_x_cord(),
			player1.get_y_cord());
	if (player1.bomb.isActive()) {
		vga_screen.draw_bomb(player1.bomb.get_x_cord(),
				player1.bomb.get_y_cord());
	} else if (player1.bomb.isExploding()) {
		vga_screen.draw_explosion(player1.bomb.damaged_blocks, true);
	} else if (player1.bomb.finishedExploding()) {
		vga_screen.draw_explosion(player1.bomb.damaged_blocks, false);
	}
}

