#include "laser_include.h"


void sendCommand( volatile uint32_t *base_addr, uint32_t cmd)
{
	IOWR_LASER_COMMAND(base_addr, cmd);
	IOWR_LASER_COMMAND(base_addr, NOTHING);
	printf("Befehl %i wurde gesendet.\n",cmd);
}

void initMemory(volatile uint32_t *base_addr)
{
	uint32_t debug = 0;

	IOWR_LASER_INIT(base_addr, 0);
	IOWR_LASER_INIT(base_addr, 1);
	//OSTimeDlyHMSM(0, 0, 3, 0);
	debug = IORD_LASER_INIT(base_addr);
	if(debug)
	{
		printf("Speicher zurueckgesetzt!\n");
	}
	else
	{
		printf("FEHLER BEIM ZURUECKSETZEN DES SPEICHERS!\n");
	}
}

uint32_t findBeginOfData(volatile uint32_t *base_addr, uint32_t offset)
{
	int i = 0;
	int pos = 0;
	int data = 0;
	for(i = 0; i < (MAX_ADDR-offset); i++)
	{
		pos= i + offset;
		IOWR_LASER_ADDR(base_addr, pos);
		data = IORD_LASER_MEMORY(base_addr);
		if(data == 'M')
		{
			IOWR_LASER_ADDR(base_addr, pos+1);
			data = IORD_LASER_MEMORY(base_addr);
			if(data == 'S')
			{
				return pos;
			}
		}
	}
	return MAX_ADDR;
}

uint32_t findEndOfData( volatile uint32_t *base_addr, uint32_t begin)
{
	uint32_t i = 0;
	uint32_t offset = begin;
	uint32_t pos = 0;
	uint32_t data =0;

	for(i = 0; i < (MAX_ADDR-offset); i++)
	{
		pos = i + offset;
		IOWR_LASER_ADDR(base_addr, pos);
		data = IORD_LASER_MEMORY(base_addr);
		if( data == 10) // 10 fuer den Character LineFeed
		{
			IOWR_LASER_ADDR(base_addr, pos+1);
			if(IORD_LASER_MEMORY(base_addr) == 10)// 10 fuer den Character LineFeed
			{
				return pos+1;
			}
		}
	}
	return 2048;
}

void printData(volatile uint32_t *base_addr, uint32_t begin, uint32_t end)
{
	uint32_t i = 0;
	uint8_t debug = 0;

	printf("Von: %i Bis: %i steht im Speicher:\n", begin,end);
	for(i = 0; i < (end-begin)+1; i++)
	{
		IOWR_LASER_ADDR(base_addr, i+begin);
		debug = IORD_LASER_MEMORY(base_addr);
		//printf("%X: ",IORD_LASER_ADDR(LASER_BASE));
		if(debug == 10)
		{
			printf("LF\n");
		}
		else
		{
			printf("%c",debug);
		}
	}
	fflush(stdout);
	printf("Speicher Ausgabe Ende\n");
}

uint32_t getBeginDistanceData(volatile uint32_t *base_addr, uint32_t beginData, uint32_t endData)
{
	uint32_t i = 0;
	uint32_t memoryPos = 0;
	uint32_t memoryData = 0;

	for(i = 0; i < endData - beginData; i++)
	{
		memoryPos = i + beginData;
		IOWR_LASER_ADDR(base_addr, memoryPos);
		memoryData = IORD_LASER_MEMORY(base_addr);
		if(memoryData == '9')
		{
			IOWR_LASER_ADDR(base_addr, memoryPos + 1);
			memoryData = IORD_LASER_MEMORY(base_addr);
			if(memoryData == '9')
			{
				IOWR_LASER_ADDR(base_addr, memoryPos + 2);
				memoryData = IORD_LASER_MEMORY(base_addr);
				if(memoryData == 'b')
				{
					return memoryPos + 10;
				}
			}
		}
	}
	//printf("Keine Daten in Abschnitt von %i bis %i!\n",beginData,endData);
	return 0;
}

uint32_t encodingDistance(volatile uint32_t *base_addr, uint32_t dataPos)
{
	uint32_t upperData = 0;
	uint32_t lowerData = 0;
	uint32_t distance = 0;

	//zwischenspeichern der oberen Bits
	IOWR_LASER_ADDR(base_addr, dataPos);
	upperData = IORD_LASER_MEMORY(base_addr);
	//printf("[%i;%i] '%c' ", dataPos, dataPos+1, upperData);
	//gemaess des encodings aus dem Kommunikationsprotokoll
	// 0x30 abziehen
	upperData = upperData - 0x30;

	//zwischenspeichern der unteren Bits
	IOWR_LASER_ADDR(base_addr, dataPos + 1);
	lowerData = IORD_LASER_MEMORY(base_addr);
	//printf("'%c'", lowerData);
	//gemaess des encodings aus dem Kommunikationsprotokoll
	// 0x30 abziehen
	//printf("-> ");
	lowerData = lowerData - 0x30;

	//Distanz errechnen
	distance = upperData;
	distance = distance << 6;
	distance = distance | lowerData;

	if(distance < 0)
	{
		return 0;
	}
	if(distance > 4000)
	{
		return 4000;
	}

	return distance;

}

void printDistances(volatile uint32_t *base_addr, uint32_t begin, uint32_t end)
{
	uint32_t i = 0;
	uint32_t anzDatensatz = 1;
	uint32_t debug = 0;


	printf("Begin Distanzen:\n");
	for(i = 0; i < end-begin; i = i + 2)
	{
		// ToDo nur zum debug
		printf("Messpunkt: %i -> Entfernung: %i \n", anzDatensatz, encodingDistance(base_addr, begin + i));

		anzDatensatz++;

		IOWR_LASER_ADDR(base_addr, begin + i + 3);
		debug = IORD_LASER_MEMORY(base_addr);
		if(debug == 10)
		{
			i = i + 2;
		}
	}
	fflush(stdout);
	printf("End Distanzen\n");

}

void printDistances2(uint16_t *array)
{
	uint32_t i = 0;

	printf("Begin Distanzen:\n");
	for(i = 0; i < ARRAY_LENGHT; i++)
	{
		// ToDo Ausgabe Array
		printf("STEP[%i]-->%i\n", i, *(array + i));
	}
}

void fillArrayDistances(volatile uint32_t *base_addr, uint32_t begin, uint32_t end, uint16_t *array)
{
	uint32_t i, k = 0;
	uint32_t debug = 0;

	for(i = 0; i < end-begin; i = i + 2 , k++)
	{
		*(array + k + 44) = encodingDistance(base_addr, begin + i);

		IOWR_LASER_ADDR(base_addr, begin + i + 3);
		debug = IORD_LASER_MEMORY(base_addr);
		if(debug == 10)
		{
			i = i + 2;
		}
	}
}

uint8_t doMeasurement(volatile uint32_t *base_addr, uint16_t *distance)
{
	int begin = 0;
	int end = 0;
	int data = 0;

	initMemory(base_addr); //Speicher initialisieren
	sendCommand(base_addr, COMMAND_MEAS); // Befehl schicken

	usleep(200*1000);

	begin = findBeginOfData(base_addr, 0); // Anfang des Messbefehls finden

	 while (begin < MAX_ADDR)
	 {
		end = findEndOfData(base_addr, begin); // Speicher wird nach LFLF durchsucht
		data = getBeginDistanceData(base_addr, begin, end); // Anfang von Distanzen finden

		if(data) // Anfang gefunden
		{
			begin = data;
			//printDistances(begin, end); // Messpunkte ausgeben
			//hier Array beschreiben.
			fillArrayDistances(base_addr, begin, end, distance);
			//Daten muessen in Array geschrieben werden, darum warten
			usleep(1*1000*1000);
			printDistances2(distance);

			return 0;
		}
		else
		{
			printData(base_addr, begin,end); //Falls ein Fehler aufgetreten ist kann hier der Fehlercode ausgegeben werden und analysiert werden.
			//OSTimeDlyHMSM(0, 0, 1, 0);
		}

		begin = findBeginOfData(base_addr, end); // Anfang des Messbefehls finden // N�chsten Eintrag im Speicher kontrollieren
	}

	 return 1; // Keine Daten gefunden.

}

uint8_t doMeasurement_laser(uint16_t *distance){

	void *virtual_base;
	volatile uint32_t *hps_laser = NULL;
	int fd;


	// map the address space for the LED registers into user space so we can interact with them.
	// we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span

	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	hps_laser = virtual_base + ( (uint32_t)( ALT_LWFPGASLVS_OFST + LASER_BASE ) & (uint32_t)( HW_REGS_MASK ) );

	doMeasurement(hps_laser, distance);


	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	close( fd );

	return( 0 );
}

