/**
  *******************************************************************************************************************
  * @file      	hmc6343.c
  * @author    	B. Eng. Urban Conrad
  * @version   	V1.0
  * @date      	18.07.2016
  * @copyright 	2009 - 2016 UniBw M - ETTI - Institut 4
  * @brief   	Functions to control HMC6343 modul
  *******************************************************************************************************************
  * @par History:
  *  @details V1.0.0 13.07.2016 Urban Conrad
  *           - Initial version
  *******************************************************************************************************************
  */
  
//	I	N	C	L	U	D	E	S

#include "hmc6343.h"

//	F	U	N	K	T	I	O	N	E	N

uint8_t write_cmd_hmc(uint8_t command){

	if(write_i2c(I2C_2, ADDR_HMC, &command, 1) == 1)
		return 0;

	return 1;
}

uint8_t post_heading_data(void){

	uint8_t data = 0x50;

	if(write_i2c(I2C_2, ADDR_HMC, &data, 1) == 1)
		return 0;

	return 1;
}


uint8_t read_data_hmc(uint8_t data_hmc[]){

	uint8_t bytes_read;

	bytes_read = read_i2c(I2C_2, ADDR_HMC, data_hmc, 6);

	if(bytes_read == 6)
		return bytes_read;

	return 1;

}
