#include <stdio.h>
#include <string.h>
#include "io.h"
#include <stdlib.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "VGA_Screen.h"

int main() {
	VGA_Screen vga_screen;
	vga_screen.init();
	vga_screen.paint_screen(vga_screen.pixel_buffer);
	vga_screen.draw_boxes(vga_screen.pixel_buffer);
	vga_screen.draw_diagonal_line(vga_screen.pixel_buffer);
	vga_screen.draw_character(vga_screen.char_buffer);
}
