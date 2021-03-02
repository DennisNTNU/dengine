#include "dengine.hpp"

#include <sys/time.h> // for gettimeofday()
#include <string.h> // for strcmp()

#include <glm/gtc/matrix_transform.hpp>

#include "mdl/l2/mdl_axes_orthnorm.hpp"
#include "mdl/l2/mdl_example0.hpp"
#include "mdl/l2/mdl_example1.hpp"
#include "mdl/l2/mdl_example2.hpp"
#include "mdl/l2/mdl_pos_tex_obj.hpp"
#include "mdl/l2/mdl_pos_tex_norm_obj.hpp"
#include "util.hpp"

Dengine::Dengine()
    : _w(nullptr)
    , _hasWindowFocus(true)
    , _width(1280)
    , _height(720)
    , _shaderIDbbox(0)
    , dt(0.016666)
    , targetFrameTime(0.016666) // 60fps -> 16.66ms
{
    gettimeofday(&tv, 0);
    gettimeofday(&tv_prev, 0);

    im.setMouseCenterCoords(_width/2, _height/2);
}

Dengine::~Dengine()
{
    if (_w != nullptr)
    {
        delete _w;
    }
    for (int i = 0; i < _models.size(); i++)
    {
        delete _models[i];
    }
}


int Dengine::init(int argc, char** argv)
{
    if (_initWindow()) return 1;
    if (_initGlew()) return 1;
    _initGLParams();

    return 0;
}
/*
int Dengine::addModel(float* positions, float* uvs, int vertex_count, int* indices, int index_count)
{
    //mdl0
    //_models.push_back(mdl0);
    return 0;
}
*/

void Dengine::addModel(const char* model, GLuint shaderID, GLuint texID)
{
    if (strcmp(model, "mdl_axes_orthnorm") == 0)
    {
        if (shaderID != 0)
        {
            Mdl_axes_orthnorm* axes = new Mdl_axes_orthnorm(shaderID);
            _models.push_back(axes);
        }
    }
    else if (strcmp(model, "mdl_example0") == 0)
    {
        if (shaderID != 0 && texID != 0)
        {
            Mdl_example0* mdl0 = new Mdl_example0(shaderID, texID);
            _models.push_back(mdl0);
        }
    }
    else if (strcmp(model, "mdl_example1") == 0)
    {
        if (shaderID != 0)
        {
            Mdl_example1* mdl1 = new Mdl_example1(shaderID);
            _models.push_back(mdl1);
        }
    }
    else if (strcmp(model, "mdl_example2") == 0)
    {
        if (shaderID != 0)
        {
            Mdl_example2* mdl2 = new Mdl_example2(shaderID);
            _models.push_back(mdl2);
        }
    }
}

void Dengine::addModel(GLuint shaderID, GLuint texID, const char* objModelPath)
{
    Mdl_pos_tex_obj* obj = new Mdl_pos_tex_obj(shaderID, texID, objModelPath);
    _models.push_back(obj);
}

void Dengine::addModel_normals(GLuint shaderID, GLuint texID, const char* objModelPath)
{
    Mdl_pos_tex_norm_obj* obj = new Mdl_pos_tex_norm_obj(shaderID, texID, objModelPath);
    _models.push_back(obj);
}

void Dengine::addModel(GLuint shaderID, const char* objModelPath)
{
    // class to be made
    //Mdl_pos_tex_obj* obj = new Mdl_pos_obj(shaderID, texID, objModelPath);
    //_models.push_back(obj);
}


void Dengine::registerBboxShader(GLuint shaderID)
{
    _shaderIDbbox = shaderID;
}


void Dengine::translateLastAddedModel(float x, float y, float z)
{
    _models.back()->translate(x, y, z);
}

int Dengine::_initWindow()
{

    sf::ContextSettings settings;
    settings.depthBits = 16;
    settings.stencilBits = 0;
    settings.antialiasingLevel = 2;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.attributeFlags = sf::ContextSettings::Attribute::Core;

    _w = new sf::Window(sf::VideoMode(_width, _height), "Does it Work!?", sf::Style::Titlebar, settings);
    
    sf::Vector2u sz = _w->getSize();
    float aspectRatio = float(sz.x) / float(sz.y);

    _cam.setPersp(aspectRatio, 90.0f * 3.141592653589793238462f / 180.0f, 0.01f, 100.0f);
    _cam.setPosition(0.0f, 1.0f, 5.0f);

    printWindowSettings(_w);

    if (!_w)
    {
        printf("Error initing window.\n");
        return -1;
    }

    _w->setActive(true);
    _w->setMouseCursorGrabbed(true);

        void registerBboxShader(GLuint shaderID);    void registerBboxShader(GLuint shaderID);    void registerBboxShader(GLuint shaderID);    void registerBboxShader(GLuint shaderID);
    _w->setMouseCursorVisible(false);
    _w->setVerticalSyncEnabled(true);

    return 0;
}

int Dengine::_initGlew()
{
    //glewExperimental = GL_TRUE; // apparently not needed
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        printf("Error initing glew: %s\n",  glewGetErrorString(glewError));
        return -1;
    }

    printf("Vendor: %s\nRenderer: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
    //printf("GLFW\t %s\n", glfwGetVersionString()); // glfwGetVersionString() undefined?
    printf("OpenGL\t %s\n", glGetString(GL_VERSION));
    printf("GLSL\t %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));


    /*
    printf("Extensions:\t ");
    
    // int howmanyextensions;
    // glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &howmanyextensions);
    // for (int i = 0; i < howmanyextensions; i++)
    // { printf("%s ", glGetStringi(GL_EXTENSIONS, i)); }

    int i = 0;
    const GLubyte* j = glGetStringi(GL_EXTENSIONS, i++);
    while (j != 0) // glGetStringi return 0 on error
    {
        printf("%s ", j);
        j = glGetStringi(GL_EXTENSIONS, i++);
    }
    printf("\nIn total %i extenstions\nThe following error is ok:\n", i);*/

    checkGLError(__FILE__, __LINE__);

    return 0;
}

void Dengine::_initGLParams(void)
{
    // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glEnable.xml

    // depth culling
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // face culling
    //glEnable(GL_CULL_FACE);
}
