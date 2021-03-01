#include "mdl/l2/mdl_example2.hpp"

#include <cstring>

Mdl_example2::Mdl_example2(GLuint shaderID)
    : Mdl_pos_col(shaderID)
{
    strncpy(_name, "Mdl_example2", 127);
    unsigned int* indices = nullptr;
    float* vertexPositions = nullptr;
    float* vertexColors = nullptr;
    int vertexCount = 0;

    initData(&indices, &vertexPositions, &vertexColors, &vertexCount);

    _initVAO(indices, vertexPositions, vertexColors, vertexCount);

    delete[] indices;
    delete[] vertexPositions;
    delete[] vertexColors;
}

Mdl_example2::~Mdl_example2()
{

}


void Mdl_example2::initData(unsigned int** indices, float** vertexPositions, float** vertexColors, int* vertexCount)
{
    // the two triangle example
    *vertexCount = 6;
    int triangleCount = 2;
    _indexCount = 3 * triangleCount;

    *indices = new unsigned int[_indexCount];
    *vertexPositions = new float[3 * (*vertexCount)];
    *vertexColors = new float[4 * (*vertexCount)];

    (*indices)[0] = 0;
    (*indices)[1] = 1;
    (*indices)[2] = 2;

    (*indices)[3] = 3;
    (*indices)[4] = 4;
    (*indices)[5] = 5;

    (*vertexPositions)[0] = 1.0f;
    (*vertexPositions)[1] = 0.0f;
    (*vertexPositions)[2] = 0.0f;

    (*vertexPositions)[3] = 0.0f;
    (*vertexPositions)[4] = 1.0f;
    (*vertexPositions)[5] = 0.0f;

    (*vertexPositions)[6] = -1.0f;
    (*vertexPositions)[7] = -1.0f;
    (*vertexPositions)[8] = 0.0f;

    (*vertexPositions)[9] = -1.0f;
    (*vertexPositions)[10] = 1.0f;
    (*vertexPositions)[11] = 0.0f;

    (*vertexPositions)[12] = 0.0f;
    (*vertexPositions)[13] = 1.0f;
    (*vertexPositions)[14] = -1.0f;

    (*vertexPositions)[15] = 1.0f;
    (*vertexPositions)[16] = 1.0f;
    (*vertexPositions)[17] = 1.0f;

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
