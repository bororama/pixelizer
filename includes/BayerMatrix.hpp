#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

class	BayerMatrix
{
	public:
		BayerMatrix(unsigned int matrix_level);
		~BayerMatrix(void);

		int		side_length(void);
		float	*operator[](int index);

	private:
		BayerMatrix(void);
		
		std::vector<float>	_matrix;
		int					_side_length;
		
		std::vector<float>	_fill_matrix(int matrix_level);
		void	_precalculate_tresholds_map(void);	
};

std::ostream	&operator<<(std::ostream &o, BayerMatrix &m);
