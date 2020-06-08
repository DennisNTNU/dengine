#ifndef MDL_EXAMPLE1_HPP
#define MDL_EXAMPLE1_HPP

#include "mdl_ind_pos_tex.hpp"

#include <GL/glew.h>

class Mdl_example1 : public Mdl_ind_pos_tex
{
public:
	Mdl_example1(GLuint shaderID, GLuint textureID);
	~Mdl_example1();

protected:
	void initData(unsigned int** indices, float** vertexPositions, float** vertexUVs, int* vertexCount);

private:
};

#endif /* MDL_EXAMPLE1_HPP */