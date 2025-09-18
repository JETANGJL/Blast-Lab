/*!
@author Wilmer
@course CSD1121F22
@section Section A.
@brief This file contains some function declarations and structs
Copyright © 2022 DigiPen, All rights reserved.
*//*______________________________________________________________________*/
#pragma once
#include <cprocessing.h>
#include "mainmenu.h"

struct Point
{
	float x;
	float y;
};

struct Tutorial
{
	// Rectangle Button
	float Rectangle_Width;

	// Rectangle Button
	float Rectangle_Height;

	// Centerpoint of the Button
	struct Point Centerpoint_Rectangle;

	// Color of the Button 
	CP_Color Color_Rectangle;
};

void tutorial_Init(void);

void tutorial_Update(void);

void tutorial_Exit(void);



