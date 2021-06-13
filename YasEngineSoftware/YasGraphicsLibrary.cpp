#include"YasGraphicsLibrary.hpp"

namespace YasGL
{
    Vector3D<uint8_t> BLACK(0, 0, 0);

    void clearColor(uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        for (int y = 0; y < windowDimensions->y; y++)
        {
            for (int x = 0; x < windowDimensions->x; x++)
            {
                pixels[3 * (y * windowDimensions->x + x) + RED_POSITION] = 0; // windowDimensions->x <- WINDOW WIDTH
                pixels[3 * (y * windowDimensions->x + x) + GREEN_POSITION] = 0;
                pixels[3 * (y * windowDimensions->x + x) + BLUE_POSITION] = 0;
            }
        }
    }

    void drawPoint(Vector2D<int>* point, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        pixels[3 * (point->y * windowDimensions->x + point->x) + RED_POSITION] = drawingColor->x; // windowDimensions->x <- WINDOW WIDTH
        pixels[3 * (point->y * windowDimensions->x + point->x) + GREEN_POSITION] = drawingColor->y;
        pixels[3 * (point->y * windowDimensions->x + point->x) + BLUE_POSITION] = drawingColor->z;
    }

    void drawPoint(int x, int y, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        pixels[3 * (y * windowDimensions->x + x) + RED_POSITION] = drawingColor->x; // windowDimensions->x <- WINDOW WIDTH
        pixels[3 * (y * windowDimensions->x + x) + GREEN_POSITION] = drawingColor->y;
        pixels[3 * (y * windowDimensions->x + x) + BLUE_POSITION] = drawingColor->z;
    }

    void  drawGentleSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
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
            drawPoint(i, y, pixels, drawingColor, windowDimensions);

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

    void drawSteepSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
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
            drawPoint(x, i, pixels, drawingColor, windowDimensions);

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

    // uint8_t* pixels, Vector2D<int>* position, int& radius, int windowWidth, Vector3D<int>* drawingColor, SDL_PixelFormat* pixelFormat
    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        // Check if it is slope line (Octant: 0,3 4,7)
        if (abs(point1->y - point0->y) < abs(point1->x - point0->x)) 
        {
            if (point0->x > point1->x)
            {
                drawGentleSlopeLine(point1, point0, pixels, drawingColor, windowDimensions);
            }
            else
            {
                drawGentleSlopeLine(point0, point1, pixels, drawingColor, windowDimensions);
            }
        }
        else // If it is not slope it is steep and these are 1,2,5, 6
        {
            if (point0->y > point1->y)
            {
                drawSteepSlopeLine(point1, point0, pixels, drawingColor, windowDimensions);
            }
            else
            {
                drawSteepSlopeLine(point0, point1, pixels, drawingColor, windowDimensions);
            }
        }
    }

    void lukeDrawLineOctan0V1(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        int x = point0->x;
        int y = point0->y;
        float cumulativeError = 0;
        float slope = static_cast<float>((point1->y - point0->y)) / (point1->x - point0->x);
        

        for (int i = point0->x; i <= point1->x; i++)
        {
            drawPoint(x, y, pixels, drawingColor, windowDimensions);
            x++;
            if (abs(cumulativeError + slope) < 0.5F) {
                cumulativeError = cumulativeError + slope;
            }
            else
            {
                y++;
                cumulativeError = cumulativeError + slope - 1;
            }
        }
    }


    void lukeDrawLineOctan0V2(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        int x0 = point0->x;
        int y0 = point0->y;
        //int x1 = point1->x;
        //int y1 = point1->y;
        int deltaX = point1->x - point0->x;
        int deltaY = point1->y - point0->y;
        int cumulativeError = 0;
        //float slope = static_cast<float>((point1->y - point0->y)) / (point1->x - point0->x);

        for (int i = point0->x; i <= point1->x; i++) {
            drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
            x0++;
            if ((2*cumulativeError + deltaY) < deltaX) {
                //y stays the same
                cumulativeError = cumulativeError + deltaY;
            }
            else
            {
                y0++;
                cumulativeError = cumulativeError + deltaY - deltaX;
            }
        }
    }



    void helsinkiDraw(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
    int dx = point1->x - point0->x;
    int dy = point1->y - point0->y;
    int y = point0->y;
    int eps = 0;

        for (int x = point0->x; x <= point1->x; x++) {
            drawPoint(x, y, pixels, drawingColor, windowDimensions);
            eps += dy;
            std::cout << "eps: " << eps << std::endl;
            if ((eps * 2) >= dx) {
                y++;  eps -= dx;
            }
        }
    }

    void cartesianPositionToWindow(Vector2D<int>* point, Vector2D<int>* windowDimensions)
    {
        point->x = point->x + (windowDimensions->x / 2);
        point->y = (point->y * -1) + (windowDimensions->y / 2);
    }

    void windowPositionToCartesian(Vector2D<int>* point, Vector2D<int>* windowDimensions)
    {
        point->x = point->x - (windowDimensions->x / 2);
        point->y = (point->y * -1) + (windowDimensions->y / 2);
    }

    void drawCartesianAxies(int screenWidth, int screenHeight, uint8_t* pixels, Vector3D<uint8_t>* drawingColor)
    {
        int centerX = screenWidth / 2;
        int centerY = screenHeight / 2;

        Vector2D<int> windowDimensions(screenWidth, screenHeight);

        for (int i=0; i < screenWidth; i++)
        {
            drawPoint(i, centerY, pixels, drawingColor, &windowDimensions);

            //SDL_RenderDrawPoint(renderer, i, centerY);

//            data[3 * (y * 100 + x) + RED_POSITION] = 255;
//            data[3 * (y * 100 + x) + GREEN_POSITION] = 0;
//            data[3 * (y * 100 + x) + BLUE_POSITION] = 0;

        }

        for (int i = 0; i < screenHeight; i++)
        {
            drawPoint(centerX, i, pixels, drawingColor, &windowDimensions);
            //SDL_RenderDrawPoint(renderer, centerX, i);
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

    void drawCircle(Vector2D<int>* position, int& radius, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        int circleX;
        int circleY;
        for (int i = 0; i < 360; i++)
        {
            circleX = static_cast<int>(position->x + radius * cos(i));
            circleY = static_cast<int>(position->y + radius * sin(i));
            Vector2D<int> circlePixelPosition(circleX, circleY);
            drawPoint(&circlePixelPosition, pixels, drawingColor, windowDimensions);
            //drawPoint(Vector2D<int>*point, uint8_t* pixels, Vector3D<uint8_t>*drawingColor, int windowWidth);
            //pixels[xyPixelToArrayPosition(&circlePixelPosition, windowWidth)] = SDL_MapRGBA(pixelFormat, drawingColor->x, drawingColor->y, drawingColor->z, 255);
            
        }
    }
}
