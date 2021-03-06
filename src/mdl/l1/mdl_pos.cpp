#include "mdl/l1/mdl_pos.hpp"

#include <cstring>

#include "util.hpp"

Mdl_pos::Mdl_pos(GLuint shaderID, GLenum primitive)
    : _indexCount(0)
    , _vaoID(0)
    , _shaderID(0)
{
    strncpy(_name, "Mdl_pos uninitialized", 127);
	_id = 2;
    _shaderID = shaderID;
    _primitive = primitive;
}

Mdl_pos::Mdl_pos(GLuint shaderID, GLenum primitive, float* vertexPositions, int vertexCount, unsigned int* indices, int indexCount)
    : _indexCount(0)
    , _vaoID(0)
    , _shaderID(0)
{
    strncpy(_name, "Mdl_pos", 127);
    _id = 2;
    _shaderID = shaderID;
    _primitive = primitive;

    _indexCount = indexCount;
    _initVAO(vertexPositions, vertexCount, indices);
}

Mdl_pos::~Mdl_pos()
{
    if (_vaoID != 0)
    {
        glDeleteVertexArrays(1, &_vaoID);
    }
}

void Mdl_pos::_initVAO(float* vertexPositions, int vertexCount, unsigned int* indices)
{
    compute_bounding_box(vertexPositions, vertexCount);

    if (_vaoID != 0)
    {
        glDeleteVertexArrays(1, &_vaoID);
    }

    glGenVertexArrays(1, &_vaoID);
    glBindVertexArray(_vaoID);

    unsigned int vboIDs[2];
    glGenBuffers(2, vboIDs); // indices, positions (color defined in shader)

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIDs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount*sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * vertexCount*sizeof(float), vertexPositions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

void Mdl_pos::draw(float* view, float* persp, void* otherdata)
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