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

/*
TODO:
Documentation
Handle fps counter with new thread
Issue : rotation isn't handled properly : why ? => Check ConvertCylinderCoord
*/

#include "Engine/Engine.h"

int main(int, char **)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
    {
        fprintf(stderr, "Couldn't initialize SDL or TTF module: %s\n", SDL_GetError());
        exit(1);
    }

    Engine Engine1(900, __int32(((tan(Camera::GetStandardFOV_V() / 2)*900) / tan(Camera::GetStandardFOV_H() / 2))));

    SDL_Event event; SDL_PollEvent(&event);

    Uint32 time = SDL_GetTicks();

    while (event.key.keysym.sym != SDLK_ESCAPE && event.type != SDL_QUIT) {

        //actions
        Engine1.UpdateEngine();
        Engine1.DrawColouredCube(700, 0, 0, 200);
        Engine1.DrawColouredCube(700, 200, 0, 200);
        Engine1.DrawColouredCube(700, 200, 0, 200);


        //FPS counter without user action
        Engine1.DispEngineInfo(1000 / (SDL_GetTicks() - time));

        //Cam moves handling
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEMOTION /*(for camera rotation v/h) */)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP: Engine1.GetCam()->DoTranslation(1, 0, 0); break;
            case SDLK_DOWN: Engine1.GetCam()->DoTranslation(-1, 0, 0); break;
            case SDLK_LEFT: Engine1.GetCam()->DoTranslation(0, -1, 0); break;
            case SDLK_RIGHT: Engine1.GetCam()->DoTranslation(0, 1, 0); break;
            case SDLK_z: Engine1.GetCam()->DoTranslation(0, 0, 1); break;
            case SDLK_w: Engine1.GetCam()->DoTranslation(0, 0, -1); break;

                //Rotation aren't displayed correctly
            case SDLK_1: Engine1.GetCam()->DoRotation(0.1f, 0); break;
            case SDLK_2: Engine1.GetCam()->DoRotation(-0.1f, 0); break;
            case SDLK_3: Engine1.GetCam()->DoRotation(0, 0.1f); break;
            case SDLK_4: Engine1.GetCam()->DoRotation(0, -0.1f); break;
            }
        }

        //cam.DoRotation(0.00, 0.001);
        //cam.DoTranslation(1, 1, 0);
        //cam.SetRotation(M_PI / 4, 0);

        time = SDL_GetTicks();
    }

    SDL_Quit();
    TTF_Quit();

    return 0;
}
