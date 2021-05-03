#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GL/glew.h>

class InputManager
{
public:
    InputManager();
    ~InputManager();

    // housekeeping
    void update();
    void reset();

    // register SFML key input events
    void registerKeyPressSFML(unsigned char keycode);
    void registerKeyReleaseSFML(unsigned char keycode);

    // get input
    int isKeyDownSFML(unsigned char keycode);
    int wasKeyPressedSFML(unsigned char keycode);


    int isKeyDown(unsigned char ascii);

    // register mouse input events
    void registerMouseJustEntered(void);
    void registerMousePos(int x, int y);
    void registerMousePress(int button, int x, int y);
    void registerMouseRelease(int button, int x, int y);

    void setMouseCenterCoords(int x, int y);

    void getMouseMove(int* dx, int* dy);

    int wasMouseReleasedSFML(int button, int* x, int* y);
    int wasMousePressedSFML(int button, int* x, int* y);

    //void registerMouseBtnLeft(unsigned char pressed);
    //void registerMouseBtnRight(unsigned char pressed);

private:
    bool _keyDownArraySFML[256];
    bool _keyDownArrayPrevSFML[256];


    bool _mouseBtnDownArraySFML[5];
    bool _mouseBtnDownArrayPrevSFML[5];

    int _mouseLeftPressX;
    int _mouseLeftPressY;

    int _mouseLeftReleaseX;
    int _mouseLeftReleaseY;

    int _mouseX;
    int _mouseY;

    int _mouse_dx_move;
    int _mouse_dy_move;

    int _mouseX_center;
    int _mouseY_center;

    // when implementing mouse input and uncommenting the following four
    // variables, remember to uncoment them also in the initializer list and in
    // the update function.
    //char _mouseLeft;
    //char _mouseRight;
    //char _mouseLeftPrev;
    //char _mouseRightPrev;

    bool _justEntered;
};

#endif