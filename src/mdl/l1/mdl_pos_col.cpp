#include "mdl/l1/mdl_pos_col.hpp"

#include "util.hpp"

Mdl_pos_col::Mdl_pos_col(GLuint shaderID)
    : _indexCount(0)
    , _vaoID(0)
    , _shaderID(0)
{
    _id = 3;
    _shaderID = shaderID;
}

Mdl_pos_col::~Mdl_pos_col()
{
    if (_vaoID != 0)
    {
        glDeleteVertexArrays(1, &_vaoID);
    }
}

void Mdl_pos_col::_initVAO(unsigned int* indices, float* vertexPositions, float* vertexColors, int vertexCount)
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[2]);
    glBufferData(GL_ARRAY_BUFFER, 4 * vertexCount*sizeof(float), vertexColors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

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

    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
    checkGLError(__FILE__, __LINE__);

    glBindVertexArray(0);
    checkGLError(__FILE__, __LINE__);

    glUseProgram(0);
    checkGLError(__FILE__, __LINE__);
}