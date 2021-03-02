#ifndef MDL_IND_POS_TEX_NORM_HPP
#define MDL_IND_POS_TEX_NORM_HPP

#include "mdl/mdl_base.hpp"

#include <GL/glew.h>

class Mdl_pos_tex_norm : public Mdl_base
{
public:
    Mdl_pos_tex_norm(GLuint shaderID, GLuint textureID);
    ~Mdl_pos_tex_norm();

    void extra_function();

    void draw(float* view, float* persp, void* otherdata);
protected:
    //virtual void initData(unsigned int** indices, float** vertexPositions, float** vertexUVs, int* vertexCount) = 0;
    void _initVAO(unsigned int* indices, float* vertexPositions, float* vertexUVs, float* vertexNormals, int vertexCount);
    unsigned int _indexCount;
private:

    GLuint _vaoID;

    GLuint _textureID;
    GLuint _shaderID;
};

#endif /* MDL_IND_POS_TEX_NORM_HPP */
