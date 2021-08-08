#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include <GL/glew.h>

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    int addProgramFile(int which, const char* vertexShaderPath, const char* fragmentShaderPath);
    int addProgramSource(int which, const char* vertexShaderSrc, const char* fragmentShaderSrc);

    void useProgram(int which);
    void unuseProgram(void);

    GLuint getProgramID(int which);

    GLuint getUniformLocation(int which, const char* uniformName);
    GLuint getAttributeLocation(int which, const char* attributeName);
private:
    GLuint _shaderProgramIDs[32];
};

#endif