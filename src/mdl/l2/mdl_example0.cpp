#include "mdl/l2/mdl_example0.hpp"

#include <cstring>

Mdl_example0::Mdl_example0(GLuint shaderID, GLuint textureID)
    : Mdl_pos_tex(shaderID, textureID, GL_TRIANGLES)
{
    strncpy(_name, "Mdl_example0", 127);

    unsigned int* indices = nullptr;
    float* vertexPositions = nullptr;
    float* vertexUVs = nullptr;
    int vertexCount = 0;

    initData(&vertexPositions, &vertexUVs, &vertexCount, &indices);

    _initVAO(vertexPositions, vertexUVs, vertexCount, indices);

    delete[] indices;
    delete[] vertexPositions;
    delete[] vertexUVs;
}

Mdl_example0::~Mdl_example0()
{

}


void Mdl_example0::initData(float** vertexPositions, float** vertexUVs, int* vertexCount, unsigned int** indices)
{
    // the 6 pyramid mesh
    *vertexCount = 30;
    int triangleCount = 24;
    _indexCount = 3 * triangleCount;

    *indices = new unsigned int[_indexCount];
    *vertexPositions = new float[3 * (*vertexCount)];
    *vertexUVs = new float[2 * (*vertexCount)];

    // mesh has vertices like a pyramid
    int p = 0;
    int i = 0;
    int u = 0;
    (*vertexPositions)[p++] = -1.0f; // 0
    (*vertexPositions)[p++] = 0.0f;
    (*vertexPositions)[p++] = 1.0f;

    (*vertexPositions)[p++] = 1.0f; // 1
    (*vertexPositions)[p++] = 0.0f;
    (*vertexPositions)[p++] = 1.0f;

    (*vertexPositions)[p++] = 1.0f; // 2
    (*vertexPositions)[p++] = 0.0f;
    (*vertexPositions)[p++] = -1.0f;

    (*vertexPositions)[p++] = -1.0f; // 3
    (*vertexPositions)[p++] = 0.0f;
    (*vertexPositions)[p++] = -1.0f;

    (*vertexPositions)[p++] = 0.0f; // 4
    (*vertexPositions)[p++] = 1.0f;
    (*vertexPositions)[p++] = 0.0f; // 15

    (*vertexUVs)[u++] = 0.0f;
    (*vertexUVs)[u++] = 0.0f;
    
    (*vertexUVs)[u++] = 1.0f;
    (*vertexUVs)[u++] = 0.0f;

    (*vertexUVs)[u++] = 0.0f;
    (*vertexUVs)[u++] = 1.0f;
    
    (*vertexUVs)[u++] = 1.0f;
    (*vertexUVs)[u++] = 1.0f;

    (*vertexUVs)[u++] = 0.0f;
    (*vertexUVs)[u++] = 0.0f;

    (*indices)[i++] = 0;
    (*indices)[i++] = 2;
    (*indices)[i++] = 1;

    (*indices)[i++] = 0;
    (*indices)[i++] = 3;
    (*indices)[i++] = 2;

    (*indices)[i++] = 0;
    (*indices)[i++] = 1;
    (*indices)[i++] = 4;

    (*indices)[i++] = 2;
    (*indices)[i++] = 3;
    (*indices)[i++] = 4;

    
    for (int j = 0; j < 5; j++)
    {
        int vc = 3*j;
        int vc_uv = 2*j;

        (*vertexPositions)[vc + 0 + 15] = (*vertexPositions)[vc + 0] + 2.0f;
        (*vertexPositions)[vc + 1 + 15] = (*vertexPositions)[vc + 1];
        (*vertexPositions)[vc + 2 + 15] = (*vertexPositions)[vc + 2];
        (*vertexUVs)[vc_uv + 0 + 10] = (*vertexUVs)[vc_uv + 0];
        (*vertexUVs)[vc_uv + 1 + 10] = (*vertexUVs)[vc_uv + 1];

        (*vertexPositions)[vc + 0 + 30] = (*vertexPositions)[vc + 0] - 2.0f;
        (*vertexPositions)[vc + 1 + 30] = (*vertexPositions)[vc + 1];
        (*vertexPositions)[vc + 2 + 30] = (*vertexPositions)[vc + 2];
        (*vertexUVs)[vc_uv + 0 + 20] = (*vertexUVs)[vc_uv + 0];
        (*vertexUVs)[vc_uv + 1 + 20] = (*vertexUVs)[vc_uv + 1];

        (*vertexPositions)[vc + 0 + 45] = (*vertexPositions)[vc + 0];
        (*vertexPositions)[vc + 1 + 45] = (*vertexPositions)[vc + 1];
        (*vertexPositions)[vc + 2 + 45] = (*vertexPositions)[vc + 2] + 2.0f;
        (*vertexUVs)[vc_uv + 0 + 30] = (*vertexUVs)[vc_uv + 0];
        (*vertexUVs)[vc_uv + 1 + 30] = (*vertexUVs)[vc_uv + 1];

        (*vertexPositions)[vc + 0 + 60] = (*vertexPositions)[vc + 0];
        (*vertexPositions)[vc + 1 + 60] = (*vertexPositions)[vc + 1];
        (*vertexPositions)[vc + 2 + 60] = (*vertexPositions)[vc + 2] - 2.0f;
        (*vertexUVs)[vc_uv + 0 + 40] = (*vertexUVs)[vc_uv + 0];
        (*vertexUVs)[vc_uv + 1 + 40] = (*vertexUVs)[vc_uv + 1];

        (*vertexPositions)[vc + 0 + 75] = (*vertexPositions)[vc + 0];
        (*vertexPositions)[vc + 1 + 75] = (*vertexPositions)[vc + 1] + 2.0f;
        (*vertexPositions)[vc + 2 + 75] = (*vertexPositions)[vc + 2];
        (*vertexUVs)[vc_uv + 0 + 50] = (*vertexUVs)[vc_uv + 0];
        (*vertexUVs)[vc_uv + 1 + 50] = (*vertexUVs)[vc_uv + 1];
    }

    for (int j = 0; j < 4; j++)
    {
        int vc = 3*j;

        (*indices)[vc + 0 + 12] = (*indices)[vc + 0] + 5;
        (*indices)[vc + 1 + 12] = (*indices)[vc + 1] + 5;
        (*indices)[vc + 2 + 12] = (*indices)[vc + 2] + 5;

        (*indices)[vc + 0 + 24] = (*indices)[vc + 0] + 10;
        (*indices)[vc + 1 + 24] = (*indices)[vc + 1] + 10;
        (*indices)[vc + 2 + 24] = (*indices)[vc + 2] + 10;

        (*indices)[vc + 0 + 36] = (*indices)[vc + 0] + 15;
        (*indices)[vc + 1 + 36] = (*indices)[vc + 1] + 15;
        (*indices)[vc + 2 + 36] = (*indices)[vc + 2] + 15;

        (*indices)[vc + 0 + 48] = (*indices)[vc + 0] + 20;
        (*indices)[vc + 1 + 48] = (*indices)[vc + 1] + 20;
        (*indices)[vc + 2 + 48] = (*indices)[vc + 2] + 20;

        (*indices)[vc + 0 + 60] = (*indices)[vc + 0] + 25;
        (*indices)[vc + 1 + 60] = (*indices)[vc + 1] + 25;
        (*indices)[vc + 2 + 60] = (*indices)[vc + 2] + 25;
    }

/*
    for (int i = 0; i < *vertexCount; i++)
    {
        (*vertexUVs)[2*i + 0] = 0.0f;
        (*vertexUVs)[2*i + 1] = 0.0f;
    }*/
}
