#ifndef MDL_IND_POS_TEX_HPP
#define MDL_IND_POS_TEX_HPP

#include "mdl_base.hpp"

#include <GL/glew.h>

class Mdl_ind_pos_tex : public Mdl_base
{
public:
	Mdl_ind_pos_tex(GLuint shaderID, GLuint textureID);
	~Mdl_ind_pos_tex();

	void extra_function();

	void draw(float* view, float* persp);
protected:
	virtual void initData(unsigned int** indices, float** vertexPositions, float** vertexUVs, int* vertexCount) = 0;
	void _initVAO(unsigned int* indices, float* vertexPositions, float* vertexUVs, int vertexCount);
    unsigned int _indexCount;
private:

    GLuint _vaoID;

    GLuint _textureID;
    GLuint _shaderID;
};

#endif /* MDL_IND_POS_TEX_HPP */