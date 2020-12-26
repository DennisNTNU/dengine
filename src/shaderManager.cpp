#include "shaderManager.hpp"

#include <stdio.h>
#include <fcntl.h> // for open()
#include <unistd.h> // for read()
#include <sys/stat.h> // fstat()

#include "util.hpp"


ShaderManager::ShaderManager()
    : _shaderProgramIDs{0}
{

}

ShaderManager::~ShaderManager()
{

}

void ShaderManager::addProgram(int which, const char* vertexShaderPath, const char* fragmentShaderPath)
{


    int fd_vert = open(vertexShaderPath, O_RDONLY);
    if (fd_vert < 0)
    {
        printf("Could not read vertex shader:\n%s\n", vertexShaderPath);
        return;
    }

    struct stat statbuf;
    fstat(fd_vert, &statbuf);

    char* vertexShader = new char[statbuf.st_size + 1];
    int byteCountRead = read(fd_vert, vertexShader, statbuf.st_size);
    if (byteCountRead != statbuf.st_size)
    {
        printf("Unexpected number of bytes (%i) read from vertex shader file. Expected %li\n", byteCountRead, statbuf.st_size);
    }
    vertexShader[statbuf.st_size] = 0;
    // printf("VertexShader:\n%s", vertexShader);

    close(fd_vert);




    int fd_frag = open(fragmentShaderPath, O_RDONLY);
    if (fd_frag < 0)
    {
        printf("Could not read fragment shader:\n%s\n", fragmentShaderPath);
        return;
    }

    fstat(fd_frag, &statbuf);

    char* fragmentShader = new char[statbuf.st_size + 1];
    byteCountRead = read(fd_frag, fragmentShader, statbuf.st_size);
    if (byteCountRead != statbuf.st_size)
    {
        printf("Unexpected number of bytes (%i) read from fragment shader file. Expected %li\n", byteCountRead, statbuf.st_size);
    }

    fragmentShader[statbuf.st_size] = 0;
    // printf("FragmentShader:\n%s", fragmentShader);

    close(fd_frag);


    
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    checkGLError(__FILE__, __LINE__);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    checkGLError(__FILE__, __LINE__);

    glShaderSource(vertexShaderID, 1, &vertexShader, nullptr);
    checkGLError(__FILE__, __LINE__);
    glShaderSource(fragmentShaderID, 1, &fragmentShader, nullptr);
    checkGLError(__FILE__, __LINE__);

    delete[] vertexShader;
    delete[] fragmentShader;
    
    GLint success = 0;
    glCompileShader(vertexShaderID);
    checkGLError(__FILE__, __LINE__);

    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        
        GLint maxLength = 0;
        glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        char* errorLog = new char[maxLength];
        glGetShaderInfoLog(vertexShaderID, maxLength, &maxLength, errorLog);
        
        printf(" -------- Couldnt compile %s\n%s\n --------\n", vertexShaderPath, errorLog);

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(vertexShaderID); // Don't leak the shader.

        delete[] errorLog;

        return;
    }
    


    glCompileShader(fragmentShaderID);
    checkGLError(__FILE__, __LINE__);
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        
        GLint maxLength = 0;
        glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &maxLength); checkGLError(__FILE__, __LINE__);

        // The maxLength includes the NULL character
        char* errorLog = new char[maxLength];
        glGetShaderInfoLog(fragmentShaderID, maxLength, &maxLength, errorLog); checkGLError(__FILE__, __LINE__);

        printf(" -------- Couldnt compile %s\n%s\n --------\n", fragmentShaderPath, errorLog);
        
        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(fragmentShaderID); // Don't leak the shader.
        checkGLError(__FILE__, __LINE__);

        delete[] errorLog;

        return;
    }


    // create shader program
    if (_shaderProgramIDs[which] != 0)
    {
        glDeleteProgram(_shaderProgramIDs[which]);
        checkGLError(__FILE__, __LINE__);
    }
    _shaderProgramIDs[which] = glCreateProgram();
    checkGLError(__FILE__, __LINE__);
    glAttachShader(_shaderProgramIDs[which], vertexShaderID);
    checkGLError(__FILE__, __LINE__);
    glAttachShader(_shaderProgramIDs[which], fragmentShaderID);
    checkGLError(__FILE__, __LINE__);

    // link the shaders
    glLinkProgram(_shaderProgramIDs[which]);
    checkGLError(__FILE__, __LINE__);
    glGetProgramiv(_shaderProgramIDs[which], GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(_shaderProgramIDs[which], GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        char* errorLog = new char[maxLength];
        glGetProgramInfoLog(_shaderProgramIDs[which], maxLength, &maxLength, errorLog);

        printf(" -------- Couldnt link shader program\n%s\n%s\n%s\n --------\n", vertexShaderPath, fragmentShaderPath, errorLog);

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteProgram(_shaderProgramIDs[which]); // Don't leak the program

        _shaderProgramIDs[which] = 0;

        delete[] errorLog;
    }

    // clean up the shaders
    glDetachShader(_shaderProgramIDs[which], vertexShaderID);
    checkGLError(__FILE__, __LINE__);
    glDetachShader(_shaderProgramIDs[which], fragmentShaderID);
    checkGLError(__FILE__, __LINE__);
    glDeleteShader(vertexShaderID);
    checkGLError(__FILE__, __LINE__);
    glDeleteShader(fragmentShaderID);
    checkGLError(__FILE__, __LINE__);

    printf("Shader program ID: %i\n", _shaderProgramIDs[which]);
}


void ShaderManager::useProgram(int which)
{
    glUseProgram(_shaderProgramIDs[which]);
    checkGLError(__FILE__, __LINE__);
}

void ShaderManager::unuseProgram(void)
{
    glUseProgram(0);
    checkGLError(__FILE__, __LINE__);
}

GLuint ShaderManager::getProgramID(int which)
{
    return _shaderProgramIDs[which];
}

GLuint ShaderManager::getUniformLocation(int which, const char* uniformName)
{
    GLuint loc =  glGetUniformLocation(_shaderProgramIDs[which], uniformName);
    if (loc == GL_INVALID_INDEX)
    {
        printf("Uniform %s not found in shader %i!", uniformName, which);
        return -1;
    }
    return loc;
}

GLuint ShaderManager::getAttributeLocation(int which, const char* attributeName)
{
    GLuint loc =  glGetAttribLocation(_shaderProgramIDs[which], attributeName);
    if (loc == GL_INVALID_INDEX)
    {
        printf("Attribute %s not found in shader %i! ", attributeName, which);
        return -1;
    }
    return loc;
}