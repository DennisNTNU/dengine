#include "model.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "util.hpp"

Model::Model()
    : _texID(0)
    , _vaoID(0)
    , _indexCount(0)
    , _shaderID(0)
{
    _model = glm::rotate(glm::mat4(1.0f), -3.1415926535f/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    _width = 1024;
    _height = 1024;

    int _pixelCount = _width*_height;
    _byteCount = 4*_pixelCount;

    _textureData = new unsigned char[_byteCount];
/*
    for (int i = 3; i < _byteCount; i += 4)
    {
        textureData[i] = 255;
    }*/

    for (int h = 0; h < _height; h++)
    {
        for (int w = 0; w < _width; w++)
        {
            _textureData[h*_width*4 + w*4 + 0] = w/4;
            _textureData[h*_width*4 + w*4 + 1] = 0;
            _textureData[h*_width*4 + w*4 + 2] = 0;
            _textureData[h*_width*4 + w*4 + 3] = 155;
        }
    }

    for (int i = 1; i < 101; i++)
    {
        printf("%i ", _textureData[i-1]);
        if (i % 24 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

Model::~Model()
{
    if (_vaoID != 0)
        glDeleteVertexArrays(1, &_vaoID);
    if (_texID != 0)
        glDeleteTextures(1, &_texID);

    delete[] _textureData;
}

void Model::init(GLuint shaderID, char* texturePath)
{
    _shaderID = shaderID;

    if (_vaoID == 0)
        //initVAOSphere(&_vaoID, &_indexCount, 16, 32, 2.0f);
        _initMesh();
    

    if (texturePath != 0)
        _initTexture(texturePath);
    else
    {
        printf("Initing texture\n");

        /*
        unsigned char image[] =
            { 255, 255, 255, 255,   100, 100, 100, 255,
              100, 100, 100, 255,   255, 255, 255, 255 };

        int width = 2;
        int height = 2;

        _initTexture(image, width, height);*/

        
        _initTexture(_textureData, _width, _height);
    }
}

void Model::draw(float* view, float* persp)
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
    glBindTexture(GL_TEXTURE_2D, _texID);
    checkGLError(__FILE__, __LINE__);
    // assign textureSampler variable in fragment shader to texture unit 0
    glUniform1i(glGetUniformLocation(_shaderID, "textureSampler"), 0);
    checkGLError(__FILE__, __LINE__);


    glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_SHORT, 0);
    checkGLError(__FILE__, __LINE__);

    glUseProgram(0);
    checkGLError(__FILE__, __LINE__);
}

void Model::_initMesh()
{

    int vertexCount = 30;
    int triangleCount = 24;
    _indexCount = 3 * triangleCount;

    unsigned short* indices = new unsigned short[_indexCount];
    float* vertexPoses = new float[3 * vertexCount];
    float* vertexUVs = new float[2 * vertexCount];


    int p = 0;
    int i = 0;
    vertexPoses[p++] = -1.0f; // 0
    vertexPoses[p++] = 0.0f;
    vertexPoses[p++] = 1.0f;

    vertexPoses[p++] = 1.0f; // 1
    vertexPoses[p++] = 0.0f;
    vertexPoses[p++] = 1.0f;

    vertexPoses[p++] = 1.0f; // 2
    vertexPoses[p++] = 0.0f;
    vertexPoses[p++] = -1.0f;

    vertexPoses[p++] = -1.0f; // 3
    vertexPoses[p++] = 0.0f;
    vertexPoses[p++] = -1.0f;

    vertexPoses[p++] = 0.0f; // 4
    vertexPoses[p++] = 1.0f;
    vertexPoses[p++] = 0.0f; // 15

    indices[i++] = 0;
    indices[i++] = 2;
    indices[i++] = 1;

    indices[i++] = 0;
    indices[i++] = 3;
    indices[i++] = 2;

    indices[i++] = 0;
    indices[i++] = 1;
    indices[i++] = 4;

    indices[i++] = 2;
    indices[i++] = 3;
    indices[i++] = 4;

    
    for (int j = 0; j < 5; j++)
    {
        int vc = 3*j;

        vertexPoses[vc + 0 + 15] = vertexPoses[vc + 0] + 2.0f;
        vertexPoses[vc + 1 + 15] = vertexPoses[vc + 1];
        vertexPoses[vc + 2 + 15] = vertexPoses[vc + 2];

        vertexPoses[vc + 0 + 30] = vertexPoses[vc + 0] - 2.0f;
        vertexPoses[vc + 1 + 30] = vertexPoses[vc + 1];
        vertexPoses[vc + 2 + 30] = vertexPoses[vc + 2];

        vertexPoses[vc + 0 + 45] = vertexPoses[vc + 0];
        vertexPoses[vc + 1 + 45] = vertexPoses[vc + 1];
        vertexPoses[vc + 2 + 45] = vertexPoses[vc + 2] + 2.0f;

        vertexPoses[vc + 0 + 60] = vertexPoses[vc + 0];
        vertexPoses[vc + 1 + 60] = vertexPoses[vc + 1];
        vertexPoses[vc + 2 + 60] = vertexPoses[vc + 2] - 2.0f;

        vertexPoses[vc + 0 + 75] = vertexPoses[vc + 0];
        vertexPoses[vc + 1 + 75] = vertexPoses[vc + 1] + 2.0f;
        vertexPoses[vc + 2 + 75] = vertexPoses[vc + 2];
    }

    for (int j = 0; j < 4; j++)
    {
        int vc = 3*j;

        indices[vc + 0 + 12] = indices[vc + 0] + 5;
        indices[vc + 1 + 12] = indices[vc + 1] + 5;
        indices[vc + 2 + 12] = indices[vc + 2] + 5;

        indices[vc + 0 + 24] = indices[vc + 0] + 10;
        indices[vc + 1 + 24] = indices[vc + 1] + 10;
        indices[vc + 2 + 24] = indices[vc + 2] + 10;

        indices[vc + 0 + 36] = indices[vc + 0] + 15;
        indices[vc + 1 + 36] = indices[vc + 1] + 15;
        indices[vc + 2 + 36] = indices[vc + 2] + 15;

        indices[vc + 0 + 48] = indices[vc + 0] + 20;
        indices[vc + 1 + 48] = indices[vc + 1] + 20;
        indices[vc + 2 + 48] = indices[vc + 2] + 20;

        indices[vc + 0 + 60] = indices[vc + 0] + 25;
        indices[vc + 1 + 60] = indices[vc + 1] + 25;
        indices[vc + 2 + 60] = indices[vc + 2] + 25;
    }


    for (int i = 0; i < vertexCount; i++)
    {
        vertexUVs[2*i + 0] = 0.0f;
        vertexUVs[2*i + 1] = 0.0f;

    }




    glGenVertexArrays(1, &_vaoID);
    glBindVertexArray(_vaoID);

    unsigned int vboIDs[3];
    glGenBuffers(3, vboIDs); // indices, positions, UVs

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIDs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount*sizeof(unsigned short), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[1]);
    glBufferData(GL_ARRAY_BUFFER, 3 * vertexCount*sizeof(float), vertexPoses, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vboIDs[2]);
    glBufferData(GL_ARRAY_BUFFER, 2 * vertexCount*sizeof(float), vertexUVs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(1);

    delete[] indices;
    delete[] vertexPoses;
    delete[] vertexUVs;
}

void Model::_initTexture(unsigned char* imageData, int width, int height)
{
    if (_texID == 0)
        glGenTextures(1, &_texID);
    checkGLError(__FILE__, __LINE__);

    //glActiveTexture(GL_TEXTURE0);
    //checkGLError(__FILE__, __LINE__);

    glBindTexture(GL_TEXTURE_2D, _texID);
    checkGLError(__FILE__, __LINE__);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    checkGLError(__FILE__, __LINE__);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    checkGLError(__FILE__, __LINE__);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    checkGLError(__FILE__, __LINE__);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    checkGLError(__FILE__, __LINE__);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    checkGLError(__FILE__, __LINE__);

    glGenerateMipmap(GL_TEXTURE_2D);
    checkGLError(__FILE__, __LINE__);

    glBindTexture(GL_TEXTURE_2D, 0);
    checkGLError(__FILE__, __LINE__);
}

void Model::_initTexture(char* texturePath)
{

}