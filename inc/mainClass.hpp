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
#include "mdl/mdl_example0.hpp"
#include "mdl/mdl_example1.hpp"
#include "mdl/mdl_example2.hpp"
#include "mdl/mdl_axes_orthnorm.hpp"

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
    TextureManager _tm;
    InputManager _im;
    Camera _cam;

    std::vector<Mdl_base*> _models;

    struct timeval tv;
    struct timeval tv_prev;
    double dt;
    double targetFrameTime;
};

#endif