#include "mdl/l1/mdl_pos_tex.hpp"

#include <cstring>

#include "util.hpp"

Mdl_pos_tex::Mdl_pos_tex(GLuint shaderID, GLuint textureID, GLenum primitive)
    : _indexCount(0)
    , _vaoID(0)
    , _textureID(0)
    , _shaderID(0)
{
    strncpy(_name, "Mdl_pos_tex uninitialized", 127);
	_id = 1;
    _shaderID = shaderID;
    _textureID = textureID;
    _primitive = primitive;
}

Mdl_pos_tex::Mdl_pos_tex(GLuint shaderID, GLuint textureID, GLenum primitive, float* vertexPositions, float* vertexUVs, int vertexCount, unsigned int* indices, int indexCount)
    : _indexCount(0)
    , _vaoID(0)
    , _textureID(0)
    , _shaderID(0)
{
    strncpy(_name, "Mdl_pos_tex", 127);
    _id = 1;
    _shaderID = shaderID;
    _textureID = textureID;
    _primitive = primitive;

    _indexCount = indexCount;
    _initVAO(vertexPositions, vertexUVs, vertexCount, indices);
}

Mdl_pos_tex::~Mdl_pos_tex()
{
    if (_vaoID != 0)
    {
        glDeleteVertexArrays(1, &_vaoID);
    }
}

void Mdl_pos_tex::_initVAO(float* vertexPositions, float* vertexUVs, int vertexCount, unsigned int* indices)
{
    compute_bounding_box(vertexPositions, vertexCount);

    if (_vaoID != 0)
    {
        glDeleteVertexArrays(1, &_vaoID);
    }

    glGenVertexArrays(1, &_vaoID);
    glBindVertexArray(_vaoID);

    unsigned int vboIDs[3];
    glGenBuffers(3, vboIDs); // indices, positions, UVs

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIDs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount*sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * vertexCount*sizeof(float), vertexPositions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[2]);
    glBufferData(GL_ARRAY_BUFFER, 2 * vertexCount*sizeof(float), vertexUVs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
}

void Mdl_pos_tex::draw(float* view, float* persp, void* otherdata)
{
    glUseProgram(_shaderID);
    checkGLError(__FILE__, __LINE__);

    glBindVertexArray(_vaoID);
    checkGLError(__FILE__, __LINE__);
    // https://open.gl/textures 
    // tutorial for multiple textures
    glUniformMatrix4fv(glGetUniformLocation(_shaderID, "modelMatrix"), 1, GL_FALSE, &(_model[0][0]));
    checkGLError(__FILE__, __LINE__);
    glUniformMatrix4fv(glGetUniformLocation(_shaderID, "viewMatrix"), 1, GL_FALSE, view);
    checkGLError(__FILE__, __LINE__);
    glUniformMatrix4fv(glGetUniformLocation(_shaderID, "perspMatrix"), 1, GL_FALSE, persp);
    checkGLError(__FILE__, __LINE__);

    // assigning texture unit 0 to fragment shader smapler2D textureSampler 
    glActiveTexture(GL_TEXTURE0);
    checkGLError(__FILE__, __LINE__);
    // bind texture to texture unit
    glBindTexture(GL_TEXTURE_2D, _textureID);
    checkGLError(__FILE__, __LINE__);
    // assign textureSampler variable in fragment shader to texture unit 0
    glUniform1i(glGetUniformLocation(_shaderID, "textureSampler"), 0);
    checkGLError(__FILE__, __LINE__);


    glDrawElements(_primitive, _indexCount, GL_UNSIGNED_INT, 0);
    checkGLError(__FILE__, __LINE__);

    glBindVertexArray(0);
    checkGLError(__FILE__, __LINE__);

    glUseProgram(0);
    checkGLError(__FILE__, __LINE__);
}