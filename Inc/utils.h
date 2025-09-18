/*!
@author Ang Jie Le Jet
@course CSD1121F22
@section Section A.
@brief This file contains some function declarations
Copyright © 2022 DigiPen, All rights reserved.
*//*______________________________________________________________________*/
#pragma once

int RandomNumberX(int size_width);
int RandomNumberY(int size_height);
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int IsTreeCollided(struct tree, float click_x, float click_y);
union CP_Vector AngleToVector(float radian_angle);  
void Screenshake(void);

extern int screenShakeCounter;