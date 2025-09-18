/*!
@author Solomon Ng
@course CSD1121F22
@section Section A.
@brief This file contains logic needed for stage 1
All content © 2022 DigiPen (SINGAPORE) Corporation, all rights reserved.
*//*______________________________________________________________________*/
//Stage 1 static targets 
#include <stdio.h>
#include "cprocessing.h"
#include "mainmenu.h"
#include "stage1.h"
#include "utils.h"
#include "stage2.h"
#include "bird.h"
#include "Highscore.h"

#define TRUE 1
#define FALSE 0

static int gIsPaused;
static int counter, initial_ammunition, ammunition_used, score;
static float countdown_timer; clouds_x_1; clouds_y_1; clouds_x_2; clouds_y_2; clouds_x_3; clouds_y_3;
static crosshair basic;
static struct sprite_bird red_bird;
static CP_Image red_bird_static = NULL;
static CP_Image red_bird_static_reverse = NULL;
static CP_Image burst = NULL;
static CP_Image background = NULL;
static CP_Image clouds_1 = NULL, clouds_2 = NULL, clouds_3 = NULL;
static CP_Image bullet_pic = NULL;
static int window_width, window_height;
static CP_Sound gunshot = NULL;
static CP_Sound Score = NULL;
static CP_Sound Stage_BG = NULL;
static CP_BOOL red_bird_live = FALSE;
//static CP_BOOL Screenshake_live = FALSE;
static float bg_time;


void stage1_init(void)
{

	//crosshair
	basic.height = 1;
	basic.width = 9;
	basic.height1 = 9;
	basic.width1 = 1;

	bg_time = 0.f;
	score = 0;
	counter = 0;
	initial_ammunition = 20;
	ammunition_used = 0;
	countdown_timer = 30.0f;
	srand(time(NULL));

	// Load background aesthetics
	background = CP_Image_Load("Assets/background.png");
	clouds_1 = CP_Image_Load("Assets/Cloud.png");
	clouds_2 = CP_Image_Load("Assets/Cloud.png");
	clouds_3 = CP_Image_Load("Assets/Cloud.png");
	bullet_pic = CP_Image_Load("Assets/Bullet.png");
	burst = CP_Image_Load("Assets/burst.png");

	// Initalise variables for static red birds
	red_bird_static = CP_Image_Load("Assets/Red Bird static.png");
	red_bird_static_reverse = CP_Image_Load("Assets/Red Bird static Reverse.png");
	red_bird.height = 250;
	red_bird.width = 250;
	red_bird.alive_time = 0.f;

	// Initalise variables for the window height and width
	window_width = 1800;
	window_height = 1200;
	CP_System_SetWindowSize(window_width, window_height);

	// Initalise variable for clouds
	clouds_x_1 = 0.f;
	clouds_y_1 = 140.f;
	clouds_x_2 = 700.f;
	clouds_y_2 = 180.f;
	clouds_x_3 = 1400.f;
	clouds_y_3 = 100.f; 

	//Sound section for gun,score,background 
	gunshot = CP_Sound_Load("Assets/Gunshot (Laser).wav");
	Score = CP_Sound_Load("Assets/Increase_Score.wav");
	Stage_BG = CP_Sound_Load("Assets/BG_2.wav");


	gIsPaused = FALSE;
}

void stage1_update(void)
{
	if (screenShakeCounter != FALSE)
	{

		Screenshake();
	}

	if (bg_time == 0.f)
	{
		bg_time += CP_System_GetDt();
		CP_Sound_PlayMusic(Stage_BG);
	}
	if ((red_bird.alive_time > 1.f) || red_bird_live == FALSE)
	{
		red_bird.x = RandomNumberX(red_bird.width);
		red_bird.y = RandomNumberY(red_bird.height);
		red_bird_live = TRUE;
		red_bird.alive_time = 0.f;
	}
	red_bird.alive_time += CP_System_GetDt();

	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

	CP_Color backgroundcolour = CP_Color_Create(135, 206, 235, 170);
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

	// Draw background
	CP_Image_Draw(background, 900.f, 755.f, window_width, window_height - 300, 255);
	CP_Image_Draw(clouds_1, clouds_x_1, clouds_y_1, 600, 300, 170);
	CP_Image_Draw(clouds_2, clouds_x_2, clouds_y_2, 600, 300, 170);
	CP_Image_Draw(clouds_3, clouds_x_3, clouds_y_3, 600, 300, 170);
	
	clouds_x_1 += 1.f;
	clouds_x_2 += 1.f;
	clouds_x_3 += 1.f;

	//Draw Static Bird Sprite
	if ((red_bird.x > (window_width / 2)))// && (red_bird_live == TRUE))
	{
		CP_Image_Draw(red_bird_static, red_bird.x, red_bird.y - 2, red_bird.width, red_bird.height, 255);
	}
	else if ((red_bird.x <= (window_width / 2))) //&& (red_bird_live == TRUE))
	{
		CP_Image_Draw(red_bird_static_reverse, red_bird.x, red_bird.y - 2, red_bird.width, red_bird.height, 255);
	}

	//Input text for Counter
	CP_Settings_TextSize(50.0f);
	CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(textcolour);
	CP_Font_DrawText("Counter:", 1600, 100);

	//Displaying of counter on the screen
	char buffer[50];
	sprintf_s(buffer, sizeof(buffer), "%d", counter);
	CP_Font_DrawText(buffer, 1750, 100);

	//Input text for Ammunition
	CP_Settings_TextSize(50.0f);
	CP_Settings_Fill(textcolour);
	CP_Font_DrawText("Ammunition:", 200, 900);
	CP_Image_Draw(bullet_pic, 400, 900, 100, 150, 255);

	//Displaying of Ammunition on the screen
	if (initial_ammunition >= 0)
	{
		char abuffer[50];
		sprintf_s(abuffer, sizeof(abuffer), "%d", initial_ammunition);
		CP_Font_DrawText(abuffer, 350, 900);
		
	}

	//Input text for countdown timer
	CP_Settings_TextSize(50.0f);
	CP_Settings_Fill(textcolour);
	CP_Font_DrawText("Time Remaining:", 700, 100);
	if (countdown_timer >= 0)
	{
		char tbuffer[50];
		sprintf_s(tbuffer, sizeof(tbuffer), "%d", (int)countdown_timer);
		CP_Font_DrawText(tbuffer, 900, 100);
	}

	//Score calculation
	score = ammunition_used * 100;
	currentscore = score;

	//Declare the condition for Pause state
	if (countdown_timer <= 0 || initial_ammunition <= 0)
	{
		gIsPaused = TRUE;
	}

	//Pause state 
	if (gIsPaused == TRUE)
	{
		CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
		//Create Summary Page
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawRect(900, 600, 800, 600);

		//Display the stats
		CP_Settings_TextSize(80.0f);
		CP_Settings_Fill(textcolour);
		CP_Font_DrawText("Summary:", 900, 350);
		CP_Settings_TextSize(50.0f);

		//Display score
		CP_Font_DrawText("Score:", 600, 500);
		char sbuffer[50];
		sprintf_s(sbuffer, sizeof(sbuffer), "%d", score);
		CP_Font_DrawText(sbuffer, 750, 500);

		//Display Ammunition used
		CP_Font_DrawText("Ammunition used:", 720, 550);
		char abuffer[50];
		sprintf_s(abuffer, sizeof(abuffer), "%d", ammunition_used);
		CP_Font_DrawText(abuffer, 920, 550);

		if (score >= 1000)
		{
			//Display rectangle for next stage
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));

			//Display text for mainmenu stage
			if (IsAreaClicked(1200, 800, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
				CP_Graphics_DrawRect(1200, 800, 160, 70);
				CP_Settings_TextSize(35.0f);
			}
			else {
				CP_Graphics_DrawRect(1200, 800, 150, 60);
				CP_Settings_TextSize(30.0f);
			}

			//Display text for next stage
			CP_Settings_Fill(textcolour);
			CP_Font_DrawText("next stage", 1200, 800);
		}

		//Display rectangle for mainmenu stage
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));

		//Display text for mainmenu stage
		if (IsAreaClicked(600, 800, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
			CP_Graphics_DrawRect(600, 800, 165, 75);
			CP_Settings_TextSize(35.0f);
		}
		else {
			CP_Graphics_DrawRect(600, 800, 150, 60);
			CP_Settings_TextSize(30.0f);
		}
		CP_Settings_Fill(textcolour);
		CP_Font_DrawText("main menu", 600, 800);

		//Logic for next game stage and heading back to mainmenu
		if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT))
		{
			if (IsAreaClicked(1200, 800, 150, 100, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				CP_Engine_SetNextGameState(stage2_init, stage2_update, stage2_exit);
			}
			if (IsAreaClicked(600, 800, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			}
		}
	}
	else
	{
		if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT)) //Logic for collision theory
		{

			CP_Sound_Play(gunshot);
			--initial_ammunition;
			
			if (IsCircleClicked(red_bird.x, red_bird.y, 200, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
			counter++;
			CP_Sound_Play(Score);
			ammunition_used++;
			CP_Image_Draw(burst, red_bird.x, red_bird.y, 300, 300, 255);
			red_bird_live = FALSE;

			}
			else {
				screenShakeCounter = TRUE;

			}
		}
		countdown_timer -= CP_System_GetDt();

	

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
}


void stage1_exit(void)
{
	CP_Image_Free(&red_bird_static_reverse);
	CP_Image_Free(&red_bird_static);
	CP_Image_Free(&clouds_1);
	CP_Image_Free(&clouds_2);
	CP_Image_Free(&clouds_3);
	CP_Image_Free(&background);
	CP_Sound_Free(&gunshot);
	CP_Sound_Free(&Score);
	CP_Sound_Free(&Stage_BG);
	CP_Image_Free(&bullet_pic);
	CP_Image_Free(&burst);
}