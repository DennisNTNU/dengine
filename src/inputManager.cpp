#include "inputManager.hpp"

#include <string.h>
#include <SFML/Window.hpp>

InputManager::InputManager()
    : _mouseX(0)
    , _mouseY(0)
    , _mouse_dx_move(0)
    , _mouse_dy_move(0)
    , _mouseX_center(0)
    , _mouseY_center(0)
//    , _mouseLeft(0)
//    , _mouseRight(0)
//    , _mouseLeftPrev(0)
//    , _mouseRightPrev(0)
    , _justEntered(1)
{

    memset(_keyDownArraySFML, 0, 256);
    memset(_keyDownArrayPrevSFML, 0, 256);
    /*    SFML index -> ASCII code
    _SFMLtoASCIIMap[0] = 97;
    _SFMLtoASCIIMap[1] = 98;
    _SFMLtoASCIIMap[2] = 99;
    _SFMLtoASCIIMap[3] = 100;
    _SFMLtoASCIIMap[4] = 101;
    _SFMLtoASCIIMap[5] = 102;
    _SFMLtoASCIIMap[6] = 103;
    _SFMLtoASCIIMap[7] = 104;
    _SFMLtoASCIIMap[8] = 105;
    _SFMLtoASCIIMap[9] = 106;
    _SFMLtoASCIIMap[10] = 107;
    _SFMLtoASCIIMap[11] = 108;
    _SFMLtoASCIIMap[12] = 109;
    _SFMLtoASCIIMap[13] = 110;
    _SFMLtoASCIIMap[14] = 111;
    _SFMLtoASCIIMap[15] = 112;
    _SFMLtoASCIIMap[16] = 113;
    _SFMLtoASCIIMap[17] = 114;
    _SFMLtoASCIIMap[18] = 115;
    _SFMLtoASCIIMap[19] = 116;
    _SFMLtoASCIIMap[20] = 117;
    _SFMLtoASCIIMap[21] = 118;
    _SFMLtoASCIIMap[22] = 119;
    _SFMLtoASCIIMap[23] = 120;
    _SFMLtoASCIIMap[24] = 121;
    _SFMLtoASCIIMap[25] = 122;

    _SFMLtoASCIIMap[26] = 48;
    _SFMLtoASCIIMap[27] = 49;
    _SFMLtoASCIIMap[28] = 50;
    _SFMLtoASCIIMap[29] = 51;
    _SFMLtoASCIIMap[30] = 52;
    _SFMLtoASCIIMap[31] = 53;
    _SFMLtoASCIIMap[32] = 54;
    _SFMLtoASCIIMap[33] = 55;
    _SFMLtoASCIIMap[34] = 56;
    _SFMLtoASCIIMap[35] = 57;

    
    _SFMLtoASCIIMap[36] = 133;
    _SFMLtoASCIIMap[37] = 134;
    _SFMLtoASCIIMap[38] = ;
    _SFMLtoASCIIMap[39] = 97;
    _SFMLtoASCIIMap[40] = 97;
    _SFMLtoASCIIMap[3] = 97;
    */

}

InputManager::~InputManager()
{
    
}

void InputManager::update()
{
    memcpy(_keyDownArrayPrevSFML, _keyDownArraySFML, 256);

    memcpy(_mouseBtnDownArrayPrevSFML, _mouseBtnDownArraySFML, 5);

//    _mouseLeftPrev = _mouseLeft;
//    _mouseRightPrev = _mouseRight;
}


void InputManager::reset()
{
    memset(_keyDownArraySFML, 0, 256);
    memset(_keyDownArrayPrevSFML, 0, 256);
}

void InputManager::registerKeyPressSFML(unsigned char keycode)
{
    if (_keyDownArraySFML[keycode] == false)
    {
        _keyDownArraySFML[keycode] = true;
    }
}

void InputManager::registerKeyReleaseSFML(unsigned char keycode)
{
    if (_keyDownArraySFML[keycode] == true)
    {
        _keyDownArraySFML[keycode] = false;
    }
}

int InputManager::isKeyDownSFML(unsigned char keycode)
{
    return _keyDownArraySFML[keycode]; // sfml keycode always less than 256
}

int InputManager::wasKeyPressedSFML(unsigned char keycode)
{
    if (_keyDownArraySFML[keycode] && !_keyDownArrayPrevSFML[keycode])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int InputManager::isKeyDown(unsigned char asciiKey)
{
    if (97 <= asciiKey && 122 >= asciiKey)
    {
        return _keyDownArraySFML[asciiKey - 97];
    }
    if (48 <= asciiKey && 57 >= asciiKey)
    {
        return _keyDownArraySFML[asciiKey - 48 + 26];
    }
    return -1;
}

void InputManager::registerMouseJustEntered(void)
{
    _justEntered = true;
}

void InputManager::registerMousePos(int x, int y)
{
    if (_justEntered)
    {
        _mouseX = x;
        _mouseY = y;

        _justEntered = false;
    }
    else
    {
        if (x == _mouseX_center && y == _mouseY_center)
        {
            // mouse did not move: mouse is at center
        }
        else
        {
            _mouseX = x;
            _mouseY = y;

            _mouse_dx_move += x - _mouseX_center;
            _mouse_dy_move += y - _mouseY_center;
        }

        //printf("Mouse Move Event: (%i, %i), total: (%i, %i)\n", _mouseX, _mouseY, _mouse_dx_move, _mouse_dy_move);
    }
}


void InputManager::registerMousePress(int button, int x, int y)
{
    _mouseBtnDownArraySFML[button] = true;
    if (button == 0)
    {
        _mouseLeftPressX = x;
        _mouseLeftPressY = y;
    }
}

void InputManager::registerMouseRelease(int button, int x, int y)
{
    _mouseBtnDownArraySFML[button] = false;
    if (button == 0)
    {
        _mouseLeftReleaseX = x;
        _mouseLeftReleaseY = y;
    }
}


void InputManager::setMouseCenterCoords(int x, int y)
{
    _mouseX_center = x;
    _mouseY_center = y;
}

void InputManager::getMouseMove(int* dx, int* dy)
{
    *dx = _mouse_dx_move;
    *dy = _mouse_dy_move;
    _mouse_dx_move = 0;
    _mouse_dy_move = 0;
}

int InputManager::wasMouseReleasedSFML(int button, int* x, int* y)
{

    if (!_mouseBtnDownArraySFML[button] && _mouseBtnDownArrayPrevSFML[button])
    {
        if (x != NULL)
        {
            *x = _mouseLeftReleaseX;
        }

        if (y != NULL)
        {
            *y = _mouseLeftReleaseY;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}



int InputManager::wasMousePressedSFML(int button, int* x, int* y)
{
    if (_mouseBtnDownArraySFML[button] && !_mouseBtnDownArrayPrevSFML[button])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
