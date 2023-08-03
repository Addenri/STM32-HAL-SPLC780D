/*
 * splc780d.c
 *
 *  Created on: Jul 21, 2023
 *      Author: Andrii
 */


#include "splc780d.h"

void LCD_Write(LCD_HandleTypeDef *hlcd, uint8_t Data, uint8_t Pins)
{
  uint8_t LCD_Command[4] = {0, 0, 0, 0};
  uint8_t High = Data & 0xF0;
  uint8_t Low = (Data << 4) & 0xF0;

  LCD_Command[0] = High | Pins | LCD_BACKLIGHT | LCD_E;
  LCD_Command[1] = High | Pins | LCD_BACKLIGHT;
  LCD_Command[2] = Low | Pins | LCD_BACKLIGHT | LCD_E;
  LCD_Command[3] = Low | Pins | LCD_BACKLIGHT;

  HAL_I2C_Master_Transmit(hlcd->hi2c, hlcd->address, (uint8_t*)&LCD_Command, sizeof(LCD_Command), HAL_MAX_DELAY);
  HAL_Delay(5);
}

void LCD_Init(LCD_HandleTypeDef *hlcd, I2C_HandleTypeDef *hi2c, uint8_t i2c_address)
{
  hlcd->hi2c = hi2c;
  hlcd->address = (i2c_address << 1);   //STM32 HAL use 1-bit shifted address
  HAL_Delay(40);
  if(HAL_I2C_IsDeviceReady(hlcd->hi2c, hlcd->address, 1, HAL_MAX_DELAY) != HAL_OK)
	Error_Handler();
  LCD_Write(hlcd, LCD_CLEAR, LCD_RS_INSTRUCTION);
}

void LCD_Print(LCD_HandleTypeDef *hlcd, char *Text)
{
  while(*Text)
  {
    //if(*Text == '\n')

      //LCD_Write(hlcd, 0xC0, LCD_RS_INSTRUCTION);
    //else
      LCD_Write(hlcd, (uint8_t)(*Text), LCD_RS);
    Text++;
  }
}

void LCD_CreateSymbol(LCD_HandleTypeDef *hlcd, uint8_t Cell, uint8_t *SymbolMap)
{
  Cell &= 0x7;
  LCD_Write(hlcd, (Cell << 3), LCD_RS_INSTRUCTION);
  for(int i = 0; i < 8; i++)
  {
    LCD_Write(hlcd, SymbolMap[i], LCD_RS_DATA);
  }
}
