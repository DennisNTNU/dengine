#include "mdl/texturedSphere.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "mdl/sphereVAO.hpp"
#include "util.hpp"

TexturedSphere::TexturedSphere()
    : _texUpdateIncrementor(0)
    , _texID(0)
    , _vaoID(0)
    , _indexCount(0)
    , _shaderID(0)
{
    _model = glm::rotate(glm::mat4(1.0f), -3.1415926535f/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    _width = 1024;
    _height = 1024;

    _pixelCount = _width*_height;
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

    _subWidth = 1;
    _subHeight = 512;
    _textureSubData = new unsigned char[4*_subHeight*_subWidth];

    for (int h = 0; h < _subHeight; h++)
    {
        for (int w = 0; w < _subWidth; w++)
        {
            _textureSubData[h*_subWidth*4 + w*4 + 0] = 0;
            _textureSubData[h*_subWidth*4 + w*4 + 1] = 0;
            _textureSubData[h*_subWidth*4 + w*4 + 2] = 0;
            _textureSubData[h*_subWidth*4 + w*4 + 3] = 255;
        }
    }
}

TexturedSphere::TexturedSphere(char* texturePath)
    : _texID(0)
    , _vaoID(0)
    , _indexCount(0)
    , _shaderID(0)
{
    _model = glm::mat4(1.0f);
}

TexturedSphere::~TexturedSphere()
{
    glDeleteVertexArrays(1, &_vaoID);
    glDeleteTextures(1, &_texID);
    delete[] _textureData;
    delete[] _textureSubData;
}

void TexturedSphere::init(GLuint shaderID, char* texturePath)
{
    _shaderID = shaderID;

    if (_vaoID == 0)
        //initVAOSphere(&_vaoID, &_indexCount, 16, 32, 2.0f);
        initVAOSphereNoNormals(&_vaoID, &_indexCount, 16, 32, 2.0f);
    

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

void TexturedSphere::draw(float* view, float* persp)
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

    // assigning texture unit 0 to fragment shdaer smapler2D textureSampler 
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


void TexturedSphere::reinitTexture()
{
    _texUpdateIncrementor++;

    glActiveTexture(GL_TEXTURE0); checkGLError(__FILE__, __LINE__);
    glBindTexture(GL_TEXTURE_2D, _texID); checkGLError(__FILE__, __LINE__);
    glTexSubImage2D(GL_TEXTURE_2D, 0, _texUpdateIncrementor*11, 256, _subWidth, _subHeight, GL_RGBA, GL_UNSIGNED_BYTE, _textureSubData); checkGLError(__FILE__, __LINE__);
    glGenerateMipmap(GL_TEXTURE_2D); checkGLError(__FILE__, __LINE__);

    glBindTexture(GL_TEXTURE_2D, 0); checkGLError(__FILE__, __LINE__);
}


void TexturedSphere::_initTexture(unsigned char* imageData, int width, int height)
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

void TexturedSphere::_initTexture(char* texturePath)
{

}