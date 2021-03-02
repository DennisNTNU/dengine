#ifndef MDL_POS_TEX_OBJ_HPP
#define MDL_POS_TEX_OBJ_HPP

#include "mdl/l1/mdl_pos_tex.hpp"

#include <GL/glew.h>

class Mdl_pos_tex_obj : public Mdl_pos_tex
{
public:
    Mdl_pos_tex_obj(GLuint shaderID, GLuint textureID, const char* obj_file_path);
    ~Mdl_pos_tex_obj();

protected:
    //void initData(unsigned int** indices, float** vertexPositions, float** vertexUVs, int* vertexCount);

private:
};

#endif /* MDL_POS_TEX_OBJ_HPP */
