#ifndef MDL_EXAMPLE1_HPP
#define MDL_EXAMPLE1_HPP

#include "mdl/l1/mdl_pos_col_line.hpp"

#include <GL/glew.h>

class Mdl_example1 : public Mdl_pos_col_line
{
public:
	Mdl_example1(GLuint shaderID);
	~Mdl_example1();

protected:
	void initData(unsigned int** indices, float** vertexPositions, float** vertexColors, int* vertexCount);

private:
};

#endif /* MDL_EXAMPLE1_HPP */