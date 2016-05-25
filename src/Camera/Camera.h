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

#ifndef _CAMERA_H
#define _CAMERA_H

// * * * * * *
// Here is the Camera
// This class should work with Engine/main
// Camera is location in World
// * * * * * *

class Camera
{
    public:
        Camera();
        Camera(double x, double y, double z);
        Camera(double x, double y, double z, float v, float h);
        Camera(Camera&);
        ~Camera();

        void DoTranslation(double x, double y, double z);
		void SetPosition(double x = 0, double y = 0, double z = 0);
        void DoRotation(float v, float h);
		void SetRotation(float v = 0, float h = 0);
        ///void SetFOV(float fov_v, float fov_h); //WARNING: The SDL screen should be updated properly

        double GetCoordX() { return m_pos_x; }
        double GetCoordY() { return m_pos_y; }
        double GetCoordZ() { return m_pos_z; }

        double GetOrientationV() { return m_rad_v; }
        double GetOrientationH() { return m_rad_h; }

        float  GetFOV_V() { return m_fov_v; }
        float  GetFOV_H() { return m_fov_h; }

        double CalculateCamToScreenDist(double Width);

        static float GetStandardFOV_V();
        static float GetStandardFOV_H();

    private:
        double m_pos_x, m_pos_y, m_pos_z;
        double m_rad_v, m_rad_h;     //should be in radian, (0, 0) means focus on Ox axis
        float m_fov_v, m_fov_h;                  //for zoom(high values), dezoom (low values)
};

#endif