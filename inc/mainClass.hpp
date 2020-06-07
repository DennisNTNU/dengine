#ifndef LOOP_H
#define LOOP_H

#include <GL/glew.h> // for glGetError(), gluErrorString()
#include <SFML/Window.hpp> // for sf::Window, sf::VideoMode()
#include <glm/glm.hpp>

#include "shaderManager.hpp"
#include "inputManager.hpp"
#include "camera.hpp"
#include "mdl/model.hpp"

class MainClass
{
public:
    MainClass();
    ~MainClass();

    int init(int argc, char** argv);
    void loop();

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
    ShaderManager _sm;
    InputManager _im;
    Camera _cam;

    Model _mdl;

    struct timeval tv;
    struct timeval tv_prev;
    double dt;
    double targetFrameTime;
};

#endif