#pragma once

#include <glm/glm.hpp>

/* Inheritence setup: Top level -> mid level -> bottom level
 * Top level defines ID and abstract draw and init functions.
 * mid level defines geometry layout: init function inits vertex array, vertex
 *                                    buffers and textures in a specific way
 *                                    with generic geometry
 * bottom level defines the exeact geometry.
 *
 * Example: top level is a drawable
 *          mid level defines voa with vbos for posisitons, UVs and a texture
 *          bottom level defines the exact geometry: i.e. data for the vbos
 */

class Mdl_base
{
public:
	Mdl_base();
	~Mdl_base();

	int whoami() {return _id;}

	virtual void draw(float* view, float* persp) = 0;
protected:
	int _id;
    glm::mat4 _model;
};



