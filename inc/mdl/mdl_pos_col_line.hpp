#ifndef MDL_POS_COL_LINE_HPP
#define MDL_POS_COL_LINE_HPP

#include "mdl_base.hpp"

#include <GL/glew.h>

class Mdl_pos_col_line : public Mdl_base
{
public:
    Mdl_pos_col_line(GLuint shaderID);
    ~Mdl_pos_col_line();

    void draw(float* view, float* persp, void* otherdata);
protected:
    virtual void initData(unsigned int** indices, float** vertexPositions, float** vertexColors, int* vertexCount) = 0;
    void _initVAO(unsigned int* indices, float* vertexPositions, float* vertexColors, int vertexCount);

    unsigned int _indexCount;
private:
    GLuint _vaoID;
    GLuint _shaderID;
};

#endif /* MDL_POS_COL_LINE_HPP */