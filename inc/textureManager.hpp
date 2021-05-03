#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <GL/glew.h>

#define TEXTUREMANAGER_MAX_TEXTURES 32

#define TM_MONO16 1
#define TM_RGBA8 2
#define TM_MONO8 3

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();

    void addTexture(int textureManagerTextureID, const char* texturePath);
    void addTexture(int textureManagerTextureID, unsigned int width, unsigned int height, unsigned char* textureData, int texFormat);
    void addSampleTexture(int textureManagerTextureID);

    GLuint getGLTextureID(int textureManagerTextureID);
private:
    GLuint _textureIDs[TEXTUREMANAGER_MAX_TEXTURES];
};

#endif /* TEXTUREMANAGER_HPP */