#ifndef MDL_POS_TEX_NORM_OBJ_HPP
#define MDL_POS_TEX_NORM_OBJ_HPP

#include "mdl/l1/mdl_pos_tex_norm.hpp"

#include <GL/glew.h>

class Mdl_pos_tex_norm_obj : public Mdl_pos_tex_norm
{
public:
    Mdl_pos_tex_norm_obj(GLuint shaderID, GLuint textureID, const char* obj_file_path);
    ~Mdl_pos_tex_norm_obj();

protected:
    //void initData(unsigned int** indices, float** vertexPositions, float** vertexUVs, int* vertexCount);

private:
};

#endif /* MDL_POS_TEX_NORM_OBJ_HPP */
