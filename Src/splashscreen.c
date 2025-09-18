/*!
@author Ang Jie Le Jet
@course CSD1121F22
@section Section A.
@brief This file contains logic needed for splashscreen
All content © 2022 DigiPen (SINGAPORE) Corporation, all rights reserved.
*//*______________________________________________________________________*/
#include "cprocessing.h"
#include "splashscreen.h"
#include "mainmenu.h"

CP_Image digipen_logo = NULL;
// Declare accumulated time type
float accumulated_time;
float totalSeconds;
int window_width;
int window_height;

void splash_screen_init(void)
{
	// Initialise accumulated time as 0.0 in float value
	accumulated_time = 0.0f;

	// Initialised digipen_logo by loading image in file.png
	digipen_logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_WHITE.png");
	//digipen_logo = CP_Image_Load("./DigiPen_Singapore_WEB_RED.png");

	window_width = 1800;
	window_height = 1200;
	CP_System_SetWindowSize(window_width, window_height);
}

void splash_screen_update(void)
{
	// If escape key pressed game terminates
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}
	//counter
	totalSeconds = CP_System_GetSeconds();

	// Create a background color
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 50));

	// Get the width and height of the the windows
	int w = window_width;
	int h = window_height;
	CP_Image_Draw(digipen_logo, w / 2, h / 2, w / 2, h / 3, 255);


	//change game state after timer
	if (totalSeconds > 4.0) {
		CP_Engine_SetNextGameStateForced(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void splash_screen_exit(void)
{
	// Exit from engine
	CP_Image_Free(&digipen_logo);
	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
}