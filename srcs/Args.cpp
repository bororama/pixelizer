#include "Args.hpp"

void	Args::throw_error(std::string error)
{
	std::cerr << error << std::endl;
	exit(1);
}

bool 	Args::check_file_input(std::string file)
{
	if (access(file.c_str(), F_OK ) == -1)
	{
		std::cerr << "File not found" << std::endl;
		return false;
	}
	this->image = file;
	return true;
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
	std::fstream 		file(name.c_str(), std::ios_base::in);
	std::string			read_buffer;
	std::vector<Color>	palette;

	int i = 0;

	while (std::getline(file, read_buffer))
	{
		palette.push_back(std::stoul(read_buffer, 0, 16));
	}
	file.close();
	return palette;
}

Args::Args(int argc, char **argv)
{
	if (argc < 2 || !check_file_input(argv[1]))
		throw_error("usage: pixelizer \033[4mimage-file\033[0m [-bcmnsh]");
	cimg_usage("Retrieve command line arguments");

	std::string			palette_name = cimg_option("-p", "./palettes/phosphorus.palette", "Color palette sourcefile. Must be inside 'palettes' folder.");

	this->target_size = check_target_size(cimg_option("-s", 128, "In pixels, shall be a power of two. Sets the size the shortest side of the output image."));
	this->brightness = cimg_option("-b", 0, "Sets the image brightness.");
	this->contrast = cimg_option("-c", 0, "Sets image's contrast.");
	this->matrix_level = cimg_option("-m", 1, "Matrix' size");
	this->normalize = cimg_option("-n", false, "Set normalizing term");

	if (!check_file_input(argv[1]))
		throw_error("usage: pixelizer \033[4mimage-file\033[0m [-bcmnsh]");
	this->palette = create_palette(palette_name);
}

Args::~Args(void) {}
