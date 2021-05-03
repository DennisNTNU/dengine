#ifndef MDL_POS_TEX_HPP
#define MDL_POS_TEX_HPP

#include "mdl/mdl_base.hpp"

#include <GL/glew.h>

class Mdl_pos_tex : public Mdl_base
{
public:
    Mdl_pos_tex(GLuint shaderID, GLuint textureID, GLenum primitive);
    Mdl_pos_tex(GLuint shaderID, GLuint textureID, GLenum primitive, float* vertexPositions, float* vertexUVs, int vertexCount, unsigned int* indices, int indexCount);
    ~Mdl_pos_tex();

    void draw(float* view, float* persp, void* otherdata);
protected:
    void _initVAO(float* vertexPositions, float* vertexUVs, int vertexCount, unsigned int* indices);
    //virtual void initData(unsigned int** indices, float** vertexPositions, float** vertexUVs, int* vertexCount) = 0;
    unsigned int _indexCount;
private:
    GLuint _vaoID;

    GLuint _textureID;
    GLuint _shaderID;

    GLenum _primitive;
};

#endif /* MDL_POS_TEX_HPP */
