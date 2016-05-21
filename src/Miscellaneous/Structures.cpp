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

#include "Structures.h"

#define _USE_MATH_DEFINES 

#include <cmath>

Point &Point::operator=(const Vector& vect)
{
    x = vect.x; y = vect.y; z = vect.z;
    return *this;
}

void Point::operator+=(const Vector& vect)
{
    x += vect.x; y += vect.y; z += vect.z;
}

Point operator+(Point const& a, Point const& b)
{
    return fill_coord_3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator+(Vector const& a, Vector const& b)
{
    return fill_vect_3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator-(Vector const& a, Vector const& b)
{
    return fill_vect_3D(a.x - b.x, a.y - b.y, a.z - b.z);
}

double ScalarProduct(Vector vector_a, Vector vector_b)
{
    return vector_a.x*vector_b.x + vector_a.y*vector_b.y + vector_a.z*vector_b.z;
}

double DistFrom2Points(Point a, Point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

Vector ConvertCylynderCoords(double r, double h, double v)
{
    double m = r*cos(v);
    return fill_vect_3D(m*cos(h), m*sin(h), r*sin(v));
}
