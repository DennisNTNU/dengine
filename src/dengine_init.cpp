#include "dengine.hpp"

#include <sys/time.h> // for gettimeofday()
#include <string.h> // for strcmp()

#include <glm/gtc/matrix_transform.hpp>

#include "mdl/l2/mdl_axes_orthnorm.hpp"
#include "mdl/l2/mdl_example0.hpp"
#include "mdl/l2/mdl_example1.hpp"
#include "mdl/l2/mdl_example2.hpp"
#include "mdl/l2/mdl_pos_tex_data.hpp"
#include "mdl/l2/mdl_pos_tex_obj.hpp"
#include "mdl/l2/mdl_pos_tex_norm_obj.hpp"
#include "util.hpp"

Dengine::Dengine()
    : _w(nullptr)
    , _initFlags(0)
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


int Dengine::init(int argc, char** argv, int flags)
{
    _initFlags = flags;
    if (_initWindow()) return 1;
    if (_initGlew()) return 1;
    _initGLParams();

    return 0;
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

    int sfml_window_style = sf::Style::Titlebar;
    if (_initFlags & DGN_RESIZABLE)
    {
        printf("Resizable window?\n");
        sfml_window_style = sf::Style::Default;
    }

    _w = new sf::Window(sf::VideoMode(_width, _height), "Does it Work!?", sfml_window_style, settings);
    
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

    if (_initFlags & DGN_NOT_GRAB_MOUSE)
    {
        _w->setMouseCursorGrabbed(false);
    }
    else
    {
        printf("Grabbing mouse\n");
        _w->setMouseCursorGrabbed(true);
    }

    if (_initFlags & DGN_NOT_HIDE_MOUSE)
    {
        _w->setMouseCursorVisible(true);
    }
    else
    {
        printf("Hiding mouse\n");
        _w->setMouseCursorVisible(false);
    }


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



void Dengine::addModel(int whichShadID, int whichTexID, float* positions, float* uvs,
                      int vertex_count, unsigned int* indices, int index_count)
{
    Mdl_pos_tex_data* mdl = new Mdl_pos_tex_data(sm.getProgramID(whichShadID), tm.getGLTextureID(whichTexID), positions, uvs, vertex_count, indices, index_count);
    _models.push_back(mdl);
}


void Dengine::addModel(const char* model_str, int whichShadID, int whichTexID)
{
    if (strcmp(model_str, "mdl_axes_orthnorm") == 0)
    {
        Mdl_axes_orthnorm* axes = new Mdl_axes_orthnorm(sm.getProgramID(whichShadID));
        _models.push_back(axes);
    }
    else if (strcmp(model_str, "mdl_example0") == 0)
    {
        Mdl_example0* mdl0 = new Mdl_example0(sm.getProgramID(whichShadID), tm.getGLTextureID(whichTexID));
        _models.push_back(mdl0);
    }
    else if (strcmp(model_str, "mdl_example1") == 0)
    {
        Mdl_example1* mdl1 = new Mdl_example1(sm.getProgramID(whichShadID));
        _models.push_back(mdl1);
    }
    else if (strcmp(model_str, "mdl_example2") == 0)
    {
        Mdl_example2* mdl2 = new Mdl_example2(sm.getProgramID(whichShadID));
        _models.push_back(mdl2);
    }
}

void Dengine::addModel(int whichShadID, int whichTexID, const char* objModelPath)
{
    Mdl_pos_tex_obj* obj = new Mdl_pos_tex_obj(sm.getProgramID(whichShadID), tm.getGLTextureID(whichTexID), objModelPath);
    _models.push_back(obj);
}

void Dengine::addModel_normals(int whichShadID, int whichTexID, const char* objModelPath)
{
    Mdl_pos_tex_norm_obj* obj = new Mdl_pos_tex_norm_obj(sm.getProgramID(whichShadID), tm.getGLTextureID(whichTexID), objModelPath);
    _models.push_back(obj);
}

void Dengine::addModel(int whichShadID, const char* objModelPath)
{
    // class to be made
    //Mdl_pos_tex_obj* obj = new Mdl_pos_obj(sm.getProgramID(whichShadID), tm.getGLTextureID(whichTexID), objModelPath);
    //_models.push_back(obj);
    printf("%s not implemented yet\n", __func__);
}


void Dengine::registerBboxShader(int whichShadID)
{
    _shaderIDbbox = sm.getProgramID(whichShadID);
}


void Dengine::translateLastAddedModel(float x, float y, float z)
{
    _models.back()->translate(x, y, z);
}

