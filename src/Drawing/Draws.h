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

#ifndef _DRAWS_H
#define _DRAWS_H

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>

#include "../Miscellaneous/Structures.h"

// * * * * * *
// Here is the Drawing section based on SDL2.0
// We try to use the GPU, it can always be optimized
// This section provide a single window per class
// * * * * * *

#define FONT_VERDANA "verdana.ttf"

class Draws
{
public:
    Draws(int w, int h);    //initialize a new window
    ~Draws();

    int GetWidth() { return WIDTH; }
    int GetHeight() { return HEIGHT; }

    void EnableAutoDisp() { m_auto_disp = true; }
    void DisableAutoDisp() { m_auto_disp = false; }

    void UpdateWindow() { SDL_RenderPresent(Renderer); }

    void disp_txt(char *txt, int lenght, pt p, Uint32 C, char *font_name, bool aliased);

    void PrepareToColorRenderer(Uint32 coul);

    void draw_line(pt p1, pt p2, Uint32 color);
    void draw_rect(pt p1, pt p2, Uint32 color);
    void draw_fill_rect(pt p1, pt p2, Uint32 color);

    void draw_pix(int x, int y, Uint32 color);
    void draw_pix(pt p1, Uint32 color);

    void fill_screen(Uint32 color);
    void draw_circle(pt centre, int radius, Uint32 color);
    void draw_fill_circle(pt centre, int radius, Uint32 color);
    void draw_fill_ellipse(pt F1, pt F2, int r, Uint32 color);
    void draw_triangle(pt p1, pt p2, pt p3, Uint32 color);
    void draw_fill_triangle(pt p1, pt p2, pt p3, Uint32 color);

    void test();

private:
    int WIDTH, HEIGHT;

    bool m_auto_disp;

    SDL_Window *Window;
    SDL_Renderer *Renderer;

    bool in_screen(int x, int y) { if (x<0) return false; 
                                    if (x >= WIDTH) return false; 
                                    if (y<0) return false; 
                                    if (y >= HEIGHT) return false; return true; }
};

#endif