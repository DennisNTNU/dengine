#ifndef MDL_POS_COL_HPP
#define MDL_POS_COL_HPP

#include "mdl/mdl_base.hpp"

#include <GL/glew.h>

class Mdl_pos_col : public Mdl_base
{
public:
    Mdl_pos_col(GLuint shaderID, GLenum primitive);
    Mdl_pos_col(GLuint shaderID, GLenum primitive, float* vertexPositions, float* vertexColors, int vertexCount, unsigned int* indices, unsigned int indexCount);
    ~Mdl_pos_col();

    void draw(float* view, float* persp, void* otherdata);
protected:
    //virtual void initData(unsigned int** indices, float** vertexPositions, float** vertexColors, int* vertexCount) = 0;
    void _initVAO(float* vertexPositions, float* vertexColors, int vertexCount, unsigned int* indices);

    unsigned int _indexCount;
private:
    GLuint _vaoID;
    GLuint _shaderID;

    GLenum _primitive;
};

#endif /* MDL_POS_COL_HPP */