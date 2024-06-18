#include"SurfaceWithMathBasedEffects.hpp"
#include "YasGraphicsLibrary.hpp"
#include "FontSurface.hpp"

FontSurface::FontSurface()
{

}

void FontSurface::initialize(int x, int y, int width, int height, const Vector4D<Uint8>& defaultColor)
{
    position.x = x;
    position.y = y;
    viewPortSizes.x = width;
    viewPortSizes.y = height;
    pixels = new Uint8[viewPortSizes.x * viewPortSizes.y * NUMBER_OF_COLORS];
    clearColor(defaultColor);
}

FontSurface::~FontSurface()
{
    delete[] pixels;
}

void FontSurface::clearColor(const Vector4D<Uint8>& drawingColor)
{
    for (int y = 0; y < viewPortSizes.y; y++)
    {
        for (int x = 0; x < viewPortSizes.x; x++)
        {
            pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + RED_POSITION] = drawingColor.x; // windowDimensions->x <- WINDOW WIDTH
            pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + GREEN_POSITION] = drawingColor.y;
            pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + BLUE_POSITION] = drawingColor.z;
            pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + ALPHA_POSITION] = drawingColor.w;
        }
    }
}

void FontSurface::drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor)
{
    cartesianPositionToWindow(x, y);
    if (x >= 0 && x < viewPortSizes.x && y >= 0 && y < viewPortSizes.y)
    {
        pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + RED_POSITION] = drawingColor.x; // windowDimensions->x <- WINDOW WIDTH
        pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + GREEN_POSITION] = drawingColor.y;
        pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + BLUE_POSITION] = drawingColor.z;
        pixels[NUMBER_OF_COLORS * (y * viewPortSizes.x + x) + ALPHA_POSITION] = drawingColor.w;
    }
}

void FontSurface::drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, const Vector4D<Uint8>& drawingColor)
{
    int x0 = static_cast<int>(point0.x);
    int y0 = static_cast<int>(point0.y);

    int originalPoint0X = static_cast<int>(point0.x);
    int originalPoint0Y = static_cast<int>(point0.y);

    int originalPoint1X = static_cast<int>(point1.x);
    int originalPoint1Y = static_cast<int>(point1.y);

    Vector2D<int> copyPoint0(static_cast<int>(point0.x), static_cast<int>(point0.y));
    Vector2D<int> copyPoint1(static_cast<int>(point1.x), static_cast<int>(point1.y));

    int deltaX = static_cast<int>(point1.x - point0.x);
    int deltaY = static_cast<int>(point1.y - point0.y);
    int cumulativeError = 0;

    if (abs(deltaX) != abs(deltaY))
    {
        // START GENTLE LINE IF
        if (abs(deltaX) > abs(deltaY)) // DELTAS CONDITION DX > DY
        {
            if (deltaX < 0) // DELTA X < 0 CONDITION (IT MEANS WRONG ORDER)
            {
                originalPoint0X = static_cast<int>(point1.x);
                originalPoint1X = static_cast<int>(point0.x);

                // switch x for drawing
                x0 = static_cast<int>(point1.x);
                y0 = static_cast<int>(point1.y);

                // NEGATIVE SLOPE)
                if (deltaY > 0) // && (DELTAS CONDITION DX > DY) && (DELTA X < 0 CONDITION) -> IT MEANS OCTAN 3(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
                {
                    deltaX = static_cast<int>(point0.x - point1.x);
                    deltaY = static_cast<int>(point0.y - point1.y);
                    for (int i = originalPoint0X; i <= originalPoint1X; i++)
                    {
                        drawPoint(x0, y0, drawingColor);
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
                else // POSITIVE SLOPE // (deltaY < 0) && (DELTAS CONDITION DX > DY) && (DELTA X < 0 CONDITION) -> IT MEANS OCTAN 4(POSITIVE SLOPE, POINTS IN "WRONG ORDER")
                {
                    if (deltaX != 0)
                    {
                        deltaX = static_cast<int>(point0.x - point1.x);
                        deltaY = static_cast<int>(point0.y - point1.y);
                        for (int i = originalPoint0X; i <= originalPoint1X; i++)
                        {
                            drawPoint(x0, y0, drawingColor);
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
            }
            else  // DELTA X > 0 CONDITION  (IT MEANS CORRECT ORDER)
            {

                if (deltaX != 0)
                {
                    // POSITIVE SLOPE
                    if (deltaY > 0)  // && (DELTAS CONDITION DX > DY) && (DELTA X > 0 CONDITION) -> IT MEANS OCTAN 0(POSITIVE SLOPE, POINTS IN "CORRECT ORDER")
                    {
                        for (int i = originalPoint0X; i <= originalPoint1X; i++)
                        {
                            drawPoint(x0, y0, drawingColor);
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
                    else  // NEGATIVE SLOPE // (deltaY < 0) && (DELTAS CONDITION DX > DY) && (DELTA X > 0 CONDITION) -> IT MEANS OCTAN 7(NEGATIVE SLOPE, POINTS IN "CORRECT ORDER")
                    {
                        for (int i = originalPoint0X; i <= originalPoint1X; i++)
                        {
                            drawPoint(x0, y0, drawingColor);
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
                else //if (deltaX == 0) // It is straight line where x is constant. So draw simple line from y0 to y1
                {
                    if (copyPoint0.y > copyPoint1.y)
                    {
                        swapVectors(copyPoint0, copyPoint1);
                    }
                    for (int i = copyPoint0.y; i <= copyPoint1.y; i++)
                    {
                        drawPoint(copyPoint0.x, i, drawingColor);
                    }
                }
            }
        } // END GENTLE LINE IF
        else // abs(deltaX) < abs(deltaY) // DELTAS CONDITION DX < DY  // STEEP SLOPE
        {
            if (deltaY < 0) // DELTA Y < 0 CONDITION (IT MEANS WRONG ORDER (BECAUSE IN HERE Y IS LEADING AXIES)
            {
                originalPoint0Y = static_cast<int>(point1.y);
                originalPoint1Y = static_cast<int>(point0.y);

                // switch x for drawing
                x0 = static_cast<int>(point1.x);
                y0 = static_cast<int>(point1.y);

                // NEGATIVE SLOPE
                if (deltaX > 0) // && (DELTAS CONDITION DX < DY) && (DELTA Y < 0 CONDITION) IT MEANS OCTAN 6(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
                {
                    deltaX = static_cast<int>(point0.x - point1.x);
                    deltaY = static_cast<int>(point0.y - point1.y);
                    for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
                    {
                        drawPoint(x0, y0, drawingColor);
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
                else // POSITIVE SLOPE  // deltaX < 0 && (DELTAS CONDITION DX < DY) && (DELTA Y < 0 CONDITION) IT MEANS OCTAN 5(POSITIVE SLOPE, POINTS IN "WRONG ORDER")
                {
                    deltaX = static_cast<int>(point0.x - point1.x);
                    deltaY = static_cast<int>(point0.y - point1.y);
                    for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
                    {
                        drawPoint(x0, y0, drawingColor);
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
            else // DELTA Y > 0 CONDITION  (IT MEANS CORRECT ORDER)
            {
                if (deltaY != 0)
                {
                    // POSITIVE SLOPE
                    if (deltaX > 0) // && (DELTAS CONDITION DX < DY) && (DELTA Y > 0 CONDITION) -> IT MEANS OCTAN 1(POSITIVE SLOPE, POINT IN "CORRECT ORDER")
                    {
                        for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
                        {
                            drawPoint(x0, y0, drawingColor);
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
                    else // NEGATIVE SLOPE // (deltaX < 0) && (DELTAS CONDITION DX < DY) && (DELTA Y > 0 CONDITION) -> IT MEANS OCTAN 2(NEGATIVE SLOPE POINTS IN "CORRECT ORDER")
                    {
                        for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
                        {
                            drawPoint(x0, y0, drawingColor);
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
                else // deltaY == 0 It is straight line where y is constant. So draw simple line from x0 to x1
                {
                    if (copyPoint0.x > copyPoint1.x)
                    {
                        swapVectors(copyPoint0, copyPoint1);
                    }
                    for (int i = copyPoint0.x; i <= copyPoint1.x; i++)
                    {
                        drawPoint(i, copyPoint0.y, drawingColor);
                    }
                }
            }
        }
    }
    else // deltaX is equals deltaY
    {
        if (deltaX == 0 && deltaY == 0) // if both are equals 0 just draw point.
        {
            drawPoint(x0, y0, drawingColor);
        }
        else
        {
            int absDeltaX = abs(copyPoint1.x - copyPoint0.x);
            // Positive line
            int i = 0;
            if (copyPoint0.x < copyPoint1.x && copyPoint0.y < copyPoint1.y)
            {
                while (i < absDeltaX)
                {
                    drawPoint(copyPoint0.x + i, copyPoint0.y + i, drawingColor);
                    i++;
                }
            }
            if (copyPoint1.x < copyPoint0.x && copyPoint0.y > copyPoint1.y)
            {
                while (i < absDeltaX)
                {
                    drawPoint(copyPoint1.x + i, copyPoint1.y + i, drawingColor);
                    i++;
                }
            }

            // Negative line
            if (copyPoint0.x < copyPoint1.x && copyPoint0.y > copyPoint1.y)
            {
                while (i < absDeltaX)
                {
                    drawPoint(copyPoint0.x + i, copyPoint0.y - i, drawingColor);
                    i++;
                }
            }
            if (copyPoint1.x < copyPoint0.x && copyPoint1.y > copyPoint0.y)
            {
                while (i < absDeltaX)
                {
                    drawPoint(copyPoint1.x + i, copyPoint1.y - i, drawingColor);
                    i++;
                }
            }
        }
    }
}

unsigned int FontSurface::calculateMaximumNumberOfElementsToProcess(const unsigned int& primaryMaximum, bool connectedLines)
{
    int maximum = 0;
    if (primaryMaximum % 2 == 0)
    {
        maximum = primaryMaximum - 1;
    }
    else
    {
        maximum = primaryMaximum - 2;
    }
    return maximum;
}

void FontSurface::drawNumbersAsGroupOfLines(Vector2D<float>* vertices, int maximumNumberOfVertices, const Vector4D<Uint8>& color, bool areLinesContinuos)
{
    int step = 1;
    if(!areLinesContinuos)
    {
        step = 2;
    }
    if (maximumNumberOfVertices > 1)
    {
        if (maximumNumberOfVertices <= 3)
        {
            drawLine(vertices[0], vertices[1], color);
        }
        else
        {
            for (int i = 0; i < maximumNumberOfVertices -1; i += step)
            {
                drawLine(vertices[i], vertices[i + 1], color);
            }
        }
    }
}

void FontSurface::drawPolygon(GameObject* polygon)
{
}

void FontSurface::copyPixelsInToPIxelTable(PixelsTable& pixelsTable)
{
    int posX = position.x;
    int posY = position.y + viewPortSizes.y;

    pixelsTable.cartesianPositionToWindow(posX, posY);

    int startPoint = NUMBER_OF_COLORS * (posY * pixelsTable.windowDimensions.x + posX);
    int viewportIndex = 0;
    for (int i = 0; i < viewPortSizes.y; i++)
    {
        for (int j = 0; j < viewPortSizes.x; j++)
        {
            pixelsTable.pixels[NUMBER_OF_COLORS*((posY+i) * pixelsTable.windowDimensions.x + posX+j) + RED_POSITION] =   pixels[NUMBER_OF_COLORS * (i * viewPortSizes.x + j) + RED_POSITION];// + RED_POSITION];
            pixelsTable.pixels[NUMBER_OF_COLORS*((posY+i) * pixelsTable.windowDimensions.x + posX+j) + GREEN_POSITION] = pixels[NUMBER_OF_COLORS * (i * viewPortSizes.x + j) + GREEN_POSITION];// + GREEN_POSITION];
            pixelsTable.pixels[NUMBER_OF_COLORS*((posY+i) * pixelsTable.windowDimensions.x + posX+j) + BLUE_POSITION] =  pixels[NUMBER_OF_COLORS * (i * viewPortSizes.x + j) + BLUE_POSITION];// + BLUE_POSITION];
            pixelsTable.pixels[NUMBER_OF_COLORS*((posY+i) * pixelsTable.windowDimensions.x + posX+j) + ALPHA_POSITION] = pixels[NUMBER_OF_COLORS * (i * viewPortSizes.x + j) + ALPHA_POSITION];// + ALPHA_POSITION];
            viewportIndex = viewportIndex + 1;
        }
        startPoint = startPoint + viewPortSizes.x;
    }
}

void FontSurface::drawCartesianAxies()
{
    horizontalLineOnSurface(0, RED);
    verticalLineOnSurface(0, GREEN);
}
