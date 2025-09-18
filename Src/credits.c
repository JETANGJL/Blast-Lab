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

static float clouds_x_1, clouds_y_1, clouds_x_2, clouds_y_2, clouds_x_3, clouds_y_3, countdown_timer, elapsed_time;
static struct sprite_bird red_bird, blue_bird, green_bird, black_bird;
static CP_Image red_bird_Forward[4], blue_bird_Forward[4], green_bird_Forward[4], black_bird_Forward[4];
static CP_Image red_bird_Backwards[4], blue_bird_Backwards[4], green_bird_Backwards[4], black_bird_Backwards[4];
static CP_BOOL red_direction = TRUE;
static CP_BOOL blue_direction = FALSE;
static CP_BOOL green_direction = FALSE;
static CP_BOOL black_direction = FALSE;
static crosshair basic;

//Variables for sounds
static CP_Sound gunshot = NULL;
static CP_Sound Score = NULL;
static CP_Sound BGM = NULL;
static CP_Sound Bird_Effects = NULL;

static int window_width, window_height;

static CP_BOOL red_bird_live = TRUE;
static CP_BOOL blue_bird_live = TRUE;
static CP_BOOL green_bird_live = TRUE;
static CP_BOOL black_bird_live = TRUE;

button Alexis;
button Jet;
button Solo;
button Wilmer;

// Variable for background aesthetics
static CP_Image clouds_1 = NULL, clouds_2 = NULL, clouds_3 = NULL;

void credits_init(void)
{
	red_bird_live = TRUE;
	blue_bird_live = TRUE;
	green_bird_live = TRUE;
	black_bird_live = TRUE;

	//crosshair
	basic.height = 1;
	basic.width = 9;
	basic.height1 = 9;
	basic.width1 = 1;

	// Red Bird Parameters
	red_bird.speed = 300;
	red_bird.height = 150; //setting sprite to a smaller size 
	red_bird.width = 150;

	// Blue Bird Parameters
	blue_bird.speed = 300;
	blue_bird.height = 150; //setting sprite to a smaller size 
	blue_bird.width = 150;

	// Green Bird Parameters
	green_bird.speed = 300;
	green_bird.height = 150; //setting sprite to a smaller size 
	green_bird.width = 150;

	// Black Bird Parameters
	black_bird.speed = 300;
	black_bird.height = 150; //setting sprite to a smaller size 
	black_bird.width = 150;

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

	// Animating the green bird using array moving forward
	green_bird_Forward[0] = CP_Image_Load("Assets/Green Bird 1.png");
	green_bird_Forward[1] = CP_Image_Load("Assets/Green Bird 2.png");
	green_bird_Forward[2] = CP_Image_Load("Assets/Green Bird 3.png");
	green_bird_Forward[3] = CP_Image_Load("Assets/Green Bird 2.png");

	// Animate the green bird using array moving backwards
	green_bird_Backwards[0] = CP_Image_Load("Assets/Green Bird 1 Reverse.png");
	green_bird_Backwards[1] = CP_Image_Load("Assets/Green Bird 2 Reverse.png");
	green_bird_Backwards[2] = CP_Image_Load("Assets/Green Bird 3 Reverse.png");
	green_bird_Backwards[3] = CP_Image_Load("Assets/Green Bird 2 Reverse.png");

	// Animating the black bird using array moving forward
	black_bird_Forward[0] = CP_Image_Load("Assets/Decoy Bird 1.png");
	black_bird_Forward[1] = CP_Image_Load("Assets/Decoy Bird 2.png");
	black_bird_Forward[2] = CP_Image_Load("Assets/Decoy Bird 3.png");
	black_bird_Forward[3] = CP_Image_Load("Assets/Decoy Bird 2.png");

	// Animate the black bird using array moving backwards
	black_bird_Backwards[0] = CP_Image_Load("Assets/Decoy Bird 1 Reverse.png");
	black_bird_Backwards[1] = CP_Image_Load("Assets/Decoy Bird 2 Reverse.png");
	black_bird_Backwards[2] = CP_Image_Load("Assets/Decoy Bird 3 Reverse.png");
	black_bird_Backwards[3] = CP_Image_Load("Assets/Decoy Bird 2 Reverse.png");

	// Initalise variables for the window height and width
	window_width = 1800;
	window_height = 1200;
	CP_System_SetWindowSize(window_width, window_height);

	gunshot = CP_Sound_Load("Assets/Gunshot (Laser).wav");
	Score = CP_Sound_Load("Assets/Increase_Score.wav");
	BGM = CP_Sound_Load("Assets/Background (Beach).wav");
	Bird_Effects = CP_Sound_Load("../Assets/Bird_Flapping.wav");

	// Load background aesthetics
	clouds_1 = CP_Image_Load("Assets/Cloud.png");
	clouds_2 = CP_Image_Load("Assets/Cloud.png");
	clouds_3 = CP_Image_Load("Assets/Cloud.png");

	countdown_timer = 0.f;
	elapsed_time = 0.f;

	red_bird.x = 0.f;
	red_bird.y = window_width / 7;
	blue_bird.x = window_width / 2.f;
	blue_bird.y = window_width / 8;
	green_bird.x = window_width / 4.f;
	green_bird.y = window_width / 6;
	black_bird.x = (3.f * window_width) / 4.f;
	black_bird.y = window_width / 5;

	Jet.colour = CP_Color_Create(0, 255, 0, 255);
	Jet.height = 100.0;
	Jet.width = 500.0;
	Jet.centre_point.x = red_bird.x;
	Jet.centre_point.y = red_bird.y;

	Solo.colour = CP_Color_Create(0, 255, 0, 255);
	Solo.height = 100.0;
	Solo.width = 500.0;
	Solo.centre_point.x = blue_bird.x;
	Solo.centre_point.y = blue_bird.y;

	Wilmer.colour = CP_Color_Create(0, 255, 0, 255);
	Wilmer.height = 100.0;
	Wilmer.width = 500.0;
	Wilmer.centre_point.x = green_bird.x;
	Wilmer.centre_point.y = green_bird.y;

	Alexis.colour = CP_Color_Create(0, 255, 0, 255);
	Alexis.height = 100.0;
	Alexis.width = 500.0;
	Alexis.centre_point.x = black_bird.x; 
	Alexis.centre_point.y = black_bird.y;

	
}

void credits_update(void)
{
	CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(black);
	CP_Settings_TextSize(80.0f);
	CP_Font_DrawText("SHOOT THE BIRDS FOR THE CREDITS!", window_width / 2, window_height / 2);
	CP_Settings_TextSize(60.0f);
	CP_Font_DrawText("FOR MORE CREDITS, CLICK NEXT!", window_width / 2, window_height / 2 + 70);

	// Draw circle for the next credits scene
	CP_Graphics_DrawCircle(window_width / 2 - 700, window_height / 2 + 35, 120);
	CP_Graphics_DrawCircle(window_width / 2 + 700, window_height / 2 + 35, 120);

	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Settings_Fill(white);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("BACK", window_width / 2 - 700, window_height / 2 + 35);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("NEXT", window_width / 2 + 700, window_height / 2 + 35);

	if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT))
	{
		if (IsCircleClicked(window_width / 2 - 700, window_height / 2 + 35, 120 ,CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Update);
		}

		else if (IsCircleClicked(window_width / 2 + 700, window_height / 2 + 35, 120, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			CP_Engine_SetNextGameState(credits2_init, credits2_update, credits2_exit);
		}
	}

	if (CP_Input_KeyTriggered(KEY_ESCAPE))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Update);;
	}	

	// Draw background and animate clouds
	CP_Image_Draw(clouds_1, clouds_x_1, clouds_y_1, 600, 300, 170);
	CP_Image_Draw(clouds_2, clouds_x_2, clouds_y_2, 600, 300, 170);
	CP_Image_Draw(clouds_3, clouds_x_3, clouds_y_3, 600, 300, 170);

	clouds_x_1 += 1.f;
	clouds_x_2 += 1.f;
	clouds_x_3 += 1.f;

	// Movement of the bird.
	elapsed_time += CP_System_GetDt() * 4;
	int time = (int)elapsed_time;
	int sprite_position = time % 4;

	CP_Color backgroundcolour = CP_Color_Create(205, 205, 205, 170);
	CP_Graphics_ClearBackground(backgroundcolour);

	//Draw crosshair
	basic.x = CP_Input_GetMouseX() + 10;
	basic.y = CP_Input_GetMouseY();
	basic.x1 = CP_Input_GetMouseX() - 10;
	basic.y1 = CP_Input_GetMouseY();
	basic.x2 = CP_Input_GetMouseX();
	basic.y2 = CP_Input_GetMouseY() + 10;
	basic.x3 = CP_Input_GetMouseX();
	basic.y3 = CP_Input_GetMouseY() - 10;
	CP_Color crosshair = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(crosshair);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	

	if (red_bird_live == TRUE)
	{
		// Set right most limit of the screen.
		if (red_bird.x >= 1570)
		{
			red_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (red_bird.x <= 220)
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
		if (blue_bird.x >= 1550)
		{
			blue_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (blue_bird.x <= 250)
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
		if (green_bird.x >= 1550)
		{
			green_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (green_bird.x <= 250)
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

	if (black_bird_live == TRUE)
	{
		// Set right most limit of the screen.
		if (black_bird.x >= 1550)
		{
			black_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (black_bird.x <= 250)
		{
			black_direction = TRUE;
		}

		// move right.
		if (black_direction)
		{
			black_bird.x += black_bird.speed * CP_System_GetDt();
			CP_Image_Draw(black_bird_Forward[sprite_position], black_bird.x, black_bird.y, black_bird.width, black_bird.height, 255);
		}
		// move left
		else if (!black_direction)
		{
			black_bird.x -= black_bird.speed * CP_System_GetDt();
			CP_Image_Draw(black_bird_Backwards[sprite_position], black_bird.x, black_bird.y, black_bird.width, black_bird.height, 255);
		}

	}


	if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT)) //Logic for red_bird collision theory
	{
		CP_Sound_Play(gunshot);
		if (IsCircleClicked(red_bird.x, red_bird.y, 150, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
		{
			red_bird_live = FALSE;
			Jet.centre_point.x = red_bird.x;
		}

		else if (IsCircleClicked(blue_bird.x, blue_bird.y, 150, CP_Input_GetMouseX(), CP_Input_GetMouseY()))  //Logic for blue_bird collision theory
		{
			blue_bird_live = FALSE;
			Solo.centre_point.x = blue_bird.x;
		}

		else if (IsCircleClicked(green_bird.x, green_bird.y, 150, CP_Input_GetMouseX(), CP_Input_GetMouseY())) //Logic for green_bird collision theory
		{
			green_bird_live = FALSE;
			Wilmer.centre_point.x = green_bird.x;
		}

		else if (IsCircleClicked(black_bird.x, black_bird.y, 150, CP_Input_GetMouseX(), CP_Input_GetMouseY())) //Logic for green_bird collision theory
		{
			black_bird_live = FALSE;
			Alexis.centre_point.x = black_bird.x;
		}
	}
	if (black_bird_live == FALSE)
	{
		CP_Color white = CP_Color_Create(255, 255, 255, 255);
		CP_Settings_Fill(white);
		CP_Graphics_DrawRect(Alexis.centre_point.x, Alexis.centre_point.y, Alexis.width, Alexis.height);
		Alexis.centre_point.y += 30.f * CP_System_GetDt();
		CP_Color black = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(black);
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("ALEXIS TAN", Alexis.centre_point.x, Alexis.centre_point.y - 30);
		CP_Font_DrawText("PROGRAMMER", Alexis.centre_point.x, Alexis.centre_point.y + 30);

		if (Alexis.centre_point.y >= (window_height - (Alexis.height / 2)))
		{
			Alexis.centre_point.y = (window_height - (Alexis.height / 2));
		}
	}

	if (red_bird_live == FALSE)
	{
		CP_Color white = CP_Color_Create(255, 255, 255, 255);
		CP_Settings_Fill(white);
		CP_Graphics_DrawRect(Jet.centre_point.x, Jet.centre_point.y, Jet.width, Jet.height);
		Jet.centre_point.y += 30.f * CP_System_GetDt();
		CP_Color black = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(black);
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("JET ANG", Jet.centre_point.x, Jet.centre_point.y - 30);
		CP_Font_DrawText("PROGRAMMER", Jet.centre_point.x, Jet.centre_point.y + 30);

		if (Jet.centre_point.y >= (window_height - (Jet.height / 2)))
		{
			Jet.centre_point.y = (window_height - (Jet.height / 2));
		}
	}

	if (blue_bird_live == FALSE)
	{
		CP_Color white = CP_Color_Create(255, 255, 255, 255);
		CP_Settings_Fill(white);
		CP_Graphics_DrawRect(Solo.centre_point.x, Solo.centre_point.y, Solo.width, Solo.height);
		Solo.centre_point.y += 30.f * CP_System_GetDt();
		CP_Color black = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(black);
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("SOLOMON NG", Solo.centre_point.x, Solo.centre_point.y - 30);
		CP_Font_DrawText("PROGRAMMER", Solo.centre_point.x, Solo.centre_point.y + 30);

		if (Solo.centre_point.y >= (window_height - (Solo.height / 2)))
		{
			Solo.centre_point.y = (window_height - (Solo.height / 2));
		}
	}

	if (green_bird_live == FALSE)
	{
		CP_Color white = CP_Color_Create(255, 255, 255, 255);
		CP_Settings_Fill(white);
		CP_Graphics_DrawRect(Wilmer.centre_point.x, Wilmer.centre_point.y, Wilmer.width, Wilmer.height);
		Wilmer.centre_point.y += 30.f * CP_System_GetDt();
		CP_Color black = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(black);
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawText("WILMER LEE", Wilmer.centre_point.x, Wilmer.centre_point.y - 30);
		CP_Font_DrawText("PROGRAMMER", Wilmer.centre_point.x, Wilmer.centre_point.y + 30);

		if (Wilmer.centre_point.y >= (window_height - (Wilmer.height / 2)))
		{
			Wilmer.centre_point.y = (window_height - (Wilmer.height / 2));
		}
	}

	//logic for crosshair basic
	if (CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) {
		CP_Graphics_DrawRect(basic.x + 4, basic.y, basic.width, basic.height);
		CP_Graphics_DrawRect(basic.x1 - 4, basic.y1, basic.width, basic.height);
		CP_Graphics_DrawRect(basic.x2, basic.y2 + 4, basic.width1, basic.height1);
		CP_Graphics_DrawRect(basic.x3, basic.y3 - 4, basic.width1, basic.height1);
	}
	else {
		CP_Graphics_DrawRect(basic.x, basic.y, basic.width, basic.height);
		CP_Graphics_DrawRect(basic.x1, basic.y1, basic.width, basic.height);
		CP_Graphics_DrawRect(basic.x2, basic.y2, basic.width1, basic.height1);
		CP_Graphics_DrawRect(basic.x3, basic.y3, basic.width1, basic.height1);
	}
}

void credits_exit(void)
{
	for (int i = 0; i < 4; i++)
	{
		CP_Image_Free(&red_bird_Forward[i]);
		CP_Image_Free(&red_bird_Backwards[i]);

		CP_Image_Free(&blue_bird_Forward[i]);
		CP_Image_Free(&blue_bird_Backwards[i]);

		CP_Image_Free(&green_bird_Forward[i]);
		CP_Image_Free(&green_bird_Backwards[i]);

	}

	CP_Sound_Free(&gunshot);
	CP_Sound_Free(&Score);
	CP_Sound_Free(&BGM);
	CP_Sound_Free(&Bird_Effects);
	CP_Image_Free(&clouds_1);
	CP_Image_Free(&clouds_2);
	CP_Image_Free(&clouds_3);
}
