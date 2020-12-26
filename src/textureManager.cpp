#include "textureManager.hpp"

#include "util.hpp" // for checkGLError()
#include "lodepng.h"

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

void TextureManager::addTexture(int textureManagerTextureID, const char* texturePath)
{
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned char* image = NULL;
    int error = lodepng_decode32_file(&image, &width, &height, texturePath);
    if(error)
    {
        printf("Reading image error %u: %s\nTexture %i not added\n", error, lodepng_error_text(error), textureManagerTextureID);
        return;
    }
    addTexture(textureManagerTextureID, width, height, image);
}

void TextureManager::addTexture(int textureManagerTextureID, unsigned int width, unsigned int height, unsigned char* textureData)
{
    if (textureManagerTextureID >= TEXTUREMANAGER_MAX_TEXTURES)
    {
        return;
    }

    if (_textureIDs[textureManagerTextureID] != 0)
    {
        // delete preexisting texture
        glDeleteTextures(1, &(_textureIDs[textureManagerTextureID]));
    }

    glGenTextures(1, &(_textureIDs[textureManagerTextureID]));
    checkGLError(__FILE__, __LINE__);

    // doesnt need to call this here
    //glActiveTexture(GL_TEXTURE0);
    //checkGLError(__FILE__, __LINE__);

    glBindTexture(GL_TEXTURE_2D, _textureIDs[textureManagerTextureID]);
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

    printf("Texture ID: %i\n", _textureIDs[textureManagerTextureID]);
}

GLuint TextureManager::getGLTextureID(int textureManagerTextureID)
{
    if (textureManagerTextureID < TEXTUREMANAGER_MAX_TEXTURES)
    {
        return _textureIDs[textureManagerTextureID];
    }
    return -1;
}

void TextureManager::addSampleTexture(int textureManagerTextureID)
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
            texData[h*wdth*4 + w*4 + 3] = 255;
        }
    }

    addTexture(textureManagerTextureID, wdth, hght, texData);

    delete[] texData;
}