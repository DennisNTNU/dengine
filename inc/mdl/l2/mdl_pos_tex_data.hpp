#ifndef MDL_POS_TEX_DATA_HPP
#define MDL_POS_TEX_DATA_HPP

#include "mdl/l1/mdl_pos_tex.hpp"

#include <GL/glew.h>

class Mdl_pos_tex_data : public Mdl_pos_tex
{
public:
    Mdl_pos_tex_data(GLuint shaderID, GLuint textureID, float* positions, float* uvs, 
                     int vertex_count, unsigned int* indices, int index_count);
    ~Mdl_pos_tex_data();

protected:

private:
};

#endif /* MDL_POS_TEX_DATA_HPP */
