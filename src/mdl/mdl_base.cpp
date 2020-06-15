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
