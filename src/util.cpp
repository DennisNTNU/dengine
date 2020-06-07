#include <time.h> // for nanosleep()
#include <sys/time.h> // for struct timeval

#include "util.hpp"

void delay_ms(unsigned long ms)
{
        struct timespec ts;
        ts.tv_sec = ms / 1000;
        ts.tv_nsec = (ms % 1000) * 1000000;
        nanosleep(&ts, 0);
}

void delay_us(unsigned long  us)
{
        struct timespec ts;
        ts.tv_sec = us / 1000000;
        ts.tv_nsec = (us % 1000000) * 1000;
        nanosleep(&ts, 0);
}

void timediff(struct timeval* tmvl1, struct timeval* tmvl2, struct timeval* tmvl_diff)
{
    tmvl_diff->tv_sec = tmvl1->tv_sec - tmvl2->tv_sec;
    tmvl_diff->tv_usec = tmvl1->tv_usec - tmvl2->tv_usec;

    if (tmvl_diff->tv_usec < 0)
    {
    tmvl_diff->tv_usec = tmvl_diff->tv_usec + 1000000;
    tmvl_diff->tv_sec--;
    }
}

double timediff_us(struct timeval* tmvl1, struct timeval* tmvl2)
{
    struct timeval tmvl_diff;
    tmvl_diff.tv_sec = tmvl1->tv_sec - tmvl2->tv_sec;
    tmvl_diff.tv_usec = tmvl1->tv_usec - tmvl2->tv_usec;

    if (tmvl_diff.tv_usec < 0)
    {
    tmvl_diff.tv_usec = tmvl_diff.tv_usec + 1000000;
    tmvl_diff.tv_sec--;
    }

    return double(tmvl_diff.tv_sec) + double(tmvl_diff.tv_usec)/1000000.0;
}



void checkGLError(const char* file, int line)
{
    const GLubyte *errString;
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
    errString = gluErrorString(err);
    printf(" There was a gl error %i, in file %s, line %d:\n    %s\n", err, file, line, errString);
    }
}
/*
sf::Window* setupWindow(void)
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 0;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 6;

    sf::Window* window = new sf::Window(sf::VideoMode(480, 360), "Does it Work!?", sf::Style::Default, settings);

    printWindowSettings(window);

    return window;
}


sf::Window* setupWindowAndGlew(void)
{
    sf::Window* window = setupWindow();

    if (!window)
    {
    printf("Error initing window: %lx\n", (unsigned long)window);
    return 0;
    }

    window->setActive(true);
    
    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
    printf("Error initing glew\n");
    return 0;
    }

    return window;
}*/

void printWindowSettings(sf::Window* window)
{
    if (window != 0)
    {
        sf::ContextSettings settings2 = window->getSettings();

        printf("0x%lx\n", (unsigned long)window);
        printf("depth bits: %i\n", settings2.depthBits);
        printf("stencilBits: %i\n", settings2.stencilBits);
        printf("antialiasingLevel: %i\n", settings2.antialiasingLevel);
        printf("major: %i\n", settings2.majorVersion);
        printf("minor: %i\n", settings2.minorVersion);
    }
    else
    {
        printf("Could now print window settings. Window is null\n");
    }
}

void printMat4(glm::mat4* mat)
{
    printf("%.5f %.5f %.5f %.5f\n%.5f %.5f %.5f %.5f\n%.5f %.5f %.5f %.5f\n%.5f %.5f %.5f %.5f\n", 
    (*mat)[0][0], (*mat)[1][0], (*mat)[2][0], (*mat)[3][0], 
    (*mat)[0][1], (*mat)[1][1], (*mat)[2][1], (*mat)[3][1], 
    (*mat)[0][2], (*mat)[1][2], (*mat)[2][2], (*mat)[3][2], 
    (*mat)[0][3], (*mat)[1][3], (*mat)[2][3], (*mat)[3][3] );
}

/*
    # include <sys/time.h>
    struct timeval tv;
    gettimeofday(&tv);
    tv.tv_sec //seconds
    tv.tv_usec //seconds

    #include <unistd.h>
    unsigned int usecs;
    usleep(usecs);
*/