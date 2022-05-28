#include"Tile.hpp"

//derived
//Vector2D<int> position;
//Vector2D<int> viewPortSizes;
//Uint8* pixels = nullptr;


Tile::Tile()
{
    position.x = 0;
    position.y = 0;
    viewPortSizes.x = 0;
    viewPortSizes.y = 0;
    pixels = nullptr;
    clearColor(BLACK);
}

Tile::Tile(int x, int y, int width, int height, const Vector4D<Uint8>& defaultColor)
{
	position.x = x;
	position.y = y;
	viewPortSizes.x = width;
	viewPortSizes.y = height;
	pixels = new Uint8[viewPortSizes.x * viewPortSizes.y * NUMBER_OF_COLORS];
    clearColor(defaultColor);
}

Tile::Tile(Vector2D<int> position, int width, int height, const Vector4D<Uint8>& defaultColor)
{
	this->position.x = position.x;
	this->position.y = position.y;
	viewPortSizes.x = width;
	viewPortSizes.y = height;
	this->pixels = new Uint8[viewPortSizes.x * viewPortSizes.y * NUMBER_OF_COLORS];
	clearColor(defaultColor);
}

void Tile::setPositions(int x, int y)
{
    position.x = x;
    position.y = y;
}

void Tile::setSizes(int width, int height)
{
    viewPortSizes.x = width;
    viewPortSizes.y = height;
}

void Tile::setColor(const Vector4D<Uint8>& defaultColor)
{
    clearColor(defaultColor);
}

void Tile::createPixelsTable()
{
    pixels = new Uint8[viewPortSizes.x * viewPortSizes.y * NUMBER_OF_COLORS];
}



Tile::~Tile()
{
	delete[] pixels;
}

void Tile::clearColor(const Vector4D<Uint8>& drawingColor)
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

void Tile::drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor)
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

void Tile::drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor, bool cartesian)
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

void Tile::drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, const Vector4D<Uint8>& drawingColor)
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
                        deltaX = point0.x - point1.x;
                        deltaY = point0.y - point1.y;
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
                    deltaX = point0.x - point1.x;
                    deltaY = point0.y - point1.y;
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

void Tile::drawPolygon(GameObject* polygon)
{
}

void Tile::drawPattern(int pattern, const Vector4D<Uint8>& drawingColor)
{
    switch (pattern)
    {
    case 0:
        drawLeft();
        drawRight();
        break;
    case 1:
        drawTop();
        drawBottom();
        break;
    case 2:
        drawLeft();
        drawBottom();
        drawRightTopCorner();
        break;
    case 3:
        drawLeft();
        drawTop();
        drawRightBottomCorner();
        break;
    case 4:
        drawTop();
        drawRight();
        drawLeftBottomCorner();
        break;
    case 5:
        drawRight();
        drawBottom();
        drawLeftTopCorner();
        break;
    case 6:
        drawRight();
        drawBottom();
        drawLeft();
        break;
    case 7:
        drawTop();
        drawBottom();
        drawLeft();
        break;
    case 8:
        drawTop();
        drawRight();
        drawLeft();
        break;
    case 9:
        drawTop();
        drawRight();
        drawBottom();
        break;
    default:
        ;
    }
}



void Tile::copyPixelsInToPIxelTable(PixelsTable& pixelsTable)
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

void Tile::copyPixelsInToPIxelTable(PixelsTable& pixelsTable, bool cartesian)
{
    int posX = position.x;
    int posY = position.y;// +viewPortSizes.y;

    if (cartesian)
    {
        pixelsTable.cartesianPositionToWindow(posX, posY);
    }

    int startPoint = NUMBER_OF_COLORS * (posY * pixelsTable.windowDimensions.x + posX);
    int viewportIndex = 0;
    for (int i = 0; i < viewPortSizes.y; i++)
    {
        for (int j = 0; j < viewPortSizes.x; j++)
        {
            pixelsTable.pixels[NUMBER_OF_COLORS * ((posY + i) * pixelsTable.windowDimensions.x + posX + j) + RED_POSITION] = pixels[NUMBER_OF_COLORS * (i * viewPortSizes.x + j) + RED_POSITION];// + RED_POSITION];
            pixelsTable.pixels[NUMBER_OF_COLORS * ((posY + i) * pixelsTable.windowDimensions.x + posX + j) + GREEN_POSITION] = pixels[NUMBER_OF_COLORS * (i * viewPortSizes.x + j) + GREEN_POSITION];// + GREEN_POSITION];
            pixelsTable.pixels[NUMBER_OF_COLORS * ((posY + i) * pixelsTable.windowDimensions.x + posX + j) + BLUE_POSITION] = pixels[NUMBER_OF_COLORS * (i * viewPortSizes.x + j) + BLUE_POSITION];// + BLUE_POSITION];
            pixelsTable.pixels[NUMBER_OF_COLORS * ((posY + i) * pixelsTable.windowDimensions.x + posX + j) + ALPHA_POSITION] = pixels[NUMBER_OF_COLORS * (i * viewPortSizes.x + j) + ALPHA_POSITION];// + ALPHA_POSITION];
            viewportIndex = viewportIndex + 1;
        }
        startPoint = startPoint + viewPortSizes.x;
    }
}

void Tile::drawTop()
{
    for(int i = 0; i<6; i++)
    {
        horizontalLineOnViewport(i, BLUE);
    }
}

void Tile::drawRight()
{
    for (int i = 31; i >25; i--)
    {
        verticalLineOnViewport(i, BLUE);
    }
}

void Tile::drawBottom()
{
    for (int i = 31; i > 25; i--)
    {
        horizontalLineOnViewport(i, BLUE);
    }
}

void Tile::drawLeft()
{
    for(int i=0; i<6; i++)
    {
        verticalLineOnViewport(i, BLUE);
    }
}



void Tile::drawLeftTopCorner()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            drawPoint(j, i, BLUE);
        }
    }
}

void Tile::drawRightTopCorner()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 31; j > 25; j--) //int i = 31; i > 25; i--
        {
            drawPoint(j, i, BLUE);
        }
    }
}

void Tile::drawRightBottomCorner()
{
    for (int i = 31; i > 25 ; i--)
    {
        for(int j = 31; j > 31; j--)
        {
            drawPoint(j, i, BLUE);
        }
    }
}
// REMEMBER TO ADD DRAWPOINT FOR ONLY VIEWPORT POSITION
void Tile::drawLeftBottomCorner()
{
    for (int i = 31; i > 25; i--)
    {
        for (int j = 0; j < 6; j++)
        {
            drawPoint(j, i, BLUE);
        }
    }
}
