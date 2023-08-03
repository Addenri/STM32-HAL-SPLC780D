/*
 * splc780d.h
 *
 *  Created on: Jul 21, 2023
 *      Author: Andrii
 */

#ifndef INC_SPLC780D_H_
#define INC_SPLC780D_H_

#include "main.h"                   //main header must include HAL driver for your MCU
#include "stdint.h"

/*
 * Display control pins
*/
#define LCD_RS				        (0x01 << 0)	//Register Select: 1 = Data (R/W), 0 = Instruction (W)
#define LCD_RW				        (0x01 << 1)	//Register R/W Select: 1 = Read, 0 = Write
#define LCD_E				        (0x01 << 2) //Start signal for R/W
#define LCD_BACKLIGHT		        (0x01 << 3)

#define LCD_RW_READ			        (0x01 << 1)
#define LCD_RW_WRITE		        (0x00 << 1)

#define LCD_RS_DATA			        (0x01)
#define LCD_RS_INSTRUCTION	        (0x00)

/*
 * Control instructions
 */

/* Clear Display*/
#define LCD_CLEAR			        (0x01)  //Write space code to all DDRAM address

/* Return Home */
#define LCD_RETURN_HOME		        (0x02)  //Set DDRAM address to 0 without DDRAM wipe

/* Entry Mode Set */
#define LCD_MOVE_CURSOR_RIGHT       (0x06)  //Move cursor right, increase DDRAM address by 1
#define LCD_MOVE_CURSOR_LEFT        (0x04)  //Move cursor left, decrease DDRAM address by 1
#define LCD_MOVE_DISPLAY_LEFT       (0x07)
#define LCD_MOVE_DISPLAY_RIGHT      (0x05)

/* Display ON/OFF */
#define LCD_ON_DISPLAY              (0x0C)
#define LCD_ON_CURSOR               (0x0A)
#define LCD_ON_CURSOR_BLINK         (0x09)  //If Cursor Blink is "ON", no need to set Cursor "ON" bit high

/* Cursor or Display Shift */
#define LCD_SHIFT_CURSOR_LEFT       (0x10)
#define LCD_SHIFT_CURSOR_RIGHT      (0x14)
#define LCD_SHIFT_DISPLAY_LEFT      (0X18)
#define LCD_SHIFT_DISPLAY_RIGHT     (0x1C)

/*  Function Set */
#define LCD_FUNC_8BIT              (0x30)  //8-bit interface mode
#define LCD_FUNC_2LINE             (0x28)
#define LCD_FUNC_SYM5x11           (0x24)

#define LCD_TO_LINE_1               (0x0C)
#define LCD_TO_LINE_2               (0x0C)
#define LCD_TO_LINE_3               (0x92)
#define LCD_TO_LINE_4               (0xD4)

extern I2C_HandleTypeDef *hi2c;

typedef struct
{
	I2C_HandleTypeDef* hi2c;
	uint8_t address;
} LCD_HandleTypeDef;

void LCD_Write(LCD_HandleTypeDef *hlcd, uint8_t Data, uint8_t Pins);
void LCD_Read(LCD_HandleTypeDef *hlcd);
void LCD_Init(LCD_HandleTypeDef *hlcd, I2C_HandleTypeDef *hi2c, uint8_t i2c_address);
void LCD_Print(LCD_HandleTypeDef *hlcd, char *Text);
void LCD_CreateSymbol(LCD_HandleTypeDef *hlcd, uint8_t Cell, uint8_t *SymbolMap);

#endif /* INC_SPLC780D_H_ */
