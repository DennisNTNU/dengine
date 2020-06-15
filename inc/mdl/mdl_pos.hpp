#ifndef MDL_POS_HPP
#define MDL_POS_HPP

#include "mdl_base.hpp"

#include <GL/glew.h>

class Mdl_pos : public Mdl_base
{
public:
	Mdl_pos(GLuint shaderID);
	~Mdl_pos();

	void draw(float* view, float* persp);
protected:
	virtual void initData(unsigned int** indices, float** vertexPositions, int* vertexCount) = 0;
	void _initVAO(unsigned int* indices, float* vertexPositions, int vertexCount);

    unsigned int _indexCount;
private:
    GLuint _vaoID;
    GLuint _shaderID;
};

#endif /* MDL_POS_HPP */