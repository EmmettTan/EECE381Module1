/*
 * SD_Card.h
 *
 *  Created on: Oct 7, 2014
 *      Author: Emmett
 */

#ifndef SD_CARD_H_
#define SD_CARD_H_
#define Bomberman_Forward_Bitmap "b_f.bmp"
#include "altera_up_sd_card_avalon_interface.h"


class SD_Card {
public:
	bool check_sd_card();
	void scan_sd_card(char *directory, char *filename);
	bool init();
	void look_for_other_files(char *filename);

	alt_up_sd_card_dev *device_reference;
	int connected;
	char *filename;
	char *directory; // root directory
private:

};

#endif /* SD_CARD_H_ */
