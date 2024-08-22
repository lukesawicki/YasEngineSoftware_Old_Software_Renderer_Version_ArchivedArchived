//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

//#include"YasGraphicsLibrary.hpp"
//
//namespace YasGL
//{
//    uint8_t* createPixelsTable(Vector2D<int>* windowDimensions, Vector4D<uint8_t>* defaultColor)
//    {
//    uint8_t* pixels = new uint8_t[windowDimensions->x * windowDimensions->y * NUMBER_OF_COLORS];
//        clearColor(pixels, defaultColor, windowDimensions);
//        return pixels;
//    }
//
//    void clearColor(uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//    {
//        for (int y = 0; y < windowDimensions->y; y++)
//        {
//            for (int x = 0; x < windowDimensions->x; x++)
//            {
//                pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + RED_POSITION] = 0; // windowDimensions->x <- WINDOW WIDTH
//                pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + GREEN_POSITION] = 0;
//                pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + BLUE_POSITION] = 0;
//                pixels[NUMBER_OF_COLORS * (y * windowDimensions->x + x) + ALPHA_POSITION] = 0;
//            }
//        }
//    }
//
//  /// <summary>
//  /// In parameters points has coordinates where point 0,0 is in the middle of screen so
//    /// in this function point position is changing accordingly
//    /// x = x + windowsDimensions.x/2;
//    /// y = y + windowsDimensions.y/2; 
//  /// </summary>
//  /// <param name="point"></param>
//  /// <param name="pixels"></param>
//  /// <param name="drawingColor"></param>
//  /// <param name="windowDimensions"></param>
//  void drawPoint(Vector2D<int>* point, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//  {
//        point->x = point->x + windowDimensions->x * 0.5;
//        point->y = point->y + windowDimensions->y * 0.5;
//    pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + RED_POSITION] = drawingColor->x; // windowDimensions->x <- WINDOW WIDTH
//    pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + GREEN_POSITION] = drawingColor->y;
//    pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + BLUE_POSITION] = drawingColor->z;
//    pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + ALPHA_POSITION] = drawingColor->w;
//  }
//
//  /// <summary>
//    /// In parameters points has coordinates where point 0,0 is in the middle of screen so
//    /// in this function point position is changing accordingly
//    /// x = x + windowsDimensions.x/2;
//    /// y = y + windowsDimensions.y/2; 
//    /// </summary>
//    /// <param name="point"></param>
//    /// <param name="pixels"></param>
//    /// <param name="drawingColor"></param>
//    /// <param name="windowDimensions"></param>
//  void drawPoint(int x, int y, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//  {
//        //x = x + windowDimensions->x * 0.5;
//        //y = y + windowDimensions->y + 0.5;
//    pixels[NUMBER_OF_COLORS * static_cast<int>(y * (1.5*windowDimensions->x) + (x + windowDimensions->x*0.5) ) + RED_POSITION  ] = drawingColor->x; // windowDimensions->x <- WINDOW WIDTH
//    pixels[NUMBER_OF_COLORS * static_cast<int>(y * (1.5*windowDimensions->x) + (x + windowDimensions->x*0.5) ) + GREEN_POSITION] = drawingColor->y;
//    pixels[NUMBER_OF_COLORS * static_cast<int>(y * (1.5*windowDimensions->x) + (x + windowDimensions->x*0.5) ) + BLUE_POSITION ] = drawingColor->z;
//    pixels[NUMBER_OF_COLORS * static_cast<int>(y * (1.5*windowDimensions->x) + (x + windowDimensions->x*0.5) ) + ALPHA_POSITION] = drawingColor->w;
//  }
//
//  /// <summary>
//    /// In parameters points has coordinates where point 0,0 is in the middle of screen so
//    /// in this function point position is changing accordingly
//    /// x = x + windowsDimensions.x/2;
//    /// y = y + windowsDimensions.y/2; 
//    /// </summary>
//    /// <param name="point"></param>
//    /// <param name="pixels"></param>
//    /// <param name="drawingColor"></param>
//    /// <param name="windowDimensions"></param>
//  void drawPoint(Vector2D<int>* point, uint8_t* pixels, uint8_t* drawingColor, Vector2D<int>* windowDimensions)
//  {
//    point->x = point->x + windowDimensions->x * 0.5;
//    point->y = point->y + windowDimensions->y * 0.5;
//    pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + RED_POSITION] = drawingColor[RED_POSITION]; // windowDimensions->x <- WINDOW WIDTH
//    pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + GREEN_POSITION] = drawingColor[GREEN_POSITION];
//    pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + BLUE_POSITION] = drawingColor[BLUE_POSITION];
//    pixels[NUMBER_OF_COLORS * (point->y * windowDimensions->x + point->x) + ALPHA_POSITION] = drawingColor[ALPHA_POSITION];
//  }
//
//    void  drawGentleSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//    {
//        int deltaX = point1->x - point0->x;
//        int deltaY = point1->y - point0->y;
//
//        int yIteration = 1;
//
//        if (deltaY < 0)
//        {
//            yIteration = -1;
//            deltaY = -deltaY;
//        }
//
//        int difference = (2 * deltaY) - deltaX;
//
//        int y = point0->y;
//        
//        
//        for (int i = point0->x; i <= point1->x; i++)
//        {
//            drawPoint(i, y, pixels, drawingColor, windowDimensions);
//
//            if (difference > 0)
//            {
//                y = y + yIteration;
//                difference = difference + (2 * (deltaY - deltaX));
//            }
//            else
//            {
//                difference = difference + 2 * deltaY;
//            }
//        }
//        
//    }
//
//    void drawSteepSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//    {
//        int deltaX = point1->x - point0->x;
//        int deltaY = point1->y - point0->y;
//
//        int xIteration = 1;
//
//        if (deltaX < 0)
//        {
//            xIteration = -1;
//            deltaX = -deltaX;
//        }
//
//        int difference = (2 * deltaX) - deltaY;
//
//        int x = point0->x;
//
//    for (int i = point0->y; i <= point1->y; i++)
//    {
//      drawPoint(x, i, pixels, drawingColor, windowDimensions);
//
//      if (difference > 0)
//      {
//        x = x + xIteration;
//        difference = difference + (2 * (deltaX - deltaY));
//      }
//      else
//      {
//        difference = difference + 2 * deltaX;
//      }
//    }
//    }
//
//    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//    {
//        // Check if it is slope line (Octant: 0,3 4,7)
//        if (abs(point1->y - point0->y) < abs(point1->x - point0->x)) 
//        {
//            if (point0->x > point1->x)
//            {
//                drawGentleSlopeLine(point1, point0, pixels, drawingColor, windowDimensions);
//            }
//            else
//            {
//                drawGentleSlopeLine(point0, point1, pixels, drawingColor, windowDimensions);
//            }
//        }
//        else // If it is not slope it is steep and these are 1,2,5, 6
//        {
//            if (point0->y > point1->y)
//            {
//                drawSteepSlopeLine(point1, point0, pixels, drawingColor, windowDimensions);
//            }
//            else
//            {
//                drawSteepSlopeLine(point0, point1, pixels, drawingColor, windowDimensions);
//            }
//        }
//    }
//
//    void lukeDrawLineOctan0V1(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//    {
//        int x = point0->x;
//        int y = point0->y;
//        float cumulativeError = 0;
//        float slope = static_cast<float>((point1->y - point0->y)) / (point1->x - point0->x);
//        
//        for (int i = point0->x; i <= point1->x; i++)
//        {
//            drawPoint(x, y, pixels, drawingColor, windowDimensions);
//            x++;
//            if (abs(cumulativeError + slope) < 0.5F)
//            {
//                cumulativeError = cumulativeError + slope;
//            }
//            else
//            {
//                y++;
//                cumulativeError = cumulativeError + slope - 1;
//            }
//        }
//    }
//
//    // V2 Has modified equation(lukeDrawLineOctan0V1) (it is multiplied by delta X and then by 2)
//    void lukeDrawLineOctan0V2(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//    {
//        int x0 = point0->x;
//        int y0 = point0->y;
//        int deltaX = point1->x - point0->x;
//        int deltaY = point1->y - point0->y;
//        int cumulativeError = 0;
//        
//        for (int i = point0->x; i <= point1->x; i++)
//        {
//            drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
//            x0++;
//            if ((2*cumulativeError + deltaY) < deltaX)
//            {
//                //y stays the same
//                cumulativeError = cumulativeError + deltaY;
//            }
//            else
//            {
//                y0++;
//                cumulativeError = cumulativeError + deltaY - deltaX;
//            }
//        }
//    }
//
//    void helsinkiDraw(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//    {
//        // https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html
//        int dx = point1->x - point0->x;
//        int dy = point1->y - point0->y;
//        int y = point0->y;
//        int eps = 0;
//    }
//
//    void cartesianPositionToWindow(Vector2D<int>* point, Vector2D<int>* windowDimensions)
//    {
//        point->x = point->x + (windowDimensions->x / 2);
//        point->y = (point->y * -1) + (windowDimensions->y / 2); // point->y = (point->y * -1) + (windowDimensions->y / 2);
//    }
//
//    void windowPositionToCartesian(Vector2D<int>* point, Vector2D<int>* windowDimensions)
//    {
//        point->x = point->x - (windowDimensions->x / 2);
//        point->y = (point->y * -1) + (windowDimensions->y / 2);
//    }
//
//    void drawCartesianAxies(Vector2D<int>* windowDimensions, uint8_t* pixels)
//    {
//        int centerX = windowDimensions->x / 2;
//        int centerY = windowDimensions->y / 2;
//
//        Vector4D<uint8_t> xDrawingColorRed(255,0,0, 0); // RED
//        Vector4D<uint8_t> yDrawingColorGreen(0,255,0, 0); // GREEN
//
//        for (int i = 0; i < windowDimensions->x; i++) //X
//        {
//            drawPoint(i, centerY, pixels, &xDrawingColorRed, windowDimensions);
//        }
//
//        for (int i = 0; i < windowDimensions->y; i++) //Y
//        {
//            drawPoint(centerX, i, pixels, &yDrawingColorGreen, windowDimensions);
//        }
//    }
//
//    int xyPixelToArrayPosition(int x, int y, int windowWidth)
//    {
//        return y * windowWidth + x;
//    }
//
//    int xyPixelToArrayPosition(Vector2D<int>* point, int windowWidth)
//    {
//        return point->y* windowWidth + point->x;
//    }
//
//    void drawCircle(Vector2D<int>* position, int& radius, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//    {
//        int circleX;
//        int circleY;
//        for (int i = 0; i < 360; i++)
//        {
//            circleX = static_cast<int>(position->x + radius * cos(i));
//            circleY = static_cast<int>(position->y + radius * sin(i));
//            Vector2D<int> circlePixelPosition(circleX, circleY);
//                        
//            drawPoint(&circlePixelPosition, pixels, drawingColor, windowDimensions);
//        }
//    }
//}

//-----------------------------------------------------------------------------|---------------------------------------|

////// 20210925
//    // V2 Has modified equation(lukeDrawLineOctan0V1) (it is multiplied by delta X and then by 2)
//    void lukeDrawLineOctan0_V2(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions)
//    { 
//        int x0 = point0->x;
//        int y0 = point0->y;
//        int deltaX = point1->x - point0->x;
//        int deltaY = point1->y - point0->y;
//        int cumulativeError = 0;
//
//        // Check if it is slope line (Octant: 0,3 4,7)
//        //if (abs(point1->y - point0->y) < abs(point1->x - point0->x))
//        //{
//            //if (deltaY > 0)
//            //{
//                for (int i = point0->x; i <= point1->x; i++)
//                {
//                    drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
//                    x0++;
//                    if (2 * (cumulativeError + deltaY) < deltaX)
// {

//                        //y stays the same
//                        cumulativeError = cumulativeError + deltaY;
//                    }
//                    else
// {

//                        y0++;
//                        cumulativeError = cumulativeError + deltaY - deltaX;
//                    }
//                }
//            //}
//            //else
//     //       {
//     //           if (deltaY < 0)
//     //           {
//     //               for (int i = point0->x; i <= point1->x; i++)
//     //               {
//     //                   drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
//     //                   x0++;
//     //                   if (2 * (cumulativeError + deltaY) > -deltaX)
//     //                   {
//     //                       //y stays the same
//     //                       cumulativeError = cumulativeError + deltaY;
//     //                   }
//     //                   else
//     //                   {
//     //                       y0--;
//     //                       cumulativeError = cumulativeError + deltaY + deltaX;
//     //                   }
//     //               }
//     //           }
//     //           else {
//     //               //Horizontal line
//          //if (deltaX > 0)
//          //{
//          //  for (int i = point0->y; i <= point1->y; i++) // int i = point0->x; i <= point1->x; i++
//          //  {
//          //      drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
//          //      y0++; // x0++;
//          //      if (2 * (cumulativeError + deltaX) < deltaY) // cumulativeError + deltaY) < deltaX
//          //      {
//          //          //y stays the same
//          //          cumulativeError = cumulativeError + deltaX; // cumulativeError = cumulativeError + deltaY;
//          //      }
//          //      else
//          //      {
//          //          x0++; // y0++;
//          //          cumulativeError = cumulativeError + deltaX - deltaY; // cumulativeError = cumulativeError + deltaY - deltaX;
//          //      }
//          //  }
//          //}
//          //else
//          //{
//          //  if (deltaX < 0)
//          //  {
//          //      for (int i = point0->y; i <= point1->y; i++) // for (int i = point0->x; i <= point1->x; i++)
//          //      {
//          //          drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
//          //          y0++; // x0++;
//          //          if (2 * (cumulativeError + deltaX) > -deltaY) // if (2 * (cumulativeError + deltaY) > -deltaX)
//          //          {
//          //              //y stays the same
//          //              cumulativeError = cumulativeError + deltaX; // cumulativeError = cumulativeError + deltaY;
//          //          }
//          //          else
//          //          {
//          //              x0--; // y0--;
//          //              cumulativeError = cumulativeError + deltaX + deltaY; // cumulativeError = cumulativeError + deltaY + deltaX;
//          //          }
//          //      }
//          //  }
//          //  else
//          //  {
//          //      //Vertical line
//          //  }
//          //}
//     //           }
//     //       }
//
//
//
//
//        //}
//        //else // If it is not slope it is steep and these are 1,2,5, 6
//        //{
//        //    if (point0->y > point1->y)
//        //    {
//        //        for (int i = point0->y; i <= point1->y; i++) // int i = point0->x; i <= point1->x; i++
//        //        {
//        //            drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
//        //            y0++; // x0++;
//        //            if (2 * (cumulativeError + deltaX) < deltaY) // cumulativeError + deltaY) < deltaX
//        //            {
//        //                //y stays the same
//        //                cumulativeError = cumulativeError + deltaX; // cumulativeError = cumulativeError + deltaY;
//        //            }
//        //            else
//        //            {
//        //                x0++; // y0++;
//        //                cumulativeError = cumulativeError + deltaX - deltaY; // cumulativeError = cumulativeError + deltaY - deltaX;
//        //            }
//        //        }
//        //    }
//        //    else
//        //    {
//        //        if (point0->y < point1->y)
//        //        {
//        //            for (int i = point0->y; i <= point1->y; i++) // for (int i = point0->x; i <= point1->x; i++)
//        //            {
//        //                drawPoint(x0, y0, pixels, drawingColor, windowDimensions);
//        //                y0++; // x0++;
//        //                if (2 * (cumulativeError + deltaX) > -deltaY) // if (2 * (cumulativeError + deltaY) > -deltaX)
//        //                {
//        //                    //y stays the same
//        //                    cumulativeError = cumulativeError + deltaX; // cumulativeError = cumulativeError + deltaY;
//        //                }
//        //                else
//        //                {
//        //                    x0--; // y0--;
//        //                    cumulativeError = cumulativeError + deltaX + deltaY; // cumulativeError = cumulativeError + deltaY + deltaX;
//        //                }
//        //            }
//        //        }
//        //        else
//        //        {
//        //            //Vertical line
//        //        }
//        //    }
//        //}
//    }
// 
// 
//          CIRCLE DRAWING USING MATHEMATIC FORMULA FOR CIRCLE (BAD APROXIMATION FOR RECTANGLE BECAUSE OF PIXELS ARE INTEGER VALUES)
//for (int i = 0; i < 3600; i++)
//{
//circleX = static_cast<int>(position.x + radius * cos(i));
//circleY = static_cast<int>(position.y + radius * sin(i));

//circlePixelPosition.x = circleX;
//circlePixelPosition.y = circleY;

//pixelsTable.drawPoint(circlePixelPosition.x, circlePixelPosition.y, RED);
//}
// 
// 
///// END 20210925





//////////// ROTATION TO MOUSE POSITION //////////////
//////////// IN THIS VERSION ROTATING SIMPLE LINE TO SHOW IN WHICH DIRECTION WILL BE SHOOTING WORKING CORRECTLY BUT OUR OBJECT
//////////// ROTATING LIKE CRAZY RANDOMLY
//void Player::rotateToMousePosition(double oldX, double oldY, double x, double y, YasVector2D<int>* windowDimensions)
//{
//  double currentX = x;
//  double currentY = y;
//  windowPositionToCartesianPosition(currentX, currentY, windowDimensions);
//  YasVector2D<double> mousePositionVector(currentX, currentY);
//  YasVector2D<double>::normalizedVector(mousePositionVector);
//
//
//  directionMouseAngle = atan2f(
//    // uzyc nie diraction a old mouse position
//    (direction.x * mousePositionVector.x + direction.y * mousePositionVector.y),
//    (YasVector2D<double>::getVectorMagnitude(direction) * YasVector2D<double>::getVectorMagnitude(mousePositionVector))
//  );
//
//  oldDirectionMouseAngle = directionMouseAngle;
//
//  //directionMouseAngle = atan2f(
//  // 
//  //  (direction.x * mousePositionVector.x + direction.y * mousePositionVector.y),
//  //  (YasVector2D<double>::getVectorMagnitude(direction) * YasVector2D<double>::getVectorMagnitude(mousePositionVector))
//  //  
//  //);
//
//  direction.x = mousePositionVector.x;
//  direction.y = mousePositionVector.y;
//
//  for (int i = 0; i < numberOfVertices; i++)
//  {
//    float x = localVertices[i].x * cos(directionMouseAngle) - localVertices[i].y * sin(directionMouseAngle);
//    float y = localVertices[i].x * sin(directionMouseAngle) + localVertices[i].y * cos(directionMouseAngle);
//
//    localVertices[i].x = x;
//    localVertices[i].y = y;
//  }
//  generate();
//}

/////////////




//void Player::rotateToMousePosition(float mouseX, float mouseY, YasVector2D<int>& windowDimensions)
//{
//
//  windowPositionToCartesianPosition(mouseX, mouseY, windowDimensions);
//  YasVector2D<float> mousePositionVector(mouseX, mouseY);
//  YasVector2D<float>* normalizedMousePositionVector = YasVector2D<float>::getNormalizedVector(mousePositionVector);
//
//  direction.x = normalizedMousePositionVector->x;
//  direction.y = normalizedMousePositionVector->y;
//
//  generate();
//
//}


//void Player::rotateDirection(double angle)
//{
//  double directionX = direction.x * cos(angle) - direction.y * sin(angle);
//  double directionY = direction.x * sin(angle) + direction.y * cos(angle);
//  direction.x = directionX;
//  direction.y = directionY;
//}



////////////////////
/// OLD GENERATED TILES
// switch (pattern)
// {
// case 0:
//     drawLeft();
//     drawRight();
//     break;
// case 1:
//     drawTop();
//     drawBottom();
//     break;
// case 2:
//     drawLeft();
//     drawBottom();
//     drawRightTopCorner();
//     break;
// case 3:
//     drawLeft();
//     drawTop();
//     drawRightBottomCorner();
//     break;
// case 4:
//     drawTop();
//     drawRight();
//     drawLeftBottomCorner();
//     break;
// case 5:
//     drawRight();
//     drawBottom();
//     drawLeftTopCorner();
//     break;
// case 6:
//     drawRight();
//     drawBottom();
//     drawLeft();
//     break;
// case 7:
//     drawTop();
//     drawBottom();
//     drawLeft();
//     break;
// case 8:
//     drawTop();
//     drawRight();
//     drawLeft();
//     break;
// case 9:
//     drawTop();
//     drawRight();
//     drawBottom();
//     break;
// case 10:
//     drawLeftTopCorner();
//     drawRightTopCorner();
//     drawLeftBottomCorner();
//     drawRightBottomCorner();
//     break;
// default:
//     ;
// }


////////////////////////////////////////////////////////////

//void drawPoints(const std::vector<Vector2D<float>*>& cubePoints, SDL_Renderer* renderer)
//{
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//    for (auto v : cubePoints)
//    {
//        SDL_RenderDrawPoint(renderer, (int)v->x, (int)v->y);
//    }
//}
//
//float calculateY(float x, const Vector2D<float>& point0, const Vector2D<float>& point1)
//{
//    return ((point1.y - point0.y) / point1.x - point0.x) * (x - point0.x) + point0.y;
//}
//
//
//float twoPointsDistance(const Vector2D<float>& point0, const Vector2D<float>& point1)
//{
//    return sqrt(pow(point1.x - point0.x, 2.0) + pow(point1.y - point0.y, 2.0F));
//}
//
//int twoPointsDistance(const Vector2D<int>& point0, const Vector2D<int>& point1)
//{
//    return sqrt(pow(point1.x - point0.x, 2.0) + pow(point1.y - point0.y, 2.0F));
//}

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120
                                        //2021-01-17-1125pm

//void drawBresenhamLine(Vector2D<float>* point0, Vector2D<float>* point1, SDL_Renderer* renderer);
//void drawBresenhamLine20200117_01(Vector2D<float>* point0, Vector2D<float>* point1, SDL_Renderer* renderer);
//void drawBresenhamLine20200117_02(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);

//void drawBresenhamLine(Vector2D<float>* point0, Vector2D<float>* point1, SDL_Renderer* renderer)
//{
//    float deltaX = point1->x - point0->x; // good name is delta or delay
//    float deltaY = point1->y - point0->y;
//
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//
//    float deltaError = 0;
//    if (deltaX != 0)
//    {
//        deltaError = abs(deltaY / deltaX);
//    }
//
//    float error = 0.0F;
//    float y = point0->y;
//
//    for (int i = (int) point0->x; i <= point1->x; i++)
//    {
//        SDL_RenderDrawPoint(renderer, i, y);
//        //pw.setColor(i, (int) y, Color.GREEN);
//        //y = calculateY(i, point0, point1);
//        error = error + deltaError;
//        if (error >= 0.5F)
//        {
//            y = (int) (y + signum(deltaY));
//            error = error - 1;
//        }
//    }
//}
//
//void drawBresenhamLine20200117_01(Vector2D<float>* point0, Vector2D<float>* point1, SDL_Renderer* renderer)
//{
//    float deltaX = point1->x - point0->x;
//    float deltaY = point1->y - point0->y;
//
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//
//    float deltaError = 0;
//    if (deltaX != 0)
//    {
//        deltaError = abs(deltaY / deltaX);
//    }
//
//    float error = 0.0F;
//    float y = point0->y;
//
//    for (int i = (int) point0->x; i <= point1->x; i++)
//    {
//        SDL_RenderDrawPoint(renderer, i, y);
//        //pw.setColor(i, (int) y, Color.GREEN);
//        //y = calculateY(i, point0, point1);
//        error = error + deltaError;
//        if (error >= 0.5F)
//        {
//            y = (int) (y + signum(deltaY));
//            error = error - 1;
//        }
//    }
//}
//
//
////One performance issue is the 1/2 factor in the initial value of D. Since all of this is about the sign
////of the accumulated difference, then everything can be multiplied by 2 with no consequence.
//void drawBresenhamLine20200117_02(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer)
//{
//    int deltaX = point1->x - point0->x;
//    int deltaY = point1->y - point0->y;
//
//    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//
//    float deltaError = 0;
//    deltaError = (2 * deltaY) - deltaX;
//
//    int y = point0->y;
//
//    for (int i = (int) point0->x; i <= point1->x; i++)
//    {
//        SDL_RenderDrawPoint(renderer, i, y);
//        if (deltaError >0)
//        {
//            y = y + 1;
//            deltaError = deltaError - 2*deltaX;
//        }
//        deltaError = deltaError + 2*deltaY;
//    }
//}
// 
// 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //void cartesianPositionToWindow(Vector2D<int>* point, Vector2D<int>* windowDimensions)
    //{
    //    point->x = point->x + (windowDimensions->x / 2);
    //    point->y = (point->y * -1) + (windowDimensions->y / 2); // point->y = (point->y * -1) + (windowDimensions->y / 2);
    //}

    //void windowPositionToCartesian(Vector2D<int>* point, Vector2D<int>* windowDimensions)
    //{
    //    point->x = point->x - (windowDimensions->x / 2);
    //    point->y = (point->y * -1) + (windowDimensions->y / 2);
    //}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void drawCartesianAxies(Vector2D<int>* windowDimensions, uint8_t* pixels)
//{
//  int centerX = static_cast<int>(0.5F * windowDimensions->x);
//  int centerY = static_cast<int>(0.5F * windowDimensions->y);
//
//  Vector4D<uint8_t> xDrawingColorRed(255, 0, 0, 0); // RED
//  Vector4D<uint8_t> yDrawingColorGreen(0, 255, 0, 0); // GREEN
//
//  for (int i = 0; i < windowDimensions->x; i++) //X
//  {
//    drawPoint(i, centerY, pixels, &xDrawingColorRed, windowDimensions);
//  }
//
//  for (int i = 0; i < windowDimensions->y; i++) //Y
//  {
//    drawPoint(centerX, i, pixels, &yDrawingColorGreen, windowDimensions);
//  }
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//int main()
//{
//    SDL_Init(SDL_INIT_VIDEO);
//
//    SDL_Window* window = SDL_CreateWindow("YasEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 240, SDL_WINDOW_RESIZABLE);
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
//
//    int width = 320;
//    int height = 240;
//
//    // Since we are going to display a low resolution buffer,
//    // it is best to limit the window size so that it cannot
//    // be smaller than our internal buffer size.
//    SDL_SetWindowMinimumSize(window, width, height);
//
//    SDL_RenderSetLogicalSize(renderer, width, height);
//    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
//
//    SDL_Texture* screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
//
//    //this->pixels = new Uint8[windowDimensions.x * windowDimensions.y * NUMBER_OF_COLORS];
//    //{
//    //    for (int y = 0; y < windowDimensions.y; y++)
//    //    {
//    //        for (int x = 0; x < windowDimensions.x; x++)
//    //        {
//    //            pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + RED_POSITION] = drawingColor.x; // windowDimensions->x <- WINDOW WIDTH
//    //            pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + GREEN_POSITION] = drawingColor.y;
//    //            pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + BLUE_POSITION] = drawingColor.z;
//    //            pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + ALPHA_POSITION] = drawingColor.w;
//    //        }
//    //    }
//    //}
//
//
//    SDL_SetTextureBlendMode(screenTexture, SDL_BLENDMODE_BLEND);
//
//
//    int pixelsTableSize = width * height * 4;
//
//    Uint8* pixelsTable = new Uint8[pixelsTableSize];
//
//    for (int y = 0; y < height; y++)
//    {
//        for (int x = 0; x < width; x++)
//        {
//            ///0xffffffff
//            //pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + ALPHA_POSITION] = drawingColor.w;
//            pixelsTable[4 * (y * width + x) + 0] = 255;
//            pixelsTable[4 * (y * width + x) + 1] = 255;
//            pixelsTable[4 * (y * width + x) + 2] = 255;
//            pixelsTable[4 * (y * width + x) + 3] = 255;
//        }
//    }
//
//    //Uint8* NEW_RED = new Uint8(0);
//    //Uint8* NEW_GREEN = new Uint8(0);
//    //Uint8* NEW_BLUE = new Uint8(0);
//    //Uint8* ALPHA_OPAQUE = new Uint8(SDL_ALPHA_OPAQUE);
//
//
//
//    Uint8 NEW_RED = 55;
//    Uint8 NEW_GREEN = 55;
//    Uint8 NEW_BLUE = 55;
//    Uint8 ALPHA_OPAQUE = SDL_ALPHA_OPAQUE;
//
//    //SDL_SetRenderDrawColor(renderer, NEW_RED, NEW_GREEN, NEW_BLUE, ALPHA_OPAQUE);
//
//    while (1)
//    {
//        SDL_Event event;
//        while (SDL_PollEvent(&event))
//        {
//            if (event.type == SDL_QUIT) exit(0);
//        }
//
//        for (int y = 0; y < height; y++)
//        {
//            for (int x = 0; x < width; x++)
//            {
//                //pixelsTable[x + y * width] = 0x000000;
//                //pixels[NUMBER_OF_COLORS * (y * windowDimensions.x + x) + ALPHA_POSITION] = drawingColor.w;
//                pixelsTable[4 * (y * width + x) + 0] = 0;
//                pixelsTable[4 * (y * width + x) + 1] = 0;
//                pixelsTable[4 * (y * width + x) + 2] = 0;
//                pixelsTable[4 * (y * width + x) + 3] = 0;
//            }
//        }
//
//        for (int y = 0; y < 50; y++)
//        {
//            for (int x = 0; x < 50; x++)
//            {
//                if (y == x)
//                {
//                    // pixelsTable[x + y * width] = 0xFF000030;
//
//                    pixelsTable[4 * (y * width + x) + 0] = 255;
//                    pixelsTable[4 * (y * width + x) + 1] = 0;
//                    pixelsTable[4 * (y * width + x) + 2] = 0;
//                    pixelsTable[4 * (y * width + x) + 3] = 255;
//                }
//            }
//        }
//        // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//        //SDL_RenderClear(renderer);
//        SDL_UpdateTexture(screenTexture, NULL, pixelsTable, width * 4);
//        SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
//        SDL_RenderPresent(renderer);
//    }
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//float circumscribedCircleRadius; // PL - Promien okrag opisujacego


//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|




    // SECOND TIME I DO CREATING FOUR(4) RANDOM POSITIONS AND PUSH THERE SOME POSITIONS FROM LIST ALL POSITIONS 
    // while(fourRandomPositions.size() < 4) //checksWithTrueResult <= 4)
    // {
    //     srand(clock());
    //     int position = rand() % 16;
    //     for (int i = 0; i < fourRandomPositions.size(); i++)
    //     {
    //         if(//!(playerPosition.firstLevelNode == spawnersPositions.at(i)->firstLevelNode && playerPosition.secondLevelNode == spawnersPositions.at(i)->secondLevelNode) &&
    //            (
    //             (sqrt(pow((spawners->childNodes[fourRandomPositions.at(i)->firstLevelNode]->childNodes[fourRandomPositions.at(i)->secondLevelNode]->position->x -
    //                        spawners->childNodes[spawnersPositions.at(position)->firstLevelNode]->childNodes[spawnersPositions.at(position)->secondLevelNode]->position->x), 2) +
    //
    //                   pow((spawners->childNodes[fourRandomPositions.at(i)->firstLevelNode]->childNodes[fourRandomPositions.at(i)->secondLevelNode]->position->y -
    //                        spawners->childNodes[spawnersPositions.at(position)->firstLevelNode]->childNodes[spawnersPositions.at(position)->secondLevelNode]->position->y), 2)) > quadDiagonal)
    //             )
    //         )
    //         { // TODO check if checksWithResult is 4 then break all loops
    //             // TODO check if position is inside collection
    //             fourRandomPositions.push_back(spawnersPositions.at(position));
    //             checksWithTrueResult++;
    //         }
    //     }
    // }




///////   NAIVE VERSION OF DRAWING LINE BEFORE OPTIMALIZATION AND REFACOTR 2023-11-30   ////////
// REFACTOR AFTER PUBLISHING FIRST GAME "THE BEAUTY OF MATHEMATICS"
//
// void drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, PixelsTable& pixelsTable, const Vector4D<Uint8>& drawingColor)
// {
//     int x0 = static_cast<int>(point0.x);
//     int y0 = static_cast<int>(point0.y);
//
//     int originalPoint0X = static_cast<int>(point0.x);
//     int originalPoint0Y = static_cast<int>(point0.y);
//
//     int originalPoint1X = static_cast<int>(point1.x);
//     int originalPoint1Y = static_cast<int>(point1.y);
//
//     Vector2D<int> copyPoint0(static_cast<int>(point0.x), static_cast<int>(point0.y));
//     Vector2D<int> copyPoint1(static_cast<int>(point1.x), static_cast<int>(point1.y));
//
//     int deltaX = static_cast<int>(point1.x - point0.x);
//     int deltaY = static_cast<int>(point1.y - point0.y);
//     int cumulativeError = 0;
//
//     if (abs(deltaX) != abs(deltaY))
//     {
//         // START GENTLE LINE IF
//         if (abs(deltaX) > abs(deltaY)) // DELTAS CONDITION DX > DY
//         {
//             if (deltaX < 0) // DELTA X < 0 CONDITION (IT MEANS WRONG ORDER)
//             {
//                 originalPoint0X = static_cast<int>(point1.x);
//                 originalPoint1X = static_cast<int>(point0.x);
//
//                 // switch x for drawing
//                 x0 = static_cast<int>(point1.x);
//                 y0 = static_cast<int>(point1.y);
//
//                 // NEGATIVE SLOPE)
//                 if (deltaY > 0) // && (DELTAS CONDITION DX > DY) && (DELTA X < 0 CONDITION) -> IT MEANS OCTAN 3(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
//                 {
//                     deltaX = static_cast<int>(point0.x - point1.x);
//                     deltaY = static_cast<int>(point0.y - point1.y);
//                     for (int i = originalPoint0X; i <= originalPoint1X; i++)
//  {

//                         pixelsTable.drawPoint(x0, y0, drawingColor);
//                         x0++;
//                         if ((2 * (cumulativeError + deltaY)) > -deltaX)
//  {

//                             //y stays the same
//                             cumulativeError = cumulativeError + deltaY;
//                         }
//                         else
//  {

//                             y0--;
//                             cumulativeError = cumulativeError + deltaY + deltaX;
//                         }
//                     }
//                 }
//                 else // POSITIVE SLOPE // (deltaY < 0) && (DELTAS CONDITION DX > DY) && (DELTA X < 0 CONDITION) -> IT MEANS OCTAN 4(POSITIVE SLOPE, POINTS IN "WRONG ORDER")
//                 {
//                     if (deltaX != 0)
//  {

//                         deltaX = static_cast<int>(point0.x - point1.x);
//                         deltaY = static_cast<int>(point0.y - point1.y);
//                         for (int i = originalPoint0X; i <= originalPoint1X; i++)
//  {

//                             pixelsTable.drawPoint(x0, y0, drawingColor);
//                             x0++;
//                             if ((2 * (cumulativeError + deltaY)) < deltaX)
//      {

//                                 //y stays the same
//                                 cumulativeError = cumulativeError + deltaY;
//                             }
//                             else
//      {

//                                 y0++;
//                                 cumulativeError = cumulativeError + deltaY - deltaX;
//                             }
//                         }
//                     }
//                 }
//             }
//             else  // DELTA X > 0 CONDITION  (IT MEANS CORRECT ORDER)
//             {
//
//                 if (deltaX != 0)
//                 {
//                     // POSITIVE SLOPE
//                     if (deltaY > 0)  // && (DELTAS CONDITION DX > DY) && (DELTA X > 0 CONDITION) -> IT MEANS OCTAN 0(POSITIVE SLOPE, POINTS IN "CORRECT ORDER")
//  {

//                         for (int i = originalPoint0X; i <= originalPoint1X; i++)
//  {

//                             pixelsTable.drawPoint(x0, y0, drawingColor);
//                             x0++;
//                             if ((2 * (cumulativeError + deltaY)) < deltaX)
//      {

//                                 //y stays the same
//                                 cumulativeError = cumulativeError + deltaY;
//                             }
//                             else
//      {

//                                 y0++;
//                                 cumulativeError = cumulativeError + deltaY - deltaX;
//                             }
//                         }
//                     }
//                     else  // NEGATIVE SLOPE // (deltaY < 0) && (DELTAS CONDITION DX > DY) && (DELTA X > 0 CONDITION) -> IT MEANS OCTAN 7(NEGATIVE SLOPE, POINTS IN "CORRECT ORDER")
//  {

//                         for (int i = originalPoint0X; i <= originalPoint1X; i++)
//  {

//                             pixelsTable.drawPoint(x0, y0, drawingColor);
//                             x0++;
//                             if ((2 * (cumulativeError + deltaY)) > -deltaX)
//      {

//                                 //y stays the same
//                                 cumulativeError = cumulativeError + deltaY;
//                             }
//                             else
//      {

//                                 y0--;
//                                 cumulativeError = cumulativeError + deltaY + deltaX;
//                             }
//                         }
//                     }
//
//                 }
//                 else //if (deltaX == 0) // It is straight line where x is constant. So draw simple line from y0 to y1
//                 {
//                     if (copyPoint0.y > copyPoint1.y)
//  {

//                         swapVectors(copyPoint0, copyPoint1);
//                     }
//                     for (int i = copyPoint0.y; i <= copyPoint1.y; i++)
//  {

//                         pixelsTable.drawPoint(copyPoint0.x, i, drawingColor);
//                     }
//                 }
//             }
//         } // END GENTLE LINE IF
//         else // abs(deltaX) < abs(deltaY) // DELTAS CONDITION DX < DY  // STEEP SLOPE
//         {
//             if (deltaY < 0) // DELTA Y < 0 CONDITION (IT MEANS WRONG ORDER (BECAUSE IN HERE Y IS LEADING AXIES)
//             {
//                 originalPoint0Y = static_cast<int>(point1.y);
//                 originalPoint1Y = static_cast<int>(point0.y);
//
//                 // switch x for drawing
//                 x0 = static_cast<int>(point1.x);
//                 y0 = static_cast<int>(point1.y);
//
//                 // NEGATIVE SLOPE
//                 if (deltaX > 0) // && (DELTAS CONDITION DX < DY) && (DELTA Y < 0 CONDITION) IT MEANS OCTAN 6(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
//                 {
//                     deltaX = static_cast<int>(point0.x - point1.x);
//                     deltaY = static_cast<int>(point0.y - point1.y);
//                     for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
//  {

//                         pixelsTable.drawPoint(x0, y0, drawingColor);
//                         y0++;
//                         if ((2 * (cumulativeError + deltaX)) > -deltaY)
//  {

//                             //y stays the same
//                             cumulativeError = cumulativeError + deltaX;
//                         }
//                         else
//  {

//                             x0--;
//                             cumulativeError = cumulativeError + deltaX + deltaY;
//                         }
//                     }
//                 }
//                 else // POSITIVE SLOPE  // deltaX < 0 && (DELTAS CONDITION DX < DY) && (DELTA Y < 0 CONDITION) IT MEANS OCTAN 5(POSITIVE SLOPE, POINTS IN "WRONG ORDER")
//                 {
//                     deltaX = static_cast<int>(point0.x - point1.x);
//                     deltaY = static_cast<int>(point0.y - point1.y);
//                     for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
//  {

//                         pixelsTable.drawPoint(x0, y0, drawingColor);
//                         y0++;
//                         if ((2 * (cumulativeError + deltaX)) < deltaY)
//  {

//                             //y stays the same
//                             cumulativeError = cumulativeError + deltaX;
//                         }
//                         else
//  {

//                             x0++;
//                             cumulativeError = cumulativeError + deltaX - deltaY;
//                         }
//                     }
//                 }
//             }
//             else // DELTA Y > 0 CONDITION  (IT MEANS CORRECT ORDER)
//             {
//                 if (deltaY != 0)
//                 {
//                     // POSITIVE SLOPE
//                     if (deltaX > 0) // && (DELTAS CONDITION DX < DY) && (DELTA Y > 0 CONDITION) -> IT MEANS OCTAN 1(POSITIVE SLOPE, POINT IN "CORRECT ORDER")
//  {

//                         for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
//  {

//                             pixelsTable.drawPoint(x0, y0, drawingColor);
//                             y0++;
//                             if ((2 * (cumulativeError + deltaX)) < deltaY)
//      {

//                                 //y stays the same
//                                 cumulativeError = cumulativeError + deltaX;
//                             }
//                             else
//      {

//                                 x0++;
//                                 cumulativeError = cumulativeError + deltaX - deltaY;
//                             }
//                         }
//                     }
//                     else // NEGATIVE SLOPE // (deltaX < 0) && (DELTAS CONDITION DX < DY) && (DELTA Y > 0 CONDITION) -> IT MEANS OCTAN 2(NEGATIVE SLOPE POINTS IN "CORRECT ORDER")
//  {

//                         for (int i = originalPoint0Y; i <= originalPoint1Y; i++)
//  {

//                             pixelsTable.drawPoint(x0, y0, drawingColor);
//                             y0++;
//                             if ((2 * (cumulativeError + deltaX)) > -deltaY)
//      {

//                                 //y stays the same
//                                 cumulativeError = cumulativeError + deltaX;
//                             }
//                             else
//      {

//                                 x0--;
//                                 cumulativeError = cumulativeError + deltaX + deltaY;
//                             }
//                         }
//                     }
//                 }
//                 else // deltaY == 0 It is straight line where y is constant. So draw simple line from x0 to x1
//                 {
//                     if (copyPoint0.x > copyPoint1.x)
//  {

//                         swapVectors(copyPoint0, copyPoint1);
//                     }
//                     for (int i = copyPoint0.x; i <= copyPoint1.x; i++)
//  {

//                         pixelsTable.drawPoint(i, copyPoint0.y, drawingColor);
//                     }
//                 }
//             }
//         }
//     }
//     else // deltaX is equals deltaY
//     {
//         if (deltaX == 0 && deltaY == 0) // if both are equals 0 just draw point.
//         {
//             pixelsTable.drawPoint(x0, y0, drawingColor);
//         }
//         else
//         {
//             int absDeltaX = abs(copyPoint1.x - copyPoint0.x);
//             // Positive line
//             int i = 0;
//             if (copyPoint0.x < copyPoint1.x && copyPoint0.y < copyPoint1.y)
//             {
//                 while (i < absDeltaX)
//                 {
//                     pixelsTable.drawPoint(copyPoint0.x + i, copyPoint0.y + i, drawingColor);
//                     i++;
//                 }
//             }
//             if (copyPoint1.x < copyPoint0.x && copyPoint0.y > copyPoint1.y)
//             {
//                 while (i < absDeltaX)
//                 {
//                     pixelsTable.drawPoint(copyPoint1.x + i, copyPoint1.y + i, drawingColor);
//                     i++;
//                 }
//             }
//
//             // Negative line
//             if (copyPoint0.x < copyPoint1.x && copyPoint0.y > copyPoint1.y)
//             {
//                 while (i < absDeltaX)
//                 {
//                     pixelsTable.drawPoint(copyPoint0.x + i, copyPoint0.y - i, drawingColor);
//                     i++;
//                 }
//             }
//             if (copyPoint1.x < copyPoint0.x && copyPoint1.y > copyPoint0.y)
//             {
//                 while (i < absDeltaX)
//                 {
//                     pixelsTable.drawPoint(copyPoint1.x + i, copyPoint1.y - i, drawingColor);
//                     i++;
//                 }
//             }
//         }
//     }
// }


// OPTIMIZED BY CHATGPT V4
// void drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, PixelsTable& pixelsTable, const Vector4D<Uint8>& drawingColor) {
//     // Use Bresenham's line algorithm for efficient line drawing
//     int x0 = static_cast<int>(point0.x);
//     int y0 = static_cast<int>(point0.y);
//     int x1 = static_cast<int>(point1.x);
//     int y1 = static_cast<int>(point1.y);
//
//     int deltaX = abs(x1 - x0);
//     int deltaY = abs(y1 - y0);
//     int signX = x0 < x1 ? 1 : -1;
//     int signY = y0 < y1 ? 1 : -1;
//     int error = (deltaX > deltaY ? deltaX : -deltaY) / 2, error2;
//
//     while (true) {
//         pixelsTable.drawPoint(x0, y0, drawingColor);
//         if (x0 == x1 && y0 == y1) break;
//         error2 = error;
//         if (error2 > -deltaX) { error -= deltaY; x0 += signX; }
//         if (error2 < deltaY) { error += deltaX; y0 += signY; }
//     }
// }

// In version 1.9.0.1:
//
// 1 : Major revision(new UI, lots of new features, conceptual change, etc.)
//
// 9 : Minor revision(maybe a change to a search box, 1 feature added, collection of bug fixes)
//
// 0 : Bug fix release
//
// 1 : Build number(if used) that's why you see the .NET framework using something like 2.0.4.2709

