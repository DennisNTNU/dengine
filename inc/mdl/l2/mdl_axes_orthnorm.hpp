#ifndef MDL_AXES_ORTHNROM_HPP
#define MDL_AXES_ORTHNROM_HPP

#include "mdl/l1/mdl_pos_col_line.hpp"

#include <GL/glew.h>

class Mdl_axes_orthnorm : public Mdl_pos_col_line
{
public:
	Mdl_axes_orthnorm(GLuint shaderID);
	~Mdl_axes_orthnorm();

protected:
	void initData(unsigned int** indices, float** vertexPositions, float** vertexColors, int* vertexCount);

private:
};

#endif /* MDL_AXES_ORTHNROM_HPP */
