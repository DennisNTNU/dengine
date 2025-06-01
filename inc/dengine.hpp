#ifndef LOOP_H
#define LOOP_H

#include <vector>
//#include <list>

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

    int addModel(int smShaderID, int tmTextureID, float* positions, float* uvs, int vertex_count, unsigned int* indices, int index_count);

    int addModel(const char* model_str, int smShaderID, int tmTextureID);

    int addModel(int smShaderID, const char* objModelPath);
    int addModel(int smShaderID, int tmTextureID, const char* objModelPath);
    int addModel_normals(int smShaderID, int tmTextureID, const char* objModelPath);

    int addModel_linestrip(int smShaderID, float* positions, float* colors, int vertex_count, unsigned int* indices, int index_count);

    void translateLastAddedModel(float x, float y, float z);
    void translateModel(int index, float x, float y, float z);
    void setPositionModel(int index, float x, float y, float z);
    void changeTextureModel(int index, int tmTextureID);

    void removeLastModel();
    void removeModelByIndex(int index);

    void registerBboxShader(int smShaderID);

    void loop(void (*callback)(void* data), void* data);

    void getWindowDims(int* x, int* y)
    {
        sf::Vector2u sz = _w->getSize();
        *x = sz.x;
        *y = sz.y;
    }

    bool get_window_closed_bool(){ return _window_closed; }

    std::vector<Mdl_base*> _models;

    ShaderManager sm;
    TextureManager tm;
    InputManager im;
protected:
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
    bool _window_closed;
    Camera _cam;

    GLuint _shaderIDbbox;

    struct timeval tv;
    struct timeval tv_prev;
    double dt;
    double targetFrameTime;
};

#endif