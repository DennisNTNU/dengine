#include "mdl/l2/mdl_pos_tex_data.hpp"

#include <cstring>

extern "C" {
#include "obj_import.h"
}

Mdl_pos_tex_data::Mdl_pos_tex_data(GLuint shaderID, GLuint textureID, float* positions, float* uvs, 
                                   int vertex_count, unsigned int* indices, int index_count)
    : Mdl_pos_tex(shaderID, textureID)
{
    strncpy(_name, "Mdl_pos_tex_data", 127);

    _indexCount = index_count;
    _initVAO(indices, positions, uvs, vertex_count);
}

Mdl_pos_tex_data::~Mdl_pos_tex_data()
{

}
