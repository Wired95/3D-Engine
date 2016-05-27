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

#include "Engine.h"

#ifdef WIN32
#define sprintf sprintf_s
#endif

Engine::Engine(Uint32 w, Uint32 h, Camera _cam)
{
    m_cam = new Camera(_cam);
    m_Dscreen = new Draws(w, h);
}

Engine::~Engine()
{
    delete m_cam;
    delete m_Dscreen;
}

void Engine::UpdateEngine()
{
    m_Dscreen->fill_screen(black);
    FindScreenPoint();
    FindPlanParameters();
}

void Engine::DispEngineInfo(Uint32 fps)
{
    char info[500];
    if (fps == -1)
        sprintf(info, "Cam Coord(X:%lf Y:%lf Z:%lf Ov:%lf Oh:%lf)", m_cam->GetCoordX(), m_cam->GetCoordY(), m_cam->GetCoordZ(), (m_cam->GetOrientationV() * 360) / (2 * M_PI), (m_cam->GetOrientationH() * 360) / (2 * M_PI));
    else sprintf(info, "Cam Coord(X:%lf Y:%lf Z:%lf Ov:%lf Oh:%lf) FPS: %d", m_cam->GetCoordX(), m_cam->GetCoordY(), m_cam->GetCoordZ(), (m_cam->GetOrientationV() * 360) / (2 * M_PI), (m_cam->GetOrientationH() * 360) / (2 * M_PI), fps);

#ifdef LOG_TRACE
    printf("FPS : %d\n", fps);
#endif

    m_Dscreen->disp_txt(info, 12, fill_coord_2D(2, 15), white, FONT_VERDANA, false);
}

/* * * * * * Engine Core * * * * * */

void Engine::FindScreenPoint()
{
    Point delta(m_cam->GetCoordX(), m_cam->GetCoordY(), m_cam->GetCoordZ());
    delta += ConvertCylynderCoords(m_cam->CalculateCamToScreenDist(m_Dscreen->GetWidth()), 
        m_cam->GetOrientationH(), m_cam->GetOrientationV());

    Vector u, v;

    u = ConvertCylynderCoords(m_Dscreen->GetHeight() / 2, m_cam->GetOrientationH(), m_cam->GetOrientationV() + M_PI / 2);
    v = ConvertCylynderCoords(m_Dscreen->GetWidth() / 2, m_cam->GetOrientationH() + M_PI / 2, m_cam->GetOrientationV());

#ifdef LOG_TRACE
    printf("Dist cam-screen : %lf\n", m_cam->CalculateCamToScreenDist(m_Dscreen->GetWidth()));
    printf("Vector ScreenPoint delta : (%lf, %lf, %lf)\n", delta.x, delta.y, delta.z);
    printf("Vector ScreenPoint %c : (%lf, %lf, %lf)\n", 'u', u.x, u.y, u.z);
    printf("Vector ScreenPoint %c : (%lf, %lf, %lf)\n", 'v', v.x, v.y, v.z);
#endif

    for (int i = 0; i < 4; i++)
    {
        Point pt;

        switch (i)
        {
        case 0: pt = (Vector(0, 0, 0) - u) + (Vector(0, 0, 0) - v); break;
        case 1: pt = (Vector(0, 0, 0) - u) + v; break;
        case 2: pt = u + v; break;
        case 3: pt = u + (Vector(0, 0, 0) - v); break;
        }

        m_screen[i] = delta + pt;
    }

#ifdef LOG_TRACE
    for (int i = 0; i<4; i++)
        printf("Screen Point %d : (%lf, %lf, %lf)\n", i, m_screen[i].x, m_screen[i].y, m_screen[i].z);
#endif

}

void Engine::FindPlanParameters()
{
    ///determination des parametres (ax+by+cz+d=0) du plan cartesien
    Vector v2 = fill_vect_3D(m_screen[1].x - m_screen[0].x, m_screen[1].y - m_screen[0].y, m_screen[1].z - m_screen[0].z),
        v1 = fill_vect_3D(m_screen[3].x - m_screen[0].x, m_screen[3].y - m_screen[0].y, m_screen[3].z - m_screen[0].z);

#ifdef LOG_TRACE
    printf("Plan : ax+bx+cz+d\n");
    printf("Vector planParameters %d : (%lf, %lf, %lf)\n", 1, v1.x, v1.y, v1.z);
    printf("Vector planParameters %d : (%lf, %lf, %lf)\n", 2, v2.x, v2.y, v2.z);
#endif

    m_parameters[0] = v2.y*v1.z - v2.z*v1.y;
    m_parameters[1] = v2.z*v1.x - v2.x*v1.z;
    m_parameters[2] = v2.y*v1.x - v2.x*v1.z;
    m_parameters[3] = -m_screen[2].x*m_parameters[0] - m_screen[2].y*m_parameters[1] - m_screen[2].z*m_parameters[2];

#ifdef LOG_TRACE
    for (int i = 0; i<4; i++)
        printf("Parameter %d : %lf\n", i, m_parameters[i]);
#endif

}

Intersection Engine::PointIntersectionFromWorld(Point gamma)
{
    return PointIntersectionFromWorld(Point(m_cam->GetCoordX(), m_cam->GetCoordY(), m_cam->GetCoordZ()), gamma);
}

Intersection Engine::PointIntersectionFromWorld(Point omega, Point gamma)
{
    /// determination du parametre lambda 
    double lambda = (-m_parameters[3] - m_parameters[0] * omega.x - m_parameters[1] * omega.y - m_parameters[2] * omega.z)
        / (((gamma.x - omega.x)*m_parameters[0] + (gamma.y - omega.y)*m_parameters[1] + (gamma.z - omega.z)*m_parameters[2]));

#ifdef LOG_TRACE
    printf("World Point : (%lf, %lf, %lf)\n", gamma.x, gamma.y, gamma.z);
    printf("Parameter Lambda : %lf\n", lambda);
#endif

    if (lambda < 0 || lambda > 1)   //validite du parametre (point derriere l'ecran ou entre la cam et l'ecran
        return Intersection(gamma, true);

    /// determination du point 3D dans l'ecran
    Point point = fill_coord_3D(omega.x + lambda*(gamma.x - omega.x), omega.y + lambda*(gamma.y - omega.y), omega.z + lambda*(gamma.z - omega.z));

#ifdef LOG_TRACE
    printf("Point on Screen Plan : (%lf, %lf, %lf)\n", point.x, point.y, point.z);
#endif

    return Intersection(point, false);
}

Intersection* Engine::FindFinalIntersection(Intersection a, Intersection b)
{
    Intersection *FinalForm = new Intersection[2];

    FinalForm[0] = a; FinalForm[1] = b;

    if (a.behind == b.behind)
        return FinalForm;

    if (b.behind == true) {
        FinalForm[0] = PointIntersectionFromWorld(a.point, b.point);
        FinalForm[0].behind = false;
    }
    else {
        FinalForm[1] = PointIntersectionFromWorld(b.point, a.point);
        FinalForm[0].behind = false;
    }

    return FinalForm;
}

pt Engine::WorldCoordToScreenCoord(Point point)
{
    return pt(
        int((pow(DistFrom2Points(point, m_screen[1]), 2) - pow(DistFrom2Points(point, m_screen[0]), 2) +
        pow(DistFrom2Points(m_screen[0], m_screen[1]), 2)) / (2 * DistFrom2Points(m_screen[0], m_screen[1]))), 
        int((pow(DistFrom2Points(point, m_screen[0]), 2) - pow(DistFrom2Points(point, m_screen[3]), 2) +
        pow(DistFrom2Points(m_screen[3], m_screen[0]), 2)) / (2 * DistFrom2Points(m_screen[3], m_screen[0]))));
}

/* * * * * * Engine drawing * * * * * */

void Engine::DrawWorldLine(Point a, Point b, Uint32 color)
{
    Intersection *trace = FindFinalIntersection(PointIntersectionFromWorld(a),
        PointIntersectionFromWorld(b));

    if (trace[0].behind == false)
        m_Dscreen->draw_line(WorldCoordToScreenCoord(trace[0].point), WorldCoordToScreenCoord(trace[1].point), color);

    delete trace;
}

void Engine::DrawXYZpoint() {} //TODO

void Engine::DrawPolynomZInFunctionOfXZ(double coef_x, float pow_x, double coef_y, float pow_y, double add_on_coord_x, double add_on_coord_y, double add_on_coord_z, double range_x, double range_y, float res, Uint32 color)
{
    for (double x = -range_x / 2; x < range_x / 2; x += res)
        for (double y = -range_y / 2; y < range_y / 2; y += res) {
            Intersection pt = PointIntersectionFromWorld(fill_coord_3D(x + add_on_coord_x, y + add_on_coord_y, coef_x*pow(x, pow_x) +
                coef_y*pow(y, pow_y) + add_on_coord_z));
            if (pt.behind == false)
                m_Dscreen->draw_pix(WorldCoordToScreenCoord(pt.point), color);
        }
}

void Engine::DrawHalfSphere(double _x, double _y, double _z, double radius, double range_x, double range_y, float res, Uint32 color)
{
    for (double x = -range_x / 2; x < range_x / 2; x += res)
        for (double y = -range_y / 2; y < range_y / 2; y += res) {
            Intersection pt = PointIntersectionFromWorld(fill_coord_3D(x + _x, y + _y, _z + sqrt(pow(radius, 2) - pow(x, 2) - pow(y, 2))));
            if (pt.behind == false)
                m_Dscreen->draw_pix(WorldCoordToScreenCoord(pt.point), color);
        }
}

void Engine::DrawColouredCube(double x, double y, double z, double border)
{
    Point o(x, y, z);
    Vector u(border / 2, 0, 0), v(0, border / 2, 0), w(0, 0, border / 2);

    DrawWorldLine((u + v + w) + o, ((0 - u) + v + w) + o, red);
    DrawWorldLine(((0 - u) + v + w) + o, ((0 - u) +  (0 - v) + w) + o, red);
    DrawWorldLine(((0 - u) + (0 - v) + w) + o, (u + (0 - v) + w) + o, red);
    DrawWorldLine((u + (0 - v) + w) + o, (u + v + w) + o, red);

    DrawWorldLine((u + v + w) + o, (u + v + (0 - w)) + o, green);
    DrawWorldLine(((0 - u) + v + w) + o, ((0 - u) + v + (0 - w)) + o, green);
    DrawWorldLine(((0 - u) + (0 - v) + w) + o, ((0 - u) + (0 - v) + (0 - w)) + o, green);
    DrawWorldLine((u + (0 - v) + w) + o, (u + (0 - v) + (0 - w)) + o, green);

    DrawWorldLine((u + v + (0 - w)) + o, ((0 - u) + v + (0 - w)) + o, blue);
    DrawWorldLine(((0 - u) + v + (0 - w)) + o, ((0 - u) + (0 - v) + (0 - w)) + o, blue);
    DrawWorldLine(((0 - u) + (0 - v) + (0 - w)) + o, (u + (0 - v) + (0 - w)) + o, blue);
    DrawWorldLine((u + (0 - v) + (0 - w)) + o, (u + v + (0 - w)) + o, blue);

#ifdef LOG_TRACE
    printf("Draw cube on : (%lf, %lf, %lf), size : %lf\n", x, y, z, border);
#endif
}

