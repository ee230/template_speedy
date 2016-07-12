#include <stdint.h>

#include "laser.h"
#include "i2c.h"
#include "lcd.h"
#include "xbee.h"
#include "srf08.h"
#include "tpa81.h"
#include "max11613.h"
#include "gsensor_nano.h"
#include "hmc6343.h"



int main(void) {

	if(init_i2c(I2C_1) != 0){
		printf("Init I2C 100kHz Failed\n");
		return -1;
	} else {
		printf("Init I2C 100kHz successful\n");
	}

	if(init_i2c(I2C_2) != 0){
		printf("Init I2C 100kHz Failed\n");
		return -1;
	} else {
		printf("Init I2C 100kHz successful\n");
	}

	uint8_t data_register[4];

	read_register_lcd(data_register);

	printf("Freie Bytes im FIFO: %d\n", data_register[0]);

	printf("Low byte: %d\n", data_register[1]);

	printf("High Byte: %d\n", data_register[2]);

	printf("Version: %d\n", data_register[3]);

	doMeasurement_laser();



	return( 0 );
}