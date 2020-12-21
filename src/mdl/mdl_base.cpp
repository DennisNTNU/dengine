#include "mdl/mdl_base.hpp"

#include <stdio.h>

Mdl_base::Mdl_base()
    : _id(0)
{
    _model = glm::mat4(1.0f);
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