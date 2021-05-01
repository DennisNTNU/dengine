#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "util.hpp"

Camera::Camera()
    : _ar(1.0f)
    , _fovx(3.141592653589793238462f / 2.0f)
    , _near(0.1f)
    , _far(1.0f)
    , _velDecay(10.0f)
    , _angVelDecay(10.0f)
    , needsMatrixUpdate(1)
{
    _computeProjMatrixGLM();
    _view = glm::mat4(1.0f);
    _view_glm = glm::mat4(1.0f);

    _p = glm::vec3(0.0f);
    _v = glm::vec3(0.0f);
    _q = glm::vec4(0.0f);
    _q.x = 1.0f;
    _w = glm::vec3(0.0f);

    _f = glm::vec3(0.0f, 0.0f, 1.0f);
    _u = glm::vec3(0.0f, 1.0f, 0.0f);
    _s = glm::vec3(1.0f, 0.0f, 0.0f);
}

/*
 * \param ar  Projection aspect ratio
 * \param fovx  Field of view
 * \param n  near clipping plane distance
 * \param f  far clipping plane distance
 */
Camera::Camera(float ar, float fovx, float n, float f)
    : needsMatrixUpdate(1)
{
    _ar = ar;
    _fovx = fovx;
    _near = n;
    _far = f;

    _computeProjMatrixGLM();
    _view = glm::mat4(1.0f);
    _view_glm = glm::mat4(1.0f);

    // camera state: position, velocity, quaternion, angular velocity
    _p = glm::vec3(0.0f);
    _v = glm::vec3(0.0f);
    _q = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
    _w = glm::vec3(0.0f);

    // camera view, up and side vectors
    _f = glm::vec3(0.0f, 0.0f, 1.0f);
    _u = glm::vec3(0.0f, 1.0f, 0.0f);
    _s = glm::vec3(1.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{
    //_proj
}

void Camera::update(double dt)
{
    _integrate(dt);

    if (needsMatrixUpdate)
    {
        _computeViewMatrix();
    }
}

void Camera::setPersp(float ar, float fovx, float n, float f)
{
    _ar = ar;
    _fovx = fovx;
    _near = n;
    _far = f;

    _computeProjMatrixGLM();
}

void Camera::setAspect(float ar)
{
    _ar = ar;
    float r = glm::tan(_fovx/2.0f);
    float t = r / ar;

    _proj[0][0] = 1.0f/r;
    _proj[1][1] = 1.0f/t;
}

void Camera::setPosition(float x, float y, float z)
{
    _p.x = x;
    _p.y = y;
    _p.z = z;

    needsMatrixUpdate = 1;
}

void Camera::changePositionLocal(float dx, float dy, float dz)
{
    _p += dx * _s;
    _p += dy * _u;
    _p += dz * _f;

    needsMatrixUpdate = 1;
}

void Camera::changePositionGlobal(float dx, float dy, float dz)
{
    _p.x += dx;
    _p.y += dy;
    _p.z += dz;

    needsMatrixUpdate = 1;
}

void Camera::addVelGlobal(float vx, float vy, float vz)
{
    _v.x += vx;
    _v.y += vy;
    _v.z += vz;
}

void Camera::addVelLocal(float vx, float vy, float vz)
{
    _v += vx*_s + vy*_u + vz*_f;
}
/*
void Camera::setOrientation(float ang, glm::vec3 const & axis)
{
    glm::vec3 axis_n = normalize(axis);
    float sa2 = glm::sin(ang/2.0f);
    _q.x = glm::cos(ang/2.0f);
    _q.y = sa2 * axis_n.x;
    _q.z = sa2 * axis_n.y;
    _q.w = sa2 * axis_n.z;

    needsMatrixUpdate = 1;
}*/

void Camera::setOrientation(float ang, float nx, float ny, float nz)
{
    float axis_len = glm::sqrt(nx*nx + ny*ny + nz*nz);
    float sa2 = glm::sin(ang/2.0f);
    _q.x = glm::cos(ang/2.0f);
    _q.y = sa2 * nx / axis_len;
    _q.z = sa2 * ny / axis_len;
    _q.w = sa2 * nz / axis_len;

    needsMatrixUpdate = 1;
}

void Camera::setOrientationQuat(float w, float x, float y, float z)
{
    _q.x = w;
    _q.y = x;
    _q.z = y;
    _q.w = z;

    needsMatrixUpdate = 1;
}

void Camera::changeOrientationGlobal(float ang, glm::vec3 const & axis)
{
    glm::vec3 axis_n = normalize(axis);
    float sa2 = glm::sin(ang/2.0f);
    float dqw = glm::cos(ang/2.0f);
    float dqx = sa2 * axis_n.x;
    float dqy = sa2 * axis_n.y;
    float dqz = sa2 * axis_n.z;
/*
    float qw = dqw * _q.x - dqx * _q.y - dqy * _q.z - dqz * _q.w;
    float qx = dqw * _q.y + dqx * _q.x + dqy * _q.w - dqz * _q.z;
    float qy = dqw * _q.z - dqx * _q.w + dqy * _q.x + dqz * _q.y;
    float qz = dqw * _q.w + dqx * _q.z - dqy * _q.y + dqz * _q.x;*/

    float qw = dqw * _q.x - dqx * _q.y - dqy * _q.z - dqz * _q.w;
    float qx = dqx * _q.x + dqw * _q.y - dqz * _q.z + dqy * _q.w;
    float qy = dqy * _q.x + dqz * _q.y + dqw * _q.z - dqx * _q.w;
    float qz = dqz * _q.x - dqy * _q.y + dqx * _q.z + dqw * _q.w;

    //printf("dq: (%f, %f, %f, %f)\n", qw_c, qx_c, qy_c, qz_c);

    _q.x = qw;
    _q.y = qx;
    _q.z = qy;
    _q.w = qz;

    needsMatrixUpdate = 1;
}

void Camera::pitching(float ang)
{
    changeOrientationGlobal(ang, _s);
}

void Camera::yawing(float ang)
{
    changeOrientationGlobal(ang, _u);
}

void Camera::rolling(float ang)
{
    changeOrientationGlobal(ang, _f);
}


void Camera::addAngVelGlobal(float wx, float wy, float wz)
{
    _w.x += wx;
    _w.y += wy;
    _w.z += wz;
}

void Camera::addAngVelLocal(float wx, float wy, float wz)
{
    _w += wx*_s + wy*_u + wz*_f;
}

void Camera::_integrate(float dt)
{
    float velMag = glm::sqrt(_v.x*_v.x + _v.y*_v.y + _v.z*_v.z);
    float angVelMag = glm::sqrt(_w.x*_w.x + _w.y*_w.y + _w.z*_w.z);

    if (velMag > 0.001f)
    {
        _p += dt * _v;
        _v = glm::exp(-_velDecay*dt) * _v;

        needsMatrixUpdate = 1;
    }

    if (angVelMag > 0.001f)
    {
        float qw = - _q.y*_w.x - _q.z*_w.y - _q.w*_w.z;
        float qx = + _q.x*_w.x + _q.w*_w.y - _q.z*_w.z;
        float qy = - _q.w*_w.x + _q.x*_w.y + _q.y*_w.z;
        float qz = + _q.z*_w.x - _q.y*_w.y + _q.x*_w.z;

        _q.x += dt*qw/2.0f;
        _q.y += dt*qx/2.0f;
        _q.z += dt*qy/2.0f;
        _q.w += dt*qz/2.0f;

        _q = glm::normalize(_q);
        _w = glm::exp(-_angVelDecay*dt) * _w;
        needsMatrixUpdate = 1;
    }
}

void Camera::_computeProjMatrixGLM()
{
    float r = glm::tan(_fovx/2.0f);
    float t = r / _ar;
    float fovy = 2.0f * glm::atan(t);

    _proj = glm::perspective(fovy, _ar, _near, _far);
}

void Camera::_computeProjMatrix()
{
    // should be identical with glm::projection, except that fovx is given instead of fovy

    float r = glm::tan(_fovx/2.0f);
    float t = r / _ar;
    // float fovy = 2.0f * glm::atan(t);

    float a = -(_far+_near)/(_far-_near);
    float b = -2.0f*_far*_near/(_far-_near);

    _proj[0][0] = 1.0f/r; _proj[1][0] =   0.0f; _proj[2][0] =  0.0f; _proj[3][0] = 0.0f;
    _proj[0][1] =   0.0f; _proj[1][1] = 1.0f/t; _proj[2][1] =  0.0f; _proj[3][1] = 0.0f;
    _proj[0][2] =   0.0f; _proj[1][2] =   0.0f; _proj[2][2] =     a; _proj[3][2] =    b;
    _proj[0][3] =   0.0f; _proj[1][3] =   0.0f; _proj[2][3] = -1.0f; _proj[3][3] = 0.0f;
}


void Camera::_computeViewMatrix()
{
    _view_glm = glm::lookAt(_p, _p - _f, _u);

    // _q.x == scalar part
    // _q.yzw == vector part
    // _q.x == s
    // _q.y == a; _q.z == b; _q.w == c;

    float aa = _q.y*_q.y;
    float bb = _q.z*_q.z;
    float cc = _q.w*_q.w;

    float ab = _q.y*_q.z;
    float ac = _q.y*_q.w;
    float bc = _q.z*_q.w;

    float sa = _q.x*_q.y;
    float sb = _q.x*_q.z;
    float sc = _q.x*_q.w;

    _view[0][0] = 1.0f - 2.0f*(bb + cc);
    _view[0][1] = 2.0f*(ab - sc);
    _view[0][2] = 2.0f*(ac + sb);
        _view[0][3] = 0.0;
    _view[1][0] = 2.0f*(ab + sc);
    _view[1][1] = 1.0f - 2.0f*(aa + cc);
    _view[1][2] = 2.0f*(bc - sa);
        _view[1][3] = 0.0;
    _view[2][0] = 2.0f*(ac - sb);
    _view[2][1] = 2.0f*(bc + sa);
    _view[2][2] = 1.0f - 2.0f*(aa + bb);
        _view[2][3] = 0.0;
    _view[3][0] = 0.0;
    _view[3][1] = 0.0;
    _view[3][2] = 0.0;
    _view[3][3] = 1.0;


    glm::vec4 pos_homogeneous = glm::vec4(_p.x, _p.y, _p.z, 0.0f);

    pos_homogeneous = - _view * pos_homogeneous;

    _view[3][0] = pos_homogeneous.x;
    _view[3][1] = pos_homogeneous.y;
    _view[3][2] = pos_homogeneous.z;

    // s points to the right, local x axis
    // u points up, local y axis
    // f points backward, local z axis
    // V = [sx sy sz -dot(s,p);
    //      ux uy uz -dot(u,p);
    //      fx fy fz -dot(f,p);
    //       0  0  0         1 ]

    _s.x = _view[0][0];
    _s.y = _view[1][0];
    _s.z = _view[2][0];
    _u.x = _view[0][1];
    _u.y = _view[1][1];
    _u.z = _view[2][1];
    _f.x = _view[0][2];
    _f.y = _view[1][2];
    _f.z = _view[2][2];
}







void Camera::print()
{

    // position
    //printf("(%f, %f, %f)\n", _p.x, _p.y, _p.z);

    // quaternion
    //printf("(%f, %f, %f, %f)\n", _q.x, _q.y, _q.z, _q.w);

    // glm view matrix
    //printMat4(&_view_glm);
    //printf("\n");

    // custom view matrix
    //printMat4(&_view);
}



















