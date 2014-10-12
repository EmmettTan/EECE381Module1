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
#include <string>
#include <sstream>
#include "Game.h"

/*
 * IMPORTANT. in avalon_up_sd_card_avalon_interface.h, you may get a stupid error on the line:
 *
 ifndef bool
    typedef enum e_bool { false = 0, true = 1 } bool;
#endif
 *
 *
 *     Change ifndef bool to ifndef __cplusplus
 *
 */


int main() {
	Game game;
	game.init();
	game.run();
	return 0;
}

