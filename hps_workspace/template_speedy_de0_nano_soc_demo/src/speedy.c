#include "speedy.h"

uint8_t init_speedy(void){

	uint8_t data = 0x00;

	//Init I2C 1
	if(init_i2c(I2C_1) != 0)
		return 1;

	//Pyro Sensor
	if(write_i2c(I2C_1, ADDR_TPA81, &data, 1) != 1)
		return 11;

	//SRF08 hinten links
	if(write_i2c(I2C_1, SRF_HL, &data, 1) != 1)
		return 12;

	//SRF08 vorne
	if(write_i2c(I2C_1, SRF_V, &data, 1) != 1)
		return 13;

	//SRF08 hinten rechts
	if(write_i2c(I2C_1, SRF_HR, &data, 1) != 1)
		return 14;

	//Init I2C 2
	if(init_i2c(I2C_2) != 0)
		return 2;

	//HMC6343
	if(write_i2c(I2C_2, ADDR_HMC, &data, 1) != 1)
		return 21;

	//MAX11613
	if(write_i2c(I2C_2, ADDR_MAX11613, &data, 1) != 1)
		return 22;

	//LCD
	if(write_i2c(I2C_2, LCD03_ADRESS, &data, 1) != 1)
		return 23;

	//ITG3200
	if(write_i2c(I2C_2, ADDR_ITG, &data, 1) != 1)
		return 24;

	//Init Motor Modul
	if(init_itg() != 0)
		return 3;

	//Init G Sensor ADXL345 on DE0 Nano SoC
	if(!ADXL345_Init())
		return 4;

	return 0;
}


uint8_t key_1_fahren(volatile uint32_t *base_addr){

	uint16_t key;
	uint8_t text_1_key_1[] = {	"\n"
								" Speedy faehrt 60cm "
								"\n"
								"      Press #       "};

	uint8_t text_2_key_1[] = {	"   Speedy faehrt !  "};
	uint8_t text_3_key_1[] = {	"      Fertig!       "};
	uint8_t zahlen[] = {'1', '2', '3'};

	clear_lcd();
	set_courser_lcd(1, 1);
	write_data_lcd(text_1_key_1, sizeof(text_1_key_1));

	usleep(500*1000);

	do{

		key = read_key_lcd();

	}while(key != 0x0800);

	clear_lcd();
	set_courser_lcd(2, 10);
	write_data_lcd(&zahlen[2], 1);

	usleep(1000*1000);

	set_courser_lcd(2, 10);
	write_data_lcd(&zahlen[1], 1);

	usleep(1000*1000);

	set_courser_lcd(2, 10);
	write_data_lcd(&zahlen[0], 1);

	usleep(1000*1000);

	clear_lcd();
	set_courser_lcd(2, 1);
	write_data_lcd(text_2_key_1, sizeof(text_2_key_1));

	drive(base_addr, 125, 600);

	clear_lcd();
	set_courser_lcd(2, 1);
	write_data_lcd(text_3_key_1, sizeof(text_3_key_1));

	usleep(1000*1000);

	return 0;
}

uint8_t key_2_fahren(volatile uint32_t *base_addr){
	return 0;
}

uint8_t key_3_fahren(volatile uint32_t *base_addr){
	return 0;
}

uint8_t key_4_senden(){
	return 0;
}
