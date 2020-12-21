#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <GL/glew.h>

#define TEXTUREMANAGER_MAX_TEXTURES 32

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    void addTexture(int textureManagerTextureID, const char* texturePath);
    void addTexture(int textureManagerTextureID, int width, int height, unsigned char* textureData);
    void addSampleTexture(int textureManagerTextureID);

    GLuint getGLTextureID(int textureManagerTextureID);
private:
    GLuint _textureIDs[TEXTUREMANAGER_MAX_TEXTURES];
};

#endif /* TEXTUREMANAGER_HPP */