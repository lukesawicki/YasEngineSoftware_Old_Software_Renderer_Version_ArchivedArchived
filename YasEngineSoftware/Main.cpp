//#include<Windows.h>
#define SDL_MAIN_HANDLED
#include<SDL.h>
#include<SDL_endian.h>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<cmath>
#include"VariousTools.hpp"
#include"YasVector2D.hpp"
#include"YasGraphicsLibrary.hpp"
#include"TimePicker.hpp"
#include"PixelsTable.hpp"
#include"Circle.hpp"
#include"YasPolygon.hpp"
#include"Player.hpp"
#include"InputOutputHandler.hpp"

//Strange World by Darkroom (c) copyright 2022 Licensed under a Creative Commons Attribution Noncommercial  (3.0) license. http://dig.ccmixter.org/files/mactonite/64736 Ft: Martin Cee

#define DEBUG_DRAWINGS

bool shouldApplicationStopRunning = false;
YasInOut::Input* input = new YasInOut::Input();
YasInOut::MousePositionChangeInformation* mousePositionChangeInformation = new YasInOut::MousePositionChangeInformation();

int main(int argc, char* argv[])
{
    const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 768;

    YasVector2D<int>* windowDimensions = new YasVector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("YasEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_SetWindowMinimumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    listRenderersInformation();

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

    SDL_Texture* screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

    PixelsTable pixelsTable(WINDOW_WIDTH, WINDOW_HEIGHT, BLACK);

    YasVector2D<int> zeroVector;
    YasVector2D<int> direction;

	YasVector2D<int> testA;
	YasVector2D<int> testB;

	std::vector<YasPolygon*> objectsToDraw;

    Player* player = new Player(0, 0);
    player->setColor(YELLOW);
    player->setInput(input);
    player->setInput(mousePositionChangeInformation);

#ifdef DEBUG_DRAWINGS
    Circle* circle = new Circle(100, 0, 0);
    circle->setColor(BLUE);
    objectsToDraw.push_back(circle);
#endif // DEBUG_DRAWINGS

    objectsToDraw.push_back(player);

    // End of test objects definitions

    double time;
    double newTime;
    double deltaTime;
    double fps;
    double fpsTime;
    unsigned int frames;

    TimePicker timePicker = TimePicker();
    time = timePicker.getSeconds();

    fpsTime = 0.0F;
    frames = 0;
    bool close = false;
    bool firstTime = true;

    bool quit = false;

    SDL_Event event;


    while (!quit)
    {
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else
            {
                if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            quit = true;
                        break;
                        case SDLK_w:
                            input->up = true;
                            break;
                        case SDLK_s:
                            input->down = true;
                                break;
                        case SDLK_a:
                            input->left = true;
                                break;
                        case SDLK_d:
                            input->right = true;
                                break;
                        default:
                            ;
                    }
                }
                if (event.type == SDL_KEYUP)
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_w:
                            input->up = false;
                        break;
                        case SDLK_s:
                            input->down = false;
                        break;
                        case SDLK_a:
                            input->left = false;
                        break;
                        case SDLK_d:
                            input->right = false;
                        break;
                        default:
                        ;
                    }
                }
                if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
                {
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                    {
                        input->mouseLeftButton = true;
                        player->isShooting = true;
                    }
                    if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
                    {
                        input->mouseLeftButton = false;
                        player->isShooting = false;
                    }

                    mousePositionChangeInformation->mouseMoved = true;
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    mousePositionChangeInformation->x = x;
                    mousePositionChangeInformation->y = y;

                }
            }
        }

            newTime = timePicker.getSeconds();
            deltaTime = newTime - time;
            time = newTime;

            ++frames;
            fpsTime = fpsTime + deltaTime;
            if (fpsTime >= 1.0F)
            {
                fps = frames / fpsTime;
                frames = 0;
                fpsTime = 0.0F;
            }
            
            pixelsTable.clearColor(ALT_BLACK);
            
            #ifdef DEBUG_DRAWINGS
			drawCartesianAxies(pixelsTable);
            #endif // DEBUG_DRAWINGS

            if (mousePositionChangeInformation->mouseMoved || input->up || input->down || input->left || input->right)
            {
                player->rotateToMousePositionInLocalCoordinateSystem(mousePositionChangeInformation->x, mousePositionChangeInformation->y, windowDimensions);
            }

            float mouseX = mousePositionChangeInformation->x;
            float mouseY = mousePositionChangeInformation->y;

            windowPositionToCartesianPosition(mouseX, mouseY, windowDimensions);
            drawCrossOnScreen(mouseX, mouseY, pixelsTable);

            for (auto object : objectsToDraw)
            {
                object->move(static_cast<float>(deltaTime));
                object->regeneratePolygon();
                drawPolygon(object, pixelsTable);
            }

            Projectile* projectile = player->shoot();
            if (projectile != nullptr)
            {
                objectsToDraw.push_back(projectile);
            }

            projectile = nullptr;

            SDL_UpdateTexture(screenTexture, NULL, pixelsTable.pixels, WINDOW_WIDTH * 4);
            SDL_RenderCopyExF(renderer, screenTexture, NULL, NULL, 0, NULL, SDL_RendererFlip::SDL_FLIP_VERTICAL);
            SDL_RenderPresent(renderer);
    }

    for (auto drawableObject : objectsToDraw)
    {
        delete drawableObject;
    }

    return 0;
}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
