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

#ifndef _ENGINE_H
#define _ENGINE_H

#include "../Drawing/Draws.h"
#include "../Miscellaneous/Structures.h"
#include "../Camera/Camera.h"

/* This option active log in console => WARNING : can slow the program around 1000% */
//#define LOG_TRACE

// * * * * * *
// This is where the magic oppers
// 1 Engine = 1 screen = 1 World = 1 Panel of Drawing tools
// Convert 3D point into 2D screen point if exist
// Project a segment defined by any 2 3D points (behind/or not) the screen
//      => Handled by "Intersection" and tests on "behind" boolean value
//
// OPTI:    - Black faces culling
//          - How to handle Polygon collisions ???
// * * * * * *

class Engine
{
public:
    Engine(Uint32 w = 640, Uint32 h = 480, Camera _cam = Camera());
    ~Engine();

    /* Use this before every 3D Drawing => Update engine parameters for calculations */
    void UpdateEngine();

    /* Use this for handle camera moves */
    Camera* GetCam() { return m_cam; }

    //disp cam location and orientation + fps
    void DispEngineInfo(Uint32 fps = -1);

    /* Misc 3D Drawing items */
    void DrawWorldLine(Point a, Point b, Uint32 color);
    void DrawXYZpoint(); //TODO
    void DrawPolynomZInFunctionOfXZ(double coef_x, float pow_x, double coef_y, float pow_y, double add_on_coord_x, double add_on_coord_y, double add_on_coord_z, double range_x, double range_y, float res, Uint32 color);
    void DrawHalfSphere(double _x, double _y, double _z, double radius, double range_x, double range_y, float res, Uint32 color);

    void DrawColouredCube(double x, double y, double z, double border);
    void DrawColouredCube(Point o, double border) { DrawColouredCube(o.x, o.y, o.z, border); }

private:

    void FindScreenPoint();         //UpdateEngine sub-method
    void FindPlanParameters();      //UpdateEngine sub-method

    /* if behind = true : the point is the point behind the screen, not the "intersection" */
    /* this function find the intersection between a world point, the cam and the screen plan */
    Intersection PointIntersectionFromWorld(Point gamma);
    /* this function find the intersection between two world point and the screen plan */
    Intersection PointIntersectionFromWorld(Point alpha, Point beta);

    /* finalize the segment render : don't erase a segment if one point is behind the screen => find new intersection between */
    /* the tho points of the segment and the screen. Final intersection may be this intersection and the point in front of screen */
    Intersection *FindFinalIntersection(Intersection a, Intersection b);

    /* convert a 3D point on world screen to 2D screen coord */
    pt WorldCoordToScreenCoord(Point point);

    Camera *m_cam;      //The Engine camera
    Draws *m_Dscreen;   //The render screen

    Point m_screen[4];          //screen extremums points in 3D world
    double m_parameters[4];     //screen cartesian parameters : ax+by+cz+d=0
};

#endif