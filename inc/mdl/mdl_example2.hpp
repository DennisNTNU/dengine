#ifndef MDL_EXAMPLE2_HPP
#define MDL_EXAMPLE2_HPP

#include "mdl_pos_col.hpp"

#include <GL/glew.h>

class Mdl_example2 : public Mdl_pos_col
{
public:
	Mdl_example2(GLuint shaderID);
	~Mdl_example2();

protected:
	void initData(unsigned int** indices, float** vertexPositions, float** vertexColors, int* vertexCount);

private:
};

#endif /* MDL_EXAMPLE2_HPP */