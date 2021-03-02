#include "mdl/mdl_base.hpp"

#include <stdio.h>

#include "util.hpp"

Mdl_base::Mdl_base()
    : _id(0)
    , _vaoIDbbox(0)
{

    _model = glm::mat4(1.0f);

    b_box.xmin = 0.0;
    b_box.xmax = 0.0;
    b_box.ymin = 0.0;
    b_box.ymax = 0.0;
    b_box.zmin = 0.0;
    b_box.zmax = 0.0;
}

Mdl_base::~Mdl_base()
{
}


void Mdl_base::translate(float x, float y, float z)
{
    _model[3][0] += x;
    _model[3][1] += y;
    _model[3][2] += z;
}

void Mdl_base::compute_bounding_box(float* vertexPositions, int vertexCount)
{
    b_box.xmin = FLT_MAX;
    b_box.xmax = -FLT_MAX;
    b_box.ymin = FLT_MAX;
    b_box.ymax = -FLT_MAX;
    b_box.zmin = FLT_MAX;
    b_box.zmax = -FLT_MAX;
    for (int i = 0; i < vertexCount; i++)
    {
        int ix = 3*i;
        int iy = 3*i + 1;
        int iz = 3*i + 2;

        if (vertexPositions[ix] > b_box.xmax)
        {
            b_box.xmax = vertexPositions[ix];
        }

        if (vertexPositions[iy] > b_box.ymax)
        {
            b_box.ymax = vertexPositions[iy];
        }

        if (vertexPositions[iz] > b_box.zmax)
        {
            b_box.zmax = vertexPositions[iz];
        }


        if (vertexPositions[ix] < b_box.xmin)
        {
            b_box.xmin = vertexPositions[ix];
        }

        if (vertexPositions[iy] < b_box.ymin)
        {
            b_box.ymin = vertexPositions[iy];
        }

        if (vertexPositions[iz] < b_box.zmin)
        {
            b_box.zmin = vertexPositions[iz];
        }
    }

    printf("%s\n", _name);
    printf("Bounding box: x %f %f \n", b_box.xmin, b_box.xmax);
    printf("              y %f %f \n", b_box.ymin, b_box.ymax);
    printf("              z %f %f \n", b_box.zmin, b_box.zmax);

    // make bounding box buffers
    // boudning box has 24 lines, 4 for each of the 6 sides.
    // each vertex has position and color attributes
    const int element_count = 24;
    const int index_count = 2*element_count;
    const int pos_float_count = 3*element_count;
    const int col_float_count = 4*element_count;

    float positions[pos_float_count] = {
        // -y face (bottom)
        b_box.xmin, b_box.ymin-0.01f, b_box.zmin, // 0
        b_box.xmax, b_box.ymin-0.01f, b_box.zmin, // 1
        b_box.xmax, b_box.ymin-0.01f, b_box.zmax, // 2
        b_box.xmin, b_box.ymin-0.01f, b_box.zmax, // 3
        // +x face
        b_box.xmax+0.01f, b_box.ymin, b_box.zmax, // 4
        b_box.xmax+0.01f, b_box.ymin, b_box.zmin, // 5
        b_box.xmax+0.01f, b_box.ymax, b_box.zmin, // 6
        b_box.xmax+0.01f, b_box.ymax, b_box.zmax, // 7
        // +z face
        b_box.xmin, b_box.ymin, b_box.zmax+0.01f, // 8
        b_box.xmax, b_box.ymin, b_box.zmax+0.01f, // 9
        b_box.xmax, b_box.ymax, b_box.zmax+0.01f, // 10
        b_box.xmin, b_box.ymax, b_box.zmax+0.01f, // 11
        // -x face
        b_box.xmin-0.01f, b_box.ymin, b_box.zmin, // 12
        b_box.xmin-0.01f, b_box.ymin, b_box.zmax, // 13
        b_box.xmin-0.01f, b_box.ymax, b_box.zmax, // 14
        b_box.xmin-0.01f, b_box.ymax, b_box.zmin, // 15
        // -z face
        b_box.xmax, b_box.ymin, b_box.zmin-0.01f, // 16
        b_box.xmin, b_box.ymin, b_box.zmin-0.01f, // 17
        b_box.xmin, b_box.ymax, b_box.zmin-0.01f, // 18
        b_box.xmax, b_box.ymax, b_box.zmin-0.01f, // 19
        // +y face
        b_box.xmin, b_box.ymax+0.01f, b_box.zmin, // 20
        b_box.xmax, b_box.ymax+0.01f, b_box.zmin, // 21
        b_box.xmax, b_box.ymax+0.01f, b_box.zmax, // 22
        b_box.xmin, b_box.ymax+0.01f, b_box.zmax, // 23
    };

    float colors[col_float_count] = {
        // -y face (bottom)
        0.0, 0.6, 0.0, 1.0, // 0
        0.0, 0.6, 0.0, 1.0, // 1
        0.0, 0.6, 0.0, 1.0, // 2
        0.0, 0.6, 0.0, 1.0, // 3
        // +x face
        1.0, 0.0, 0.0, 1.0, // 4
        1.0, 0.0, 0.0, 1.0, // 5
        1.0, 0.0, 0.0, 1.0, // 6
        1.0, 0.0, 0.0, 1.0, // 7
        // +z face
        0.0, 0.0, 1.0, 1.0, // 8
        0.0, 0.0, 1.0, 1.0, // 9
        0.0, 0.0, 1.0, 1.0, // 10
        0.0, 0.0, 1.0, 1.0, // 11
        // -x face
        0.6, 0.0, 0.0, 1.0, // 12
        0.6, 0.0, 0.0, 1.0, // 13
        0.6, 0.0, 0.0, 1.0, // 14
        0.6, 0.0, 0.0, 1.0, // 15
        // -z face
        0.0, 0.0, 0.6, 1.0, // 16
        0.0, 0.0, 0.6, 1.0, // 17
        0.0, 0.0, 0.6, 1.0, // 18
        0.0, 0.0, 0.6, 1.0, // 19
        // +y face
        0.0, 1.0, 0.0, 1.0, // 20
        0.0, 1.0, 0.0, 1.0, // 21
        0.0, 1.0, 0.0, 1.0, // 22
        0.0, 1.0, 0.0, 1.0  // 23
    };

    // two vertices per primitive = two indices per vertex
    unsigned char indices[index_count] = {
        // -y face
         0, 1, 1, 2, 2, 3, 3, 0,
        // +x face
         4, 5, 5, 6, 6, 7, 7, 4,
        // +z face
         8, 9, 9,10,10,11,11, 8,
        // -x face
        12,13,13,14,14,15,15,12,
        // -z face
        16,17,17,18,18,19,19,16,
        // +y face
        20,21,21,22,22,23,23,20
    };


    // make bounding box vao
    if (_vaoIDbbox != 0)
    {
        glDeleteVertexArrays(1, &_vaoIDbbox);
    }

    glGenVertexArrays(1, &_vaoIDbbox);
    glBindVertexArray(_vaoIDbbox);

    unsigned int vboIDs[3];
    glGenBuffers(3, vboIDs); // indices, positions, colors

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIDs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count*sizeof(unsigned char), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
    glBufferData(GL_ARRAY_BUFFER, pos_float_count*sizeof(float), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[2]);
    glBufferData(GL_ARRAY_BUFFER, col_float_count*sizeof(float), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}


void Mdl_base::draw_bbox(GLuint shaderIDbbox, float* view, float* persp)
{
    if (_vaoIDbbox != 0)
    {
        glUseProgram(shaderIDbbox);
        checkGLError(__FILE__, __LINE__);

        glBindVertexArray(_vaoIDbbox);
        checkGLError(__FILE__, __LINE__);

        glUniformMatrix4fv(glGetUniformLocation(shaderIDbbox, "modelMatrix"), 1, GL_FALSE, &(_model[0][0]));
        checkGLError(__FILE__, __LINE__);
        glUniformMatrix4fv(glGetUniformLocation(shaderIDbbox, "viewMatrix"), 1, GL_FALSE, view);
        checkGLError(__FILE__, __LINE__);
        glUniformMatrix4fv(glGetUniformLocation(shaderIDbbox, "perspMatrix"), 1, GL_FALSE, persp);
        checkGLError(__FILE__, __LINE__);

        glDrawElements(GL_LINES, 48, GL_UNSIGNED_BYTE, 0);
        checkGLError(__FILE__, __LINE__);

        glBindVertexArray(0);
        checkGLError(__FILE__, __LINE__);

        glUseProgram(0);
        checkGLError(__FILE__, __LINE__);
    }
}
