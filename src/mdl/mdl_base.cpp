#include "mdl/mdl_base.hpp"

#include <stdio.h>

Mdl_base::Mdl_base()
	: _id(0)
{
	_model = glm::mat4(1.0f);
	_model[0][0] = 1.0f; // temporary change
	_model[1][1] = 1.0f; // temporary change
	_model[2][2] = 1.0f; // temporary change
	_model[3][3] = 1.0f; // temporary change

	_model[3][1] = 6.0f; // temporary change
}

Mdl_base::~Mdl_base()
{
	printf("%i: I'm dying\n", _id);
}
