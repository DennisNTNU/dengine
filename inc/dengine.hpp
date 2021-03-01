#ifndef LOOP_H
#define LOOP_H

#include <vector>

#include <GL/glew.h> // for glGetError(), gluErrorString()
#include <SFML/Window.hpp> // for sf::Window, sf::VideoMode()
#include <glm/glm.hpp>

#include "shaderManager.hpp"
#include "textureManager.hpp"
#include "inputManager.hpp"
#include "camera.hpp"
#include "mdl/mdl_base.hpp"

class Dengine
{
public:
    Dengine();
    ~Dengine();

    int init(int argc, char** argv);

    void addModel(const char* model, GLuint shaderID, GLuint texID);
    void addModel(GLuint shaderID, GLuint texID, const char* objModelPath);
    void addModel(GLuint shaderID, const char* objModelPath);
    int addModel(float* positions, float* uvs, int vertex_count, int* indices, int index_count);

    void translateLastAddedModel(float x, float y, float z);

    void registerBboxShader(GLuint shaderID);

    void loop();

    std::vector<Mdl_base*> _models;

    ShaderManager sm;
    TextureManager tm;
    InputManager im;
private:
    int _initWindow();
    int _initGlew();
    void _initGLParams();
    void _initShaders();


    bool _handleSFMLEvents();
    bool _handleInput();

    void _computeProjectionMatrix();

    void _updateScene(double dt);

    void _draw();
    void _glClear();

    sf::Window* _w;
    bool _hasWindowFocus;
    int _width;
    int _height;
    Camera _cam;

    GLuint _shaderIDbbox;

    struct timeval tv;
    struct timeval tv_prev;
    double dt;
    double targetFrameTime;
};

#endif