#ifndef MDL_POS_HPP
#define MDL_POS_HPP

#include "mdl/mdl_base.hpp"

#include <GL/glew.h>

class Mdl_pos : public Mdl_base
{
public:
    Mdl_pos(GLuint shaderID, GLenum primitive);
    Mdl_pos(GLuint shaderID, GLenum primitive, float* vertexPositions, int vertexCount, unsigned int* indices, int indexCount);
    ~Mdl_pos();

    void draw(float* view, float* persp, void* otherdata);
protected:
    //virtual void initData(unsigned int** indices, float** vertexPositions, int* vertexCount) = 0;
    void _initVAO(float* vertexPositions, int vertexCount, unsigned int* indices);

    unsigned int _indexCount;
private:
    GLuint _vaoID;
    GLuint _shaderID;

    GLenum _primitive;
};

#endif /* MDL_POS_HPP */