/**
  *******************************************************************************************************************
  * @file      	srf08.h
  * @author    	B. Eng. Urban Conrad
  * @version   	V1.0
  * @date      	14.07.2016
  * @copyright 	2009 - 2016 UniBw M - ETTI - Institut 4
  * @brief   	Header functions to control srf08 modul
  *******************************************************************************************************************
  * @par History:
  *  @details V1.0.0 14.07.2016 Urban Conrad
  *           - Initial version
  *******************************************************************************************************************
  */
  
#ifndef ITG3200_H_
#define ITG3200_H_

//	I	N	C	L	U	D	E	S

#include <stdint.h>

#include "i2c.h"

//	D	E	F	I	N	E	S

#define ADDR_ITG	0x69

//	F	U	N	K	T	I	O	N	E	N

/**
 *******************************************************************************************************************
 *
 *	@brief		uint8_t read_version_itg(void)
 *
 *	@details	Diese Funktion liest die Version des ITG3200 Moduls aus
 *
 *	@param		void
 *
 *	@retval		x	Version
 *				-1	Fehler beim schreiben auf I2C
 *				-2	Fehler beim lesen auf I2C
 *
 *******************************************************************************************************************/
 
uint8_t read_version_itg(void);

/**
 *******************************************************************************************************************
 *
 *	@brief		uint16_t read_temp_itg(void)
 *
 *	@details	Diese Funktion liest die Temperatur des ITG3200 Moduls aus
 *
 *	@param		void
 *
 *	@retval		x	Temperatur
 *				-1	Fehler beim schreiben auf I2C
 *				-2	Fehler beim lesen auf I2C
 *
 *******************************************************************************************************************/
 
uint16_t read_temp_itg(void);


#endif /* ITG3200_H_ */
