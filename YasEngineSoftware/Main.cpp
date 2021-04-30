#include<cstdlib>
#include<iostream>
#include<vector>
#include<cmath>
#include<SDL.h>
#include"Vector2D.hpp"
#include"YasGraphicsLibrary.hpp"
#include"TimePicker.hpp"


//void drawGentleSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
//void drawSteepSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
//void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
//void render(float dt, SDL_Renderer *renderer);

float aspect;

int windowWidth = 1024;
int windowHeight = 768;

int pixelCounter = 0;
//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120
int main(int argc, char * argv[])
{
    SDL_Renderer *renderer;
    SDL_Window* window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer);

    if(!window)
    {
        std::cerr << "Error failed to create window!\n";
        return 1;
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    SDL_Event event;
    bool running = true;


    double time;
    double newTime;
    double deltaTime;
    double fps;
    double fpsTime;
    unsigned int frames;
    MSG message;

    TimePicker timePicker = TimePicker();
    time = timePicker.getSeconds();

    fpsTime = 0.0F;
    frames = 0;
    message.message = WM_NULL;

    int circleSpeedFactor = 1000;
    int circleSpeed = 2 * circleSpeedFactor;
    int circleCenterX = 50;
    int circleCenterY = 300;
    int circleX = 0;
    int circleY = 0;

    float canvasWidth = 2, canvasHeight = 2;
    uint32_t imageWidth = 512, imageHeight = 512;

    Vector2D<int>* line1_A = new Vector2D<int>(50, 50);
    Vector2D<int>* line1_B = new Vector2D<int>(400, 60);

    Vector2D<int>* line2_A= new Vector2D<int>(-10, 400);
    Vector2D<int>* line2_B= new Vector2D<int>(550, -20);

    while(running)
    {
    
        while(SDL_PollEvent(&event))
        {
            running = event.type != SDL_QUIT;
        }
        
        newTime = timePicker.getSeconds();  
        deltaTime = newTime - time;
        time = newTime;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        int randomX = rand() % 600;
        int randomY = rand() & 600;
        pixelCounter++;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        circleCenterX = static_cast<int>(circleCenterX + deltaTime * circleSpeed);
        if (circleCenterX <= 0 || circleCenterX >= 1024) {
            circleSpeed = circleSpeed * -1;
        }
        //(Vector2D<int>*point0, Vector2D<int>*point1, SDL_Renderer * renderer)

        YasGL::drawLine(line1_A, line1_B, renderer);

        YasGL::drawLine(line2_B, line2_A, renderer);

        for(int i=0; i< 360;i++) {
            circleX = static_cast<int>(circleCenterX + 32*cos(i));
            circleY = static_cast<int>(circleCenterY + 32*sin(i));
            SDL_RenderDrawPoint(renderer, circleX, circleY);
        }

        SDL_RenderPresent(renderer);

        ++frames;
        fpsTime = fpsTime + deltaTime;
        if(fpsTime >= 1.0F)
        {
            fps = frames / fpsTime;
            frames = 0;
            fpsTime = 0.0F;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|

//
//void drawGentleSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
//{
//    int deltaX = point1->x - point0->x;
//    int deltaY = point1->y - point0->y;
//
//    int yIteration = 1;
//
//    if(deltaY <0)
//    {
//        yIteration = -1;
//        deltaY = -deltaY;
//    }
//
//    int difference = (2 * deltaY) - deltaX;
//
//    int y = point0->y;
//
//    for (int i = point0->x; i <= point1->x; i++)
//    {
//        SDL_RenderDrawPoint(renderer, i, y);
//        if(difference >0)
//        {
//            y = y + yIteration;
//            difference = difference + (2*(deltaY - deltaX));
//        }
//        else
//        {
//            difference = difference + 2*deltaY;
//        }
//    }
//}
//
//
//void drawSteepSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
//{
//    int deltaX = point1->x - point0->x;
//    int deltaY = point1->y - point0->y;
//
//    int xIteration = 1;
//
//    if(deltaX <0)
//    {
//        xIteration = -1;
//        deltaX = -deltaX;
//    }
//
//    int difference = (2 * deltaX) - deltaY;
//
//    int x = point0->x;
//
//    for (int i = point0->y; i <= point1->y; i++)
//    {
//        SDL_RenderDrawPoint(renderer, x, i);
//        if(difference >0)
//        {
//            x = x + xIteration;
//            difference = difference + (2*(deltaX - deltaY));
//        }
//        else
//        {
//            difference = difference + 2*deltaX;
//        }
//    }
//}
//
//void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
//{
//    if(abs(point1->y - point0->y) < abs(point1->x - point0->x))
//    {
//        if(point0->x > point1->x)
//        {
//            drawGentleSlopeLine(point1, point0, renderer);
//        }
//        else
//        {
//            drawGentleSlopeLine(point0, point1, renderer);
//        }
//    }
//    else
//    {
//        if(point0->y > point1->y)
//        {
//            drawSteepSlopeLine(point1, point0, renderer);
//        }
//        else
//        {
//            drawSteepSlopeLine(point0, point1, renderer);
//        }
//    }
//}
//
//void render(float dt, SDL_Renderer *renderer)
//{
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//    SDL_RenderClear(renderer);
//    int randomX = rand() % 600;
//    int randomY = rand() & 600;
//    pixelCounter++;
//    if(pixelCounter < 1000)
//    {
//        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
//        SDL_RenderDrawPoint(renderer, randomX, randomY);
//    }
//    SDL_RenderPresent(renderer);
//}