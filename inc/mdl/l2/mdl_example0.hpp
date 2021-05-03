#ifndef MDL_EXAMPLE0_HPP
#define MDL_EXAMPLE0_HPP

#include "mdl/l1/mdl_pos_tex.hpp"

#include <GL/glew.h>

class Mdl_example0 : public Mdl_pos_tex
{
public:
	Mdl_example0(GLuint shaderID, GLuint textureID);
	~Mdl_example0();

protected:
	void initData(float** vertexPositions, float** vertexUVs, int* vertexCount, unsigned int** indices);

private:
};

#endif /* MDL_EXAMPLE0_HPP */