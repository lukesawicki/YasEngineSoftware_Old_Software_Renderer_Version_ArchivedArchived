#include"YasGraphicsLibrary.hpp"

namespace YasGL
{
    void drawGentleSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, Uint32* pixels, Vector3D<int>* drawingColor, SDL_PixelFormat* pixelFormat, int windowWidth)
    {
        int deltaX = point1->x - point0->x;
        int deltaY = point1->y - point0->y;

        int yIteration = 1;

        if (deltaY < 0)
        {
            yIteration = -1;
            deltaY = -deltaY;
        }

        int difference = (2 * deltaY) - deltaX;

        int y = point0->y;

        for (int i = point0->x; i <= point1->x; i++)
        {
            //SDL_RenderDrawPoint(renderer, i, y);
            pixels[xyPixelToArrayPosition(i, y, windowWidth)] = SDL_MapRGBA(pixelFormat, drawingColor->x, drawingColor->y, drawingColor->z, 0);
            if (difference > 0)
            {
                y = y + yIteration;
                difference = difference + (2 * (deltaY - deltaX));
            }
            else
            {
                difference = difference + 2 * deltaY;
            }
        }
    }

    void drawSteepSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, Uint32* pixels, Vector3D<int>* drawingColor, SDL_PixelFormat* pixelFormat, int windowWidth)
    {
        int deltaX = point1->x - point0->x;
        int deltaY = point1->y - point0->y;

        int xIteration = 1;

        if (deltaX < 0)
        {
            xIteration = -1;
            deltaX = -deltaX;
        }

        int difference = (2 * deltaX) - deltaY;

        int x = point0->x;

        for (int i = point0->y; i <= point1->y; i++)
        {
            // SDL_RenderDrawPoint(renderer, x, i);
            pixels[xyPixelToArrayPosition(x, i, windowWidth)] = SDL_MapRGBA(pixelFormat, drawingColor->x, drawingColor->y, drawingColor->z, 0);
            if (difference > 0)
            {
                x = x + xIteration;
                difference = difference + (2 * (deltaX - deltaY));
            }
            else
            {
                difference = difference + 2 * deltaX;
            }
        }
    }


    // Uint32* pixels, Vector2D<int>* position, int& radius, int windowWidth, Vector3D<int>* drawingColor, SDL_PixelFormat* pixelFormat
    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, Uint32* pixels, Vector3D<int>* drawingColor, SDL_PixelFormat* pixelFormat, int windowWidth)
    {
        if (abs(point1->y - point0->y) < abs(point1->x - point0->x))
        {
            if (point0->x > point1->x)
            {
                drawGentleSlopeLine(point1, point0, pixels, drawingColor, pixelFormat, windowWidth);
            }
            else
            {
                drawGentleSlopeLine(point0, point1, pixels, drawingColor, pixelFormat, windowWidth);
            }
        }
        else
        {
            if (point0->y > point1->y)
            {
                drawSteepSlopeLine(point1, point0, pixels, drawingColor, pixelFormat, windowWidth);
            }
            else
            {
                drawSteepSlopeLine(point0, point1, pixels, drawingColor, pixelFormat, windowWidth);
            }
        }
    }

    void cartesianPositionToWindow(Vector2D<int>* point, Vector2D<int>* screen)
    {
        point->x = point->x + (screen->x / 2);
        point->y = (point->y * -1) + (screen->y / 2);
    }

    void windowPositionToCartesian(Vector2D<int>* point, Vector2D<int>* screen)
    {
        point->x = point->x - (screen->x / 2);
        point->y = (point->y * -1) + (screen->y / 2);
    }

    void drawCartesianAxies(SDL_Renderer* renderer, int screenWidth, int screenHeight, Vector3D<int>* color) {
        SDL_SetRenderDrawColor(renderer, 0, color->x, color->y, color->z);

        int centerX = screenWidth / 2;
        int centerY = screenHeight / 2;

        for (int i=0; i < screenWidth; i++)
        {
            SDL_RenderDrawPoint(renderer, i, centerY);
        }

        for (int i = 0; i < screenHeight; i++)
        {
            SDL_RenderDrawPoint(renderer, centerX, i);
        }
    }

    int xyPixelToArrayPosition(int x, int y, int windowWidth)
    {
        return y * windowWidth + x;
    }

    int xyPixelToArrayPosition(Vector2D<int>* point, int windowWidth)
    {
        return point->y* windowWidth + point->x;
    }

    void drawCircle(Uint32* pixels, Vector2D<int>* position,int& radius, int windowWidth, Vector3D<int>* drawingColor, SDL_PixelFormat* pixelFormat)
    {
        int circleX;
        int circleY;
        for (int i = 0; i < 360; i++)
        {
            circleX = static_cast<int>(position->x + radius * cos(i));
            circleY = static_cast<int>(position->y + radius * sin(i));
            Vector2D<int> circlePixelPosition(circleX, circleY);
            pixels[xyPixelToArrayPosition(&circlePixelPosition, windowWidth)] = SDL_MapRGBA(pixelFormat, drawingColor->x, drawingColor->y, drawingColor->z, 0);
            
        }
    }
}
