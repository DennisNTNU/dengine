#include "dengine.hpp"

#include <sys/time.h> // for gettimeofday()
#include <string.h> // for strcmp()

#include <glm/gtc/matrix_transform.hpp>

#include "mdl/l1/mdl_pos_tex.hpp"
#include "mdl/l2/mdl_axes_orthnorm.hpp"
#include "mdl/l2/mdl_example0.hpp"
#include "mdl/l2/mdl_example1.hpp"
#include "mdl/l2/mdl_example2.hpp"
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
    settings.antialiasingLevel = 0;
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

    if (!_w)
    {
        printf("Error initing window.\n");
        return -1;
    }

    printWindowSettings(_w);

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


// textured mesh (triangles)
int Dengine::addModel(int smShaderID, int tmTextureID, float* positions, float* uvs,
                      int vertex_count, unsigned int* indices, int index_count)
{
    Mdl_pos_tex* mdl = new Mdl_pos_tex(sm.getProgramID(smShaderID), tm.getGLTextureID(tmTextureID), GL_TRIANGLES, positions, uvs, vertex_count, indices, index_count);
    _models.push_back(mdl);
    return _models.size()-1;
}


// line strip
int Dengine::addModel_linestrip(int smShaderID, float* positions, float* colors, int vertex_count, unsigned int* indices, int index_count)
{
    Mdl_pos_col* mdl = new Mdl_pos_col(sm.getProgramID(smShaderID), GL_LINE_STRIP, positions, colors, vertex_count, indices, index_count);
    _models.push_back(mdl);
    return _models.size()-1;
}


int Dengine::addModel(const char* model_str, int smShaderID, int tmTextureID)
{
    if (strcmp(model_str, "mdl_axes_orthnorm") == 0)
    {
        Mdl_axes_orthnorm* axes = new Mdl_axes_orthnorm(sm.getProgramID(smShaderID));
        _models.push_back(axes);
    }
    else if (strcmp(model_str, "mdl_example0") == 0)
    {
        Mdl_example0* mdl0 = new Mdl_example0(sm.getProgramID(smShaderID), tm.getGLTextureID(tmTextureID));
        _models.push_back(mdl0);
    }
    else if (strcmp(model_str, "mdl_example1") == 0)
    {
        Mdl_example1* mdl1 = new Mdl_example1(sm.getProgramID(smShaderID));
        _models.push_back(mdl1);
    }
    else if (strcmp(model_str, "mdl_example2") == 0)
    {
        Mdl_example2* mdl2 = new Mdl_example2(sm.getProgramID(smShaderID));
        _models.push_back(mdl2);
    }
    return _models.size()-1;
}

int Dengine::addModel(int smShaderID, int tmTextureID, const char* objModelPath)
{
    Mdl_pos_tex_obj* obj = new Mdl_pos_tex_obj(sm.getProgramID(smShaderID), tm.getGLTextureID(tmTextureID), objModelPath);
    _models.push_back(obj);
    return _models.size()-1;
}

int Dengine::addModel_normals(int smShaderID, int tmTextureID, const char* objModelPath)
{
    Mdl_pos_tex_norm_obj* obj = new Mdl_pos_tex_norm_obj(sm.getProgramID(smShaderID), tm.getGLTextureID(tmTextureID), objModelPath);
    _models.push_back(obj);
    return _models.size()-1;
}

int Dengine::addModel(int smShaderID, const char* objModelPath)
{
    // obj without tex or normals, just positions
    // class to be made
    //Mdl_pos_tex_obj* obj = new Mdl_pos_obj(sm.getProgramID(smShaderID), tm.getGLTextureID(tmTextureID), objModelPath);
    //_models.push_back(obj);
    printf("%s not implemented yet\n", __func__);
    return _models.size()-1;
}



void Dengine::translateLastAddedModel(float x, float y, float z)
{
    _models.back()->translate(x, y, z);
}

void Dengine::translateModel(int index, float x, float y, float z)
{
    if (index > 0 && index < _models.size())
    {
        _models[index]->translate(x, y, z);
    }
}

void Dengine::setPositionModel(int index, float x, float y, float z)
{
    if (index > 0 && index < _models.size())
    {
        _models[index]->setPosition(x, y, z);
    }
}

void Dengine::changeTextureModel(int index, int tmTextureID)
{
    if (index > 0 && index < _models.size())
    {
        _models[index]->changeTexture(tm.getGLTextureID(tmTextureID));
    }
}

void Dengine::registerBboxShader(int smShaderID)
{
    _shaderIDbbox = sm.getProgramID(smShaderID);
}


void Dengine::removeLastModel()
{
    _models.pop_back();
}

void Dengine::removeModelByIndex(int index)
{
    delete _models[index];
    _models.erase(_models.begin()+index);
}

