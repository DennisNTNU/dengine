#pragma once

#include <glm/glm.hpp>

/**
 * Inheritence setup: Top level -> mid level -> bottom level
 * Top level defines ID and abstract draw and init functions.
 * mid level defines geometry layout: init function inits vertex array, vertex
 *                                    buffers and textures in a specific way
 *                                    with generic geometry
 * bottom level defines the exeact geometry.
 *
 * Example: top level is a drawable
 *          mid level defines voa with vbos for posisitons, UVs and a texture
 *          bottom level defines the exact geometry: i.e. data for the vbos
 *
 * Workflow: decide whether you need only e.g. vertex positions with constant
 * color, vertex position and vertex color, or vertex positions and vertex UVs,
 * then inherit from the corresponding mid level clas e.g. Mdl_pos or Mdl_pos_col,
 * and define the initData() function and call the partent constructor from the
 * child constructor and afterward call the initData() and _initVAO funciton.
 * See one of the examples.
 */

class Mdl_base
{
public:
	Mdl_base();
	~Mdl_base();

	int whoami() {return _id;}

	void translate(float x, float y, float z);

	virtual void draw(float* view, float* persp) = 0;
protected:
	int _id;
    glm::mat4 _model;
};



