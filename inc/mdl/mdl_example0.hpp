#ifndef MDL_EXAMPLE0_HPP
#define MDL_EXAMPLE0_HPP

#include "mdl_ind_pos_tex.hpp"

#include <GL/glew.h>

class Mdl_example0 : public Mdl_ind_pos_tex
{
public:
	Mdl_example0(GLuint shaderID, GLuint textureID);
	~Mdl_example0();

protected:
	void initData(unsigned int** indices, float** vertexPositions, float** vertexUVs, int* vertexCount);

private:
};

#endif /* MDL_EXAMPLE0_HPP */