/*!
@author Ang Jie Le Jet
@course CSD1121F22
@section Section A.
@brief This file contains all utils definition
All content © 2022 DigiPen (SINGAPORE) Corporation, all rights reserved.
*//*______________________________________________________________________*/

#include <cprocessing.h>
#include "mainmenu.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h> /* time */
#include <stage1.h>
#include "bird.h"

float rect_max_x;
float rect_min_x;
float rect_max_y;
float rect_min_y;

float distance_to_center;
int screenShakeCounter;
float timer, defaultimer;


int RandomNumberX(int size_width) {
	int r;
	return r = (rand() % (CP_System_GetWindowWidth()- size_width)) + size_width;
}
int RandomNumberY(int size_height) {
	int r;
	return r = (rand() % (CP_System_GetWindowHeight()- size_height)) + size_height;
}

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{

	// find the maximum right boundary 
	rect_max_x = area_center_x + (area_width / 2);

	// find the maximum left boundary 
	rect_min_x = area_center_x - (area_width / 2);

	// find the maximum top boundary 
	rect_max_y = area_center_y + (area_height / 2);

	// find the maximum bottom boundary 
	rect_min_y = area_center_y - (area_height / 2);

	// if the click is after the left boundary
	// and if the click is before the right boundary
	if (rect_min_x < click_x && click_x < rect_max_x && rect_min_y < click_y && click_y < rect_max_y)
	{
		// return true
		return 1;
	}
	else
	{
		// return false
		return 0;
	}
	
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	float difference_in_x = click_x - circle_center_x;
	float squared_x = difference_in_x * difference_in_x;
	float difference_in_y = click_y - circle_center_y;
	float squared_y = difference_in_y * difference_in_y;
	float radius = diameter / 2;

	distance_to_center = (float)sqrt(squared_x + squared_y);
	
	
	if (distance_to_center <= radius)
	{
		// return true
		return 1;
	}
	else
	{
		// else return false
		return 0;
	}
}

int IsTreeCollided(struct tree t, float click_x, float click_y)
{

	float maxtrunk_x = (t.x - 30.f) + ((t.width / 9.f)/2);
	float mintrunk_x = (t.x - 30.f) - ((t.width / 9.f)/2);

	float maxtrunk_y = (t.y + (t.height / 2.5) + 400.f);
	float mintrunk_y = (t.y - (t.height / 2.5) + 400.f);

	if (IsCircleClicked(t.x, ((t.y - (t.height / 4) + 100.f)), 450.0f, click_x, click_y))
	{

		return 1;
	}
	else if (mintrunk_x < click_x && click_x < maxtrunk_x && mintrunk_y < click_y && click_y < maxtrunk_y)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

CP_Vector AngleToVector(float radian_angle)
{
	CP_Vector result = CP_Vector_Set(cos(radian_angle), sin(radian_angle));
    return result;
}

void Screenshake(void) 
{
	timer += CP_System_GetDt();
	if (screenShakeCounter < 30) {
	
		if ((screenShakeCounter % 4) == 0)
		{
			CP_Settings_Translate(5.f, 0.f);
		}
		

		else if ((screenShakeCounter % 4) == 1)
		{
			CP_Settings_Translate(0.f, 5.f);
			
		}
		
		else if ((screenShakeCounter % 4) == 2)
		{
			CP_Settings_Translate(-5.f, 0.f);
			
		}

		else if ((screenShakeCounter % 4) == 3)
		{
			CP_Settings_Translate(0.f, -5.f);
			
		}
		screenShakeCounter++;
	}
	else
		screenShakeCounter = 0;


}