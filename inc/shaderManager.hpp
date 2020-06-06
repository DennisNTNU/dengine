#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <GL/glew.h>

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    void makeProgram(const char* vertexShaderPath, const char* fragmentShaderPath, int which);
    void useProgram(int which);
    void unuseProgram(void);

    GLuint getProgramID(int which);

    GLuint getUniformLocation(int which, const char* uniformName);
    GLuint getAttributeLocation(int which, const char* attributeName);
private:
    GLuint _shaderProgramIDs[32];
};

#endif