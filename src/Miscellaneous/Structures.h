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

#ifndef _STRUCTURES_H
#define _STRUCTURES_H

#include <vector>

// * * * * * *
// Here is defined some useful math structures like points, vectors... And operators
// * * * * * *

/* * * * * 2D point * * * * */
struct pt {
    int x, y;
};

inline pt fill_coord_2D(int x, int y) { pt a; a.x = x, a.y = y; return a; }

/* * * * * 3D Vector * * * * */
struct Vector { 
    double x, y, z; 
    Vector::Vector(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}
};

inline Vector fill_vect_3D(double x, double y, double z) { Vector a; a.x = x; a.y = y; a.z = z; return a; }

Vector operator+(Vector const& a, Vector const& b);
Vector operator-(Vector const& a, Vector const& b);

Vector ConvertCylynderCoords(double r, double h, double v);

/* * * * * 3D point * * * * */
struct Point {
    double x, y, z;
    Point &operator=(const Vector &);
    void operator+=(Vector const& a);
    Point::Point(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}
};

inline Point fill_coord_3D(double x, double y, double z) { Point a; a.x = x; a.y = y; a.z = z; return a; }

Point operator+(Point const& a, Point const& b);

double DistFrom2Points(Point a, Point b);

/* * * * * 3D Intersection * * * * */
// Intersection is the intersection point between a "segment" defined by cam and a 3D point, and a our screen
// If behind is true, it means that the intersection cannot be found because 3D point is behind the screen
//     |=> As a result, point is filled with the original point, NOT the intersection
struct Intersection
{
    Point point; bool behind;
    Intersection::Intersection() : point(fill_coord_3D(0, 0, 0)), behind(false) {}
    Intersection::Intersection(Point _pt, bool _behind) : point(_pt), behind(_behind) {}
    Intersection::Intersection(double x, double y, double z, bool _behind) : point(fill_coord_3D(x, y, z)), behind(_behind) {}
};

struct Polygon { std::vector<Point> coords; bool filled = true; };  //base closed surfaces, should be 

/* * * * * Others Functions * * * * */
inline int min(int i, int j) { return i < j ? i : j; }
inline int max(int i, int j) { return i > j ? i : j; }
inline int min(int i, int j, int k) { return min(i, min(j, k)); }
inline int max(int i, int j, int k) { return max(i, max(j, k)); }

#endif
