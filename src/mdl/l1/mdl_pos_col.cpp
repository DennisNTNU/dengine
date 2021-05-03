#include "mdl/l1/mdl_pos_col.hpp"

#include <cstring>

#include "util.hpp"

Mdl_pos_col::Mdl_pos_col(GLuint shaderID, GLenum primitive)
    : _indexCount(0)
    , _vaoID(0)
    , _shaderID(0)
{
    strncpy(_name, "Mdl_pos_col uninitialized", 127);
    _id = 3;
    _shaderID = shaderID;
    _primitive = primitive;
}

Mdl_pos_col::Mdl_pos_col(GLuint shaderID, GLenum primitive, float* vertexPositions, float* vertexColors, int vertexCount, unsigned int* indices, unsigned int indexCount)
    : _indexCount(0)
    , _vaoID(0)
    , _shaderID(0)
{
    strncpy(_name, "Mdl_pos_col", 127);
    _id = 3;
    _shaderID = shaderID;
    _primitive = primitive;

    _indexCount = indexCount;
    _initVAO(vertexPositions, vertexColors, vertexCount, indices);
}

Mdl_pos_col::~Mdl_pos_col()
{
    if (_vaoID != 0)
    {
        glDeleteVertexArrays(1, &_vaoID);
    }
}

void Mdl_pos_col::_initVAO(float* vertexPositions, float* vertexColors, int vertexCount, unsigned int* indices)
{
    compute_bounding_box(vertexPositions, vertexCount);

    if (_vaoID != 0)
    {
        glDeleteVertexArrays(1, &_vaoID);
    }

    glGenVertexArrays(1, &_vaoID);
    glBindVertexArray(_vaoID);

    unsigned int vboIDs[3];
    glGenBuffers(3, vboIDs); // indices, positions, colors

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIDs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount*sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * vertexCount*sizeof(float), vertexPositions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[2]);
    glBufferData(GL_ARRAY_BUFFER, 4 * vertexCount*sizeof(float), vertexColors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void Mdl_pos_col::draw(float* view, float* persp, void* otherdata)
{
    glUseProgram(_shaderID);
    checkGLError(__FILE__, __LINE__);

    glBindVertexArray(_vaoID);
    checkGLError(__FILE__, __LINE__);

    glUniformMatrix4fv(glGetUniformLocation(_shaderID, "modelMatrix"), 1, GL_FALSE, &(_model[0][0]));
    checkGLError(__FILE__, __LINE__);
    glUniformMatrix4fv(glGetUniformLocation(_shaderID, "viewMatrix"), 1, GL_FALSE, view);
    checkGLError(__FILE__, __LINE__);
    glUniformMatrix4fv(glGetUniformLocation(_shaderID, "perspMatrix"), 1, GL_FALSE, persp);
    checkGLError(__FILE__, __LINE__);

    glDrawElements(_primitive, _indexCount, GL_UNSIGNED_INT, 0);
    checkGLError(__FILE__, __LINE__);

    glBindVertexArray(0);
    checkGLError(__FILE__, __LINE__);

    glUseProgram(0);
    checkGLError(__FILE__, __LINE__);
}