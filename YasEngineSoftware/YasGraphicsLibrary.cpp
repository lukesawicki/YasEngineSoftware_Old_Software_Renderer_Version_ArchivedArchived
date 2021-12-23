#include"YasGraphicsLibrary.hpp"

namespace YasGL
{

	void prepareTestLines(LineSlope lineSlope, PositionInSpace whichSpace, PointsOrder order, Vector2D<int>*& positivePointA, Vector2D<int>*& positivePointB,Vector2D<int>*& negativePointA, Vector2D<int>*& negativePointB, const Vector2D<int>* windowDimensions)
	{
        int quadrantsWidth = windowDimensions->x / 2;
        int quadrantsHeight = windowDimensions->y / 2;

        // Q1 | Q0
        //---------
        // Q2 | Q3

        switch (lineSlope)
        {
            case LineSlope::GENTLE:
			{
				positivePointA = new Vector2D<int>(10, 5);
				positivePointB = new Vector2D<int>(370, 25);

				negativePointA = new Vector2D<int>(10, 25);
				negativePointB = new Vector2D<int>(370, 5);
                break;
			}

            case LineSlope::STEEP:
		    {
		        positivePointA = new Vector2D<int>(7, 10); //(25, 40);
		        positivePointB = new Vector2D<int>(260, 360);

		        negativePointA = new Vector2D<int>(7, 370); //(25, 40);
		        negativePointB = new Vector2D<int>(260, 10); //(256, 192);

		        int x = 0;
                break;
		    }

			case LineSlope::HORIZONTAL:
			{

                positivePointA = new Vector2D<int>(-30,20);
				positivePointB = new Vector2D<int>(200,20);

				negativePointA = new Vector2D<int>(30, 60);
				negativePointB = new Vector2D<int>(-30, 60);
				break;
			}

			case LineSlope::VERTICAL:
			{
                positivePointA = new Vector2D<int>(-60, 30);
                positivePointB = new Vector2D<int>(-60,-200);
                                                  
				negativePointA = new Vector2D<int>(-10,-100);
				negativePointB = new Vector2D<int>(-10,30);
				break;
			}
            default:
            {
                positivePointA = new Vector2D<int>(10, 5);
                positivePointB = new Vector2D<int>(370, 25);

                negativePointA = new Vector2D<int>(10, 25);
                negativePointB = new Vector2D<int>(370, 5);
                break;
            }
        }

        Vector2D<int>* temporaryVector = nullptr;
        if (order == PointsOrder::REVERSE)
        {
            temporaryVector = positivePointA;
            positivePointA = positivePointB;
            positivePointB = temporaryVector;
            
            temporaryVector = negativePointA;
            negativePointA = negativePointB;
            negativePointB = temporaryVector;
            temporaryVector = nullptr;
        }

        switch (whichSpace)
        {
            case PositionInSpace::Q0:
            {
                if (positivePointA == nullptr && positivePointB == nullptr && negativePointA == nullptr && negativePointB == nullptr)
                {
                    positivePointA = new Vector2D<int>(10, 5);
                    positivePointB = new Vector2D<int>(370, 25);

                    negativePointA = new Vector2D<int>(10, 25);
                    negativePointB = new Vector2D<int>(370, 5);
                }
                break;
            }
            
			case PositionInSpace::Q1:
			{
                modifyTestPoints(positivePointA, positivePointB, negativePointA, negativePointB, -quadrantsWidth, 0, - quadrantsWidth, 0);
                break;
			}
			
			case PositionInSpace::Q2:
			{
				modifyTestPoints(positivePointA, positivePointB, negativePointA, negativePointB, -quadrantsWidth, -quadrantsHeight, -quadrantsWidth, -quadrantsHeight);
                break;
			}
			
			case PositionInSpace::Q3:
			{
				modifyTestPoints(positivePointA, positivePointB, negativePointA, negativePointB, 0, -quadrantsHeight, 0, -quadrantsHeight);
                break;
			}
			
            case PositionInSpace::Q10:
			{
				modifyTestPoints(positivePointA, positivePointB, negativePointA, negativePointB, -quadrantsWidth/2, 0, -quadrantsWidth/2, 0);
                break;
			}
			
            case PositionInSpace::Q23:
			{
				modifyTestPoints(positivePointA, positivePointB, negativePointA, negativePointB, -quadrantsWidth/2, -quadrantsHeight, -quadrantsWidth/2, -quadrantsHeight);
                break;
			}
			
            case PositionInSpace::Q123_230:
            {
                negativePointA->x = negativePointA->x - quadrantsWidth / 2;
                negativePointA->y = negativePointA->y - quadrantsHeight / 18;
				negativePointB->x = negativePointB->x - quadrantsWidth / 2;
				negativePointB->y = negativePointB->y - quadrantsHeight / 18;

				positivePointA->x = positivePointA->x - quadrantsWidth / 2;
				positivePointA->y = positivePointA->y - quadrantsHeight / 18;
				positivePointB->x = positivePointB->x - quadrantsWidth / 2;
				positivePointB->y = positivePointB->y - quadrantsHeight / 18;
                break;
            }


            // Q1 | Q0
            //---------
            // Q2 | Q3
            case PositionInSpace::Q10_H:
            {
			    //positivePointA = new Vector2D<int>(-windowDimensions->x / 2, windowDimensions->y / 2);
			    //positivePointB = new Vector2D<int>(windowDimensions->x / 2, windowDimensions->y / 2);

       //         negativePointB = new Vector2D<int>(-windowDimensions->x / 2, windowDimensions->y / 3);
       //         negativePointB = new Vector2D<int>(windowDimensions->x / 2, windowDimensions->y / 3);
			    break;
            }

            case PositionInSpace::Q12_V:
			{
				//positivePointA = new Vector2D<int>(-windowDimensions->x / 2, windowDimensions->y / 2);
				//positivePointB = new Vector2D<int>(-windowDimensions->x / 2, -windowDimensions->y / 2);

				//negativePointB = new Vector2D<int>(-windowDimensions->x / 2, windowDimensions->y / 3);
				//negativePointB = new Vector2D<int>(-windowDimensions->x / 2, -windowDimensions->y / 3);
				break;
			}

            default:
            {
                // Positive slope
                positivePointA = new Vector2D<int>(10, 5);
                positivePointB = new Vector2D<int>(370, 25);

                // Negative slope
                negativePointA = new Vector2D<int>(10, 25);
                negativePointB = new Vector2D<int>(384, 5);
                break;
            }
        }
	}

    void modifyTestPoints(Vector2D<int>* positivePointA, Vector2D<int>* positivePointB, Vector2D<int>* negativePointA, Vector2D<int>* negativePointB, int positiveXmodifier, int positiveYmodifier, int negativeXmodifier, int negativeYmodifier)
    {
        positivePointA->x = positivePointA->x + positiveXmodifier;
        positivePointA->y = positivePointA->y + positiveYmodifier;
		positivePointB->x = positivePointB->x + positiveXmodifier;
		positivePointB->y = positivePointB->y + positiveYmodifier;

		negativePointA->x = negativePointA->x + negativeXmodifier;
		negativePointA->y = negativePointA->y + negativeYmodifier;
		negativePointB->x = negativePointB->x + negativeXmodifier;
		negativePointB->y = negativePointB->y + negativeYmodifier;
    }

    void deleteTestLines(Vector2D<int>*& positivePointA, Vector2D<int>*& positivePointB, Vector2D<int>*& negativePointA, Vector2D<int>*& negativePointB)
    {
        delete positivePointA;
        delete positivePointB;
        delete negativePointA;
        delete negativePointB;
    }


    void  drawGentleSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, PixelsTable* pixelsTable, Vector4D<uint8_t>* drawingColor)
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
            pixelsTable->drawPoint(i, y, drawingColor);

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

    void drawSteepSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, PixelsTable* pixelsTable, Vector4D<uint8_t>* drawingColor)
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
            pixelsTable->drawPoint(x, i, drawingColor);

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

    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, PixelsTable* pixelsTable, Vector4D<uint8_t>* drawingColor)
    {
        // Check if it is slope line (Octant: 0,3 4,7)
        if (abs(point1->y - point0->y) < abs(point1->x - point0->x))
        {
            if (point0->x > point1->x)
            {
                drawGentleSlopeLine(point1, point0, pixelsTable, drawingColor);
            }
            else
            {
                drawGentleSlopeLine(point0, point1, pixelsTable, drawingColor);
            }
        }
        else // If it is not slope it is steep and these are 1,2,5, 6
        {
            if (point0->y > point1->y)
            {
                drawSteepSlopeLine(point1, point0, pixelsTable, drawingColor);
            }
            else
            {
                drawSteepSlopeLine(point0, point1, pixelsTable, drawingColor);
            }
        }
    }

    void drawNotSteepLine(Vector2D<int>* point0, Vector2D<int>* point1, PixelsTable* pixelsTable, Vector4D<uint8_t>* drawingColor)
    {
		int x0 = point0->x;
		int y0 = point0->y;
		int deltaX = point1->x - point0->x;
		int deltaY = point1->y - point0->y;
		int cumulativeError = 0;

		for (int i = point0->x; i <= point1->x; i++)
		{
			pixelsTable->drawPoint(x0, y0, drawingColor);
			x0++;
			if ( ( 2 * (cumulativeError + deltaY) ) < deltaX)
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

    void lukeDrawLineOctanNEWEST(Vector2D<int>* point0, Vector2D<int>* point1, PixelsTable* pixelsTable, Vector4D<uint8_t>* drawingColor)
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
                            pixelsTable->drawPoint(x0, y0, drawingColor);
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
                            pixelsTable->drawPoint(x0, y0, drawingColor);
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
                            pixelsTable->drawPoint(x0, y0, drawingColor);
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
                            pixelsTable->drawPoint(x0, y0, drawingColor);
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
					        pixelsTable->drawPoint(x0, y0, drawingColor);
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
					        pixelsTable->drawPoint(x0, y0, drawingColor);
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
					        pixelsTable->drawPoint(x0, y0, drawingColor);
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
					        pixelsTable->drawPoint(x0, y0, drawingColor);
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
                    pixelsTable->drawPoint(copyPoint0->x, i, drawingColor);
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
					pixelsTable->drawPoint(i, copyPoint0->y, drawingColor);
				}
            }
        }
        else
        {
            if (deltaX == 0 && deltaY == 0) // if both are equals 0 just draw point.
            {
                pixelsTable->drawPoint(x0, y0, drawingColor);
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
						pixelsTable->drawPoint(copyPoint0->x + i, copyPoint0->y + i, drawingColor);
						i++;
					}
				}
				if (copyPoint1->x < copyPoint0->x && copyPoint0->y > copyPoint1->y)
				{
                    while (i < absDeltaX)
					{
                        pixelsTable->drawPoint(copyPoint1->x + i, copyPoint1->y + i, drawingColor);
						i++;
					}
				}

				// Negative line
				if (copyPoint0->x < copyPoint1->x && copyPoint0->y > copyPoint1->y)
				{
					while (i < absDeltaX)
					{
                        pixelsTable->drawPoint(copyPoint0->x + i, copyPoint0->y - i, drawingColor);
						i++;
					}
				}
				if (copyPoint1->x < copyPoint0->x && copyPoint1->y > copyPoint0->y)
				{
					while (i < absDeltaX)
					{
                        pixelsTable->drawPoint(copyPoint1->x + i, copyPoint1->y - i, drawingColor);
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

    void drawCartesianAxies(PixelsTable* pixelsTable)
    {
        int maxX = static_cast<int>(0.5F * pixelsTable->windowDimensions->x);
        int maxY = static_cast<int>(0.5F * pixelsTable->windowDimensions->y);

        Vector4D<uint8_t> xDrawingColorRed(255,0,0, 0); // RED
        Vector4D<uint8_t> yDrawingColorGreen(0,255,0, 0); // GREEN

        for (int i = -maxX; i < maxX; i++) //X
        {
            pixelsTable->drawPoint(i, 0, &xDrawingColorRed);
        }

        for (int i = -maxY; i < maxY; i++) //Y
        {
            pixelsTable->drawPoint(0, i, &yDrawingColorGreen);
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

    void drawCircle(Vector2D<int>* position, int& radius, PixelsTable* pixelsTable, Vector4D<uint8_t>* drawingColor)
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
                        
            pixelsTable->drawPoint(&circlePixelPosition, drawingColor);
        }
    }
}
