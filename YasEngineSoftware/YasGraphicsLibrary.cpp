#include"YasGraphicsLibrary.hpp"

    void drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, PixelsTable& pixelsTable, const Vector4D<Uint8>& drawingColor)
    {
        int x0 = point0.x;
        int y0 = point0.y;

        int originalPoint0X = point0.x;
        int originalPoint0Y = point0.y;

        int originalPoint1X = point1.x;
        int originalPoint1Y = point1.y;

        Vector2D<int> copyPoint0(point0.x, point0.y);
        Vector2D<int> copyPoint1(point1.x, point1.y);

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

    void drawPolygon(GameObject* polygon, PixelsTable& pixelsTable)
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

    int calculateMaximuNumberOfElementsToProcess(const int& primaryMaximum)
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

    Vector2D<float>* generateVerticesFromNumbers(const std::vector<int> &numbers)
    {
        if (numbers.size() < 4)
        {
            return nullptr;
        }
        int numbersSize = numbers.size();
        int maximumNumberOfVertices = numbersSize / 2;

        Vector2D<float>* vertices = new Vector2D<float>[maximumNumberOfVertices];

        int maximum = calculateMaximuNumberOfElementsToProcess(numbersSize);

        int j = 0;
        for (int i = 0; i < maximum; i += 2)
        {
            vertices[j].x = numbers.at(i);
            vertices[j].y = numbers.at(i + 1);
            j++;
        }

        return vertices;
    }

    Vector2D<float>* generateVerticesFromNumbersAsVerticalLines(const std::vector<int>& numbers)
    {
        //if (numbers.size() < 4)
        //{
        //    return nullptr;
        //}
        //int numbersSize = numbers.size();
        int maximumNumberOfVertices = calculateMaximuNumberOfElementsToProcess(numbers.size());

        Vector2D<float>* vertices = new Vector2D<float>[maximumNumberOfVertices];

        for (int i = 0; i < numbers.size(); i++)
        {
            
        }

        //int maximum = calculateMaximuNumberOfElementsToProcess(numbersSize);

        //int j = 0;
        //for (int i = 0; i < maximum; i += 2)
        //{
        //    vertices[j].x = numbers.at(i);
        //    vertices[j].y = numbers.at(i + 1);
        //    j++;
        //}

        return vertices;
    }

    void drawNumbersAsLineSegmentsNotContinuous(Vector2D<float>* vertices, int maximumNumberOfVertices, PixelsTable& pixelsTable)
    {
        if (maximumNumberOfVertices <= 3)
        {
            drawLine(vertices[0], vertices[1], pixelsTable, YELLOW);
        }
        else
        {
            int maximumVerticesToGenerateSegments = calculateMaximuNumberOfElementsToProcess(maximumNumberOfVertices);

            for (int i = 0; i < maximumVerticesToGenerateSegments; i+=2)
            {
                drawLine(vertices[i], vertices[i + 1], pixelsTable, YELLOW);
            }
        }
    }

    void drawNumbersAsPolyline(Vector2D<float>* vertices, int maximumNumberOfVertices, PixelsTable& pixelsTable)
    {
        if (maximumNumberOfVertices == 2)
        {
            drawLine(vertices[0], vertices[1], pixelsTable, YELLOW);
        }
        else
        {
            for (int i = 0; i < maximumNumberOfVertices - 1; i++)
            {
                drawLine(vertices[i], vertices[i + 1], pixelsTable, YELLOW);
            }
        }
    }

    void drawBinaryRepresentationOfFixedNumbers(std::vector<int> numbers, PixelsTable& pixelsTable)
    {
        for (int i = 0; i < numbers.size(); i++)
        {
            std::string str = std::bitset<10>(numbers.at(i)).to_string();
            for (int j = 0; j < 10; j++)
            {
                if (str.at(j) == '1')
                {
                    pixelsTable.drawPoint(j, i, YELLOW);
                }
                else
                {
                    pixelsTable.drawPoint(j, i, BLUE);
                }
            }
            str.clear();
        }
    }

    void drawPolygonDirection(GameObject* polygon, PixelsTable& pixelsTable)
    {
        Vector2D<float> direction(polygon->direction.x*100, polygon->direction.y*100);
        drawLine(polygon->vectorZero, direction, pixelsTable, polygon->color);
    }

    void swapVectors(Vector2D<int>& point0, Vector2D<int>& point1)
    {
        int temporaryX = point0.x;
        int temporaryY = point0.y;
        point0.x = point1.x;
        point0.y = point1.y;
        point1.x = temporaryX;
        point1.y = temporaryY;
    }

    void swapVectors(Vector2D<float>& point0, Vector2D<float>& point1)
    {
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

    void drawCrossHair(float x, float y, PixelsTable& pixelsTable)
    {
        horizontalLineOnScreen(pixelsTable, y, BLUE);
        verticalLineOnScreen(pixelsTable, x, BLUE);
    }

    void horizontalLineOnScreen(PixelsTable& pixelsTable, int y, Vector4D<Uint8> color)
    {
        int maxX = static_cast<int>(0.5F * pixelsTable.windowDimensions.x);
		for (int i = -maxX; i < maxX; i++) //X
		{
			pixelsTable.drawPoint(i, y, color);
		}
    }

	void verticalLineOnScreen(PixelsTable& pixelsTable, int x, Vector4D<Uint8> color)
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

    int xyPixelToArrayPosition(Vector2D<int>& point, int windowWidth)
    {
        return point.y* windowWidth + point.x;
    }

    void windowPositionToCartesianPosition(float& x, float& y, Vector2D<int>* windowDimensions)
    {
        x = x - static_cast<int>(0.5 * windowDimensions->x);
        y = (-(y - static_cast<int>(0.5 * windowDimensions->y)));
    }
