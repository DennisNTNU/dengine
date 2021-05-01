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

#define DGN_2D 1
#define DGN_NOT_GRAB_MOUSE 2
#define DGN_NOT_HIDE_MOUSE 4
#define DGN_RESIZABLE 8

class Dengine
{
public:
    Dengine();
    ~Dengine();

    int init(int argc, char** argv, int flags);

    void addModel(int whichShadID, int whichTexID, float* positions, float* uvs, int vertex_count, unsigned int* indices, int index_count);
    void addModel(const char* model_str, int whichShadID, int whichTexID);
    void addModel(int whichShadID, int whichTexID, const char* objModelPath);
    void addModel_normals(int whichShadID, int whichTexID, const char* objModelPath);
    void addModel(int whichShadID, const char* objModelPath);

    void translateLastAddedModel(float x, float y, float z);

    void registerBboxShader(int whichShadID);

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
    int _initFlags;
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