#ifndef MDL_EXAMPLE1_HPP
#define MDL_EXAMPLE1_HPP

#include "mdl/l1/mdl_pos_col.hpp"

#include <GL/glew.h>

class Mdl_example1 : public Mdl_pos_col
{
public:
	Mdl_example1(GLuint shaderID);
	~Mdl_example1();

protected:
	void initData(float** vertexPositions, float** vertexColors, int* vertexCount, unsigned int** indices);

private:
};

#endif /* MDL_EXAMPLE1_HPP */