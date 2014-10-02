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

int main() {
	Player p;
	MatrixMap m;
	m.print_matrix();

	VGA_Screen vga_screen;
	vga_screen.init();

	vga_screen.clear_screen(vga_screen.pixel_buffer);
	vga_screen.paint_screen(vga_screen.pixel_buffer, 0xF000);
	vga_screen.draw_map_from_array(m.map);
	vga_screen.draw_box_from_coordinate(0, 0, 'p');
	while (1) {
		p.move(p.get_direction(), m);
		p.place_bomb();
		if(p.bomb.isActive()){
			vga_screen.draw_bomb(p.bomb.get_x_cord(), p.bomb.get_y_cord());
		}
		if (p.bomb.check_explosion(vga_screen)) {
			int bomb_x_cord = p.bomb.get_x_cord();
			int bomb_y_cord = p.bomb.get_y_cord();
			p.check_explosion(bomb_x_cord, bomb_y_cord);
			m.check_explosion(bomb_x_cord, bomb_y_cord, vga_screen);
		}
		//printf("%c\n", p.get_direction());
		//printf("x = %d   y = %d	cord=%c\n", p.get_x_cord(), p.get_y_cord(), m.get_cord(p.get_x_cord(), p.get_y_cord()));
		vga_screen.erase_and_redraw_player(p.get_old_x_cord(),
				p.get_old_y_cord(), p.get_x_cord(), p.get_y_cord());
		usleep(30000);
	}

	return 0;
}
