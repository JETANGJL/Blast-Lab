/*!
@author Alexis Tan
@course CSD1121F22
@section Section A.
@brief This file provides the first page for the credits
Copyright © 2022 DigiPen, All rights reserved.
*//*______________________________________________________________________*/
#include <stdio.h>
#include "cprocessing.h"
#include "mainmenu.h"
#include "stage1.h"
#include "utils.h"
#include "stage3.h"
#include "bird.h"
#include "stage4.h"
#include "Highscore.h"
#include "credits.h"



#define TRUE 1
#define FALSE 0


static CP_Image credits[2];
float elapsed_time;
int credit_time;
int window_width;
int window_height;

void credits2_init(void)
{
	// Animating the red bird using array moving forward
	credits[0] = CP_Image_Load("Assets/credits0.jpg");
	credits[1] = CP_Image_Load("Assets/credits1.jpg");
	elapsed_time = 0.f;
	// Initalise variables for the window height and width
	window_width = 1800;
	window_height = 1200;
	CP_System_SetWindowSize(window_width, window_height);
}

void credits2_update(void)
{
	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_SetNextGameState(credits_init, credits_update, credits_exit);
	}

	elapsed_time += CP_System_GetDt() * 0.5;
	credit_time = (int)elapsed_time;
	int credits_position = credit_time % 2;
	CP_Image_Draw(credits[credits_position], window_width / 2, window_height / 2, window_width, window_height, 255);
}

void credits2_exit(void)
{
	for (int i = 0; i < 2; i++)
	{
		CP_Image_Free(credits[i]);
	}
}
