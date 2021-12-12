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
            {
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

    void lukesDrawLine(Vector2D<int>*point0, Vector2D<int>*point1, uint8_t * pixels, Vector4D<uint8_t>*drawingColor, Vector2D<int>*windowDimensions)
    {
        int x0 = point0->x;
        int y0 = point0->y;

        int originalPoint0X = point0->x;
        int originalPoint0Y = point0->y;

        int originalPoint1X = point1->x;
        int originalPoint1Y = point1->y;

        Vector2D<int>* copyPoint0 = new Vector2D<int>(point0->x, point0->y);
        Vector2D<int>* copyPoint1 = new Vector2D<int>(point1->x, point1->y);

        int deltaX = point1->x - point0->x;
        int deltaY = point1->y - point0->y;
        int cumulativeError = 0;

        if (abs(deltaX) != abs(deltaY))
        {
            // Check if it is gentle slope
            if (abs(deltaX) > abs(deltaY))
            {
                if (deltaX < 0)
                {
                    // you have to swtich points that point0 is end of line and point1 i start of the line;

                    // swtich x for for loop condition
                    //temporaryForForLoopCondition = originalPoint0X;
                    originalPoint0X = point1->x;
                    originalPoint1X = point0->x;

                    // switch x for drawing
                    x0 = point1->x;
                    y0 = point1->y;

                    if (deltaY > 0) // it is positive slope so it means octan 0 and points in correct order ( incorrect order is octan 4 )
                    {
                        deltaX = point0->x - point1->x;
                        deltaY = point0->y - point1->y;
                        for (int i = originalPoint0X; i <= originalPoint1X; i++)
                        {
                            drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
                            x0++;
                            if ((2 * (cumulativeError + deltaY)) > -deltaX)
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
                    else // it is negitive slope so it means octan 8 and points in "correct order" ( incorrect order is ocatn 3 )
                    {
                        deltaX = point0->x - point1->x;
                        deltaY = point0->y - point1->y;
                        for (int i = originalPoint0X; i <= originalPoint1X; i++)
                        {
                            drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
                            x0++;
                            if ((2 * (cumulativeError + deltaY)) < deltaX)
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
                }
                else
                {

                    if (deltaY > 0) // it is positive slope so it means octan 0 and points in correct order ( incorrect order is octan 4 )
                    {
                        for (int i = originalPoint0X; i <= originalPoint1X; i++)
                        {
                            drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
                            x0++;
                            if ((2 * (cumulativeError + deltaY)) < deltaX)
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
                    else // it is negitive slope so it means octan 8 and points in "correct order" ( incorrect order is ocatn 3 )
                    {
                        for (int i = originalPoint0X; i <= originalPoint1X; i++)
                        {
                            drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
                            x0++;
                            if ((2 * (cumulativeError + deltaY)) > -deltaX)
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
                }
            } // end gentle
            else // it is steep slope  STEEP STEEP STEEP STEEP
            {
		        if (deltaY < 0) 
                {
                    // STEEEEEEEEEP
			        // you have to swtich points that point0 is end of line and point1 i start of the line;
			        // swtich x for for loop condition
			        //temporaryForForLoopCondition = originalPoint0X;
			        originalPoint0Y = point1->y;
			        originalPoint1Y = point0->y;

			        // switch x for drawing
			        x0 = point1->x;
			        y0 = point1->y;

			        if (deltaX > 0) // it is positive slope so it means octan 0 and points in correct order ( incorrect order is octan 4 )
			        {
				        deltaX = point0->x - point1->x;
				        deltaY = point0->y - point1->y;
				        for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
				        {
					        drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
					        y0++;
					        if ((2 * (cumulativeError + deltaX)) > -deltaY)
					        {
						        //y stays the same
						        cumulativeError = cumulativeError + deltaX;
					        }
					        else
					        {
						        x0--;
						        cumulativeError = cumulativeError + deltaX + deltaY;
					        }
				        }
			        }
			        else // it is negitive slope so it means octan 8 and points in "correct order" ( incorrect order is ocatn 3 )
			        {
				        deltaX = point0->x - point1->x;
				        deltaY = point0->y - point1->y;
				        for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
				        {
					        drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
					        y0++;
					        if ((2 * (cumulativeError + deltaX)) < deltaY)
					        {
						        //y stays the same
						        cumulativeError = cumulativeError + deltaX;
					        }
					        else
					        {
						        x0++;
						        cumulativeError = cumulativeError + deltaX - deltaY;
					        }
				        }
			        }
		        }
		        else
		        {
			        if (deltaX > 0) // it is positive slope so it means octan 0 and points in correct order ( incorrect order is octan 4 )
			        {
				        for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
				        {
					        drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
					        y0++;
					        if ((2 * (cumulativeError + deltaX)) < deltaY)
					        {
						        //y stays the same
						        cumulativeError = cumulativeError + deltaX;
					        }
					        else
					        {
						        x0++;
						        cumulativeError = cumulativeError + deltaX - deltaY;
					        }
				        }
			        }
			        else // it is negitive slope so it means octan 8 and points in "correct order" ( incorrect order is ocatn 3 )
			        {
				        for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
				        {
					        drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
					        y0++;
					        if ((2 * (cumulativeError + deltaX)) > -deltaY)
					        {
						        //y stays the same
						        cumulativeError = cumulativeError + deltaX;
					        }
					        else
					        {
						        x0--;
						        cumulativeError = cumulativeError + deltaX + deltaY;
					        }
				        }
			        }
		        }
            }
            if(deltaX == 0) // It is straight line where x is constant. So draw simple line from y0 to y1
            {
                if (copyPoint0->y > copyPoint1->y)
                {
                    swapVectors(copyPoint0, copyPoint1);
                }
                for (int i = copyPoint0->y; i <= copyPoint1->y; i++ )
                {
                    drawPoint(copyPoint0->x, i, pixels, drawingColor, windowDimensions);
                }
            }
            else // deltaY == 0 It is straight line where y is constant. So draw simple line from x0 to x1
            { 
				if (copyPoint0->x > copyPoint1->x)
				{
					swapVectors(copyPoint0, copyPoint1);
				}
				for (int i = copyPoint0->x; i <= copyPoint1->x; i++)
				{
					drawPoint(i, copyPoint0->y, pixels, drawingColor, windowDimensions);
				}
            }
        }
        else
        {
            if (deltaX == 0 && deltaY == 0) // if both are equals 0 just draw point.
            {
                drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
            }
            else
            {
				int absDeltaX = abs(copyPoint1->x - copyPoint0->x);
				// Positive line
                int i = 0;
				if (copyPoint0->x < copyPoint1->x && copyPoint0->y < copyPoint1->y)
				{
					while (i < absDeltaX)
					{
						drawPoint(copyPoint0->x + i, copyPoint0->y + i, pixels, drawingColor, windowDimensions);
						i++;
					}
				}
				if (copyPoint1->x < copyPoint0->x && copyPoint0->y > copyPoint1->y)
				{
                    while (i < absDeltaX)
					{
						drawPoint(copyPoint1->x + i, copyPoint1->y + i, pixels, drawingColor, windowDimensions);
						i++;
					}
				}

				// Negative line
				if (copyPoint0->x < copyPoint1->x && copyPoint0->y > copyPoint1->y)
				{
					while (i < absDeltaX)
					{
						drawPoint(copyPoint0->x + i, copyPoint0->y - i, pixels, drawingColor, windowDimensions);
						i++;
					}
				}
				if (copyPoint1->x < copyPoint0->x && copyPoint1->y > copyPoint0->y)
				{
					while (i < absDeltaX)
					{
						drawPoint(copyPoint1->x + i, copyPoint1->y - i, pixels, drawingColor, windowDimensions);
						i++;
					}
				}
            }
        }

        delete copyPoint0;
        delete copyPoint1;
    }

    void swapVectors(Vector2D<int>*& point0, Vector2D<int>*& point1)
    {
        Vector2D<int>* tmpVector;
        tmpVector = point0;
        point0 = point1;
        point1 = tmpVector;
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
