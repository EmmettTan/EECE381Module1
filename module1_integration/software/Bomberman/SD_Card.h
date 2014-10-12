/*
 * SD_Card.h
 *
 *  Created on: Oct 7, 2014
 *      Author: Emmett
 */

#ifndef SD_CARD_H_
#define SD_CARD_H_

// Bitmap Filenames
// Bomberman
#define Bomberman_Forward_Bitmap "b_f.bmp"
#define Bomberman_Right_Bitmap

// Powerup
#define Speed_Powerup_Bitmap "SpeedUp.bmp"

// Flame

#define Flame_Bitmap "b_f.bmp"


#include "altera_up_sd_card_avalon_interface.h"


class SD_Card {
public:
	void scan_sd_card(char *directory, char *filename);
	bool init();
	void look_for_other_files(char *filename);
	void setup_bitmaps_from_sd_card();


	short int bomberman_forward_array[20][20];

	// Bomberman Forward Arrays
	short int bomberman_forward_f00_array[20][20];
	short int bomberman_forward_f01_array[20][20];
	short int bomberman_forward_f02_array[20][20];
	short int bomberman_forward_f03_array[20][20];
	short int bomberman_forward_f04_array[20][20];
	short int bomberman_forward_f05_array[20][20];
	short int bomberman_forward_f06_array[20][20];
	short int bomberman_forward_f07_array[20][20];

	// Bomberman Right Arrays
	short int bomberman_right_f00_array[20][20];
	short int bomberman_right_f01_array[20][20];
	short int bomberman_right_f02_array[20][20];
	short int bomberman_right_f03_array[20][20];
	short int bomberman_right_f04_array[20][20];
	short int bomberman_right_f05_array[20][20];
	short int bomberman_right_f06_array[20][20];
	short int bomberman_right_f07_array[20][20];

	// Bomberman  Left Arrays
	short int bomberman_left_f00_array[20][20];
	short int bomberman_left_f01_array[20][20];
	short int bomberman_left_f02_array[20][20];
	short int bomberman_left_f03_array[20][20];
	short int bomberman_left_f04_array[20][20];
	short int bomberman_left_f05_array[20][20];
	short int bomberman_left_f06_array[20][20];
	short int bomberman_left_f07_array[20][20];

	// Bomberman  backwards Arrays
	short int bomberman_backwards_f00_array[20][20];
	short int bomberman_backwards_f01_array[20][20];
	short int bomberman_backwards_f02_array[20][20];
	short int bomberman_backwards_f03_array[20][20];
	short int bomberman_backwards_f04_array[20][20];
	short int bomberman_backwards_f05_array[20][20];
	short int bomberman_backwards_f06_array[20][20];
	short int bomberman_backwards_f07_array[20][20];

	// Powerup Arrays
	short int speed_powerup_array[20][20];

	// Flame Arrays
	short int flame_array[20][20];


	alt_up_sd_card_dev *device_reference;
	int connected;
	char *filename;
	char *directory; // root directory
private:


	void change_bitmap_array_from_file(char* filename, short int bitmap_array[20][20]);

};

#endif /* SD_CARD_H_ */
