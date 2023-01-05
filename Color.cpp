#include "Color.hpp"

Color::Color(void):
_channel(), _bit_representation()
{}

Color::Color(int color_value)
{
	_channel[RED_CHANNEL] = get_red_byte(color_value);
	_channel[GREEN_CHANNEL] = get_green_byte(color_value);	
	_channel[BLUE_CHANNEL] = get_blue_byte(color_value);	
	_channel[ALPHA_CHANNEL] = get_alpha_byte(color_value);
	_bit_representation = color_value;
}

Color::Color(int R, int G, int B, int A)
{
	_channel[RED_CHANNEL] = R;	
	_channel[GREEN_CHANNEL] = G;	
	_channel[BLUE_CHANNEL] = B;	
	_channel[ALPHA_CHANNEL] = A;
	_bit_representation = color32(R, G, B, A);
}

int Color::operator[](int i)
{
	return _channel[i];
}

int	Color::get_bits(void)
{
	return _bit_representation;
}

int get_red_byte(int color)
{
	return ((color & RED) >> 3 * 8);
}

int get_green_byte(int color)
{
	return ((color & GREEN) >> 2 * 8);
}

int get_blue_byte(int color)
{
	return ((color & BLUE) >> 1 * 8);
}

int get_alpha_byte(int color)
{
	return (color & ALPHA);
}

int		color32(char R, char G, char B, char A)
{
	int color;

	color = color & (int)(R << 24);
	color = color & (int)(G << 16);
	color = color & (int)(B << 8);
	color = color & (A);

	return color;
}

std::ostream &operator<<(std::ostream &o, Color &c)
{
	int color = c.get_bits();
	o << " array form: " << c[0] << " " << c[1] << " " << c[2] << ";";
	o << " bit form: ";
	o << "R[" << (int)get_red_byte(color) << "]";
	o <<"G[" << (int)get_green_byte(color) << "]";
	o <<"B[" << (int)get_blue_byte(color) << "];";
	//o << std::endl;
	return o;
}
