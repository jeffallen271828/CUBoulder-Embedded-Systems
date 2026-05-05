/*
 * Matrixdef.h
 *
 *  Created on: Nov 19, 2024
 *      Author: jeffreya181
 */

#ifndef INC_MATRIXDEF_H_
#define INC_MATRIXDEF_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "LCD_Driver.h"
#include "Scheduler.h"

#define cut_Mode 1

#define pixel_Width 24
#define pixel_Length 24
#define pixel_Area (pixel_Width*pixel_Length)
#define ROWS 13
#define COLS 10

#define BLOCK_WIDTH   (240 / COLS)  // 32 pixels
#define BLOCK_HEIGHT  (320 / ROWS) // ~18 pixels
/*	MATRIX PLAN
 13x10 Grid, x = 0 starts at left screen
 	 	 	 y = 0 starts at bottom of screen
 	 	 	      	  	  	  Tetris <- We have a spare L=8pixels and w= 240 pixels to add whatever
 	y-axis
 	 	12 	 	0	0	0	0	0	0	0	0	0	0
 	 	11 	 	0	0	0	0	0	0	0	0	0	0
 	 	10 	 	0	0	0	0	0	0	0	0	0	0
 	 	9 	 	0	0	0	0	0	0	0	0	0	0
 	 	8 	 	0	0	0	0	0	0	0	0	0	0
 	 	7 	 	0	0	0	0	0	0	0	0	0	0
 	 	6 	 	0	0	0	0	0	0	0	0	0	0
 	 	5 	 	0	0	0	0	0	0	0	0	0	0
 	 	4 	 	0	0	0	0	0	0	0	0	0	0
 	 	3 		0	0	0	0	0	0	0	0	0	0
 	 	2 	 	0	0	0	0	0	0	0	0	0	0
 	 	1 	 	0	0	0	0	0	0	0	0	0	0
 	 	0 	 	0	0	0	0	0	0	0	0	0	0

 	 x-axis     0	1	2	3	4	5	6	7	8	9
 */

typedef enum { // Orioinal Names of Tetris blocks
	ORICKY,
	BRICKY,
	CLEVELAND,
	RHODE,
	HERO,
	TEEWEE,
	SMASHBOY
} Tetris_name;

typedef enum{
	ROTATION_0,
	ROTATION_1,
	ROTATION_2,
	ROTATION_3
} rotation;

typedef struct {
	uint8_t x;
	uint8_t y;
} coordinates;

typedef struct {
	Tetris_name name;
	rotation Rotation;
	coordinates originbit;
	coordinates suboriginbit_0;
	coordinates suboriginbit_1;
	coordinates suboriginbit_2;
} Object;
/*
static Object object;
static uint8_t dummyTable[ROWS][COLS];
static uint32_t randomNumber;
*/


/*******
 Functions used for matrix manipulation of variable
*******/
void START_SCREEN(void);
void GAME_OVER(uint32_t total_time);

void RND_NUM(void);
uint8_t check_State(void); // Essentially passing in an object that has be transformed to see if it violates issues
void object_Select(void);
//void shift_Left(uint32_t X);
//void shift_Right(uint32_t X);
void shift_Left(void);
void shift_Right(void);
void transform_rotation(void); // Rotating the object
void tick_Matrix(void);
void printMatrix(void);
void Matrix_clear(void);
void Matrix_update(void);

#endif /* INC_MATRIXDEF_H_ */
