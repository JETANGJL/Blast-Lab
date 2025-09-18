/*!
@author Solomon Ng
@course CSD1121F22
@section Section A.
@brief This file contains a few structs for the mainmenu
Copyright © 2022 DigiPen, All rights reserved.
*//*______________________________________________________________________*/
#pragma once
#include <cprocessing.h>

typedef struct centre_point
{
	// x and y coordinates
	float x;
	float y;

} centre_point;

typedef struct button
{
	// make the colour
	CP_Color colour;

	// size of the button
	float height;
	float width;

	// centre point of the buttons
	centre_point centre_point;

} button;

void Main_Menu_Init(void);
void Main_Menu_Update(void);
void Main_Menu_Exit(void);