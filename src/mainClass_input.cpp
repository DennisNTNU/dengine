#include "mainClass.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "util.hpp"


bool MainClass::_handleSFMLEvents()
{
    if (_hasWindowFocus)
    {
        // register mouse move independent from SFML events
        sf::Vector2i mousePos = sf::Mouse::getPosition();
        if (mousePos.x == _im.mouseX_center && mousePos.y == _im.mouseY_center)
        {
            // mouse did not move / mouse is at center
        }
        else
        {
            _im.registerMouseMove(mousePos.x, mousePos.y);
        }
        sf::Mouse::setPosition(sf::Vector2i(_width/2, _height/2), *_w);
        // gets global position but sets local position !?

        sf::Vector2i mousePosCenter = sf::Mouse::getPosition();
        _im.mouseX_center = mousePosCenter.x;
        _im.mouseY_center = mousePosCenter.y;
    }

    sf::Event e;
    while (_w->pollEvent(e))
    {

        switch (e.type)
        {
        case sf::Event::Closed:
            _w->close();
            return 1;
            break;
        case sf::Event::Resized:
        {
            glViewport(0, 0, e.size.width, e.size.height);
            float newAspectRatio = float(e.size.width) / float(e.size.height);

            _cam.setAspect(newAspectRatio);

            printf("Resize Event: (%i, %i)\n", e.size.width, e.size.height);
            break;
        }
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Key::Escape)
                return true;
            _im.registerKeyPress(e.key.code);
            // printf("Key Press Event: %i\n", e.key.code);
            break;
        case sf::Event::KeyReleased:
            _im.registerKeyRelease(e.key.code);
            // printf("Key Release Event\n");
            break;
        case sf::Event::MouseWheelScrolled:
            printf("Mouse Scroll Event\n");
            break;
        case sf::Event::MouseButtonPressed:
            printf("Mouse Button Press Event\n");
            break;
        case sf::Event::MouseButtonReleased:
            printf("Mouse Button Release Event\n");
            break;
        case sf::Event::MouseMoved:
            //printf("Mouse Move Event: (%i, %i)\n", e.mouseMove.x, e.mouseMove.y);
            break;
        case sf::Event::MouseEntered:
            _im.registerMouseJustEntered();
            //printf("Mouse Entered Window Event\n");
            break;
        case sf::Event::MouseLeft:
            printf("Mouse Left Window Event\n");
            break;
        case sf::Event::GainedFocus:
            printf("Gained Window Focus Event\n");
            _hasWindowFocus = true;
            _w->setMouseCursorGrabbed(true);
            _w->setMouseCursorVisible(false);
            break;
        case sf::Event::LostFocus:
            printf("Lost Window Focus Event\n");
            _hasWindowFocus = false;
            _im.resetAllKeys();
            _w->setMouseCursorGrabbed(false);
            _w->setMouseCursorVisible(true);
            break;


        case sf::Event::TextEntered:
            break;
        case sf::Event::MouseWheelMoved:
            break;
        case sf::Event::JoystickButtonPressed:
            break;
        case sf::Event::JoystickButtonReleased:
            break;
        case sf::Event::JoystickMoved:
            break;
        case sf::Event::JoystickConnected:
            break;
        case sf::Event::JoystickDisconnected:
            break;
        case sf::Event::TouchBegan:
            break;
        case sf::Event::TouchMoved:
            break;
        case sf::Event::TouchEnded:
            break;
        case sf::Event::SensorChanged:
            break;
        case sf::Event::Count:
            break;
        }
    }
    return false;
}

bool MainClass::_handleInput()
{
    _im.update();

    if (_handleSFMLEvents()) // true, if window should close
        return true;

    // e.g. update camera orientation and position
    int dx = 0, dy = 0;
    _im.getMouseMove(&dx, &dy);

    //_cam.pitching(-dy*glm::sqrt(glm::sqrt(dt))*0.02f);
    //_cam.yawing(-dx*glm::sqrt(glm::sqrt(dt))*0.02f);

    _cam.addAngVelLocal(-dy*0.01f, 0.0f, 0.0f);
    _cam.addAngVelLocal(0.0f, -dx*0.01f, 0.0f);


    float speed = 2.0f * dt;
    if (_im.isKeyDownSFML(sf::Keyboard::Key::LShift))
        speed *= 10.0f;

    if (_im.isKeyDownSFML(sf::Keyboard::Key::A))
        //_cam.changePositionLocal(-speed, 0.0f, 0.0f);
        _cam.addVelLocal(-speed, 0.0f, 0.0f);

    if (_im.isKeyDownSFML(sf::Keyboard::Key::D))
        //_cam.changePositionLocal(speed, 0.0f, 0.0f);
        _cam.addVelLocal(speed, 0.0f, 0.0f);

    if (_im.isKeyDownSFML(sf::Keyboard::Key::W))
        //_cam.changePositionLocal(0.0f, 0.0f, -speed);
        _cam.addVelLocal(0.0f, 0.0f, -speed);

    if (_im.isKeyDownSFML(sf::Keyboard::Key::S))
        //_cam.changePositionLocal(0.0f, 0.0f, speed);
        _cam.addVelLocal(0.0f, 0.0f, speed);


    if (_im.isKeyDownSFML(sf::Keyboard::Key::R))
        //_cam.changePositionLocal(0.0f, speed, 0.0f);
        _cam.addVelLocal(0.0f, speed, 0.0f);

    if (_im.isKeyDownSFML(sf::Keyboard::Key::F))
        //_cam.changePositionLocal(0.0f, -speed, 0.0f);
        _cam.addVelLocal(0.0f, -speed, 0.0f);


    if (_im.isKeyDownSFML(sf::Keyboard::Key::Num1))
        targetFrameTime = 0.016666;

    if (_im.isKeyDownSFML(sf::Keyboard::Key::Num2))
        targetFrameTime = 0.033333;

    if (_im.isKeyDownSFML(sf::Keyboard::Key::Num3))
        targetFrameTime = 0.066666;


/*
    float speed2 = 0.5f * dt;
    if (_im.isKeyDownSFML(sf::Keyboard::Key::U))
        _cam.changePositionLocal(speed2, 0.0f, 0.0f);

    if (_im.isKeyDownSFML(sf::Keyboard::Key::J))
        _cam.changePositionLocal(-speed2, 0.0f, 0.0f);

    if (_im.isKeyDownSFML(sf::Keyboard::Key::I))
        _cam.changePositionLocal(0.0f, 0.0f, speed2);

    if (_im.isKeyDownSFML(sf::Keyboard::Key::K))
        _cam.changePositionLocal(0.0f, 0.0f, -speed2);*/


    if (_im.isKeyDownSFML(sf::Keyboard::Key::Q))
    {
        //_cam.rolling(3.141592653589793238462f/4.0f*dt);
        _cam.addAngVelLocal(0.0f, 0.0f, 0.1f);
    }
    if (_im.isKeyDownSFML(sf::Keyboard::Key::E))
    {
        //_cam.rolling(-3.141592653589793238462f/4.0f*dt);
        _cam.addAngVelLocal(0.0f, 0.0f, -0.1f);
    }
    if (_im.isKeyPressedSFML(sf::Keyboard::Key::X))
        _cam.setOrientation(0.0f, 0.0f, 0.0f, 1.0f);


    return 0;
}