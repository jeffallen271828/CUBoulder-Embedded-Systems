/*
 * Matrixdef_cut.c
 *
 *  Created on: Dec 10, 2024
 *      Author: jeffreya181
 */
#include "Matrixdef.h"
#if cut_Mode == 1

static Object object;
static uint8_t dummyTable[ROWS][COLS];
static uint32_t randomNumber;

void START_SCREEN(void){
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++) {
			dummyTable[i][j] = 0;
		}
	}

	LCD_Clear(0,LCD_COLOR_BLUE);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);
	// TETRIS
	LCD_DisplayChar(70,110,'T');
	LCD_DisplayChar(90,110,'E');
	LCD_DisplayChar(110,110,'T');
	LCD_DisplayChar(130,110,'R');
	LCD_DisplayChar(150,110,'I');
	LCD_DisplayChar(170,110,'S');
	// PRESS
	LCD_DisplayChar(80,130,'P');
	LCD_DisplayChar(100,130,'R');
	LCD_DisplayChar(120,130,'E');
	LCD_DisplayChar(140,130,'S');
	LCD_DisplayChar(160,130,'S');
	// BUTTON
	LCD_DisplayChar(70,150,'B');
	LCD_DisplayChar(90,150,'U');
	LCD_DisplayChar(110,150,'T');
	LCD_DisplayChar(130,150,'T');
	LCD_DisplayChar(150,150,'O');
	LCD_DisplayChar(170,150,'N');
	// TO
	LCD_DisplayChar(110,170,'T');
	LCD_DisplayChar(130,170,'O');
	// START
	LCD_DisplayChar(80,190,'S');
	LCD_DisplayChar(100,190,'T');
	LCD_DisplayChar(120,190,'A');
	LCD_DisplayChar(140,190,'R');
	LCD_DisplayChar(160,190,'T');
}

void GAME_OVER(uint32_t total_time) { // code for displaying game over
	LCD_Clear(0,LCD_COLOR_BLUE);
	LCD_SetTextColor(LCD_COLOR_WHITE);
	LCD_SetFont(&Font16x24);

	// GAME
	LCD_DisplayChar(90,100,'G');
	LCD_DisplayChar(110,100,'A');
	LCD_DisplayChar(130,100,'M');
	LCD_DisplayChar(150,100,'E');
	// OVER
	LCD_DisplayChar(90,130,'O');
	LCD_DisplayChar(110,130,'V');
	LCD_DisplayChar(130,130,'E');
	LCD_DisplayChar(150,130,'R');
	// TIME:
	LCD_DisplayChar(85,160,'T');
	LCD_DisplayChar(105,160,'I');
	LCD_DisplayChar(125,160,'M');
	LCD_DisplayChar(145,160,'E');
	LCD_DisplayChar(165,160,':');

	//Timer to keep tract
	// t_on = ARR / 16MHz
	total_time = total_time / 1599999;
	uint32_t minutes = total_time / 60;
	uint32_t seconds = total_time % 60;

	char m1 = '0' + (minutes / 10);  // Tens place of minutes
	char m2 = '0' + (minutes % 10);  // Units place of minutes
	char s1 = '0' + (seconds / 10);  // Tens place of seconds
	char s2 = '0' + (seconds % 10);  // Units place of seconds

	LCD_DisplayChar(85,190,m1);
	LCD_DisplayChar(105,190,m2);
	LCD_DisplayChar(125,190,':');
	LCD_DisplayChar(145,190,s1);
	LCD_DisplayChar(165,190,s2);
}

void RND_NUM(void) { // issue here
	uint32_t RND;
	RNG_HandleTypeDef hrng;
	hrng.Instance = RNG;
	if (HAL_RNG_Init(&hrng) != HAL_OK)
	{
		while(1);
	}
    if (HAL_RNG_GenerateRandomNumber(&hrng, &RND) != HAL_OK) {
	    printf("Error Generating Random Number");
	}
	randomNumber = RND;
}

uint8_t check_State(void) {
	//Built for 0 row on top
	//CASES
	//	1. Hits bottom of screen -> Update Matrix, make new object
	//	2. Collision with a 1
	//		a. Is it at the top of the screen -> Update Matrix, end game
	//		b. Hits other block -> Update Matrix, make new object
	if((object.originbit.y == 0) || (object.suboriginbit_0.y == 0) ||
	   (object.suboriginbit_1.y == 0) || (object.suboriginbit_1.y == 0)) {
		Matrix_update();
		object_Select();
		printf("Hit bottom\n");
		return 0; // 0 -> Hit bottom

	} else if((dummyTable[object.originbit.y - 1][object.originbit.x] == 1) ||
			  (dummyTable[object.suboriginbit_0.y - 1][object.suboriginbit_0.x] == 1) ||
			  (dummyTable[object.suboriginbit_1.y - 1][object.suboriginbit_1.x] == 1) ||
			  (dummyTable[object.suboriginbit_2.y - 1][object.suboriginbit_2.x] == 1) ){
		uint8_t rowNonZeros[ROWS] = {0};
		uint32_t compareRow = 0x3FF; // Mask to check the first 10 bits
		for (int i = 0; i < ROWS; i++) {
		    for (int j = 0; j < COLS; j++) {
		        if (dummyTable[i][j] & compareRow) {  // Check if at least one bit in dummyTable[i][j] is non-zero
		            rowNonZeros[i] = 1;
		            break;  // Exit the inner loop once we've found a non-zero bit
		        }
		    }
		}

		for (int i = 0; i < ROWS; i++) {
		    if (rowNonZeros[i] == 0) {
		    	Matrix_update();
		    	object_Select();
		    	printf("Collision\n");
		        return 1; // 1 -> Not all rows have non-zero values
		    }
		}
		removeSchedulerEvent(MATRIX_UPDATE_EVENT);
		printf("Game End\n");
		return 2; // 2-> Collision with Block to end game

	} else {
		return 3; // 3-> Safe operation
	}
}

void object_Select(void){
	RND_NUM();
	randomNumber = randomNumber % 7;
	switch(randomNumber) {
		case(ORICKY):{
			Object Oricky = {
				.name = ORICKY,
				.Rotation = ROTATION_0 - 1,			  //       1
				.originbit = { .x = 5, .y = 12 },     // 1 [1] 1
				.suboriginbit_0 = {5, 12},
				.suboriginbit_1 = {5, 12},
				.suboriginbit_2 = {5, 12}
			};
			object = Oricky;
		    transform_rotation();
			break;
		}
		case(BRICKY):{
			Object Bricky = {
				.name = BRICKY,
				.Rotation = ROTATION_0 - 1,           // 1
				.originbit = { .x = 5, .y = 12 },     // 1 [1] 1
				.suboriginbit_0 = {5, 12},
				.suboriginbit_1 = {5, 12},
				.suboriginbit_2 = {5, 12}
			};
			object = Bricky;
			transform_rotation();
			break;
		}
		case(CLEVELAND):{
			Object Cleveland = {
				.name = CLEVELAND,
				.Rotation = ROTATION_0 - 1,           //   1 1
				.originbit = { .x = 5, .y = 12 }, 	  //    [1] 1
				.suboriginbit_0 = {5, 12},
				.suboriginbit_1 = {5, 12},
				.suboriginbit_2 = {5, 12}
			};
			object = Cleveland;
		    transform_rotation();
			break;
		}
		case(RHODE):{
			Object Rhode = {
				.name = RHODE,
				.Rotation = ROTATION_0 - 1,           //        1 1
				.originbit = { .x = 5, .y = 12 },     //     1 [1]
				.suboriginbit_0 = {5, 12},
				.suboriginbit_1 = {5, 12},
				.suboriginbit_2 = {5, 12}
			};
			object = Rhode;
			transform_rotation();
			break;
		}
		case(HERO):{
			Object Hero = {
				.name = HERO,
				.Rotation = ROTATION_0 - 1,          	     //
				.originbit = { .x = 5, .y = 12 }, 			 //  1 1 [1] 1
				.suboriginbit_0 = {5, 12},
				.suboriginbit_1 = {5, 12},
				.suboriginbit_2 = {5, 12}
			};
			object = Hero;
			transform_rotation();
			break;
		}
		case(TEEWEE):{
			Object Teewee = {
				.name = TEEWEE,
				.Rotation = ROTATION_0 - 1,          			//    1
				.originbit = { .x = 5, .y = 12 }, 			 	// 1 [1] 1
				.suboriginbit_0 = {5, 12},
				.suboriginbit_1 = {5, 12},
				.suboriginbit_2 = {5, 12}
			};
			object = Teewee;
			transform_rotation();
			break;
		}
		case(SMASHBOY):{
			Object Smashboy = {
				.name = SMASHBOY,
				.Rotation = ROTATION_0 - 1,          			// 1  1
				.originbit = { .x = 5, .y = 12 }, 			 	//[1] 1
				.suboriginbit_0 = {5, 12},
				.suboriginbit_1 = {5, 12},
				.suboriginbit_2 = {5, 12}
			};
			object = Smashboy;
			transform_rotation();
			break;
		}

	}

}


void shift_Left(void){
	Object temp = object;
	Matrix_clear();
	object.originbit.x -= 1;
	object.suboriginbit_0.x -= 1;
	object.suboriginbit_1.x -= 1;
	object.suboriginbit_2.x -= 1;
	object.Rotation -= 1;
	transform_rotation();
	if(check_State() == 1) {
		object = temp;
	}
	Matrix_update();
	printMatrix();
}
void shift_Right(void){
	Object temp = object;
	Matrix_clear();
	object.originbit.x += 1;
	object.suboriginbit_0.x += 1;
	object.suboriginbit_1.x += 1;
	object.suboriginbit_2.x += 1;
	object.Rotation -= 1;
	transform_rotation();
	if(check_State() == 1) {
		object = temp;
	}
	Matrix_update();
	printMatrix();
}

void tick_Matrix(void){
	//Object temp = object;
	Matrix_clear();
	object.originbit.y -= 1;
	object.suboriginbit_0.y -= 1;
	object.suboriginbit_1.y -= 1;
	object.suboriginbit_2.y -= 1;
	object.Rotation -= 1;
	transform_rotation();
	check_State();
/*
	if(check_State() == 1) {
		object = temp;
	}
*/
	Matrix_update();
	printMatrix();
}

void transform_rotation(void){
	//Matrix_clear();
	object.Rotation += 1;
	if((object.Rotation > 3) || (object.Rotation < 0)) {
		object.Rotation = 0;
	}

	switch(object.name){
		case(ORICKY):
			switch(object.Rotation) {
				case(ROTATION_0):
						//       1
						// 1 [1] 1
					object.suboriginbit_0.x = object.originbit.x - 1;   //		 1
					object.suboriginbit_0.y = object.originbit.y;		// [1] 1 1

					object.suboriginbit_1.x = object.originbit.x + 1;	//        1
					object.suboriginbit_1.y = object.originbit.y;		//  1  1 [1]

					object.suboriginbit_2.x = object.originbit.x + 1;	// 	  [1]
					object.suboriginbit_2.y = object.originbit.y + 1; 	// 1 1 1

					break;
				case(ROTATION_1):
						// 1  1
						//   [1]
						//    1
					object.suboriginbit_0.x = object.originbit.x;
					object.suboriginbit_0.y = object.originbit.y - 1;

					object.suboriginbit_1.x = object.originbit.x;
					object.suboriginbit_1.y = object.originbit.y + 1;

					object.suboriginbit_2.x = object.originbit.x - 1;
					object.suboriginbit_2.y = object.originbit.y + 1;

					break;
				case(ROTATION_2):
						// 1  [1]  1
						// 1
					object.suboriginbit_0.x = object.originbit.x + 1;
					object.suboriginbit_0.y = object.originbit.y;

					object.suboriginbit_1.x = object.originbit.x - 1;
					object.suboriginbit_1.y = object.originbit.y;

					object.suboriginbit_2.x = object.originbit.x - 1;
					object.suboriginbit_2.y = object.originbit.y - 1;

					break;
				case(ROTATION_3):
						//  1
						// [1]
						//  1 1
					object.suboriginbit_0.x = object.originbit.x;
					object.suboriginbit_0.y = object.originbit.y + 1;

					object.suboriginbit_1.x = object.originbit.x;
					object.suboriginbit_1.y = object.originbit.y - 1;

					object.suboriginbit_2.x = object.originbit.x + 1;
					object.suboriginbit_2.y = object.originbit.y - 1;

					break;
			}
			break;
		case(BRICKY):
			switch(object.Rotation) {
				case(ROTATION_0):
						// 1
						// 1 [1] 1
					object.suboriginbit_0.x = object.originbit.x - 1;   //	1
					object.suboriginbit_0.y = object.originbit.y;		// [1] 1 1

					object.suboriginbit_1.x = object.originbit.x + 1;	//  1
					object.suboriginbit_1.y = object.originbit.y;		//  1  1 [1]

					object.suboriginbit_2.x = object.originbit.x - 1;	//[1]
					object.suboriginbit_2.y = object.originbit.y + 1; 	// 1 1 1

					break;
				case(ROTATION_1):
						// 1 1
						//[1]
						// 1
					object.suboriginbit_0.x = object.originbit.x;
					object.suboriginbit_0.y = object.originbit.y + 1;

					object.suboriginbit_1.x = object.originbit.x + 1;
					object.suboriginbit_1.y = object.originbit.y + 1;

					object.suboriginbit_2.x = object.originbit.x;
					object.suboriginbit_2.y = object.originbit.y - 1;

					break;
				case(ROTATION_2):
						// 1 [1] 1
						//       1
					object.suboriginbit_0.x = object.originbit.x + 1;
					object.suboriginbit_0.y = object.originbit.y;

					object.suboriginbit_1.x = object.originbit.x - 1;
					object.suboriginbit_1.y = object.originbit.y;

					object.suboriginbit_2.x = object.originbit.x + 1;
					object.suboriginbit_2.y = object.originbit.y - 1;

					break;
				case(ROTATION_3):
						//   1
						//  [1]
						// 1 1
					object.suboriginbit_0.x = object.originbit.x;
					object.suboriginbit_0.y = object.originbit.y - 1;

					object.suboriginbit_1.x = object.originbit.x;
					object.suboriginbit_1.y = object.originbit.y + 1;

					object.suboriginbit_2.x = object.originbit.x - 1;
					object.suboriginbit_2.y = object.originbit.y + 1;

					break;
			}

			break;
		case(CLEVELAND):
			switch(object.Rotation) {
				case(ROTATION_0):
						// 1 1
						//  [1] 1
					object.suboriginbit_0.x = object.originbit.x;			 //	1 [1]
					object.suboriginbit_0.y = object.originbit.y + 1;		 //    1 1

					object.suboriginbit_1.x = object.originbit.x - 1;		 // [1] 1
					object.suboriginbit_1.y = object.originbit.y + 1;		 //     1 1

					object.suboriginbit_2.x = object.originbit.x + 1;		 //  1 1
					object.suboriginbit_2.y = object.originbit.y; 	     	//    1 [1]

					break;
				case(ROTATION_1):
						//     1
						// [1] 1
						//  1
					object.suboriginbit_0.x = object.originbit.x+1;
					object.suboriginbit_0.y = object.originbit.y;

					object.suboriginbit_1.x = object.originbit.x+1;
					object.suboriginbit_1.y = object.originbit.y+1;

					object.suboriginbit_2.x = object.originbit.x;
					object.suboriginbit_2.y = object.originbit.y-1;

					break;
				case(ROTATION_2):
						// 1 [1]
						//    1  1
					object.suboriginbit_0.x = object.originbit.x - 1;
					object.suboriginbit_0.y = object.originbit.y;

					object.suboriginbit_1.x = object.originbit.x;
					object.suboriginbit_1.y = object.originbit.y - 1;

					object.suboriginbit_2.x = object.originbit.x + 1;
					object.suboriginbit_2.y = object.originbit.y - 1;

					break;
				case(ROTATION_3):
						//     1
						//  1 [1]
						//  1
					object.suboriginbit_0.x = object.originbit.x - 1;
					object.suboriginbit_0.y = object.originbit.y;

					object.suboriginbit_1.x = object.originbit.x - 1;
					object.suboriginbit_1.y = object.originbit.y - 1;

					object.suboriginbit_2.x = object.originbit.x;
					object.suboriginbit_2.y = object.originbit.y + 1;

					break;
			}
			break;
		case(RHODE):
			switch(object.Rotation) {
				case(ROTATION_0):
						//    1 1
						// 1 [1]
					object.suboriginbit_0.x = object.originbit.x;			 //	  [1] 1
					object.suboriginbit_0.y = object.originbit.y + 1;		 //  1 1

					object.suboriginbit_1.x = object.originbit.x + 1;		 //    1 [1]
					object.suboriginbit_1.y = object.originbit.y + 1;		 //  1 1

					object.suboriginbit_2.x = object.originbit.x - 1;		 //     1 1
					object.suboriginbit_2.y = object.originbit.y; 	     // [1] 1

					break;
				case(ROTATION_1):
						// 1
						//[1] 1
						//    1
					object.suboriginbit_0.x = object.originbit.x;
					object.suboriginbit_0.y = object.originbit.y + 1;

					object.suboriginbit_1.x = object.originbit.x + 1;
					object.suboriginbit_1.y = object.originbit.y;

					object.suboriginbit_2.x = object.originbit.x + 1;
					object.suboriginbit_2.y = object.originbit.y - 1;

					break;
				case(ROTATION_2):
						//  [1] 1
						// 1 1
					object.suboriginbit_0.x = object.originbit.x + 1;
					object.suboriginbit_0.y = object.originbit.y;

					object.suboriginbit_1.x = object.originbit.x;
					object.suboriginbit_1.y = object.originbit.y - 1;

					object.suboriginbit_2.x = object.originbit.x - 1;
					object.suboriginbit_2.y = object.originbit.y - 1;

					break;
				case(ROTATION_3):
						// 1
						// 1 [1]
						//    1
					object.suboriginbit_0.x = object.originbit.x;
					object.suboriginbit_0.y = object.originbit.y - 1;

					object.suboriginbit_1.x = object.originbit.x - 1;
					object.suboriginbit_1.y = object.originbit.y;

					object.suboriginbit_2.x = object.originbit.x - 1;
					object.suboriginbit_2.y = object.originbit.y + 1;

					break;
			}
			break;
		case(HERO):
			switch(object.Rotation) {
				case(ROTATION_0):
						// 1 1 [1] 1
					object.suboriginbit_0.x = object.originbit.x - 1;	 //
					object.suboriginbit_0.y = object.originbit.y;		 // 1 [1] 1 1

					object.suboriginbit_1.x = object.originbit.x - 2;	 //
					object.suboriginbit_1.y = object.originbit.y;		 // [1] 1 1 1

					object.suboriginbit_2.x = object.originbit.x + 1;	 //
					object.suboriginbit_2.y = object.originbit.y; 	     //  1 1 1 [1]

					break;
				case(ROTATION_1):
						//  1
						//  1
						// [1]
						//  1
					object.suboriginbit_0.x = object.originbit.x;
					object.suboriginbit_0.y = object.originbit.y + 1;

					object.suboriginbit_1.x = object.originbit.x;
					object.suboriginbit_1.y = object.originbit.y - 1;

					object.suboriginbit_2.x = object.originbit.x;
					object.suboriginbit_2.y = object.originbit.y + 2;

					break;
				case(ROTATION_2):
						// 1 [1] 1 1
					object.suboriginbit_0.x = object.originbit.x - 1;
					object.suboriginbit_0.y = object.originbit.y;

					object.suboriginbit_1.x = object.originbit.x + 1;
					object.suboriginbit_1.y = object.originbit.y;

					object.suboriginbit_2.x = object.originbit.x + 2;
					object.suboriginbit_2.y = object.originbit.y;

					break;
				case(ROTATION_3):
						//  1
						// [1]
						//  1
						//  1
					object.suboriginbit_0.x = object.originbit.x;
					object.suboriginbit_0.y = object.originbit.y + 1;

					object.suboriginbit_1.x = object.originbit.x;
					object.suboriginbit_1.y = object.originbit.y - 1;

					object.suboriginbit_2.x = object.originbit.x;
					object.suboriginbit_2.y = object.originbit.y - 2;

					break;
			}

			break;
		case(TEEWEE):
			switch(object.Rotation) {
				case(ROTATION_0):
						//    1
						// 1 [1] 1
					object.suboriginbit_0.x = object.originbit.x - 1;	 //     1
					object.suboriginbit_0.y = object.originbit.y;		 // [1] 1 1

					object.suboriginbit_1.x = object.originbit.x + 1;	 //	  1
					object.suboriginbit_1.y = object.originbit.y;		 // 1 1 [1]

					object.suboriginbit_2.x = object.originbit.x;	     //	 [1]
					object.suboriginbit_2.y = object.originbit.y + 1; 	 // 1 1 1

					break;
				case(ROTATION_1):
						//  1
						// [1] 1
						//  1
					object.suboriginbit_0.x = object.originbit.x + 1;
					object.suboriginbit_0.y = object.originbit.y;

					object.suboriginbit_1.x = object.originbit.x;
					object.suboriginbit_1.y = object.originbit.y + 1;

					object.suboriginbit_2.x = object.originbit.x;
					object.suboriginbit_2.y = object.originbit.y - 1;

					break;
				case(ROTATION_2):
						// 1 [1] 1
						//    1
					object.suboriginbit_0.x = object.originbit.x;
					object.suboriginbit_0.y = object.originbit.y - 1;

					object.suboriginbit_1.x = object.originbit.x + 1;
					object.suboriginbit_1.y = object.originbit.y;

					object.suboriginbit_2.x = object.originbit.x - 1;
					object.suboriginbit_2.y = object.originbit.y;

					break;
				case(ROTATION_3):
						//    1
						// 1 [1]
						//    1
					object.suboriginbit_0.x = object.originbit.x - 1;
					object.suboriginbit_0.y = object.originbit.y;

					object.suboriginbit_1.x = object.originbit.x;
					object.suboriginbit_1.y = object.originbit.y + 1;

					object.suboriginbit_2.x = object.originbit.x;
					object.suboriginbit_2.y = object.originbit.y - 1;

					break;
			}

			break;
		case(SMASHBOY):
			switch(object.Rotation) {
				case(ROTATION_0):
					object.suboriginbit_0.x = object.originbit.x + 1;	 //  1  1
					object.suboriginbit_0.y = object.originbit.y;		 //  1 [1]

					object.suboriginbit_1.x = object.originbit.x;		 //	[1] 1
					object.suboriginbit_1.y = object.originbit.y + 1;	 //  1  1

					object.suboriginbit_2.x = object.originbit.x + 1;	 //	1 [1]
					object.suboriginbit_2.y = object.originbit.y + 1; 	 // 1  1

					break;
				case(ROTATION_1):

					object.suboriginbit_0.x = object.originbit.x + 1;	 //  1  1
					object.suboriginbit_0.y = object.originbit.y;		 //  1 [1]

					object.suboriginbit_1.x = object.originbit.x;		 //	[1] 1
					object.suboriginbit_1.y = object.originbit.y + 1;	 //  1  1

					object.suboriginbit_2.x = object.originbit.x + 1;	 //	1 [1]
					object.suboriginbit_2.y = object.originbit.y + 1; 	 // 1  1

					break;
				case(ROTATION_2):
					object.suboriginbit_0.x = object.originbit.x + 1;	 //  1  1
					object.suboriginbit_0.y = object.originbit.y;		 //  1 [1]

					object.suboriginbit_1.x = object.originbit.x;		 //	[1] 1
					object.suboriginbit_1.y = object.originbit.y + 1;	 //  1  1

					object.suboriginbit_2.x = object.originbit.x + 1;	 //	1 [1]
					object.suboriginbit_2.y = object.originbit.y + 1; 	 // 1  1

					break;
				case(ROTATION_3):

					object.suboriginbit_0.x = object.originbit.x + 1;	 //  1  1
					object.suboriginbit_0.y = object.originbit.y;		 //  1 [1]

					object.suboriginbit_1.x = object.originbit.x;		 //	[1] 1
					object.suboriginbit_1.y = object.originbit.y + 1;	 //  1  1

					object.suboriginbit_2.x = object.originbit.x + 1;	 //	1 [1]
					object.suboriginbit_2.y = object.originbit.y + 1; 	 // 1  1

					break;
			}
		break;
	}

}


void printMatrix(void){
	// Connect to the LCD screen and update that
	//LCD_Draw_Circle_Fill(x,y,radius,color);
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			uint8_t value = dummyTable[i][j];
			if(value){
				// Calculate top-left corner of the block
				int x = j * 24;//BLOCK_WIDTH;
				int y = i * 24;//BLOCK_HEIGHT;

				// Draw the block on the screen

				for (int row = 0; row < BLOCK_HEIGHT; row++) {
					for (int col = 0; col < BLOCK_WIDTH; col++) {
						LCD_Draw_Pixel(x+col,y+row,LCD_COLOR_RED);
					}
				}
			} else {
				int x = j * 24;//BLOCK_WIDTH;
				int y = i * 24;//BLOCK_HEIGHT;

				// Draw the block on the screen

				for (int row = 0; row < BLOCK_HEIGHT; row++) {
					for (int col = 0; col < BLOCK_WIDTH; col++) {
						LCD_Draw_Pixel(x+col,y+row,LCD_COLOR_WHITE);
					}
				}
			}
		}
	}
}


void Matrix_clear(void) {
	dummyTable[object.originbit.y][object.originbit.x] = 0;
	dummyTable[object.suboriginbit_0.y][object.suboriginbit_0.x] = 0;
	dummyTable[object.suboriginbit_1.y][object.suboriginbit_1.x] = 0;
	dummyTable[object.suboriginbit_2.y][object.suboriginbit_2.x] = 0;
}
void Matrix_update(void){
	dummyTable[object.originbit.y][object.originbit.x] = 1;
	dummyTable[object.suboriginbit_0.y][object.suboriginbit_0.x] = 1;
	dummyTable[object.suboriginbit_1.y][object.suboriginbit_1.x] = 1;
	dummyTable[object.suboriginbit_2.y][object.suboriginbit_2.x] = 1;
}
#endif
