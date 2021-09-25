#include"YasGraphicsLibrary.hpp"

namespace YasGL
{
    uint8_t* createPixelsTable(Vector2D<int>* windowDimensions, Vector4D<uint8_t>* defaultColor)
    {
        uint8_t* pixels = new uint8_t[windowDimensions->x * windowDimensions->y * NUMBER_OF_COLORS];
        clearColor(pixels, defaultColor, windowDimensions);
        return pixels;
    }

    void clearColor(uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        for (int y = 0; y < windowDimensions->y; y++)
        {
            for (int x = 0; x < windowDimensions->x; x++)
            {///
                pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + RED_POSITION] = 0; // windowDimensions->x <- WINDOW WIDTH
                pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + GREEN_POSITION] = 0;
                pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + BLUE_POSITION] = 0;
                pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + ALPHA_POSITION] = 0;
            }
        }
    }

    void drawPoint(Vector2D<int>* point, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        cartesianPositionToWindow(point, windowDimensions);
        if (point->x >= 0 && point->x < windowDimensions->x && point->y >= 0 && point->y < windowDimensions->y)
        {
            pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + RED_POSITION] = drawingColor->x; // windowDimensions->x <- WINDOW WIDTH
            pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + GREEN_POSITION] = drawingColor->y;
            pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + BLUE_POSITION] = drawingColor->z;
            pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + ALPHA_POSITION] = drawingColor->w;
        }
    }

    void drawPoint(int x, int y, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        cartesianPositionToWindow(x, y, windowDimensions);
        if (x >= 0 && x < windowDimensions->x && y >= 0 && y < windowDimensions->y)
        {
            pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + RED_POSITION] = drawingColor->x; // windowDimensions->x <- WINDOW WIDTH
            pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + GREEN_POSITION] = drawingColor->y;
            pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + BLUE_POSITION] = drawingColor->z;
            pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + ALPHA_POSITION] = drawingColor->w;
        }
    }

    void  drawGentleSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
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

    void drawSteepSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
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

    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
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

    void lukeDrawLineOctan0V1(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        int x = point0->x;
        int y = point0->y;
        float cumulativeError = 0;
        float slope = static_cast<float>((point1->y - point0->y)) / (point1->x - point0->x);

        for (int i = point0->x; i <= point1->x; i++)
        {
            drawPoint(x, y, pixels, drawingColor, windowDimensions);
            x++;
            if (abs(cumulativeError + slope) < 0.5F)
            {
                cumulativeError = cumulativeError + slope;
            }
            else
            {
                y++;
                cumulativeError = cumulativeError + slope - 1;
            }
        }
    }


    // Negative slope line is like "\" Positive slope line is like "/"
    // Not steep line is line where slope (defined as dy/dx) > 1 

    // V2 Has modified equation(lukeDrawLineOctan0V1) (it is multiplied by delta X and then by 2)

    void drawNotSteepLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
		int x0 = point0->x;
		int y0 = point0->y;
		int deltaX = point1->x - point0->x;
		int deltaY = point1->y - point0->y;
		int cumulativeError = 0;

		for (int i = point0->x; i <= point1->x; i++)
		{
			drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
			x0++;
			if (2 * (cumulativeError + deltaY) < deltaX)
			{
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

    void lukeDrawLineFullUnderstandingVersion(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    { 
        int x0 = point0->x;
        int y0 = point0->y;
        int deltaX = point1->x - point0->x;
        int deltaY = point1->y - point0->y;
        int cumulativeError = 0;

        // Check if line is not steep (Octant: 0,3 4,7)
        if (abs(deltaY) < abs(deltaX))
        {
            if (point0->x < point1->x)
            {
                drawNotSteepLine(point0, point1, pixels, drawingColor, windowDimensions);
            }
            else
            {
                drawNotSteepLine(point1, point0, pixels, drawingColor, windowDimensions);
            }
        }
        else // if line is steep or is horizontal
        {

        }
    }

    void lukeDrawLineOctan4(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        int x0 = point0->x;
        int y0 = point0->y;
        int deltaX = point1->x - point0->x;
        int deltaY = point1->y - point0->y;
        int cumulativeError = 0;

        //if (point0->x > point1->x) this is 

        for (int i = point0->x; i <= point1->x; i++)
        {
            drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
            x0++;
            if (2 * (cumulativeError + deltaY) < deltaX)
            {
                //y stays the same
                cumulativeError = cumulativeError + deltaY;
            }
            else
            {
                y0++;
                cumulativeError = cumulativeError + deltaY - deltaX;
            }
        }

        FIRST THING IS TO PUT HERE SOMWHERE IF IT IS OCTAN 7
    }


    // This is instead writing more options in lukeDrawLineOctan0_V2 - for learning poprose of course
    void lukeDrawLineOctan7(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        int x0 = point0->x;
        int y0 = point0->y;
        int deltaX = point1->x - point0->x;
        int deltaY = point1->y - point0->y;
        int cumulativeError = 0;

		for (int i = point0->x; i <= point1->x; i++)
		{
		    drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
		    x0++;
		    if (2 * (cumulativeError + deltaY) > -deltaX)
		    {
		        //y stays the same
		        cumulativeError = cumulativeError + deltaY;
		    }
		    else
		    {
		        y0--;
		        cumulativeError = cumulativeError + deltaY + deltaX;
		    }
		}
    }

    void helsinkiDraw(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        // https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html
        int dx = point1->x - point0->x;
        int dy = point1->y - point0->y;
        int y = point0->y;
        int eps = 0;
    }

    void drawCartesianAxies(Vector2D<int>* windowDimensions, uint8_t* pixels)
    {
        int maxX = static_cast<int>(0.5F * windowDimensions->x);
        int maxY = static_cast<int>(0.5F * windowDimensions->y);

        Vector4D<uint8_t> xDrawingColorRed(255,0,0, 0); // RED
        Vector4D<uint8_t> yDrawingColorGreen(0,255,0, 0); // GREEN

        for (int i = -maxX; i < maxX; i++) //X
        {
            drawPoint(i, 0, pixels, &xDrawingColorRed, windowDimensions);
        }

        for (int i = -maxY; i < maxY; i++) //Y
        {
            drawPoint(0, i, pixels, &yDrawingColorGreen, windowDimensions);
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

    void drawCircle(Vector2D<int>* position, int& radius, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
    {
        int circleX;
        int circleY;
        Vector2D<int> circlePixelPosition;
        for (int i = 0; i < 360; i++)
        {
            circleX = static_cast<int>(position->x + radius * cos(i));
            circleY = static_cast<int>(position->y + radius * sin(i));

            circlePixelPosition.x = circleX;
            circlePixelPosition.y = circleY;
                        
            drawPoint(&circlePixelPosition, pixels, drawingColor, windowDimensions);
        }
    }

    void cartesianPositionToWindow(Vector2D<int>* point, Vector2D<int>* windowDimenstions) {
        point->x = point->x + static_cast<int>(0.5F * windowDimenstions->x);
        point->y = point->y + static_cast<int>(0.5F * windowDimenstions->y);
    }

	void cartesianPositionToWindow(int& x, int& y, Vector2D<int>* windowDimenstions) {
		x = x + static_cast<int>(0.5F * windowDimenstions->x);
		y = y + static_cast<int>(0.5F * windowDimenstions->y);
	}
}
