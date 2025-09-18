/*!
@author Wilmer
@course CSD1121F22
@section Section A.
@brief This file provides the the logic to read and write highscore
Copyright © 2022 DigiPen, All rights reserved.
*//*______________________________________________________________________*/
#include "Highscore.h"
#include <stdio.h>
#include <errno.h>

void save_data(void)
{
	FILE* data;
	errno = 0;
	
	errno = fopen_s(&data, "Data/Highscore.txt", "w+");

	if (errno == 0 && data != NULL)
	{
		for (int count = 0; count < 10; count++)
		{
			if (highscore[count] != 0)
			{
				fprintf(data, "%d\n", highscore[count]);
			}

		}
		fclose(data);
	}
}

void read_data(void)
{
	FILE* data;
	errno = 0;
	errno = fopen_s(&data, "Data/Highscore.txt", "r+");
	if (errno == 0 && data != NULL)
	{	
		for (int count = 0; count < 10; count++)
		{
			fscanf_s(data, "%d", &highscore[count]);
	
		}
		fclose(data);
	}
}

