#include <cstdint>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "BayerMatrix.hpp"
#include "Color.hpp"
#include "Args.hpp"

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
			image(x, y, z) = clamp_color(correction_factor * (image(x, y, z) - 128) + 128);
		}
	}
}

void	adjust_brightness(int adjustment, CImg<unsigned char> &image)
{
	adjustment = clamp(adjustment, -255, 255);
	cimg_forXY(image, x, y)
	{
		for (int z = 0; z < 3; ++z)
		{
			image(x, y, z) = clamp_color(image(x, y, z) + adjustment);
		}
	}

}

void	sprite_resize(int target_size, CImg<unsigned char> &image)
{
	int		smallest_side = std::min(image.width(), image.height());
	float	scaling_factor = (float)target_size / smallest_side;

	image.resize(image.width() * scaling_factor, image.height() * scaling_factor);
}


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


/*
	find closest color
	
	smallestdifference = color
	for each element on the list
		compute difference
		if difference > smallest_difference
		smallest_difference = difference
		save element as closest_color
	return closest_color;
*/

Color	closest_color_in_palette(Color const &target_color, std::vector<Color> const palette)
{

	if (!palette.size())
		throw std::invalid_argument("Empty color-palette...");

	Color 	closest_color(*(palette.begin()));
	float	smallest_difference = RGBcolor_distance(target_color, closest_color);
	float	current_difference = smallest_difference;

	for (std::vector<Color>::const_iterator color = palette.begin(); color != palette.end(); ++color)
	{
		current_difference = RGBcolor_distance(target_color, *color);
		if (current_difference < smallest_difference)
		{
			smallest_difference = current_difference;
			closest_color = *color;
		}
	}
	return closest_color;
}


//gamma correction according to theosib
void pseudo_gamma_correction(CImg<unsigned char> &image)
{
	cimg_forXY(image, x, y)
	{
		for (int z = 0; z < 3; ++z)
		{
			image(x, y, z) = image(x,y,z) - sqrt(image(x, y, z));
		}
	}

}

void standard_ordered_dithering(unsigned int matrix_level, CImg<unsigned char> &image, std::vector<Color> palette, bool normalize = true)
{
	BayerMatrix			matrix(matrix_level);
	float				factor;
	Color 				input_color;
	Color				target_color;
	Color				output_color;

	//this r factor is screwing with more subtle palettes...
	float	r = (float)256/ palette.size();

	cimg_forXY(image, x, y)
	{
		input_color.assign(image(x, y, 0), image(x, y, 1), image(x, y, 2));
		factor = matrix[x % matrix.side_length()][y % matrix.side_length()];
		target_color = input_color + ((r * (factor - (0.5 * normalize)))); //factor could be normalized by substracting 1/2
		output_color = closest_color_in_palette(target_color, palette);
		for (int z = 0; z < 3; ++z)
		{
			image(x, y, z) = output_color[z];
		}
	}

}

int main(int argc, char **argv)
{
	Args				arguments(argc, argv);
	CImg<unsigned char> image(arguments.image);

	adjust_brightness(arguments.brightness, image);
	adjust_contrast(arguments.contrast, image);
	sprite_resize(arguments.target_size, image);
	standard_ordered_dithering(arguments.matrix_level, image, arguments.palette, arguments.normalize);
	image.save("test.jpg");
	return 0;
}
