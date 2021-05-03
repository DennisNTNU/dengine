#ifndef MDL_AXES_ORTHNROM_HPP
#define MDL_AXES_ORTHNROM_HPP

#include "mdl/l1/mdl_pos_col.hpp"

#include <GL/glew.h>

class Mdl_axes_orthnorm : public Mdl_pos_col
{
public:
	Mdl_axes_orthnorm(GLuint shaderID);
	~Mdl_axes_orthnorm();

protected:
	void initData(float** vertexPositions, float** vertexColors, int* vertexCount, unsigned int** indices);

private:
};

#endif /* MDL_AXES_ORTHNROM_HPP */
