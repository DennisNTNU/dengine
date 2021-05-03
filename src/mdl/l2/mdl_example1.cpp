#include "mdl/l2/mdl_example1.hpp"

#include <cstring>

Mdl_example1::Mdl_example1(GLuint shaderID)
    : Mdl_pos_col(shaderID, GL_LINES)
{
    strncpy(_name, "Mdl_example1", 127);

    unsigned int* indices = nullptr;
    float* vertexPositions = nullptr;
    float* vertexColors = nullptr;
    int vertexCount = 0;

    initData(&vertexPositions, &vertexColors, &vertexCount, &indices);

    _initVAO(vertexPositions, vertexColors, vertexCount, indices);

    delete[] indices;
    delete[] vertexPositions;
    delete[] vertexColors;
}

Mdl_example1::~Mdl_example1()
{

}


void Mdl_example1::initData(float** vertexPositions, float** vertexColors, int* vertexCount, unsigned int** indices)
{
    // lines mesh example
    *vertexCount = 6;
    _indexCount = 2 * (*vertexCount);

    *indices = new unsigned int[_indexCount];
    *vertexPositions = new float[3 * (*vertexCount)];
    *vertexColors = new float[4 * (*vertexCount)];

    (*indices)[0] = 0;
    (*indices)[1] = 1;

    (*indices)[2] = 1;
    (*indices)[3] = 2;

    (*indices)[4] = 2;
    (*indices)[5] = 3;

    (*indices)[6] = 3;
    (*indices)[7] = 4;

    (*indices)[8] = 4;
    (*indices)[9] = 5;

    (*indices)[10] = 5;
    (*indices)[11] = 0;

    (*vertexPositions)[0] = 2.0f;
    (*vertexPositions)[1] = 0.0f;
    (*vertexPositions)[2] = 0.0f;

    (*vertexPositions)[3] = 0.0f;
    (*vertexPositions)[4] = 2.0f;
    (*vertexPositions)[5] = 0.0f;

    (*vertexPositions)[6] = -2.0f;
    (*vertexPositions)[7] = -2.0f;
    (*vertexPositions)[8] = 0.0f;

    (*vertexPositions)[9] = -2.0f;
    (*vertexPositions)[10] = 2.0f;
    (*vertexPositions)[11] = 0.0f;

    (*vertexPositions)[12] = 0.0f;
    (*vertexPositions)[13] = 2.0f;
    (*vertexPositions)[14] = -2.0f;

    (*vertexPositions)[15] = 2.0f;
    (*vertexPositions)[16] = 2.0f;
    (*vertexPositions)[17] = 2.0f;

    (*vertexColors)[0] = 1.0f;
    (*vertexColors)[1] = 0.0f;
    (*vertexColors)[2] = 0.0f;
    (*vertexColors)[3] = 1.0f;

    (*vertexColors)[4] = 0.0f;
    (*vertexColors)[5] = 1.0f;
    (*vertexColors)[6] = 0.0f;
    (*vertexColors)[7] = 1.0f;

    (*vertexColors)[8] = 1.0f;
    (*vertexColors)[9] = 1.0f;
    (*vertexColors)[10] = 0.0f;
    (*vertexColors)[11] = 1.0f;

    (*vertexColors)[12] = 1.0f;
    (*vertexColors)[13] = 1.0f;
    (*vertexColors)[14] = 0.0f;
    (*vertexColors)[15] = 1.0f;

    (*vertexColors)[16] = 0.0f;
    (*vertexColors)[17] = 1.0f;
    (*vertexColors)[18] = 1.0f;
    (*vertexColors)[19] = 1.0f;

    (*vertexColors)[20] = 1.0f;
    (*vertexColors)[21] = 1.0f;
    (*vertexColors)[22] = 1.0f;
    (*vertexColors)[23] = 1.0f;
}
