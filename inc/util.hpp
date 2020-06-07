#ifndef UTIL_H
#define UTIL_H

#include <GL/glew.h> // for glGetError(), gluErrorString()
#include <SFML/Window.hpp> // for sf::Window, sf::VideoMode()
#include <glm/glm.hpp>

void delay_ms(unsigned long ms);
void delay_us(unsigned long us);

void timediff(struct timeval* tmvl1, struct timeval* tmvl2, struct timeval* tmvl_diff);
double timediff_us(struct timeval* tmvl1, struct timeval* tmvl2);

void checkGLError(const char* file, int line);

sf::Window* setupWindow(void);
void printWindowSettings(sf::Window* window);
sf::Window* setupWindowAndGlew(void);

void printMat4(glm::mat4* mat);

#endif