/*  3D-Engine
*  Copyright (c) - 2016 - BWired95 - <ncourtig@gmail.com>
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include "Camera.h"

#define _USE_MATH_DEFINES 

#include <cmath>

// This is where camera defaults/standards fovs are set-up
// used to define the screen field of view (commonly 90-110° in 16:9 for fps games)
#define FOV_DEFAULT_H M_PI/2
#define FOV_DEFAULT_V M_PI/4

Camera::Camera() :
    m_pos_x(0), m_pos_y(0), m_pos_z(0), m_rad_v(0), m_rad_h(0),
    m_fov_v(float(FOV_DEFAULT_V)), m_fov_h(float(FOV_DEFAULT_H)) { }

Camera::Camera(double x, double y, double z) :
    m_pos_x(x), m_pos_y(y), m_pos_z(z), m_rad_v(0), m_rad_h(0),
    m_fov_v(float(FOV_DEFAULT_V)), m_fov_h(float(FOV_DEFAULT_H)) { }

Camera::Camera(double x, double y, double z, float v, float h) :
    m_pos_x(x), m_pos_y(y), m_pos_z(z), m_rad_v(v),  m_rad_h(h), 
    m_fov_v(float(FOV_DEFAULT_V)), m_fov_h(float(FOV_DEFAULT_H)) { }

Camera::Camera(Camera& c) :
    m_pos_x(c.GetCoordX()), m_pos_y(c.GetCoordY()), m_pos_z(c.GetCoordY()),
    m_rad_v(c.GetOrientationV()), m_rad_h(c.GetOrientationH()),
    m_fov_v(c.GetFOV_V()), m_fov_h(c.GetFOV_H()) { }

Camera::~Camera() { }

void Camera::DoTranslation(double x, double y, double z)
{
	m_pos_x += x; m_pos_y += y; m_pos_z += z;
}

void Camera::SetPosition(double x, double y, double z)
{
	m_pos_x = x; m_pos_y = y; m_pos_z = z;
}

void Camera::DoRotation(float v, float h)
{
	m_rad_v += v; m_rad_h += h;
}

void Camera::SetRotation(float v, float h)
{
	m_rad_v = v; m_rad_h = h;
}

///void SetFOV(float fov_v, float fov_h); //WARNING: The SDL screen should be updated properly

double Camera::CalculateCamToScreenDist(double Width)
{
    return double((Width / 2) / abs(tan(m_fov_h / 2)));
}

float Camera::GetStandardFOV_V()
{
    return float(FOV_DEFAULT_V);
}

float Camera::GetStandardFOV_H()
{
    return float(FOV_DEFAULT_H);
}
