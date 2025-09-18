/*!
@author Solomon ng
@course CSD1121F22
@section Section A.
@brief This file contains logic needed for the mainmenu.
All content © 2022 DigiPen (SINGAPORE) Corporation, all rights reserved.
*//*______________________________________________________________________*/
#include "mainmenu.h"
#include "stage1.h"
#include "Tutorial.h"
#include "utils.h"
//#include "splashscreen.h"
#include <stdio.h>
#include "cprocessing.h"
#include "stage3.h"
#include "bird.h"
#include "stage4.h"
#include "Highscore.h"
#include "credits.h"

button start_button;
button exit_button;
button game_button;
button credits_button;
CP_Sound Startstate = NULL;
float mainmenu_time;

static float elapsed_time;
static struct sprite_bird red_bird, blue_bird, green_bird, red2_bird, blue2_bird, green2_bird;
static CP_Image red_bird_Forward[4], blue_bird_Forward[4], green_bird_Forward[4], red2_bird_Forward[4], blue2_bird_Forward[4], green2_bird_Forward[4];
static CP_Image red_bird_Backwards[4], blue_bird_Backwards[4], green_bird_Backwards[4], red2_bird_Backwards[4], blue2_bird_Backwards[4], green2_bird_Backwards[4];
static CP_BOOL red_direction = TRUE;
static CP_BOOL blue_direction = TRUE;
static CP_BOOL green_direction = TRUE;
static CP_BOOL red2_direction = TRUE;
static CP_BOOL blue2_direction = TRUE;
static CP_BOOL green2_direction = TRUE;


static CP_BOOL red_bird_live = FALSE;
static CP_BOOL blue_bird_live = FALSE;
static CP_BOOL green_bird_live = FALSE;
static CP_BOOL red2_bird_live = FALSE;
static CP_BOOL blue2_bird_live = FALSE;
static CP_BOOL green2_bird_live = FALSE;

void Main_Menu_Init()
{
	// decalre window size
	CP_System_SetWindowSize(1800, 1200);
	Startstate = CP_Sound_Load("Assets/Start_State.wav"); //mainmenu sound
	mainmenu_time = 0.f;

	// Red Bird Parameters
	red_bird.speed = 300;
	red_bird.height = 150; //setting sprite to a smaller size 
	red_bird.width = 150;
	red_bird.alive_time = 0.f;
	elapsed_time = 0.0f;
	// Blue Bird Parameters
	blue_bird.speed = 300;
	blue_bird.height = 150; //setting sprite to a smaller size 
	blue_bird.width = 150;
	blue_bird.alive_time = 0.f;
	elapsed_time = 0.0f;
	// Green Bird Parameters
	green_bird.speed = 300;
	green_bird.height = 150; //setting sprite to a smaller size 
	green_bird.width = 150;
	green_bird.alive_time = 0.f;

	// Red2 Bird Parameters
	red2_bird.speed = 300;
	red2_bird.height = 150; //setting sprite to a smaller size 
	red2_bird.width = 150;
	red2_bird.alive_time = 0.f;
	elapsed_time = 0.0f;
	// Blue2 Bird Parameters
	blue2_bird.speed = 300;
	blue2_bird.height = 150; //setting sprite to a smaller size 
	blue2_bird.width = 150;
	blue2_bird.alive_time = 0.f;
	elapsed_time = 0.0f;
	// Green2 Bird Parameters
	green2_bird.speed = 300;
	green2_bird.height = 150; //setting sprite to a smaller size 
	green2_bird.width = 150;
	green2_bird.alive_time = 0.f;

	// Animating the red bird using array moving forward
	red_bird_Forward[0] = CP_Image_Load("Assets/Red Bird 1.png");
	red_bird_Forward[1] = CP_Image_Load("Assets/Red Bird 2.png");
	red_bird_Forward[2] = CP_Image_Load("Assets/Red Bird 3.png");
	red_bird_Forward[3] = CP_Image_Load("Assets/Red Bird 2.png");
	// Animating the red bird using array moving backwards
	red_bird_Backwards[0] = CP_Image_Load("Assets/Red Bird 1 Reverse.png");
	red_bird_Backwards[1] = CP_Image_Load("Assets/Red Bird 2 Reverse.png");
	red_bird_Backwards[2] = CP_Image_Load("Assets/Red Bird 3 Reverse.png");
	red_bird_Backwards[3] = CP_Image_Load("Assets/Red Bird 2 Reverse.png");

	// Animating the blue bird using array moving forward
	blue_bird_Forward[0] = CP_Image_Load("Assets/Blue Bird 1.png");
	blue_bird_Forward[1] = CP_Image_Load("Assets/Blue Bird 2.png");
	blue_bird_Forward[2] = CP_Image_Load("Assets/Blue Bird 3.png");
	blue_bird_Forward[3] = CP_Image_Load("Assets/Blue Bird 2.png");

	// Animate the blue bird using array moving backwards
	blue_bird_Backwards[0] = CP_Image_Load("Assets/Blue Bird 1 Reverse.png");
	blue_bird_Backwards[1] = CP_Image_Load("Assets/Blue Bird 2 Reverse.png");
	blue_bird_Backwards[2] = CP_Image_Load("Assets/Blue Bird 3 Reverse.png");
	blue_bird_Backwards[3] = CP_Image_Load("Assets/Blue Bird 2 Reverse.png");

	//Animate the green bird using array moving forward
	green_bird_Forward[0] = CP_Image_Load("Assets/Green Bird 1.png");
	green_bird_Forward[1] = CP_Image_Load("Assets/Green Bird 2.png");
	green_bird_Forward[2] = CP_Image_Load("Assets/Green Bird 3.png");
	green_bird_Forward[3] = CP_Image_Load("Assets/Green Bird 2.png");

	//Animate the green bird using array moving backward
	green_bird_Backwards[0] = CP_Image_Load("Assets/Green Bird 1 Reverse.png");
	green_bird_Backwards[1] = CP_Image_Load("Assets/Green Bird 2 Reverse.png");
	green_bird_Backwards[2] = CP_Image_Load("Assets/Green Bird 3 Reverse.png");
	green_bird_Backwards[3] = CP_Image_Load("Assets/Green Bird 2 Reverse.png");

	// Animating the red2 bird using array moving forward
	red2_bird_Forward[0] = CP_Image_Load("Assets/Red Bird 1.png");
	red2_bird_Forward[1] = CP_Image_Load("Assets/Red Bird 2.png");
	red2_bird_Forward[2] = CP_Image_Load("Assets/Red Bird 3.png");
	red2_bird_Forward[3] = CP_Image_Load("Assets/Red Bird 2.png");
	// Animating the red2 bird using array moving backwards
	red2_bird_Backwards[0] = CP_Image_Load("Assets/Red Bird 1 Reverse.png");
	red2_bird_Backwards[1] = CP_Image_Load("Assets/Red Bird 2 Reverse.png");
	red2_bird_Backwards[2] = CP_Image_Load("Assets/Red Bird 3 Reverse.png");
	red2_bird_Backwards[3] = CP_Image_Load("Assets/Red Bird 2 Reverse.png");

	// Animating the blue2 bird using array moving forward
	blue2_bird_Forward[0] = CP_Image_Load("Assets/Blue Bird 1.png");
	blue2_bird_Forward[1] = CP_Image_Load("Assets/Blue Bird 2.png");
	blue2_bird_Forward[2] = CP_Image_Load("Assets/Blue Bird 3.png");
	blue2_bird_Forward[3] = CP_Image_Load("Assets/Blue Bird 2.png");

	// Animate the blue2 bird using array moving backwards
	blue2_bird_Backwards[0] = CP_Image_Load("Assets/Blue Bird 1 Reverse.png");
	blue2_bird_Backwards[1] = CP_Image_Load("Assets/Blue Bird 2 Reverse.png");
	blue2_bird_Backwards[2] = CP_Image_Load("Assets/Blue Bird 3 Reverse.png");
	blue2_bird_Backwards[3] = CP_Image_Load("Assets/Blue Bird 2 Reverse.png");

	//Animate the green2 bird using array moving forward
	green2_bird_Forward[0] = CP_Image_Load("Assets/Green Bird 1.png");
	green2_bird_Forward[1] = CP_Image_Load("Assets/Green Bird 2.png");
	green2_bird_Forward[2] = CP_Image_Load("Assets/Green Bird 3.png");
	green2_bird_Forward[3] = CP_Image_Load("Assets/Green Bird 2.png");

	//Animate the green2 bird using array moving backward
	green2_bird_Backwards[0] = CP_Image_Load("Assets/Green Bird 1 Reverse.png");
	green2_bird_Backwards[1] = CP_Image_Load("Assets/Green Bird 2 Reverse.png");
	green2_bird_Backwards[2] = CP_Image_Load("Assets/Green Bird 3 Reverse.png");
	green2_bird_Backwards[3] = CP_Image_Load("Assets/Green Bird 2 Reverse.png");
}

void Main_Menu_Update()
{
	// Movement of the bird.
	elapsed_time += CP_System_GetDt() * 4;
	int time = (int)elapsed_time;
	int sprite_position = time % 4;

	//Setting random position X and Position Y.
	if (red_bird_live == FALSE)
	{
		red_bird.x = RandomNumberX(red_bird.width);
		red_bird.y = RandomNumberY(red_bird.height);
		red_bird_live = TRUE;
	}
	//Setting random position X and Position Y.
	if (blue_bird_live == FALSE)
	{
		blue_bird.x = RandomNumberX(blue_bird.width);
		blue_bird.y = RandomNumberY(blue_bird.height);
		blue_bird_live = TRUE;
	}
	//Setting random position X and Position Y.
	if (green_bird_live == FALSE)
	{
		green_bird.x = RandomNumberX(green_bird.width);
		green_bird.y = RandomNumberY(green_bird.height);
		green_bird_live = TRUE;
	}

	//Setting random position X and Position Y.
	if (red2_bird_live == FALSE)
	{
		red2_bird.x = RandomNumberX(red2_bird.width);
		red2_bird.y = RandomNumberY(red2_bird.height);
		red2_bird_live = TRUE;
	}
	//Setting random position X and Position Y.
	if (blue2_bird_live == FALSE)
	{
		blue2_bird.x = RandomNumberX(blue2_bird.width);
		blue2_bird.y = RandomNumberY(blue2_bird.height);
		blue2_bird_live = TRUE;
	}
	//Setting random position X and Position Y.
	if (green2_bird_live == FALSE)
	{
		green2_bird.x = RandomNumberX(green2_bird.width);
		green2_bird.y = RandomNumberY(green2_bird.height);
		green2_bird_live = TRUE;
	}

	if (red_bird_live == TRUE)
	{
		// Set right most limit of the screen.
		if (red_bird.x >= 1800)
		{
			red_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (red_bird.x <= 0)
		{
			red_direction = TRUE;
		}

		// move right.
		if (red_direction)
		{
			red_bird.x += red_bird.speed * CP_System_GetDt();
			CP_Image_Draw(red_bird_Forward[sprite_position], red_bird.x, red_bird.y, red_bird.width, red_bird.height, 255);
		}
		// move left
		else if (!red_direction)
		{
			red_bird.x -= red_bird.speed * CP_System_GetDt();
			CP_Image_Draw(red_bird_Backwards[sprite_position], red_bird.x, red_bird.y, red_bird.width, red_bird.height, 255);
		}

	}

	if (blue_bird_live == TRUE)
	{
		// Set right most limit of the screen.
		if (blue_bird.x >= 1800)
		{
			blue_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (blue_bird.x <= 0)
		{
			blue_direction = TRUE;
		}

		// move right.
		if (blue_direction)
		{
			blue_bird.x += blue_bird.speed * CP_System_GetDt();
			CP_Image_Draw(blue_bird_Forward[sprite_position], blue_bird.x, blue_bird.y, blue_bird.width, blue_bird.height, 255);
		}
		// move left
		else if (!blue_direction)
		{
			blue_bird.x -= blue_bird.speed * CP_System_GetDt();
			CP_Image_Draw(blue_bird_Backwards[sprite_position], blue_bird.x, blue_bird.y, blue_bird.width, blue_bird.height, 255);
		}

	}
	if (green_bird_live == TRUE)
	{
		// Set right most limit of the screen.
		if (green_bird.x >= 1800)
		{
			green_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (green_bird.x <= 0)
		{
			green_direction = TRUE;
		}

		// move right.
		if (green_direction)
		{
			green_bird.x += green_bird.speed * CP_System_GetDt();
			CP_Image_Draw(green_bird_Forward[sprite_position], green_bird.x, green_bird.y, green_bird.width, green_bird.height, 255);
		}
		// move left
		else if (!green_direction)
		{
			green_bird.x -= green_bird.speed * CP_System_GetDt();
			CP_Image_Draw(green_bird_Backwards[sprite_position], green_bird.x, green_bird.y, green_bird.width, green_bird.height, 255);
		}
	}
	if (red2_bird_live == TRUE)
	{
		// Set right most limit of the screen.
		if (red2_bird.x >= 1800)
		{
			red2_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (red2_bird.x <= 0)
		{
			red2_direction = TRUE;
		}

		// move right.
		if (red2_direction)
		{
			red2_bird.x += red2_bird.speed * CP_System_GetDt();
			CP_Image_Draw(red2_bird_Forward[sprite_position], red2_bird.x, red2_bird.y, red2_bird.width, red2_bird.height, 255);
		}
		// move left
		else if (!red2_direction)
		{
			red2_bird.x -= red2_bird.speed * CP_System_GetDt();
			CP_Image_Draw(red2_bird_Backwards[sprite_position], red2_bird.x, red2_bird.y, red2_bird.width, red2_bird.height, 255);
		}

	}

	if (blue2_bird_live == TRUE)
	{
		// Set right most limit of the screen.
		if (blue2_bird.x >= 1800)
		{
			blue2_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (blue2_bird.x <= 0)
		{
			blue2_direction = TRUE;
		}

		// move right.
		if (blue2_direction)
		{
			blue2_bird.x += blue2_bird.speed * CP_System_GetDt();
			CP_Image_Draw(blue2_bird_Forward[sprite_position], blue2_bird.x, blue2_bird.y, blue2_bird.width, blue2_bird.height, 255);
		}
		// move left
		else if (!blue2_direction)
		{
			blue2_bird.x -= blue2_bird.speed * CP_System_GetDt();
			CP_Image_Draw(blue2_bird_Backwards[sprite_position], blue2_bird.x, blue2_bird.y, blue2_bird.width, blue2_bird.height, 255);
		}

	}
	if (green2_bird_live == TRUE)
	{
		// Set right most limit of the screen.
		if (green2_bird.x >= 1800)
		{
			green2_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (green2_bird.x <= 0)
		{
			green2_direction = TRUE;
		}

		// move right.
		if (green2_direction)
		{
			green2_bird.x += green2_bird.speed * CP_System_GetDt();
			CP_Image_Draw(green2_bird_Forward[sprite_position], green2_bird.x, green2_bird.y, green2_bird.width, green2_bird.height, 255);
		}
		// move left
		else if (!green2_direction)
		{
			green2_bird.x -= green2_bird.speed * CP_System_GetDt();
			CP_Image_Draw(green2_bird_Backwards[sprite_position], green2_bird.x, green2_bird.y, green2_bird.width, green2_bird.height, 255);
		}

	}

	if (mainmenu_time == 0.f)
	{
		mainmenu_time += CP_System_GetDt();
		CP_Sound_PlayMusic(Startstate);
	}

	// clear background
	CP_Color backgroundcolour = CP_Color_Create(245, 245, 220, 0);
	CP_Graphics_ClearBackground(backgroundcolour);

	// decalre the infomation of the game button
	game_button.colour = CP_Color_Create(150, 229, 136, 255);
	game_button.height = 70.0;
	game_button.width = 450.0;
	game_button.centre_point.x = (float)CP_System_GetWindowWidth() / 2;
	game_button.centre_point.y = (float)CP_System_GetWindowHeight() / 1.7;

	// declare the infomation of the tutorial button
	start_button.colour = CP_Color_Create(255, 255, 0, 255);
	start_button.height = 70.0;
	start_button.width = 450.0;
	start_button.centre_point.x = (float) CP_System_GetWindowWidth() / 2;
	start_button.centre_point.y = game_button.centre_point.y + 90;

	// declare the infomation of the credits button
	credits_button.colour = CP_Color_Create(210, 4, 45, 255);
	credits_button.height = 70.0;
	credits_button.width = 450.0;
	credits_button.centre_point.x = (float)CP_System_GetWindowWidth() / 2;
	credits_button.centre_point.y = start_button.centre_point.y + 90;

	// declare the infomation of the exit button
	exit_button.colour = CP_Color_Create(255, 190, 142, 255);
	exit_button.height = 70.0;
	exit_button.width = 450.0;
	exit_button.centre_point.x = (float) CP_System_GetWindowWidth() / 2;
	exit_button.centre_point.y = credits_button.centre_point.y + 90;


	// set the anchor of the rectangle to be the center
	CP_Settings_RectMode(CP_POSITION_CENTER);

	if (IsAreaClicked(game_button.centre_point.x, game_button.centre_point.y, game_button.width, game_button.height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		// define the start rectangle, set the color of the start button
		// and set the position
		CP_Settings_Fill(game_button.colour);
		CP_Graphics_DrawRect(game_button.centre_point.x, game_button.centre_point.y, game_button.width + 20, game_button.height + 20);
		// set the text to be anchored to its center
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		// set the text size
		CP_Settings_TextSize(70.0f);
		// set text colour to black
		CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(textcolour);
		// insert the game of life word
		CP_Font_DrawText("START!", game_button.centre_point.x, game_button.centre_point.y);
	}
	else {
		// define the start rectangle, set the color of the start button
		// and set the position
		CP_Settings_Fill(game_button.colour);
		CP_Graphics_DrawRect(game_button.centre_point.x, game_button.centre_point.y, game_button.width, game_button.height);
		// set the text to be anchored to its center
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		// set the text size
		CP_Settings_TextSize(50.0f);
		// set text colour to black
		CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(textcolour);
		// insert the game of life word
		CP_Font_DrawText("START", game_button.centre_point.x, game_button.centre_point.y);
	}

	if (IsAreaClicked(start_button.centre_point.x, start_button.centre_point.y, start_button.width, start_button.height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		// define the game rectangle, set the color of the start button
		// and set the position
		CP_Settings_Fill(start_button.colour);
		CP_Graphics_DrawRect(start_button.centre_point.x, start_button.centre_point.y, start_button.width + 20, start_button.height + 20);
		// set the text to be anchored to its center
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		// set the text size
		CP_Settings_TextSize(67.0f);
		// set text colour to black
		CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(textcolour);
		// insert the start word
		CP_Font_DrawText("TUTORIAL", start_button.centre_point.x, start_button.centre_point.y);
	}
	else {
		// define the game rectangle, set the color of the start button
		// and set the position
		CP_Settings_Fill(start_button.colour);
		CP_Graphics_DrawRect(start_button.centre_point.x, start_button.centre_point.y, start_button.width, start_button.height);
		// set the text to be anchored to its center
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		// set the text size
		CP_Settings_TextSize(50.0f);
		// set text colour to black
		CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(textcolour);
		// insert the start word
		CP_Font_DrawText("TUTORIAL", start_button.centre_point.x, start_button.centre_point.y);
	}

	if (IsAreaClicked(credits_button.centre_point.x, credits_button.centre_point.y, credits_button.width, credits_button.height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		// define the start rectangle, set the color of the start button
		// and set the position
		CP_Settings_Fill(credits_button.colour);
		CP_Graphics_DrawRect(credits_button.centre_point.x, credits_button.centre_point.y, credits_button.width + 20, credits_button.height + 20);
		// set the text to be anchored to its center
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		// set the text size
		CP_Settings_TextSize(70.0f);
		// set text colour to black
		CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(textcolour);
		// insert the start word
		CP_Font_DrawText("CREDITS", credits_button.centre_point.x, credits_button.centre_point.y);
	}
	else {
		// define the start rectangle, set the color of the start button
		// and set the position
		CP_Settings_Fill(credits_button.colour);
		CP_Graphics_DrawRect(credits_button.centre_point.x, credits_button.centre_point.y, credits_button.width, credits_button.height);
		// set the text to be anchored to its center
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		// set the text size
		CP_Settings_TextSize(50.0f);
		// set text colour to black
		CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(textcolour);
		// insert the start word
		CP_Font_DrawText("CREDITS", credits_button.centre_point.x, credits_button.centre_point.y);
	}

	if (IsAreaClicked(exit_button.centre_point.x, exit_button.centre_point.y, exit_button.width, exit_button.height, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		// define the start rectangle, set the color of the start button
		// and set the position
		CP_Settings_Fill(exit_button.colour);
		CP_Graphics_DrawRect(exit_button.centre_point.x, exit_button.centre_point.y, exit_button.width + 20, exit_button.height + 20);
		// set the text to be anchored to its center
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		// set the text size
		CP_Settings_TextSize(70.0f);
		// set text colour to black
		CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(textcolour);
		// insert the start word
		CP_Font_DrawText("EXIT", exit_button.centre_point.x, exit_button.centre_point.y);
	}
	else {
		// define the start rectangle, set the color of the start button
		// and set the position
		CP_Settings_Fill(exit_button.colour);
		CP_Graphics_DrawRect(exit_button.centre_point.x, exit_button.centre_point.y, exit_button.width, exit_button.height);
		// set the text to be anchored to its center
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		// set the text size
		CP_Settings_TextSize(50.0f);
		// set text colour to black
		CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(textcolour);
		// insert the start word
		CP_Font_DrawText("EXIT", exit_button.centre_point.x, exit_button.centre_point.y);
	}

	float textsize = 150.0f;
	CP_Settings_TextSize(textsize);
	CP_Font_DrawText("SHOOTDABIRD", exit_button.centre_point.x, game_button.centre_point.y - 250);


	// check if the mouse is clicked
	if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT))
	{
		if (IsAreaClicked(game_button.centre_point.x, game_button.centre_point.y, game_button.width, game_button.height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameState(stage1_init, stage1_update, stage1_exit);
		}
		
		else if (IsAreaClicked(start_button.centre_point.x, start_button.centre_point.y, start_button.width, start_button.height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameState(tutorial_Init, tutorial_Update, tutorial_Exit);
		}

		else if (IsAreaClicked(credits_button.centre_point.x, credits_button.centre_point.y, credits_button.width, credits_button.height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameState(credits_init, credits_update, credits_exit);
		}

		else if (IsAreaClicked(exit_button.centre_point.x, exit_button.centre_point.y, exit_button.width, exit_button.height, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_Terminate();
		}
	}
}

void Main_Menu_Exit()
{
	for (int i = 0; i < 4; i++)
	{
		CP_Image_Free(&red_bird_Forward[i]);
		CP_Image_Free(&red_bird_Backwards[i]);

		CP_Image_Free(&blue_bird_Forward[i]);
		CP_Image_Free(&blue_bird_Backwards[i]);

		CP_Image_Free(&green_bird_Forward[i]);
		CP_Image_Free(&green_bird_Backwards[i]);

		CP_Image_Free(&red2_bird_Forward[i]);
		CP_Image_Free(&red2_bird_Backwards[i]);

		CP_Image_Free(&blue2_bird_Forward[i]);
		CP_Image_Free(&blue2_bird_Backwards[i]);

		CP_Image_Free(&green2_bird_Forward[i]);
		CP_Image_Free(&green2_bird_Backwards[i]);
	}
	CP_Sound_Free(&Startstate);
}