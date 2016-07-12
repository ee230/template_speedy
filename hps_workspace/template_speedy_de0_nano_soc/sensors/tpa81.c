#include "tpa81.h"

uint8_t read_version_srf08(void){

	uint8_t version = 0;

	uint8_t cmd_reg_0 = {0};

	write_i2c(I2C_1, ADDR_TPA81, &cmd_reg_0, 1);

	read_i2c(I2C_1, ADDR_TPA81, &version, 1);

	return version;
}

uint8_t read_umgebungs_temp(void){

	uint8_t version = 0;

	uint8_t cmd_reg_1 = {1};

	write_i2c(I2C_1, ADDR_TPA81, &cmd_reg_1, 1);

	read_i2c(I2C_1, ADDR_TPA81, &version, 1);

	return version;
}

uint8_t read_pixel_temp(uint8_t pixel, uint8_t data_tpa[]){

	uint8_t byte = 1;
	uint8_t command;
	uint8_t bytes_read;

	switch (pixel){

			case 0:
				byte = 8;
				command = 2;
				break;
			case 1:
				command = 2;
				break;
			case 2:
				command = 3;
				break;
			case 3:
				command = 4;
				break;
			case 4:
				command = 5;
				break;
			case 5:
				command = 6;
				break;
			case 6:
				command = 7;
				break;
			case 7:
				command = 8;
				break;
			case 8:
				command = 9;
				break;
		}

	write_i2c(I2C_1, ADDR_TPA81, &command, 1);


	bytes_read = read_i2c(I2C_1, ADDR_TPA81, data_tpa, byte);

	if(bytes_read == byte)
		return bytes_read;

	return -1;

}