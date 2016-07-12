#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

#include "i2c.h"
#include "max11613.h"


int main(int argc, char *argv[]){

	printf("===== I2C test =====\r\n");

	if(init_i2c(I2C_2) != 0){
		printf("Init I2C 100kHz Failed\n");
		return -1;
	} else {
		printf("Init I2C 100kHz successful\n");
	}

	write_setup_byte();
	write_config_byte();

	uint8_t data[2];

	read_data_max11613(2, data);


	return 0;
	
}