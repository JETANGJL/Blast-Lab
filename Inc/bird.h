/*!
@author Jet Ang
@course CSD1121F22
@section Section A.
@brief This file provides some struct definitions for our bird
Copyright © 2022 DigiPen, All rights reserved.
*//*______________________________________________________________________*/

#pragma once

struct sprite_bird {
	int x;
	int y;

	int height;
	int width;

	int speed;

	float alive_time;

};

struct tree {

	float x;
	float y;

	float height;
	float width;
};

//crosshair
typedef struct crosshair{

	// x and y coordinates
	float x;
	float y;

	// x and y coordinates
	float x1;
	float y1;

	float x2;
	float y2;

	float x3;
	float y3;

	// size of the button
	float height;
	float width;

	// size of the button
	float height1;
	float width1;

} crosshair;