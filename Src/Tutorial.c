/*!
@author Wilmer
@course CSD1121F22
@section Section A.
@brief This file provides the tutorial page
All content © 2022 DigiPen (SINGAPORE) Corporation, all rights reserved.
*//*______________________________________________________________________*/
#include "cprocessing.h"
#include "mainmenu.h"
#include "Tutorial.h"
#include "utils.h"
#include <stdio.h>

static CP_Image BackButton = NULL;
static CP_Image Tutorial = NULL;
static int window_width, window_height;
struct Tutorial Tutorial_button;


void tutorial_Init()
{
	// set the window title 
	CP_System_SetWindowTitle("Tutorial");

	window_width = 1800;
	window_height = 1200;
	CP_System_SetWindowSize(window_width, window_height);
	
	//Load image of back button
	BackButton = CP_Image_Load("Assets/Back Arrow.png");
	Tutorial = CP_Image_Load("Assets/GameTutorial.png");
	
}

void tutorial_Update()
{
	CP_System_SetWindowTitle("Tutorial");
	// clear background
	CP_Image_Draw(Tutorial, window_width/2.f, window_height/2.f, window_width, window_height, 255);
		
	// Logic if click Back button will go back mainmenu
	CP_Image_Draw(BackButton, 80, 100, 150,150, 255);
	if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT))
	{
		if (IsAreaClicked(80, 100, 300, 300, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
		}
	}

	// if escape key is triggered
	if (CP_Input_KeyDown(KEY_ESCAPE)) {
		CP_Engine_Terminate();
	}
}

void tutorial_Exit()
{

}