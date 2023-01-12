#include "BayerMatrix.hpp"

static float baseBayerMatrix[4] = {0, 2, 3, 1};

BayerMatrix::BayerMatrix(unsigned int matrix_level):
_side_length(2 << (matrix_level))
{
	_matrix = _fill_matrix(matrix_level);
	_precalculate_tresholds_map();
}

void	BayerMatrix::_precalculate_tresholds_map(void)
{
	for (int i = 0; i < _matrix.size(); ++i)
		_matrix[i] /= _matrix.size();
}

std::vector<float>	BayerMatrix::_fill_matrix(int matrix_level)
{
	std::vector<float> matrix(pow((2 << matrix_level), 2));
	std::vector<float> sub_matrix;

	if (matrix_level == 0)
	{
		for (int i = 0; i < 4; ++i)
			matrix[i] = baseBayerMatrix[i];
	}
	else
	{
		sub_matrix = _fill_matrix(matrix_level - 1);
		int sub_side_length = (1 << matrix_level);
		int side_length = (2 << (matrix_level));
		int m = 0;
	
		for (int quadrant = 0; quadrant < 4; ++quadrant)
		{
			for (int i = 0; i < sub_side_length; ++i)
			{
				for (int j = 0; j < sub_side_length; ++j)
					matrix[(i * side_length) + j + (m)] = 
					(4 * sub_matrix[(i * sub_side_length) + j]) + baseBayerMatrix[quadrant];
			}
			m += sub_side_length;
			if (quadrant == 1)
				m = (sub_matrix.size() * 2);
		}
	}
	return matrix;
}

BayerMatrix::~BayerMatrix(void)
{
}

float	*BayerMatrix::operator[](int index)
{
	return &_matrix[index * side_length()];
}

int	BayerMatrix::side_length(void)
{
	return _side_length;
}

std::ostream	&operator<<(std::ostream &o, BayerMatrix &m)
{
	o << std::fixed;
	for (int i = 0; i < m.side_length(); ++i)
	{
		for (int j = 0; j < m.side_length(); ++j)
		{
			o << "[" << std::setprecision(2) << m[i][j] << "] ";
		}
		o << std::endl;
	}
	return o;
}
