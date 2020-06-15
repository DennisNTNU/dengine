#include "textureManager.hpp"

#include "util.hpp" // for checkGLError()

TextureManager::TextureManager()
    : _textureIDs{0}
{
}

TextureManager::~TextureManager()
{
    for (int i = 0; i < TEXTUREMANAGER_MAX_TEXTURES; i++)
    {
        if (_textureIDs[i] != 0)
        {
            // delete preexisting texture
            glDeleteTextures(1, &(_textureIDs[i]));
        }
    }
}

void TextureManager::addTexture(int which, const char* texturePath)
{

}

void TextureManager::addTexture(int which, int width, int height, unsigned char* textureData)
{
    if (which >= TEXTUREMANAGER_MAX_TEXTURES)
    {
        return;
    }

    if (_textureIDs[which] != 0)
    {
        // delete preexisting texture
        glDeleteTextures(1, &(_textureIDs[which]));
    }

    glGenTextures(1, &(_textureIDs[which]));
    checkGLError(__FILE__, __LINE__);

    // doesnt need to call this here
    //glActiveTexture(GL_TEXTURE0);
    //checkGLError(__FILE__, __LINE__);

    glBindTexture(GL_TEXTURE_2D, _textureIDs[which]);
    checkGLError(__FILE__, __LINE__);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    checkGLError(__FILE__, __LINE__);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    checkGLError(__FILE__, __LINE__);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    checkGLError(__FILE__, __LINE__);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    checkGLError(__FILE__, __LINE__);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    checkGLError(__FILE__, __LINE__);

    glGenerateMipmap(GL_TEXTURE_2D);
    checkGLError(__FILE__, __LINE__);

    glBindTexture(GL_TEXTURE_2D, 0);
    checkGLError(__FILE__, __LINE__);

    printf("Texture ID: %i\n", _textureIDs[which]);
}

GLuint TextureManager::getTextureID(int which)
{
    if (which < TEXTUREMANAGER_MAX_TEXTURES)
    {
        return _textureIDs[which];
    }
    return -1;
}

void TextureManager::addSampleTexture(int which)
{
    int wdth = 1024;
    int hght = 1024;
    int pxlCount = wdth*hght;
    int byteCount = 4*pxlCount;
    unsigned char* texData = new unsigned char[byteCount];

    for (int h = 0; h < hght; h++)
    {
        for (int w = 0; w < wdth; w++)
        {
            texData[h*wdth*4 + w*4 + 0] = w/4;
            texData[h*wdth*4 + w*4 + 1] = 0;
            texData[h*wdth*4 + w*4 + 2] = 0;
            texData[h*wdth*4 + w*4 + 3] = 155;
        }
    }

    addTexture(which, wdth, hght, texData);

    delete[] texData;
}