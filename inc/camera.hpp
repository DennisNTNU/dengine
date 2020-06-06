#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	Camera(float ar, float fovx, float n, float f);
	~Camera();

	// recalculating view and projection matrix, and integrating state
	void update(double dt);
	/*
	void translationSmoothness(float smoothness);
	float translationSmoothness();
	void rotationSmoothness(float smoothness);
	float rotationSmoothness();*/

	// changing perpective projection matrix
	void setPersp(float ar, float fovx, float n, float f);
	void setAspect(float ar);
	/*void setFOV(float fovx);*/

	// changing position
	void setPosition(float x, float y, float z);
	void changePositionLocal(float dx, float dy, float dz);
	void changePositionGlobal(float dx, float dy, float dz);

	void addVelGlobal(float vx, float vy, float vz);
	void addVelLocal(float vx, float vy, float vz);

	// changing orinetation
	void setOrientation(float ang, float nx, float ny, float nz);
	void setOrientationQuat(float w, float x, float y, float z);
	void changeOrientation(float ang, glm::vec3 const & axis);
	/*void changeOrientation(float ang, float nx, float ny, float nz);*/

	void pitching(float ang);
	void yawing(float ang);
	void rolling(float ang);

	void addAngVelGlobal(float wx, float wy, float wz);
	void addAngVelLocal(float wx, float wy, float wz);

	// matrix getters
	glm::mat4 getPerspViewMatrix();

	glm::mat4 getPerspMatrix();
	glm::mat4* getPerspMatrix_p();
	float* getPerspMatrix_pf();

	glm::mat4 getViewMatrix();
	glm::mat4* getViewMatrix_p();
	float* getViewMatrix_pf();


	glm::mat4* getGLMViewMatrix_p();

	glm::vec3 getPos() { return _p; }
	glm::vec3 getQuat() { return _q; }
	glm::vec3 getVel() { return _v; }
	glm::vec3 getAngVel() { return _w; }

	void print();

private:
	void _integrateVelocities(float dt);

	void _computeProjMatrix();
	void _computeViewMatrix();

	// prespective matrix parameters
	float _ar;
	float _fovx;
	float _near;
	float _far;

	// view matrix paramters
	glm::vec3 _p; // position
	glm::vec4 _q; // quaternion

	glm::vec3 _v; // velocity
	glm::vec3 _w; // angularVelocity

	float _velDecay;
	float _angVelDecay;

	glm::vec3 _f; // view/front dir
	glm::vec3 _u; // up dir
	glm::vec3 _s; // side dir


	glm::mat4 _persp;
	glm::mat4 _view;

	glm::mat4 _view_glm;

	int needsMatrixUpdate;
};

#endif