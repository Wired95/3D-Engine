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
    Camera* GetCam() { return cam; }

    /* Misc 3D Drawing items */
    void DrawWorldLine(Point a, Point b, Point Plan[4], double Parameters[4], Point cam, Draws screen, Uint32 color);
    void drawXYZpoint(); //TODO
    void DrawPolynomZInFunctionOfXZ(double coef_x, float pow_x, double coef_y, float pow_y, double add_on_coord_x, double add_on_coord_y, double add_on_coord_z, double range_x, double range_y, float res, Point Plan[4], double Parameters[4], Point cam, Draws screen, Uint32 color);
    void DrawHalfSphere(double _x, double _y, double _z, double radius, double range_x, double range_y, float res, Point Plan[4], double Parameters[4], Point cam, Draws screen, Uint32 color);

private:

    Point* FindScreenPoint(Camera cam, double W, double H); //UpdateEngine
    static double* init_planParameters(Point Screen[4]);    //UpdateEngine

    //if behind = true : the point is the point behind the screen, not the "intersection"
    Intersection PointIntersectionFromWorld(/* double Parameters[4], Point cam, */Point gamma);

    Intersection* FindFinalIntersection(Intersection a, Intersection b/*, double Parameters[4]*/);
    pt WorldCoordToScreenCoord(Point Plan[4], Point point);

    Camera *cam;
    Draws *screen;

    Point Screen[4];
    double Parameters[4];
};

#endif