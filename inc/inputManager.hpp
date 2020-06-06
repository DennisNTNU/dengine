#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GL/glew.h>

class InputManager
{
public:
    InputManager();
    ~InputManager();

    // get input
    int isKeyDown(unsigned char ascii);
    int isKeyDownSFML(unsigned char keycode);

    int isKeyPressedSFML(unsigned char keycode);

    void getMouseMove(int* dx, int* dy);

    //
    void update();

    // register input to input manager
    void registerKeyPress(unsigned char keycode);
    void registerKeyRelease(unsigned char keycode);

    void registerMouseJustEntered(void);

    void registerMouseBtnLeft(unsigned char pressed);
    void registerMouseBtnRight(unsigned char pressed);

    void registerMouseMove(int x, int y);

    void resetAllKeys();

    int mouseX_center;
    int mouseY_center;

private:
    bool _keyDownArray[256];
    bool _keyDownArrayPrev[256];

    char _mouseLeft;
    char _mouseRight;
    char _mouseLeftPrev;
    char _mouseRightPrev;


    int _mouseX;
    int _mouseY;

    int _mouse_dx_move;
    int _mouse_dy_move;


    bool _justEntered;
};

#endif