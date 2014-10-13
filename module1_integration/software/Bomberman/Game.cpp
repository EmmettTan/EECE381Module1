/*
 * Game.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: Emmett
 */

#include "Game.h"

// Constructor
Game::Game() {

}

void Game::init() {
	this->sd_card.init();

	this->vga_screen.init(sd_card);
	this->vga_screen.clear_screen(vga_screen.pixel_buffer);
	this->vga_screen.paint_screen(vga_screen.pixel_buffer, 0xF000);
	this->vga_screen.draw_map_from_array(matrix_map.map);
	this->vga_screen.draw_box_from_coordinate(0, 0, 'p');

	this->vga_screen.draw_image_from_bitmap(5,0,this->sd_card.flame_array);
}

void Game::game_drawing(Player &player1, MatrixMap &matrix_map,
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

void Game::game_logic(Player &player1, MatrixMap &matrix_map,
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

void Game::run() {
	while (1) {
		game_logic(player1, matrix_map, vga_screen);
		game_drawing(player1, matrix_map, vga_screen);
		usleep(30000);
	}
}

