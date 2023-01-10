#include "Args.hpp"

void	Args::throw_error(std::string error)
{
	std::cerr << error << std::endl;
	exit(1);
}

std::string	Args::check_file_input(std::string file)
{
	if (access(file.c_str(), F_OK ) == -1)
		throw_error("Invalid or not existing file");
	return file;
}

unsigned int	Args::check_target_size(unsigned int n)
{
	if ((n & (n - 1)) == 0)
		return n;
	else
	{
		std::cerr << "Target size must be a power of 2 - Set to 0" << std::endl;
		return 0;
	}
}

std::vector<Color>	Args::create_palette(std::string name)
{
	std::vector<Color>	palette;

	if (name == "A")
	{
		palette.push_back(BLACK);
		palette.push_back(WHITE);
		palette.push_back(GUALDA);
		palette.push_back(SP_RED);
	}
	else
	{
		palette.push_back(BLACK);
		palette.push_back(GREEN);
	}
	return palette;
}

Args::Args(int argc, char **argv)
{
	if (argc < 2)
		throw_error("You should at least pass one argument (image to pixelize)");
	cimg_usage("Retrieve command line arguments");

	std::string			palette_name = cimg_option("-p", "DEFAULT", "Color palette");
	this->palette = create_palette(palette_name);

	this->image = check_file_input(argv[1]);
	this->target_size = check_target_size(cimg_option("-t", 0, ""));
	this->brightness = cimg_option("-b", 0, "");
	this->contrast = cimg_option("-c", 0, "");
	this->matrix_level = cimg_option("-l", 0, "");
	this->normalize = cimg_option("-n", false, "");
}

Args::~Args(void) {}