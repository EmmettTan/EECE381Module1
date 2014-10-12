/*
 * SD_Card.h
 *
 *  Created on: Oct 7, 2014
 *      Author: Emmett
 */

#ifndef SD_CARD_H_
#define SD_CARD_H_
#define Bomberman_Forward_Bitmap "b_f.bmp"
#define Speed_Powerup_Bitmap "SpeedUp.bmp"
#include "altera_up_sd_card_avalon_interface.h"


class SD_Card {
public:
	void scan_sd_card(char *directory, char *filename);
	bool init();
	void look_for_other_files(char *filename);
	void change_bitmap_array_from_file(char* filename);


	short int bitmap_array[20][20];
	alt_up_sd_card_dev *device_reference;
	int connected;
	char *filename;
	char *directory; // root directory
private:

};

#endif /* SD_CARD_H_ */
