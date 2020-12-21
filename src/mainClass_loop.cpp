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
                printf("%s: Frame time: %f ms\n", __FUNCTION__, 1000.0*dt);
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

    _mdl_->draw(_cam.getViewMatrix_pf(), _cam.getPerspMatrix_pf());
    _mdl1->draw(_cam.getViewMatrix_pf(), _cam.getPerspMatrix_pf());
    _mdl2->draw(_cam.getViewMatrix_pf(), _cam.getPerspMatrix_pf());

    _w->display();
}


void MainClass::_glClear()
{
    glClearColor(0.2f, 0.4f, 0.8f, 1.0f);

    //glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    //glDepthMask (GL_TRUE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
