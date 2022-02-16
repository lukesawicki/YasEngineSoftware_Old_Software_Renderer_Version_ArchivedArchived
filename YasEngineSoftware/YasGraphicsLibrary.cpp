#include"YasGraphicsLibrary.hpp"

    void drawLine(const YasVector2D<float>& point0, const YasVector2D<float>& point1, PixelsTable& pixelsTable, const YasVector4D<uint8_t>& drawingColor)
    {
        int x0 = point0.x;
        int y0 = point0.y;

        int originalPoint0X = point0.x;
        int originalPoint0Y = point0.y;

        int originalPoint1X = point1.x;
        int originalPoint1Y = point1.y;

        YasVector2D<int> copyPoint0(point0.x, point0.y);
        YasVector2D<int> copyPoint1(point1.x, point1.y);

        int deltaX = point1.x - point0.x;
        int deltaY = point1.y - point0.y;
        int cumulativeError = 0;

        if (abs(deltaX) != abs(deltaY))
        {
            // START GENTLE LINE IF
            if (abs(deltaX) > abs(deltaY)) // DELTAS CONDITION DX > DY
            {
                if (deltaX < 0) // DELTA X < 0 CONDITION (IT MEANS WRONG ORDER)
                {
                    originalPoint0X = point1.x;
                    originalPoint1X = point0.x;

                    // switch x for drawing
                    x0 = point1.x;
                    y0 = point1.y;

                    // NEGATIVE SLOPE)
                    if (deltaY > 0) // && (DELTAS CONDITION DX > DY) && (DELTA X < 0 CONDITION) -> IT MEANS OCTAN 3(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
                    {
                        deltaX = point0.x - point1.x;
                        deltaY = point0.y - point1.y;
                        for (int i = originalPoint0X; i <= originalPoint1X; i++)
                        {
                            pixelsTable.drawPoint(x0, y0, drawingColor);
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
                            deltaX = point0.x - point1.x;
                            deltaY = point0.y - point1.y;
                            for (int i = originalPoint0X; i <= originalPoint1X; i++)
                            {
                                pixelsTable.drawPoint(x0, y0, drawingColor);
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
                                pixelsTable.drawPoint(x0, y0, drawingColor);
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
                                pixelsTable.drawPoint(x0, y0, drawingColor);
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
							pixelsTable.drawPoint(copyPoint0.x, i, drawingColor);
						}
                    }
                }
            } // END GENTLE LINE IF
            else // abs(deltaX) < abs(deltaY) // DELTAS CONDITION DX < DY  // STEEP SLOPE
            {
                if (deltaY < 0) // DELTA Y < 0 CONDITION (IT MEANS WRONG ORDER (BECAUSE IN HERE Y IS LEADING AXIES)
                {
                    originalPoint0Y = point1.y;
                    originalPoint1Y = point0.y;

                    // switch x for drawing
                    x0 = point1.x;
                    y0 = point1.y;

                    // NEGATIVE SLOPE
                    if (deltaX > 0) // && (DELTAS CONDITION DX < DY) && (DELTA Y < 0 CONDITION) IT MEANS OCTAN 6(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
                    {
                        deltaX = point0.x - point1.x;
                        deltaY = point0.y - point1.y;
                        for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
                        {
                            pixelsTable.drawPoint(x0, y0, drawingColor);
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
                        deltaX = point0.x - point1.x;
                        deltaY = point0.y - point1.y;
                        for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
                        {
                            pixelsTable.drawPoint(x0, y0, drawingColor);
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
                                pixelsTable.drawPoint(x0, y0, drawingColor);
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
                                pixelsTable.drawPoint(x0, y0, drawingColor);
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
                            pixelsTable.drawPoint(i, copyPoint0.y, drawingColor);
                        }
                    }
                }
            }
        }
        else // deltaX is equals deltaY
        {
            if (deltaX == 0 && deltaY == 0) // if both are equals 0 just draw point.
            {
                pixelsTable.drawPoint(x0, y0, drawingColor);
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
                        pixelsTable.drawPoint(copyPoint0.x + i, copyPoint0.y + i, drawingColor);
                        i++;
                    }
                }
                if (copyPoint1.x < copyPoint0.x && copyPoint0.y > copyPoint1.y)
                {
                    while (i < absDeltaX)
                    {
                        pixelsTable.drawPoint(copyPoint1.x + i, copyPoint1.y + i, drawingColor);
                        i++;
                    }
                }

                // Negative line
                if (copyPoint0.x < copyPoint1.x && copyPoint0.y > copyPoint1.y)
                {
                    while (i < absDeltaX)
                    {
                        pixelsTable.drawPoint(copyPoint0.x + i, copyPoint0.y - i, drawingColor);
                        i++;
                    }
                }
                if (copyPoint1.x < copyPoint0.x && copyPoint1.y > copyPoint0.y)
                {
                    while (i < absDeltaX)
                    {
                        pixelsTable.drawPoint(copyPoint1.x + i, copyPoint1.y - i, drawingColor);
                        i++;
                    }
                }
            }
        }
    }

    void drawPolygon(YasPolygon* polygon, PixelsTable& pixelsTable)
    {
        drawLine(polygon->worldVertices[0], polygon->worldVertices[1], pixelsTable, polygon->color);
        for (int i = 0; i < polygon->numberOfVertices; i++)
        {
            if ((i == polygon->numberOfVertices - 1))
            {
                drawLine(polygon->worldVertices[i], polygon->worldVertices[0], pixelsTable, polygon->color);
            }
            else
            {
                drawLine(polygon->worldVertices[i], polygon->worldVertices[i + 1], pixelsTable, polygon->color);
            }
        }
    }

    void drawPolygonDirection(YasPolygon* polygon, PixelsTable& pixelsTable)
    {
        YasVector2D<float> direction(polygon->direction.x*100, polygon->direction.y*100);
        drawLine(polygon->vectorZero, direction, pixelsTable, polygon->color);
    }

    void swapVectors(YasVector2D<int>& point0, YasVector2D<int>& point1)
    {
        //Vector2D<int>* tmpVector;
        int temporaryX = point0.x;
        int temporaryY = point0.y;
        point0.x = point1.x;
        point0.y = point1.y;
        point1.x = temporaryX;
        point1.y = temporaryY;
    }

    void swapVectors(YasVector2D<float>& point0, YasVector2D<float>& point1)
    {
        //Vector2D<int>* tmpVector;
        float temporaryX = point0.x;
        float temporaryY = point0.y;
        point0.x = point1.x;
        point0.y = point1.y;
        point1.x = temporaryX;
        point1.y = temporaryY;
    }

    void drawCartesianAxies(PixelsTable& pixelsTable)
    {
        horizontalLineOnScreen(pixelsTable, 0, RED);
        verticalLineOnScreen(pixelsTable, 0, GREEN);
    }

    void horizontalLineOnScreen(PixelsTable& pixelsTable, int y, YasVector4D<uint8_t> color)
    {
        int maxX = static_cast<int>(0.5F * pixelsTable.windowDimensions.x);
		for (int i = -maxX; i < maxX; i++) //X
		{
			pixelsTable.drawPoint(i, y, color);
		}
    }

	void verticalLineOnScreen(PixelsTable& pixelsTable, int x, YasVector4D<uint8_t> color)
	{
		int maxY = static_cast<int>(0.5F * pixelsTable.windowDimensions.y);
		for (int i = -maxY; i < maxY; i++) //X
		{
			pixelsTable.drawPoint(x, i, color);
		}
	}

    int xyPixelToArrayPosition(int x, int y, int windowWidth)
    {
        return y * windowWidth + x;
    }

    int xyPixelToArrayPosition(YasVector2D<int>& point, int windowWidth)
    {
        return point.y* windowWidth + point.x;
    }

	void windowPositionToCartesianPosition(float& x, float& y, YasVector2D<int>& windowDimensions)
	{
		x = x - static_cast<int>(0.5F * windowDimensions.x);
		y = ( -( y - static_cast<int>(0.5F * windowDimensions.y) ) );
	}


