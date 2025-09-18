/*!
@author Alexis Tan
@course CSD1121F22
@section Section A.
@brief This file contains logic needed for stage 5
All content © 2022 DigiPen (SINGAPORE) Corporation, all rights reserved.
*//*______________________________________________________________________*/
//Stage 5 Decoy Bird
#include <stdio.h>
#include "cprocessing.h"
#include "mainmenu.h"
#include "stage1.h"
#include "utils.h"
#include "bird.h"
#include "stage5.h"
#include "Highscore.h"


#define TRUE 1
#define FALSE 0

static float explosion_timer = 0.3f;
static int gIsPaused;
static int counter, initial_ammunition, ammunition_used, score;
static float countdown_timer; clouds_x_1; clouds_y_1; clouds_x_2; clouds_y_2; clouds_x_3; clouds_y_3;
static float elapsed_time;
static struct sprite_bird red_bird, blue_bird, green_bird,decoy_bird,decoy2_bird;
CP_Image red_bird_Forward[4], blue_bird_Forward[4], green_bird_Forward[4], decoy_bird_Forward[4],decoy2_bird_Forward[4];
CP_Image red_bird_Backwards[4], blue_bird_Backwards[4], green_bird_Backwards[4], decoy_bird_Backwards[4], decoy2_bird_Backwards[4];
CP_BOOL red_direction = TRUE;
CP_BOOL blue_direction = TRUE;
CP_BOOL green_direction = TRUE;
CP_BOOL decoy_direction = TRUE;
CP_BOOL decoy2_direction = TRUE;
static crosshair basic;
static CP_Image explode = NULL;

//Variables for sounds
static CP_Sound gunshot = NULL;
static CP_Sound Score = NULL;
static CP_Sound BGM = NULL;
static CP_Sound Bird_Effects = NULL;
static CP_Sound Gameover = NULL;
static float bg_time;

//static CP_Image red_bird_static = NULL;
//static CP_Image red_bird_static_reverse = NULL;
static int window_width, window_height;


static CP_BOOL red_bird_live = FALSE;
static CP_BOOL blue_bird_live = FALSE;
static CP_BOOL green_bird_live = FALSE;
static CP_BOOL decoy_bird_live = FALSE;
static CP_BOOL decoy2_bird_live = FALSE;

static CP_BOOL score_added = FALSE;

// Variable for background aesthetics
static CP_Image background = NULL;
static CP_Image clouds_1 = NULL, clouds_2 = NULL, clouds_3 = NULL;
static CP_Image bullet_pic = NULL;
static CP_Image burst = NULL;

// Variable for Trees
static struct tree big_tree, mid_tree, small_tree;
static CP_Image bigtree = NULL;
static CP_Image midtree = NULL;
static CP_Image smalltree = NULL;


static CP_BOOL highscorelogic = FALSE;
char gamehighscore[256];


void stage5_init(void)
{
	// set all highscore to be 0.
	for (int count = 0; count < 10; count++)
	{
		highscore[count] = 0;
	}
	// reading highscore
	read_data();
	
	//crosshair
	basic.height = 1;
	basic.width = 9;
	basic.height1 = 9;
	basic.width1 = 1;

	score = 0;
	counter = 0;
	initial_ammunition = 20;
	ammunition_used = 0;
	countdown_timer = 30.0f;
	bg_time = 0.f;
	srand(time(NULL));
	// Red Bird Parameters
	red_bird.speed = 300;
	red_bird.height = 250;
	red_bird.width = 250;
	// Blue Bird Parameters
	blue_bird.speed = 500;
	blue_bird.height = 250;
	blue_bird.width = 250;
	elapsed_time = 0.0f;
	// Green Bird Parameters
	green_bird.speed = 1000;
	green_bird.height = 250;
	green_bird.width = 250;
	elapsed_time = 0.0f;
	// Decoy Bird Parameters
	decoy_bird.speed = 600;
	decoy_bird.height = 250;
	decoy_bird.width = 250;
	elapsed_time = 0.0f;

	// Decoy Bird 2 Parameters
	decoy2_bird.speed = 800;
	decoy2_bird.height = 250;
	decoy2_bird.width = 250;
	elapsed_time = 0.0f;

	//background_stage1 = CP_Image_Load("../Assets/background.png");

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

	// Animating the decoy bird using array moving forward
	decoy_bird_Forward[0] = CP_Image_Load("Assets/Decoy Bird 1.png");
	decoy_bird_Forward[1] = CP_Image_Load("Assets/Decoy Bird 2.png");
	decoy_bird_Forward[2] = CP_Image_Load("Assets/Decoy Bird 3.png");
	decoy_bird_Forward[3] = CP_Image_Load("Assets/Decoy Bird 2.png");

	// Animate the decoy bird using array moving backwards
	decoy_bird_Backwards[0] = CP_Image_Load("Assets/Decoy Bird 1 Reverse.png");
	decoy_bird_Backwards[1] = CP_Image_Load("Assets/Decoy Bird 2 Reverse.png");
	decoy_bird_Backwards[2] = CP_Image_Load("Assets/Decoy Bird 3 Reverse.png");
	decoy_bird_Backwards[3] = CP_Image_Load("Assets/Decoy Bird 2 Reverse.png");

	// Animating the decoy bird using array moving forward
	decoy2_bird_Forward[0] = CP_Image_Load("Assets/Decoy Bird 1.png");
	decoy2_bird_Forward[1] = CP_Image_Load("Assets/Decoy Bird 2.png");
	decoy2_bird_Forward[2] = CP_Image_Load("Assets/Decoy Bird 3.png");
	decoy2_bird_Forward[3] = CP_Image_Load("Assets/Decoy Bird 2.png");

	// Animate the decoy bird using array moving backwards
	decoy2_bird_Backwards[0] = CP_Image_Load("Assets/Decoy Bird 1 Reverse.png");
	decoy2_bird_Backwards[1] = CP_Image_Load("Assets/Decoy Bird 2 Reverse.png");
	decoy2_bird_Backwards[2] = CP_Image_Load("Assets/Decoy Bird 3 Reverse.png");
	decoy2_bird_Backwards[3] = CP_Image_Load("Assets/Decoy Bird 2 Reverse.png");

	gunshot = CP_Sound_Load("Assets/Gunshot (Laser).wav");
	Score = CP_Sound_Load("Assets/Increase_Score.wav");
	BGM = CP_Sound_Load("Assets/Background (Beach).wav");
	Bird_Effects = CP_Sound_Load("Assets/Bird_Flapping.wav");
	Gameover = CP_Sound_Load("Assets/Game Over.wav");

	red_bird.height = 150; 
	red_bird.width = 150;
	red_bird.alive_time = 0.f;

	blue_bird.height = 150; 
	blue_bird.width = 150;
	blue_bird.alive_time = 0.f;

	green_bird.height = 150; 
	green_bird.width = 150;
	green_bird.alive_time = 0.f;

	decoy_bird.height = 350; 
	decoy_bird.width = 350;
	decoy_bird.alive_time = 0.f;

	decoy2_bird.height = 350;
	decoy2_bird.width = 350;
	decoy2_bird.alive_time = 0.f;

	// Initalise variables for the window height and width
	window_width = 1800;
	window_height = 1200;
	CP_System_SetWindowSize(window_width, window_height);

	
	// Loading Trees
	bigtree = CP_Image_Load("Assets/Tree 3.png");
	midtree = CP_Image_Load("Assets/Tree 3.png");
	smalltree = CP_Image_Load("Assets/Tree 3.png");
	// Initialising variables for the Trees
	big_tree.height = 700.f;
	big_tree.width = 700.f;

	mid_tree.height = 700.f;
	mid_tree.width = 700.f;

	small_tree.height = 700.f;
	small_tree.width = 700.f;

	big_tree.x = RandomNumberX(big_tree.width);
	big_tree.y = (CP_System_GetWindowHeight() - (big_tree.height / 2) + 100);
	mid_tree.x = RandomNumberX(mid_tree.width);
	mid_tree.y = (CP_System_GetWindowHeight() - (mid_tree.height / 2) + 100);
	small_tree.x = RandomNumberX(small_tree.width);
	small_tree.y = (CP_System_GetWindowHeight() - (small_tree.height / 2) + 100);

	if ((abs(big_tree.x - small_tree.x) <= 600.f))
	{
		if (big_tree.x < window_width - 1200.f)
		{
			big_tree.x += 1200.f;
		}

		else if (big_tree.x - 1200.f > 0.f && big_tree.x - 1200.f < 300.f)
		{
			big_tree.x -= 1200.f;
		}

		else
		{
			big_tree.x -= 600.f;
		}

		if ((abs(mid_tree.x - small_tree.x) <= 600.f))
		{
			if (mid_tree.x < window_width - 1200.f)
			{
				mid_tree.x += 1200.f;
			}

			else if (mid_tree.x - 1200.f > 0.f && mid_tree.x - 1200.f < 300.f)
			{
				mid_tree.x -= 1200.f;
			}

			else
			{
				mid_tree.x -= 600.f;
			}
		}
	}

	// Load background aesthetics
	background = CP_Image_Load("Assets/background 5.png");
	clouds_1 = CP_Image_Load("Assets/Cloud.png");
	clouds_2 = CP_Image_Load("Assets/Cloud.png");
	clouds_3 = CP_Image_Load("Assets/Cloud.png");
	explode = CP_Image_Load("Assets/Explode.png");
	bullet_pic = CP_Image_Load("Assets/Bullet.png");
	burst = CP_Image_Load("Assets/burst.png");

	// Initalise variable for clouds
	clouds_x_1 = 0.f;
	clouds_y_1 = 140.f;
	clouds_x_2 = 700.f;
	clouds_y_2 = 180.f;
	clouds_x_3 = 1400.f;
	clouds_y_3 = 100.f;

	gIsPaused = FALSE;
}


void stage5_update(void)
{
	if (screenShakeCounter != FALSE)
	{

		Screenshake();
	}

	if ((decoy_bird.alive_time > 3.f) || decoy_bird_live == FALSE)
	{
		decoy_bird.x = RandomNumberX(decoy_bird.width);
		decoy_bird.y = RandomNumberY(decoy_bird.height);
		decoy_bird_live = TRUE;
		decoy_bird.alive_time = 0.f;
	}
	decoy_bird.alive_time += CP_System_GetDt();

	if ((decoy2_bird.alive_time > 3.f) || decoy_bird_live == FALSE)
	{
		decoy2_bird.x = RandomNumberX(decoy2_bird.width);
		decoy2_bird.y = RandomNumberY(decoy2_bird.height);
		decoy2_bird_live = TRUE;
		decoy2_bird.alive_time = 0.f;
	}
	decoy2_bird.alive_time += CP_System_GetDt();

	if (bg_time == 0.f)
	{
		bg_time += CP_System_GetDt();
		CP_Sound_PlayMusic(BGM);
		CP_Sound_PlayMusic(Bird_Effects);
	}
	// Draw background and animate clouds
	CP_Image_Draw(background, 900.f, 755.f, window_width, window_height - 300, 255);
	CP_Image_Draw(clouds_1, clouds_x_1, clouds_y_1, 600, 300, 170);
	CP_Image_Draw(clouds_2, clouds_x_2, clouds_y_2, 600, 300, 170);
	CP_Image_Draw(clouds_3, clouds_x_3, clouds_y_3, 600, 300, 170);

	clouds_x_1 += 1.f;
	clouds_x_2 += 1.f;
	clouds_x_3 += 1.f;

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

	// Movement of the bird.
	elapsed_time += CP_System_GetDt() * 4;
	int time = (int)elapsed_time;
	int sprite_position = time % 4;


	if (CP_Input_KeyDown(KEY_ESCAPE))
	{
		CP_Engine_Terminate();
	}

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
	if (decoy_bird_live == FALSE)
	{
		decoy_bird.x = RandomNumberX(decoy_bird.width);
		decoy_bird.y = RandomNumberY(decoy_bird.height);
		decoy_bird_live = TRUE;
	}
	//Setting random position X and Position Y.
	if (decoy2_bird_live == FALSE)
	{
		decoy2_bird.x = RandomNumberX(decoy2_bird.width);
		decoy2_bird.y = RandomNumberY(decoy2_bird.height);
		decoy2_bird_live = TRUE;
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
	if (decoy_bird_live == TRUE)
	{
		// Set right most limit of the screen.
		if (decoy_bird.x >= 1800)
		{
			decoy_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (decoy_bird.x <= 0)
		{
			decoy_direction = TRUE;
		}

		// move right.
		if (decoy_direction)
		{
			decoy_bird.x += decoy_bird.speed * CP_System_GetDt();
			CP_Image_Draw(decoy_bird_Forward[sprite_position], decoy_bird.x, decoy_bird.y, decoy_bird.width, decoy_bird.height, 255);
		}
		// move left
		else if (!decoy_direction)
		{
			decoy_bird.x -= decoy_bird.speed * CP_System_GetDt();
			CP_Image_Draw(decoy_bird_Backwards[sprite_position], decoy_bird.x, decoy_bird.y, decoy_bird.width, decoy_bird.height, 255);
		}
	}
	if (decoy2_bird_live == TRUE)
	{
		// Set right most limit of the screen.
		if (decoy2_bird.x >= 1800)
		{
			decoy2_direction = FALSE;
		}
		// Set left most limit of the screen.
		else if (decoy2_bird.x <= 0)
		{
			decoy2_direction = TRUE;
		}

		// move right.
		if (decoy2_direction)
		{
			decoy2_bird.x += decoy2_bird.speed * CP_System_GetDt();
			CP_Image_Draw(decoy2_bird_Forward[sprite_position], decoy2_bird.x, decoy2_bird.y, decoy2_bird.width, decoy2_bird.height, 255);
		}
		// move left
		else if (!decoy2_direction)
		{
			decoy2_bird.x -= decoy2_bird.speed * CP_System_GetDt();
			CP_Image_Draw(decoy2_bird_Backwards[sprite_position], decoy2_bird.x, decoy2_bird.y, decoy2_bird.width, decoy2_bird.height, 255);
		}
	}

	CP_Image_Draw(bigtree, big_tree.x, big_tree.y, big_tree.width, big_tree.height, 255);
	CP_Image_Draw(midtree, mid_tree.x, mid_tree.y, mid_tree.width, mid_tree.height, 255);
	CP_Image_Draw(smalltree, small_tree.x, small_tree.y, small_tree.width, small_tree.height, 255);

		if (CP_Input_KeyDown(KEY_ESCAPE))
		{
			CP_Engine_Terminate();
		}
		CP_Color backgroundcolour = CP_Color_Create(66, 77, 81, 120);
		CP_Graphics_ClearBackground(backgroundcolour);


		//Input text for Counter
		CP_Settings_TextSize(50.0f);
		CP_Color textcolour = CP_Color_Create(0, 0, 0, 255);
		CP_Settings_Fill(textcolour);
		CP_Font_DrawText("Counter:", 1600, 100);

		//Displaying of counter on the screen
		if (counter >= 0)
		{
			char buffer[50];
			sprintf_s(buffer, sizeof(buffer), "%d", counter);
			CP_Font_DrawText(buffer, 1750, 100);
		}

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
	

		//Declare the condition for Pause state
		if (countdown_timer <= 0 || initial_ammunition <= 0)
		{
			gIsPaused = TRUE;
		}

		//Pause state 
		if (gIsPaused == TRUE)
		{
			if (explosion_timer >= 0.0f)
			{
				CP_Image_Draw(explode, decoy_bird.x, decoy_bird.y, 1800, 1500, 255);
				CP_Image_Draw(explode, decoy2_bird.x, decoy2_bird.y, 1800, 1500, 255);
				explosion_timer -= CP_System_GetDt();
			}
			else
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

				//Displaying of counter on the screen
				if (counter >= 0)
				{
					char buffer[50];
					sprintf_s(buffer, sizeof(buffer), "%d", counter);
					CP_Font_DrawText(buffer, 1750, 100);
				}

				//Score calculation
				score = counter * 100;

				if (score_added == FALSE)
				{
					currentscore += score;
					printf("%d", score);
				}
				score_added = TRUE;

				if (score >= 0)
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
					CP_Font_DrawText("HIGHSCORE!", 1200, 800);

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
					if (IsAreaClicked(1200, 800, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
					{
							(highscorelogic = TRUE);
					}
					if (IsAreaClicked(600, 800, 150, 60, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
					{
						CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
					}
				}

				if (highscorelogic == TRUE)
				{	
					int base_y = 380;

					CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
					CP_Graphics_DrawRect(900, 600, 800, 600);

					//Display text for highscore
					CP_Settings_TextSize(40.0f);
					CP_Settings_Fill(textcolour);
					CP_Font_DrawText("Highscore: ", 900, 350);
					CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
					CP_Graphics_DrawRect(600, 800, 150, 60);
					CP_Settings_Fill(textcolour);
					CP_Settings_TextSize(30.0f);
					CP_Font_DrawText("main menu", 600, 800);
					


					for (int i = 0; i < 10; ++i)
					{
							//printing of highscore
							sprintf_s(gamehighscore, 256, "%d", highscore[i]);
							base_y += 45;
							CP_Font_DrawText(gamehighscore, 900, base_y);

					}
				
				}
			}
		}
		else
		{

			if (CP_Input_MouseClicked(MOUSE_BUTTON_LEFT)) //Logic for red_bird collision theory
			{
				CP_Sound_Play(gunshot);
				--initial_ammunition;
				if ((IsTreeCollided(small_tree, CP_Input_GetMouseX(), CP_Input_GetMouseY())) || IsTreeCollided(mid_tree, CP_Input_GetMouseX(), CP_Input_GetMouseY()) || IsTreeCollided(big_tree, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
				{
					printf("mouse collided with tree\n");
				}



				else if (IsCircleClicked(red_bird.x, red_bird.y, 100, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
				{
					counter++;
					CP_Sound_Play(Score);
					ammunition_used++;
					CP_Image_Draw(burst, red_bird.x, red_bird.y, 250, 250, 255);
					red_bird_live = FALSE;
				}

				else if (IsCircleClicked(blue_bird.x, blue_bird.y, 100, CP_Input_GetMouseX(), CP_Input_GetMouseY()))  //Logic for blue_bird collision theory
				{
					counter = counter + 2;
					CP_Sound_Play(Score);
					ammunition_used++;
					CP_Image_Draw(burst, blue_bird.x, blue_bird.y, 250, 250, 255);
					blue_bird_live = FALSE;
				}

				else if (IsCircleClicked(green_bird.x, green_bird.y, 100, CP_Input_GetMouseX(), CP_Input_GetMouseY())) //Logic for green_bird collision theory
				{
					counter = counter + 3;
					CP_Sound_Play(Score);
					ammunition_used++;
					CP_Image_Draw(burst, green_bird.x, green_bird.y, 250, 250, 255);
					green_bird_live = FALSE;
				}

				else if (IsCircleClicked(decoy_bird.x, decoy_bird.y, 150, CP_Input_GetMouseX(), CP_Input_GetMouseY())) //Logic for decoy_bird collision theory
				{
					screenShakeCounter = TRUE;
					CP_Sound_Play(Gameover);
					CP_Image_Draw(explode, decoy_bird.x, decoy_bird.y, 1800, 1500, 255);
					gIsPaused = TRUE; //Once hit decoy bird will show summary page
					decoy_bird_live = FALSE;
				}
				else if (IsCircleClicked(decoy2_bird.x, decoy2_bird.y, 150, CP_Input_GetMouseX(), CP_Input_GetMouseY())) //Logic for decoy_bird collision theory
				{
					CP_Sound_Play(Gameover);
					CP_Image_Draw(explode, decoy2_bird.x, decoy2_bird.y, 1800, 1500, 255);
					gIsPaused = TRUE; //Once hit decoy bird will show summary page
					decoy2_bird_live = FALSE;
				}
				else {
					screenShakeCounter = TRUE;

				}

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


void stage5_exit(void)
{
	for (int i = 0; i < 4; i++)
	{
		CP_Image_Free(&red_bird_Forward[i]);
		CP_Image_Free(&red_bird_Backwards[i]);

		CP_Image_Free(&blue_bird_Forward[i]);
		CP_Image_Free(&blue_bird_Backwards[i]);

		CP_Image_Free(&green_bird_Forward[i]);
		CP_Image_Free(&green_bird_Backwards[i]);

		CP_Image_Free(&decoy_bird_Forward[i]);
		CP_Image_Free(&decoy_bird_Backwards[i]);

		CP_Image_Free(&decoy2_bird_Forward[i]);
		CP_Image_Free(&decoy2_bird_Backwards[i]);
	}

	CP_Sound_Free(&gunshot);
	CP_Sound_Free(&Score);
	CP_Sound_Free(&BGM);
	CP_Sound_Free(&Bird_Effects);
	CP_Sound_Free(&Gameover);
	for (int count = 0; count < 10; count++)
	{
		if (currentscore > highscore[count])
		{
			highscore[count] = currentscore;
			save_data();
			break;
		}
	}
	CP_Image_Free(&clouds_1);
	CP_Image_Free(&clouds_2);
	CP_Image_Free(&clouds_3);
	CP_Image_Free(&background);
	CP_Image_Free(&big_tree);
	CP_Image_Free(&mid_tree);
	CP_Image_Free(&small_tree);
	CP_Image_Free(&bullet_pic);
	CP_Image_Free(&burst);
}
