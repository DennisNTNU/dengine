#include "mainClass.hpp"

#include <unistd.h> // for usleep()
#include <sys/time.h> // for gettimeofday()

#include "util.hpp"



void MainClass::loop()
{
    int i = 0;
    while (_w->isOpen())
    {
        gettimeofday(&tv, 0);
        dt = timediff_us(&tv, &tv_prev);

        if (dt >= targetFrameTime)
        {
            tv_prev = tv;

            if (_handleInput()) // true, if window should close
                break;

            _updateScene(dt);

            _draw();

            if ( (i++ % 20) == 0)
            {
                printf("%s: Frametime: %f\n------------------ %f\n", __FUNCTION__, dt, _cam.getPos()[2]);
            }
        }
        else
        {
            usleep(int((targetFrameTime - dt)*1000000));
        }
    }
}







void MainClass::_updateScene(double dt)
{
    _cam.update(dt);
}

void MainClass::_draw()
{
    _glClear(); checkGLError(__FILE__, __LINE__);

    _mdl.draw(_cam.getViewMatrix_pf(), _cam.getPerspMatrix_pf());

    _w->display();
}


void MainClass::_glClear()
{
    glClearColor(0.1f, 0.2f, 0.4f, 1.0f);

    //glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    //glDepthMask (GL_TRUE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
