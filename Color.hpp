#pragma once
#include <iostream>

enum e_colors
{
	BLACK =	0x00000000,
	WHITE =	0xffffff00,
	RED = 0xff000000,
	GREEN =	0x00ff0000,
	BLUE = 0x0000ff00,
	YELLOW = 0xffff0000,
	GREY  = 0x80808000,
	SP_RED = 0xad151900,
	GUALDA = 0xfabd0000,
	ALPHA =	 0x000000ff
};

enum e_color_channels
{
	RED_CHANNEL, GREEN_CHANNEL, BLUE_CHANNEL, ALPHA_CHANNEL
};

class Color
{
	public:

		Color(void);
		Color(int color_value);
		Color(int R, int G, int B, int A = 0xff);

		int		operator[](int i);

		int		get_bits(void);

	private:


		int		_channel[4];
		int		_bit_representation;
};

int	get_red_byte(int color);
int	get_green_byte(int color);
int	get_blue_byte(int color);
int	get_alpha_byte(int color);
int	color32(char R, char G, char B, char A);

std::ostream &operator<<(std::ostream &o, Color &c);
