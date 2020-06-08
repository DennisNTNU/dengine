#include "mdl/mdl_pos.hpp"

#include "util.hpp"

Mdl_pos::Mdl_pos(GLuint shaderID)
    : _indexCount(0)
    , _vaoID(0)
    , _shaderID(0)
{
	_id = 2;
    _shaderID = shaderID;
}

Mdl_pos::~Mdl_pos()
{
    if (_vaoID != 0)
    {
        glDeleteVertexArrays(1, &_vaoID);
    }
}

void Mdl_pos::_initVAO(unsigned int* indices, float* vertexPositions, int vertexCount)
{
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    printf("Vertex positions:\n");
    for (int i = 0; i < vertexCount; i++)
    {
        printf("%f %f %f\n", vertexPositions[3*i + 0]
                           , vertexPositions[3*i + 1]
                           , vertexPositions[3*i + 2]);
    }

    printf("Indices:\n");
    for (int i = 0; i < _indexCount; i++)
    {
        printf("%i\n", indices[i]);
    }
}

void Mdl_pos::draw(float* view, float* persp)
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

    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
    checkGLError(__FILE__, __LINE__);

    glBindVertexArray(0);
    checkGLError(__FILE__, __LINE__);

    glUseProgram(0);
    checkGLError(__FILE__, __LINE__);
}