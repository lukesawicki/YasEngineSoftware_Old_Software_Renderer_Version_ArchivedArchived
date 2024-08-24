#include "yas_graphics_library.hpp"

#include <bitset>

void DrawLine(const Vector2D<float>& point0, const Vector2D<float>& point1,
              PixelsTable& pixelsTable, const Vector4D<Uint8>& drawingColor) {
  int x0 = static_cast<int>(point0.x_);
  int y0 = static_cast<int>(point0.y_);

  int originalPoint0X = static_cast<int>(point0.x_);
  int originalPoint0Y = static_cast<int>(point0.y_);

  int originalPoint1X = static_cast<int>(point1.x_);
  int originalPoint1Y = static_cast<int>(point1.y_);

  Vector2D<int> copyPoint0(static_cast<int>(point0.x_),
                           static_cast<int>(point0.y_));
  Vector2D<int> copyPoint1(static_cast<int>(point1.x_),
                           static_cast<int>(point1.y_));

  int deltaX = static_cast<int>(point1.x_ - point0.x_);
  int deltaY = static_cast<int>(point1.y_ - point0.y_);
  int cumulativeError = 0;

  if (abs(deltaX) != abs(deltaY)) {
    // START GENTLE LINE IF
    if (abs(deltaX) > abs(deltaY)) {
      // DELTAS CONDITION DX > DY
      if (deltaX < 0) {
        // DELTA X < 0 CONDITION (IT MEANS WRONG ORDER)
        originalPoint0X = static_cast<int>(point1.x_);
        originalPoint1X = static_cast<int>(point0.x_);

        // switch x_ for drawing
        x0 = static_cast<int>(point1.x_);
        y0 = static_cast<int>(point1.y_);

        // NEGATIVE SLOPE)
        if (deltaY > 0) {
          // && (DELTAS CONDITION DX > DY) && (DELTA X < 0 CONDITION) -> IT
          // MEANS OCTAN 3(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")

          deltaX = static_cast<int>(point0.x_ - point1.x_);
          deltaY = static_cast<int>(point0.y_ - point1.y_);
          for (int i = originalPoint0X; i <= originalPoint1X; i++) {
            pixelsTable.DrawPoint(x0, y0, drawingColor);
            x0++;
            if ((2 * (cumulativeError + deltaY)) > -deltaX) {
              // y_ stays the same
              cumulativeError = cumulativeError + deltaY;
            } else {
              y0--;
              cumulativeError = cumulativeError + deltaY + deltaX;
            }
          }
        } else {
          // POSITIVE SLOPE // (deltaY < 0) && (DELTAS CONDITION DX > DY) &&
          // (DELTA X < 0 CONDITION) -> IT MEANS OCTAN 4(POSITIVE SLOPE, POINTS
          // IN "WRONG ORDER")

          if (deltaX != 0) {
            deltaX = static_cast<int>(point0.x_ - point1.x_);
            deltaY = static_cast<int>(point0.y_ - point1.y_);
            for (int i = originalPoint0X; i <= originalPoint1X; i++) {
              pixelsTable.DrawPoint(x0, y0, drawingColor);
              x0++;
              if ((2 * (cumulativeError + deltaY)) < deltaX) {
                // y_ stays the same
                cumulativeError = cumulativeError + deltaY;
              } else {
                y0++;
                cumulativeError = cumulativeError + deltaY - deltaX;
              }
            }
          }
        }
      } else {
        // DELTA X > 0 CONDITION  (IT MEANS CORRECT ORDER)
        if (deltaX != 0) {
          // POSITIVE SLOPE
          if (deltaY > 0) {
            // && (DELTAS CONDITION DX > DY) && (DELTA X > 0 CONDITION) -> IT
            // MEANS OCTAN 0(POSITIVE SLOPE, POINTS IN "CORRECT ORDER")
            for (int i = originalPoint0X; i <= originalPoint1X; i++) {
              pixelsTable.DrawPoint(x0, y0, drawingColor);
              x0++;
              if ((2 * (cumulativeError + deltaY)) < deltaX) {
                // y_ stays the same
                cumulativeError = cumulativeError + deltaY;
              } else {
                y0++;
                cumulativeError = cumulativeError + deltaY - deltaX;
              }
            }
          } else {
            // NEGATIVE SLOPE // (deltaY < 0) && (DELTAS CONDITION DX > DY) &&
            // (DELTA X > 0 CONDITION) -> IT MEANS OCTAN 7(NEGATIVE SLOPE,
            // POINTS IN "CORRECT ORDER")
            for (int i = originalPoint0X; i <= originalPoint1X; i++) {
              pixelsTable.DrawPoint(x0, y0, drawingColor);
              x0++;
              if ((2 * (cumulativeError + deltaY)) > -deltaX) {
                // y_ stays the same
                cumulativeError = cumulativeError + deltaY;
              } else {
                y0--;
                cumulativeError = cumulativeError + deltaY + deltaX;
              }
            }
          }
        } else {
          // if (deltaX == 0) // It is straight line where x_ is constant. So
          // draw simple line from y0 to y1
          if (copyPoint0.y_ > copyPoint1.y_) {
            SwapVectors(copyPoint0, copyPoint1);
          }
          for (int i = copyPoint0.y_; i <= copyPoint1.y_; i++) {
            pixelsTable.DrawPoint(copyPoint0.x_, i, drawingColor);
          }
        }
      }
    }  // END GENTLE LINE IF
    else {
      // abs(deltaX) < abs(deltaY) // DELTAS CONDITION DX < DY  // STEEP SLOPE
      if (deltaY < 0) {
        // DELTA Y < 0 CONDITION (IT MEANS WRONG ORDER (BECAUSE IN HERE Y IS
        // LEADING AXIES)
        originalPoint0Y = static_cast<int>(point1.y_);
        originalPoint1Y = static_cast<int>(point0.y_);

        // switch x_ for drawing
        x0 = static_cast<int>(point1.x_);
        y0 = static_cast<int>(point1.y_);

        // NEGATIVE SLOPE
        if (deltaX > 0) {
          // && (DELTAS CONDITION DX < DY) && (DELTA Y < 0 CONDITION) IT MEANS
          // OCTAN 6(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
          deltaX = static_cast<int>(point0.x_ - point1.x_);
          deltaY = static_cast<int>(point0.y_ - point1.y_);
          for (int i = originalPoint0Y; i <= originalPoint1Y; i++) {
            pixelsTable.DrawPoint(x0, y0, drawingColor);
            y0++;
            if ((2 * (cumulativeError + deltaX)) > -deltaY) {
              // y_ stays the same
              cumulativeError = cumulativeError + deltaX;
            } else {
              x0--;
              cumulativeError = cumulativeError + deltaX + deltaY;
            }
          }
        } else {
          // POSITIVE SLOPE  // deltaX < 0 && (DELTAS CONDITION DX < DY) &&
          // (DELTA Y < 0 CONDITION) IT MEANS OCTAN 5(POSITIVE SLOPE, POINTS IN
          // "WRONG ORDER")

          deltaX = static_cast<int>(point0.x_ - point1.x_);
          deltaY = static_cast<int>(point0.y_ - point1.y_);
          for (int i = originalPoint0Y; i <= originalPoint1Y; i++) {
            pixelsTable.DrawPoint(x0, y0, drawingColor);
            y0++;
            if ((2 * (cumulativeError + deltaX)) < deltaY) {
              // y_ stays the same
              cumulativeError = cumulativeError + deltaX;
            } else {
              x0++;
              cumulativeError = cumulativeError + deltaX - deltaY;
            }
          }
        }
      } else {
        // DELTA Y > 0 CONDITION  (IT MEANS CORRECT ORDER)
        if (deltaY != 0) {
          // POSITIVE SLOPE
          if (deltaX > 0) {
            // && (DELTAS CONDITION DX < DY) && (DELTA Y > 0 CONDITION) -> IT
            // MEANS OCTAN 1(POSITIVE SLOPE, POINT IN "CORRECT ORDER")

            for (int i = originalPoint0Y; i <= originalPoint1Y; i++) {
              pixelsTable.DrawPoint(x0, y0, drawingColor);
              y0++;
              if ((2 * (cumulativeError + deltaX)) < deltaY) {
                // y_ stays the same
                cumulativeError = cumulativeError + deltaX;
              } else {
                x0++;
                cumulativeError = cumulativeError + deltaX - deltaY;
              }
            }
          } else {
            // NEGATIVE SLOPE // (deltaX < 0) && (DELTAS CONDITION DX < DY) &&
            // (DELTA Y > 0 CONDITION) -> IT MEANS OCTAN 2(NEGATIVE SLOPE POINTS
            // IN "CORRECT ORDER")
            for (int i = originalPoint0Y; i <= originalPoint1Y; i++) {
              pixelsTable.DrawPoint(x0, y0, drawingColor);
              y0++;
              if ((2 * (cumulativeError + deltaX)) > -deltaY) {
                // y_ stays the same
                cumulativeError = cumulativeError + deltaX;
              } else {
                x0--;
                cumulativeError = cumulativeError + deltaX + deltaY;
              }
            }
          }
        } else {
          // deltaY == 0 It is straight line where y_ is constant. So draw
          // simple line from x0 to x1
          if (copyPoint0.x_ > copyPoint1.x_) {
            SwapVectors(copyPoint0, copyPoint1);
          }
          for (int i = copyPoint0.x_; i <= copyPoint1.x_; i++) {
            pixelsTable.DrawPoint(i, copyPoint0.y_, drawingColor);
          }
        }
      }
    }
  } else {
    // deltaX is equals deltaY
    if (deltaX == 0 && deltaY == 0) {
      // if both are equals 0 just draw point.

      pixelsTable.DrawPoint(x0, y0, drawingColor);
    } else {
      int absDeltaX = abs(copyPoint1.x_ - copyPoint0.x_);
      // Positive line
      int i = 0;
      if (copyPoint0.x_ < copyPoint1.x_ && copyPoint0.y_ < copyPoint1.y_) {
        while (i < absDeltaX) {
          pixelsTable.DrawPoint(copyPoint0.x_ + i, copyPoint0.y_ + i,
                                drawingColor);
          i++;
        }
      }
      if (copyPoint1.x_ < copyPoint0.x_ && copyPoint0.y_ > copyPoint1.y_) {
        while (i < absDeltaX) {
          pixelsTable.DrawPoint(copyPoint1.x_ + i, copyPoint1.y_ + i,
                                drawingColor);
          i++;
        }
      }

      // Negative line
      if (copyPoint0.x_ < copyPoint1.x_ && copyPoint0.y_ > copyPoint1.y_) {
        while (i < absDeltaX) {
          pixelsTable.DrawPoint(copyPoint0.x_ + i, copyPoint0.y_ - i,
                                drawingColor);
          i++;
        }
      }
      if (copyPoint1.x_ < copyPoint0.x_ && copyPoint1.y_ > copyPoint0.y_) {
        while (i < absDeltaX) {
          pixelsTable.DrawPoint(copyPoint1.x_ + i, copyPoint1.y_ - i,
                                drawingColor);
          i++;
        }
      }
    }
  }
}

void DrawPolygon(GameObject* polygon, PixelsTable& pixelsTable) {
  DrawLine(polygon->world_vertices_[0], polygon->world_vertices_[1],
           pixelsTable, polygon->color_);
  for (int i = 0; i < polygon->number_of_vertices_; i++) {
    if ((i == polygon->number_of_vertices_ - 1)) {
      DrawLine(polygon->world_vertices_[i], polygon->world_vertices_[0],
               pixelsTable, polygon->color_);
    } else {
      DrawLine(polygon->world_vertices_[i], polygon->world_vertices_[i + 1],
               pixelsTable, polygon->color_);
    }
  }
}

unsigned int calculateMaximumNumberOfElementsToProcess(
    const unsigned int& primaryMaximum) {
  int maximum = 0;
  if (primaryMaximum % 2 == 0) {
    maximum = primaryMaximum - 1;
  } else {
    maximum = primaryMaximum - 2;
  }
  return maximum;
}

Vector2D<float>* GenerateVerticesFromNumbers(const std::vector<int>& numbers) {
  if (numbers.size() < 4) {
    return nullptr;
  }
  const unsigned int numbersSize = static_cast<unsigned int>(numbers.size());
  const unsigned int maximumNumberOfVertices = numbersSize / 2;

  Vector2D<float>* vertices = new Vector2D<float>[maximumNumberOfVertices];

  const unsigned int maximum = calculateMaximumNumberOfElementsToProcess(
      static_cast<unsigned int>(numbersSize));

  int j = 0;
  for (unsigned int i = 0; i < maximum; i += 2) {
    vertices[j].x_ = static_cast<float>(numbers.at(i));
    vertices[j].y_ = static_cast<float>(numbers.at(i + 1));
    j++;
  }

  return vertices;
}

Vector2D<float>* generateVerticesFromNumbersAsVerticalLines(
    const std::vector<int>& numbers) {
  int maximumNumberOfVertices = calculateMaximumNumberOfElementsToProcess(
      static_cast<int>(numbers.size()));

  Vector2D<float>* vertices = new Vector2D<float>[maximumNumberOfVertices];

  for (int i = 0; i < static_cast<int>(numbers.size()); i++) {
  }

  return vertices;
}

void DrawNumbersAsGroupOfLines(Vector2D<float>* vertices,
                               int maximumNumberOfVertices,
                               const Vector4D<Uint8>& color,
                               bool areLinesContinuos,
                               PixelsTable& pixelsTable) {
  int step = 1;
  if (!areLinesContinuos) {
    step = 2;
  }
  if (maximumNumberOfVertices > 1) {
    if (maximumNumberOfVertices <= 3) {
      DrawLine(vertices[0], vertices[1], pixelsTable, color);
    } else {
      for (int i = 0; i < maximumNumberOfVertices - 1; i += step) {
        DrawLine(vertices[i], vertices[i + 1], pixelsTable, color);
      }
    }
  }
}

void DrawNumbersAsGroupOfLines(Vector2D<float>* vertices,
                               int maximumNumberOfVertices,
                               PixelsTable& pixelsTable) {
  if (maximumNumberOfVertices <= 3) {
    DrawLine(vertices[0], vertices[1], pixelsTable, kYellow);
  } else {
    int maximumVerticesToGenerateSegments =
        calculateMaximumNumberOfElementsToProcess(maximumNumberOfVertices);

    for (int i = 0; i < maximumVerticesToGenerateSegments; i += 2) {
      DrawLine(vertices[i], vertices[i + 1], pixelsTable, kYellow);
    }
  }
}

void DrawNumbersAsPolyline(Vector2D<float>* vertices,
                           int maximumNumberOfVertices,
                           PixelsTable& pixelsTable) {
  if (maximumNumberOfVertices == 2) {
    DrawLine(vertices[0], vertices[1], pixelsTable, kYellow);
  } else {
    for (int i = 0; i < maximumNumberOfVertices - 1; i++) {
      DrawLine(vertices[i], vertices[i + 1], pixelsTable, kYellow);
    }
  }
}

void drawBinaryRepresentationOfFixedNumbers(std::vector<int> numbers,
                                            PixelsTable& pixelsTable) {
  for (unsigned int i = 0; i < static_cast<unsigned int>(numbers.size()); i++) {
    std::string str = std::bitset<10>(numbers.at(i)).to_string();
    for (int j = 0; j < 10; j++) {
      if (str.at(j) == '1') {
        pixelsTable.DrawPoint(j, i, kYellow);
      } else {
        pixelsTable.DrawPoint(j, i, kBlue);
      }
    }
    str.clear();
  }
}

void DrawPolygonDirection(GameObject* polygon, PixelsTable& pixelsTable) {
  Vector2D<float> direction(polygon->direction_.x_ * 100,
                            polygon->direction_.y_ * 100);
  DrawLine(polygon->vector_zero_, direction, pixelsTable, polygon->color_);
}

void SwapVectors(Vector2D<int>& point0, Vector2D<int>& point1) {
  int temporaryX = point0.x_;
  int temporaryY = point0.y_;
  point0.x_ = point1.x_;
  point0.y_ = point1.y_;
  point1.x_ = temporaryX;
  point1.y_ = temporaryY;
}

void SwapVectors(Vector2D<float>& point0, Vector2D<float>& point1) {
  float temporaryX = point0.x_;
  float temporaryY = point0.y_;
  point0.x_ = point1.x_;
  point0.y_ = point1.y_;
  point1.x_ = temporaryX;
  point1.y_ = temporaryY;
}

void DrawCartesianAxies(PixelsTable& pixelsTable) {
  HorizontalLineOnWholeScreen(pixelsTable, 0, kRed);
  VerticalLineOnWholeScreen(pixelsTable, 0, kGreen);
}

void DrawCrossHair(float x, float y, PixelsTable& pixelsTable,
                   bool isFullScreen) {
  DrawCrossHair(x, y, pixelsTable, isFullScreen, kGreen);
}

void DrawCrossHair(float x, float y, PixelsTable& pixelsTable,
                   bool isFullScreen, Vector4D<Uint8> color) {
  if (isFullScreen) {
    HorizontalLineOnWholeScreen(pixelsTable, static_cast<int>(y), kBlue);
    VerticalLineOnWholeScreen(pixelsTable, static_cast<int>(x), kBlue);
  } else {
    // TODO refactor methods drawHor... and drawVer... should have float
    // arguments and then round and cast
    DrawHorizontalLine(pixelsTable, static_cast<int>(round(x) - 15),
                       static_cast<int>(round(x) - 5),
                       static_cast<int>(round(y)), color);
    DrawHorizontalLine(pixelsTable, static_cast<int>(round(x) + 5),
                       static_cast<int>(round(x) + 15),
                       static_cast<int>(round(y)), color);

    DrawVerticalLine(pixelsTable, static_cast<int>(round(y) - 15),
                     static_cast<int>(round(y) - 5), static_cast<int>(round(x)),
                     color);
    DrawVerticalLine(pixelsTable, static_cast<int>(round(y) + 5),
                     static_cast<int>(round(y) + 15),
                     static_cast<int>(round(x)), color);
  }
}

void DrawHorizontalLine(PixelsTable& pixelsTable, int x0, int x1, int y,
                        Vector4D<Uint8> color) {
  for (int i = x0; i < x1; i++) {
    pixelsTable.DrawPoint(i, y, color);
  }
}

void DrawVerticalLine(PixelsTable& pixelsTable, int y0, int y1, int x,
                      Vector4D<Uint8> color) {
  if (y0 > y1) {
    int tmp = y0;
    y0 = y1;
    y1 = tmp;
  }
  for (int i = y0; i < y1; i++) {
    pixelsTable.DrawPoint(x, i, color);
  }
}

void HorizontalLineOnWholeScreen(PixelsTable& pixelsTable, int y,
                                 Vector4D<Uint8> color) {
  int maxX = static_cast<int>(0.5F * pixelsTable.window_dimensions_.x_);
  for (int i = -maxX; i < maxX; i++) {
    // X

    pixelsTable.DrawPoint(i, y, color);
  }
}

void VerticalLineOnWholeScreen(PixelsTable& pixelsTable, int x,
                               Vector4D<Uint8> color) {
  int maxY = static_cast<int>(0.5F * pixelsTable.window_dimensions_.y_);
  for (int i = -maxY; i < maxY; i++) {
    // X

    pixelsTable.DrawPoint(x, i, color);
  }
}

int ScreenPixelPositionToArrayPosition(int x, int y, int windowWidth) {
  return y * windowWidth + x;
}

int ScreenPixelPositionToArrayPosition(Vector2D<int>& point, int windowWidth) {
  return point.y_ * windowWidth + point.x_;
}

void WindowPositionToCartesianPosition(float& x, float& y,
                                       Vector2D<int>* windowDimensions) {
  x = x - static_cast<int>(0.5 * windowDimensions->x_);
  y = (-(y - static_cast<int>(0.5 * windowDimensions->y_)));
}

void DrawMandelbrotSet() {}

void DrawRectangle(PixelsTable& pixelsTable, int x, int y, int width,
                   int height, Vector4D<Uint8> color) {
  int posX = x;
  int posY = y;

  pixelsTable.CartesianPositionToWindow(posX, posY);

  int startPoint =
      kNumberOfColors * (posY * pixelsTable.window_dimensions_.x_ + posX);
  int viewportIndex = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      pixelsTable.pixels_[kNumberOfColors *
                              ((posY + i) * pixelsTable.window_dimensions_.x_ +
                               posX + j) +
                          kRedPosition] = color.x_;  // + kRedPosition];
      pixelsTable.pixels_[kNumberOfColors *
                              ((posY + i) * pixelsTable.window_dimensions_.x_ +
                               posX + j) +
                          kGreenPosition] = color.y_;  // + kGreenPosition];
      pixelsTable.pixels_[kNumberOfColors *
                              ((posY + i) * pixelsTable.window_dimensions_.x_ +
                               posX + j) +
                          kBluePosition] = color.z_;  // + kBluePosition];
      pixelsTable.pixels_[kNumberOfColors *
                              ((posY + i) * pixelsTable.window_dimensions_.x_ +
                               posX + j) +
                          kAlphaPosition] = color.w_;  // + kAlphaPosition];
      viewportIndex = viewportIndex + 1;
    }
    startPoint = startPoint + width;
  }
}
