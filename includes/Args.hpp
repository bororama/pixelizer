#pragma once

#include <vector>
#include "CImg.h"
#include "Color.hpp"
#include <fstream>

class Args
{
	public:
		std::vector<Color>	palette;
		std::string			image;
		unsigned int		target_size;
		int					brightness;
		int					contrast;
		unsigned int		matrix_level;
		bool				normalize;

		Args(int argc, char **argv);
		~Args(void);

		void			throw_error(std::string error);
		bool			check_file_input(std::string file);
		unsigned int	check_target_size(unsigned int input);
		std::vector<Color>	create_palette(std::string name);
};
