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

#include "Draws.h"

size_t Draws::count = 1;

Draws::Draws(int w, int h) : WIDTH(w), HEIGHT(h), m_auto_disp(true)
{
    char title[225];
    sprintf(title, "3D-Engine : Window %d", count);
    Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!Window) {
        fprintf(stderr, "Couldn't create a new window %s\n", SDL_GetError());
        exit(1);
    }

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
    if (!Renderer) {
        fprintf(stdout, "Couldn't build a new renderer (%s)\n", SDL_GetError());
        exit(1);
    }
    count++;
    UpdateWindow();
}

Draws::~Draws()
{
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    count--;
}

void Draws::disp_txt(char *txt, int size, pt p, Uint32 color, char *font_name, bool aliased)
{
    TTF_Font* Font = TTF_OpenFont(font_name, size); //this opens a font style and sets a size
    SDL_Surface* surfaceMessage;

    if (!Font)
    {
        fprintf(stdout, "Couldn't find any font.\n");
        return;
    }

    SDL_Color coul = { (color & 0xFF00000) / 0x10000, (color & 0x00FF00) / 0x100, (color & 0x0000FF), 0 };

    if (aliased)
        surfaceMessage = TTF_RenderText_Solid(Font, txt, coul);
    else
        surfaceMessage = TTF_RenderText_Blended(Font, txt, coul);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer, surfaceMessage);
    SDL_Rect Message_rect{ int(p.x), HEIGHT - int(p.y), surfaceMessage->w, surfaceMessage->h };

    SDL_RenderCopy(Renderer, Message, NULL, &Message_rect);

    if (m_auto_disp) UpdateWindow();
}

void Draws::PrepareToColorRenderer(Uint32 coul)
{
    SDL_SetRenderDrawColor(Renderer, (coul & 0xFF00000) / 0x10000, (coul & 0x00FF00) / 0x100, (coul & 0x0000FF), 0);
}

void Draws::draw_line(pt p1, pt p2, Uint32 color)
{
    PrepareToColorRenderer(color);
    SDL_RenderDrawLine(Renderer, p1.x,HEIGHT - p1.y, p2.x, HEIGHT - p2.y);

    if (m_auto_disp) UpdateWindow();
}

void Draws::draw_rect(pt p1, pt p2, Uint32 color)
{
    PrepareToColorRenderer(color);
    SDL_Rect rect{ p1.x, HEIGHT - p1.y, p2.x - p1.x, -(p2.y - p1.y) };
    SDL_RenderDrawRect(Renderer, &rect);

    if (m_auto_disp) UpdateWindow();
}

void Draws::draw_fill_rect(pt p1, pt p2, Uint32 color)
{
    PrepareToColorRenderer(color);
    int minx = min(p1.x, p2.x); int miny = min(p1.y, p2.y), dx = abs(p2.x - p1.x), dy = abs(p2.y - p1.y);
    for (int i = 0; i <= dy; i++)
        SDL_RenderDrawLine(Renderer, minx, HEIGHT - miny - i, minx + dx, HEIGHT - miny - i);

    if (m_auto_disp) UpdateWindow();
}

void Draws::draw_pix(int x, int y, Uint32 color)
{
    PrepareToColorRenderer(color);
    SDL_RenderDrawPoint(Renderer, x, y);
    if (m_auto_disp) UpdateWindow();
}

void Draws::draw_pix(pt p1, Uint32 color)
{
    PrepareToColorRenderer(color);
    SDL_RenderDrawPoint(Renderer, p1.x, p1.y);
    if (m_auto_disp) UpdateWindow();
}

void Draws::fill_screen(Uint32 color) {
    PrepareToColorRenderer(color);
    SDL_RenderFillRect(Renderer, NULL);

    if (m_auto_disp) UpdateWindow();
}

void Draws::draw_circle(pt centre, int radius, Uint32 color) {
    PrepareToColorRenderer(color);
    pt min, max;
    int i, j;
    float dx, dy, rr;

    min.x = centre.x - radius;  max.x = centre.x + radius;
    min.y = centre.y - radius;  max.y = centre.y + radius;
    rr = float(radius*radius);

    for (i = min.x; i <= max.x; i++)
    {
        dx = float(i - centre.x);
        dy = sqrt(rr - dx*dx);
        j = int(centre.y + dy);
        SDL_RenderDrawPoint(Renderer, i, HEIGHT - j);
        j = int(centre.y - dy);
        SDL_RenderDrawPoint(Renderer, i, HEIGHT - j);
    }
    for (j = min.y; j <= max.y; j++)
    {
        dy = float(j - centre.y);
        dx = sqrt(rr - dy*dy);
        i = int(centre.x + dx);
        SDL_RenderDrawPoint(Renderer, i, HEIGHT - j);
        i = int(centre.x - dx);
        SDL_RenderDrawPoint(Renderer, i, HEIGHT - j);
    }

    if (m_auto_disp) UpdateWindow();
}

void Draws::draw_fill_circle(pt centre, int radius, Uint32 color) {
    PrepareToColorRenderer(color);
    pt min, max;
    int i, j;
    float dx, dy, rr;

    min.x = centre.x - radius; max.x = centre.x + radius;
    min.y = centre.y - radius; max.y = centre.y + radius;

    rr = float(radius*radius);

    for (i = min.x; i <= max.x; i++)
    {
        dx = float(i - centre.x);
        for (j = min.y; j <= max.y; j++)
        {
            dy = float(j - centre.y);
            if (dx*dx + dy*dy <= rr) SDL_RenderDrawPoint(Renderer, i, HEIGHT - j);
        }
    }

    if (m_auto_disp) UpdateWindow();
}

void Draws::draw_fill_ellipse(pt F1, pt F2, int r, Uint32 color) {
    PrepareToColorRenderer(color);
    int i, j;
    int dx, fx;
    int dy, fy;
    float d, d1, d2;

    d = float((F1.x - F2.x)*(F1.x - F2.x) + (F1.y - F2.y)*(F1.y - F2.y));
    d = sqrt(d);

    if (F1.x<F2.x) { dx = int(F1.x - d - r); fx = int(F2.x + d + r); }
    else { dx = int(F2.x - d - r); fx = int(F1.x + d + r); }
    if (F1.y<F2.y) { dy = int(F1.y - d - r); fy = int(F2.y + d + r); }
    else { dy = int(F2.y - d - r); fy = int(F1.y + d + r); }
    for (i = dx; i <= fx; i++)
        for (j = dy; j <= fy; j++)
            if (in_screen(i, j))
            {
                d1 = float((i - F1.x)*(i - F1.x) + (j - F1.y)*(j - F1.y));
                d1 = sqrt(d1);
                d2 = float((i - F2.x)*(i - F2.x) + (j - F2.y)*(j - F2.y));
                d2 = sqrt(d2);
                if (d1 + d2 < d + r) SDL_RenderDrawPoint(Renderer, i, HEIGHT - j);
            }

    if (m_auto_disp) UpdateWindow();
}

void Draws::draw_triangle(pt p1, pt p2, pt p3, Uint32 color) {
    draw_line(p1, p2, color);
    draw_line(p2, p3, color);
    draw_line(p3, p1, color);
}

void Draws::draw_fill_triangle(pt p1, pt p2, pt p3, Uint32 color) {
    PrepareToColorRenderer(color);
    float a12, b12, a23, b23, a31, b31;
    float s1, s2, s3;

    a12 = (p1.y - p2.y) / (float)(p1.x - p2.x);   b12 = p1.y - a12*p1.x;
    a23 = (p2.y - p3.y) / (float)(p2.x - p3.x);   b23 = p2.y - a23*p2.x;
    a31 = (p3.y - p1.y) / (float)(p3.x - p1.x);   b31 = p3.y - a31*p3.x;

    s3 = p3.y - (a12*p3.x + b12);
    s1 = p1.y - (a23*p1.x + b23);
    s2 = p2.y - (a31*p2.x + b31);

    int minx, maxx, miny, maxy;
    minx = min(p1.x, p2.x, p3.x); maxx = max(p1.x, p2.x, p3.x);
    miny = min(p1.y, p2.y, p3.y); maxy = max(p1.y, p2.y, p3.y);

    int i, j;
    int ok;
    for (i = minx; i<maxx; i++)
        for (j = miny; j<maxy; j++)
        {
            ok = 1;
            if (s3 * (j - (a12*i + b12)) < 0) ok = 0;
            if (s1 * (j - (a23*i + b23)) < 0) ok = 0;
            if (s2 * (j - (a31*i + b31)) < 0) ok = 0;
            if (ok) SDL_RenderDrawPoint(Renderer, i, HEIGHT - j);
        }

    if (m_auto_disp) UpdateWindow();
}

void Draws::test()
{
    bool test(false);
    if (m_auto_disp) { DisableAutoDisp(); test = true; }
    disp_txt("TEST", 32, fill_coord_2D(10, 50), 0xFFFFFFFF, FONT_VERDANA, false);
    draw_line(fill_coord_2D(0, 0), fill_coord_2D(640, 480), 0xFF00FF);
    draw_rect(fill_coord_2D(0, 1), fill_coord_2D(GetWidth(), GetHeight() - 1), 0x00FF00);
    draw_fill_triangle(fill_coord_2D(300, 300), fill_coord_2D(400, 300), fill_coord_2D(350, 450), 0x0000A5);
    UpdateWindow();
    SDL_Delay(3000);
    if (test) { EnableAutoDisp(); }
    fill_screen(0);
}
