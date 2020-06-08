#include "mdl/mdl_example2.hpp"

Mdl_example2::Mdl_example2(GLuint shaderID)
	: Mdl_pos(shaderID)
{
    unsigned int* indices = nullptr;
    float* vertexPositions = nullptr;
    int vertexCount = 0;

    initData(&indices, &vertexPositions,&vertexCount);

    _initVAO(indices, vertexPositions, vertexCount);

    delete[] indices;
    delete[] vertexPositions;
}

Mdl_example2::~Mdl_example2()
{

}


void Mdl_example2::initData(unsigned int** indices, float** vertexPositions, int* vertexCount)
{
    *vertexCount = 6;
    int triangleCount = 2;
    _indexCount = 3 * triangleCount;

    *indices = new unsigned int[_indexCount];
    *vertexPositions = new float[3 * (*vertexCount)];

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

    /*
    *vertexCount = 30;
    int triangleCount = 24;
    _indexCount = 3 * triangleCount;

    *indices = new unsigned int[_indexCount];
    *vertexPositions = new float[3 * (*vertexCount)];
    *vertexUVs = new float[2 * (*vertexCount)];

    int p = 0;
    int i = 0;
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

        (*vertexPositions)[vc + 0 + 15] = (*vertexPositions)[vc + 0] + 2.0f;
        (*vertexPositions)[vc + 1 + 15] = (*vertexPositions)[vc + 1];
        (*vertexPositions)[vc + 2 + 15] = (*vertexPositions)[vc + 2];

        (*vertexPositions)[vc + 0 + 30] = (*vertexPositions)[vc + 0] - 2.0f;
        (*vertexPositions)[vc + 1 + 30] = (*vertexPositions)[vc + 1];
        (*vertexPositions)[vc + 2 + 30] = (*vertexPositions)[vc + 2];

        (*vertexPositions)[vc + 0 + 45] = (*vertexPositions)[vc + 0];
        (*vertexPositions)[vc + 1 + 45] = (*vertexPositions)[vc + 1];
        (*vertexPositions)[vc + 2 + 45] = (*vertexPositions)[vc + 2] + 2.0f;

        (*vertexPositions)[vc + 0 + 60] = (*vertexPositions)[vc + 0];
        (*vertexPositions)[vc + 1 + 60] = (*vertexPositions)[vc + 1];
        (*vertexPositions)[vc + 2 + 60] = (*vertexPositions)[vc + 2] - 2.0f;

        (*vertexPositions)[vc + 0 + 75] = (*vertexPositions)[vc + 0];
        (*vertexPositions)[vc + 1 + 75] = (*vertexPositions)[vc + 1] + 2.0f;
        (*vertexPositions)[vc + 2 + 75] = (*vertexPositions)[vc + 2];
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

        indices[vc + 0 + 60] = indices[vc + 0] + 25;
        indices[vc + 1 + 60] = indices[vc + 1] + 25;
        indices[vc + 2 + 60] = indices[vc + 2] + 25;
    }


    for (int i = 0; i < *vertexCount; i++)
    {
        (*vertexUVs)[2*i + 0] = 0.0f;
        (*vertexUVs)[2*i + 1] = 0.0f;
    }
    */


}
