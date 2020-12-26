#include "dengine.hpp"

#include <unistd.h> // for usleep()
#include <sys/time.h> // for gettimeofday()

#include "util.hpp"



void Dengine::loop()
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

            if ( (i++ % 30) == 0)
            {
                printf("%s: Frame time: %f ms\n", __FUNCTION__, 1000.0*dt);
            }
        }
        else
        {
            // only need this usleep if vync is off
            //usleep(int((targetFrameTime - dt)*1000000));
        }
    }
}







void Dengine::_updateScene(double dt)
{
    _cam.update(dt);
}

void Dengine::_draw()
{
    _glClear(); checkGLError(__FILE__, __LINE__);

    for (int i = 0; i < _models.size(); i++)
    {
        _models[i]->draw(_cam.getViewMatrix_pf(), _cam.getPerspMatrix_pf(), NULL);
    }

    _w->display();
}


void Dengine::_glClear()
{
    glClearColor(0.2f, 0.4f, 0.8f, 1.0f);

    //glColorMask (GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    //glDepthMask (GL_TRUE);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
