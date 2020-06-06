#ifndef TEXTUREDSPHERE_H
#define TEXTUREDSPHERE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class TexturedSphere
{
public:
    TexturedSphere();
    TexturedSphere(char* texturePath);
    ~TexturedSphere();

    void addTexture(char* texturePath);

    void init(GLuint shaderID, char* texturePath);

    void draw(float* view, float* persp);

    void reinitTexture();

private:
    void _initTexture(unsigned char* imageData, int width, int height);
    void _initTexture(char* texturePath);

    int _width;
    int _height;
    int _pixelCount;
    int _byteCount;
    unsigned char* _textureData;

    int _subWidth;
    int _subHeight;
    unsigned char* _textureSubData;

    int _texUpdateIncrementor;


    GLuint _texID;

    GLuint _vaoID;
    unsigned int _indexCount;

    GLuint _shaderID;

    glm::mat4 _model;
};

#endif