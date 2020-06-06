#include "mainClass.hpp"

#include <sys/time.h> // for gettimeofday()

#include <glm/gtc/matrix_transform.hpp>

#include "util.hpp"

MainClass::MainClass()
    : _w(nullptr)
    , _hasWindowFocus(true)
    , _width(1280)
    , _height(720)
    , dt(0.1)
    , targetFrameTime(0.016666) // 60fps -> 16.66ms
{
    gettimeofday(&tv, 0);
    gettimeofday(&tv_prev, 0);
}

MainClass::~MainClass()
{
    if (_w != nullptr)
    {
        delete _w;
    }
}


int MainClass::init(int argc, char** argv)
{
    if (_initWindow()) return 0;
    if (_initGlew()) return 0;
    _initGLParams();
    _initShaders();

    _mdl.init(_sm.getProgramID(1), 0);

    return 1;
}










int MainClass::_initWindow()
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
    _cam.setPosition(4.5f, 1.0f, 1.0f);

    printWindowSettings(_w);

    //w = setupWindow();

    if (!_w)
    {
        printf("Error initing window: %lx\n", (unsigned long)_w);
        return -1;
    }

    _w->setActive(true);
    _w->setMouseCursorGrabbed(true);
    _w->setMouseCursorVisible(false);
    _w->setVerticalSyncEnabled(true);

    return 0;
}

int MainClass::_initGlew()
{
    //glewExperimental = GL_TRUE; // apparently not needed
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        printf("Error initing glew: %s\n",  glewGetErrorString(glewError));
        return -1;
    }

    printf("%s: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
    //printf("GLFW\t %s\n", glfwGetVersionString());
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

void MainClass::_initGLParams(void)
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

void MainClass::_initShaders()
{
    printf("Initing Shaders\n");
    _sm.makeProgram("src/shaders/vertexShader.glsl", "src/shaders/fragmentShader.glsl", 0);
    _sm.makeProgram("src/shaders/textureShader_vert.glsl", "src/shaders/textureShader_frag.glsl", 1);
}
