#include <stdio.h>

#include "util.h"
#include "mainClass.hpp"

int main(int argc, char** argv)
{
    MainClass mainclass;

    if (mainclass.init(argc, argv)) mainclass.loop(); // only start loop if init was successful

    printf("-----------------------------------------------\nGoing to exit\n");
    delay_ms(10);

    return 0;
}

