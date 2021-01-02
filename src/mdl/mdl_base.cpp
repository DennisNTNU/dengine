#include "mdl/mdl_base.hpp"

#include <stdio.h>

Mdl_base::Mdl_base()
    : _id(0)
{

    _model = glm::mat4(1.0f);

    b_box.xmin = 0.0;
    b_box.xmax = 0.0;
    b_box.ymin = 0.0;
    b_box.ymax = 0.0;
    b_box.zmin = 0.0;
    b_box.zmax = 0.0;
}

Mdl_base::~Mdl_base()
{
}


void Mdl_base::translate(float x, float y, float z)
{
    _model[3][0] += x;
    _model[3][1] += y;
    _model[3][2] += z;
}

void Mdl_base::compute_bounding_box(float* vertexPositions, int vertexCount)
{
    b_box.xmin = FLT_MAX;
    b_box.xmax = -FLT_MAX;
    b_box.ymin = FLT_MAX;
    b_box.ymax = -FLT_MAX;
    b_box.zmin = FLT_MAX;
    b_box.zmax = -FLT_MAX;
    for (int i = 0; i < vertexCount; i++)
    {
        int ix = 3*i;
        int iy = 3*i + 1;
        int iz = 3*i + 2;

        if (vertexPositions[ix] > b_box.xmax)
        {
            b_box.xmax = vertexPositions[ix];
        }

        if (vertexPositions[iy] > b_box.ymax)
        {
            b_box.ymax = vertexPositions[iy];
        }

        if (vertexPositions[iz] > b_box.zmax)
        {
            b_box.zmax = vertexPositions[iz];
        }


        if (vertexPositions[ix] < b_box.xmin)
        {
            b_box.xmin = vertexPositions[ix];
        }

        if (vertexPositions[iy] < b_box.ymin)
        {
            b_box.ymin = vertexPositions[iy];
        }

        if (vertexPositions[iz] < b_box.zmin)
        {
            b_box.zmin = vertexPositions[iz];
        }
    }

    printf("%s\n", _name);
    printf("Bounding box: x %f %f \n", b_box.xmin, b_box.xmax);
    printf("              y %f %f \n", b_box.ymin, b_box.ymax);
    printf("              z %f %f \n", b_box.zmin, b_box.zmax);
}
