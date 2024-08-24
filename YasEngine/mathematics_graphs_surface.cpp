#include "mathematics_graphs_surface.hpp"

#include "yas_graphics_library.hpp"

void MathematicsGraphsSurface::render(double& deltaTime) {}

MathematicsGraphsSurface::MathematicsGraphsSurface(
    int x, int y, int width, int height, const Vector4D<Uint8>& defaultColor) {
  position_.x_ = x;
  position_.y_ = y;
  view_port_sizes_.x_ = width;
  view_port_sizes_.y_ = height;
  pixels_ =
      new Uint8[view_port_sizes_.x_ * view_port_sizes_.y_ * kNumberOfColors];
  clearColor(defaultColor);
}

MathematicsGraphsSurface::MathematicsGraphsSurface(
    Vector2D<int> position, int width, int height,
    const Vector4D<Uint8>& defaultColor) {
  this->position_.x_ = position.x_;
  this->position_.y_ = position.y_;
  view_port_sizes_.x_ = width;
  view_port_sizes_.y_ = height;
  this->pixels_ =
      new Uint8[view_port_sizes_.x_ * view_port_sizes_.y_ * kNumberOfColors];
  clearColor(defaultColor);
}

MathematicsGraphsSurface::~MathematicsGraphsSurface() { delete[] pixels_; }

void MathematicsGraphsSurface::clearColor(const Vector4D<Uint8>& drawingColor) {
  for (int y = 0; y < view_port_sizes_.y_; y++) {
    for (int x = 0; x < view_port_sizes_.x_; x++) {
      pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kRedPosition] =
          drawingColor.x_;
      pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) +
              kGreenPosition] = drawingColor.y_;
      pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kBluePosition] =
          drawingColor.z_;
      pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) +
              kAlphaPosition] = drawingColor.w_;
    }
  }
}

void MathematicsGraphsSurface::drawPoint(int x, int y,
                                         const Vector4D<Uint8>& drawingColor) {
  cartesianPositionToWindow(x, y);
  if (x >= 0 && x < view_port_sizes_.x_ && y >= 0 && y < view_port_sizes_.y_) {
    pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kRedPosition] =
        drawingColor.x_;
    pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kGreenPosition] =
        drawingColor.y_;
    pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kBluePosition] =
        drawingColor.z_;
    pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kAlphaPosition] =
        drawingColor.w_;
  }
}

void MathematicsGraphsSurface::drawLine(const Vector2D<float>& point0,
                                        const Vector2D<float>& point1,
                                        const Vector4D<Uint8>& drawingColor) {
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
            drawPoint(x0, y0, drawingColor);
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
              drawPoint(x0, y0, drawingColor);
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
              drawPoint(x0, y0, drawingColor);
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
              drawPoint(x0, y0, drawingColor);
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
            swapVectors(copyPoint0, copyPoint1);
          }
          for (int i = copyPoint0.y_; i <= copyPoint1.y_; i++) {
            drawPoint(copyPoint0.x_, i, drawingColor);
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
            drawPoint(x0, y0, drawingColor);
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
            drawPoint(x0, y0, drawingColor);
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
              drawPoint(x0, y0, drawingColor);
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
              drawPoint(x0, y0, drawingColor);
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
            swapVectors(copyPoint0, copyPoint1);
          }
          for (int i = copyPoint0.x_; i <= copyPoint1.x_; i++) {
            drawPoint(i, copyPoint0.y_, drawingColor);
          }
        }
      }
    }
  } else {
    // deltaX is equals deltaY
    if (deltaX == 0 && deltaY == 0) {
      // if both are equals 0 just draw point.

      drawPoint(x0, y0, drawingColor);
    } else {
      int absDeltaX = abs(copyPoint1.x_ - copyPoint0.x_);
      // Positive line
      int i = 0;
      if (copyPoint0.x_ < copyPoint1.x_ && copyPoint0.y_ < copyPoint1.y_) {
        while (i < absDeltaX) {
          drawPoint(copyPoint0.x_ + i, copyPoint0.y_ + i, drawingColor);
          i++;
        }
      }
      if (copyPoint1.x_ < copyPoint0.x_ && copyPoint0.y_ > copyPoint1.y_) {
        while (i < absDeltaX) {
          drawPoint(copyPoint1.x_ + i, copyPoint1.y_ + i, drawingColor);
          i++;
        }
      }

      // Negative line
      if (copyPoint0.x_ < copyPoint1.x_ && copyPoint0.y_ > copyPoint1.y_) {
        while (i < absDeltaX) {
          drawPoint(copyPoint0.x_ + i, copyPoint0.y_ - i, drawingColor);
          i++;
        }
      }
      if (copyPoint1.x_ < copyPoint0.x_ && copyPoint1.y_ > copyPoint0.y_) {
        while (i < absDeltaX) {
          drawPoint(copyPoint1.x_ + i, copyPoint1.y_ - i, drawingColor);
          i++;
        }
      }
    }
  }
}

void MathematicsGraphsSurface::drawNumbersAsGroupOfLines(
    Vector2D<float>* vertices, int maximumNumberOfVertices,
    int& currentNumberOfVertices, const Vector4D<Uint8>& color,
    bool areLinesContinuos) {
  int step = 1;
  if (!areLinesContinuos) {
    step = 2;
  }

  if (currentNumberOfVertices > 1) {
    if (currentNumberOfVertices <= 3) {
      drawLine(vertices[0], vertices[1], color);
    } else {
      for (int i = 0; i < currentNumberOfVertices; i += step) {
        drawLine(vertices[i], vertices[i + 1], color);
      }
    }
  }
}

void MathematicsGraphsSurface::drawPolygon(GameObject* polygon) {}

void MathematicsGraphsSurface::copyPixelsInToPIxelTable(
    PixelsTable& pixelsTable) {
  int posX = position_.x_;
  int posY = position_.y_;

  pixelsTable.cartesianPositionToWindow(posX, posY);

  int startPoint =
      kNumberOfColors * (posY * pixelsTable.window_dimensions_.x_ + posX);
  int viewportIndex = 0;
  for (int i = 0; i < view_port_sizes_.y_; i++) {
    for (int j = 0; j < view_port_sizes_.x_; j++) {
      pixelsTable.pixels_[kNumberOfColors *
                              ((posY + i) * pixelsTable.window_dimensions_.x_ +
                               posX + j) +
                          kRedPosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kRedPosition];
      pixelsTable.pixels_[kNumberOfColors *
                              ((posY + i) * pixelsTable.window_dimensions_.x_ +
                               posX + j) +
                          kGreenPosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kGreenPosition];
      pixelsTable.pixels_[kNumberOfColors *
                              ((posY + i) * pixelsTable.window_dimensions_.x_ +
                               posX + j) +
                          kBluePosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kBluePosition];
      pixelsTable.pixels_[kNumberOfColors *
                              ((posY + i) * pixelsTable.window_dimensions_.x_ +
                               posX + j) +
                          kAlphaPosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kAlphaPosition];
      viewportIndex = viewportIndex + 1;
    }
    startPoint = startPoint + view_port_sizes_.x_;
  }
}

void MathematicsGraphsSurface::drawCartesianAxies() {
  horizontalLineOnSurface(0, kRed);
  verticalLineOnSurface(0, kGreen);
}
