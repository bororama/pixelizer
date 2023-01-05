#include "CImg.h"
#include <cstdint>
#include <iostream>
#include <algorithm>
#include "BayerMatrix.hpp"

using namespace cimg_library;

int		clamp(int value, int min, int max)
{
	value = (value < min) ? min : value;
	value = (value > max) ? max : value;

	return value;
}

int	clamp_color(int color_value)
{
	return clamp(color_value, 0, 255);
}

void	adjust_contrast(int adjustment, CImg<unsigned char> &image)
{
	float correction_factor;

	adjustment = clamp(adjustment, -255, 255);
	correction_factor = (float)(259 * (adjustment + 255))/(255 * (259 - adjustment));
	cimg_forXY(image, x, y)
	{
		for (int z = 0; z < 3; ++z)
		{
			image(x, y, z) = clamp_color(correction_factor * (image(x,y,z) - 128) + 128);
		}
	}
}

void	sprite_resize(int target_size, CImg<unsigned char> &image)
{
	int		smallest_side = std::min(image.width(), image.height());
	float	scaling_factor = (float)target_size / smallest_side;

	image.resize(image.width() * scaling_factor, image.height() * scaling_factor);
}

enum e_colors
{
	BLACK =	0x000000ff,
	WHITE =	0xffffffff,
	RED = 0xff0000ff,
	GREEN =	0x00ff00ff,
	BLUE = 0x0000ffff,
	YELLOW = 0xffff00ff,
	GREY  = 0x808080ff,
	SP_RED = 0xad1519ff,
	GUALDA = 0xfabd00ff
};

/*
**	pseudocode:
**
**	Threshold = COLOR(256/4, 256/4, 256/4); Estimated precision of the palette 
**	  For each pixel, Input, in the original picture:
**		Factor  = ThresholdMatrix[xcoordinate % X][ycoordinate % Y];
**		Attempt = Input + Factor * Threshold
**		Color = FindClosestColorFrom(Palette, Attempt)
**		Draw pixel using Color
*/

void standard_ordered_dithering(unsigned int matrix_level, CImg<unsigned char> &image)
{
	std::vector<int>	palette(BLACK, GREEN);
	BayerMatrix			matrix(matrix_level);
	float	factor;
	char	attemp;


	cimg_forXY(image, x, y)
	{
		for (int z = 0; z < 3; ++z)
		{
			std::cout << (int)image(x, y, z) << std::endl;
		}
		return ;
	}

}

int main()
{
	CImg<unsigned char> apavel("apavel.jpg");

	adjust_contrast( 65, apavel);
	sprite_resize(128, apavel);
	standard_ordered_dithering(0, apavel);
	apavel.save("test.jpg");
	return 0;
}
