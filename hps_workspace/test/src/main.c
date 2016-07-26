#include "speedy.h"

int main(void) {

	uint8_t init;			//Variable fuer init_speedy
	uint16_t key;

	uint8_t text_1[] = {"     HPS Speedy     "
				  	  	"\n"
				  	  	" INIT: Ok  Press #  "};

	uint8_t text_2[] = {"\n"
						" * + # = Terminate  "
						"\n"
						"      Press #       "};

	uint8_t text_3[] = {"\n"
						" * + # = Terminate  "
						"\n"
						"      Press #       "};

	int memmory;			//file pointer fuer speicher
	void *virtual_base;
	volatile uint32_t *hps_laser = NULL;
	volatile uint32_t *hps_saber = NULL;



	//Init Speedy Peripheral, no Laser and Drive
	init = init_speedy();

	if(init != 0){
		printf("Init Speedy Failed: %d", init);
		return init;
	}

	//Init HPS Bridge

	if( ( memmory = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return 5;
	}

	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, memmory, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close(memmory);
		return 6;
	}

	hps_laser = virtual_base + ( (uint32_t)( ALT_LWFPGASLVS_OFST + LASER_BASE ) & (uint32_t)( HW_REGS_MASK ) );
	hps_saber = virtual_base + ( (uint32_t)( ALT_LWFPGASLVS_OFST + MOTOR_MODUL_BASE ) & (uint32_t)( HW_REGS_MASK ) );

	//Init memmory laser
	initMemory(hps_laser);

	//Write on LCD

	clear_lcd();
	blacklight_on_lcd();
	set_courser_lcd(0, 0);

	write_data_lcd(text_1, sizeof(text_1));

	do{

		key = read_key_lcd();

	}while(key != 0x0800);

	write_data_lcd(text_2, sizeof(text_2));

	do{

		key = read_key_lcd();

		if(key == 0x0A00){

			clear_lcd();
			blacklight_off_lcd();

			if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
				printf( "ERROR: munmap() failed...\n" );
				close( memmory );
				return 7;
			}

			close(memmory);

			return 0;
		}

	}while(key != 0x0800);

	write_data_lcd(text_3, sizeof(text_3));

	while(read_key_lcd() != 0x0A00){

		//Enter CODE here!!!!!!!!!!!!!







	};

	clear_lcd();
	blacklight_off_lcd();

	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( memmory );
		return 7;
	}

	close(memmory);

	return 0;

}
