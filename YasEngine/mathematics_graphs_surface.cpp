#include "mathematics_graphs_surface.hpp"

#include "yas_graphics_library.hpp"

void MathematicsGraphsSurface::Render(double& deltaTime) {}

MathematicsGraphsSurface::MathematicsGraphsSurface(
    int x, int y, int width, int height, const Vector4D<Uint8>& default_color) {
  position_.x_ = x;
  position_.y_ = y;
  view_port_sizes_.x_ = width;
  view_port_sizes_.y_ = height;
  pixels_ =
      new Uint8[view_port_sizes_.x_ * view_port_sizes_.y_ * kNumberOfColors];
  ClearColor(default_color);
}

MathematicsGraphsSurface::MathematicsGraphsSurface(
    Vector2D<int> position, int width, int height,
    const Vector4D<Uint8>& default_color) {
  this->position_.x_ = position.x_;
  this->position_.y_ = position.y_;
  view_port_sizes_.x_ = width;
  view_port_sizes_.y_ = height;
  this->pixels_ =
      new Uint8[view_port_sizes_.x_ * view_port_sizes_.y_ * kNumberOfColors];
  ClearColor(default_color);
}

MathematicsGraphsSurface::~MathematicsGraphsSurface() { delete[] pixels_; }

void MathematicsGraphsSurface::ClearColor(const Vector4D<Uint8>& drawing_color) {
  for (int y = 0; y < view_port_sizes_.y_; y++) {
    for (int x = 0; x < view_port_sizes_.x_; x++) {
      pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kRedPosition] =
          drawing_color.x_;
      pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) +
              kGreenPosition] = drawing_color.y_;
      pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kBluePosition] =
          drawing_color.z_;
      pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) +
              kAlphaPosition] = drawing_color.w_;
    }
  }
}

void MathematicsGraphsSurface::DrawPoint(int x, int y,
                                         const Vector4D<Uint8>& drawing_color) {
  CartesianPositionToWindow(x, y);
  if (x >= 0 && x < view_port_sizes_.x_ && y >= 0 && y < view_port_sizes_.y_) {
    pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kRedPosition] =
        drawing_color.x_;
    pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kGreenPosition] =
        drawing_color.y_;
    pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kBluePosition] =
        drawing_color.z_;
    pixels_[kNumberOfColors * (y * view_port_sizes_.x_ + x) + kAlphaPosition] =
        drawing_color.w_;
  }
}

void MathematicsGraphsSurface::DrawLine(const Vector2D<float>& point_0,
                                        const Vector2D<float>& point_1,
                                        const Vector4D<Uint8>& drawing_color) {
  int x0 = static_cast<int>(point_0.x_);
  int y0 = static_cast<int>(point_0.y_);

  int originalPoint0X = static_cast<int>(point_0.x_);
  int originalPoint0Y = static_cast<int>(point_0.y_);

  int originalPoint1X = static_cast<int>(point_1.x_);
  int originalPoint1Y = static_cast<int>(point_1.y_);

  Vector2D<int> copyPoint0(static_cast<int>(point_0.x_),
                           static_cast<int>(point_0.y_));
  Vector2D<int> copyPoint1(static_cast<int>(point_1.x_),
                           static_cast<int>(point_1.y_));

  int deltaX = static_cast<int>(point_1.x_ - point_0.x_);
  int deltaY = static_cast<int>(point_1.y_ - point_0.y_);
  int cumulativeError = 0;

  if (abs(deltaX) != abs(deltaY)) {
    // START GENTLE LINE IF
    if (abs(deltaX) > abs(deltaY)) {
      // DELTAS CONDITION DX > DY

      if (deltaX < 0) {
        // DELTA X < 0 CONDITION (IT MEANS WRONG ORDER)

        originalPoint0X = static_cast<int>(point_1.x_);
        originalPoint1X = static_cast<int>(point_0.x_);

        // switch x_ for drawing
        x0 = static_cast<int>(point_1.x_);
        y0 = static_cast<int>(point_1.y_);

        // NEGATIVE SLOPE)
        if (deltaY > 0) {
          // && (DELTAS CONDITION DX > DY) && (DELTA X < 0 CONDITION) -> IT
          // MEANS OCTAN 3(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
          deltaX = static_cast<int>(point_0.x_ - point_1.x_);
          deltaY = static_cast<int>(point_0.y_ - point_1.y_);
          for (int i = originalPoint0X; i <= originalPoint1X; i++) {
            DrawPoint(x0, y0, drawing_color);
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
            deltaX = static_cast<int>(point_0.x_ - point_1.x_);
            deltaY = static_cast<int>(point_0.y_ - point_1.y_);
            for (int i = originalPoint0X; i <= originalPoint1X; i++) {
              DrawPoint(x0, y0, drawing_color);
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
              DrawPoint(x0, y0, drawing_color);
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
              DrawPoint(x0, y0, drawing_color);
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
            DrawPoint(copyPoint0.x_, i, drawing_color);
          }
        }
      }
    }  // END GENTLE LINE IF
    else {
      // abs(deltaX) < abs(deltaY) // DELTAS CONDITION DX < DY  // STEEP SLOPE
      if (deltaY < 0) {
        // DELTA Y < 0 CONDITION (IT MEANS WRONG ORDER (BECAUSE IN HERE Y IS
        // LEADING AXIES)
        originalPoint0Y = static_cast<int>(point_1.y_);
        originalPoint1Y = static_cast<int>(point_0.y_);

        // switch x_ for drawing
        x0 = static_cast<int>(point_1.x_);
        y0 = static_cast<int>(point_1.y_);

        // NEGATIVE SLOPE
        if (deltaX > 0) {
          // && (DELTAS CONDITION DX < DY) && (DELTA Y < 0 CONDITION) IT MEANS
          // OCTAN 6(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
          deltaX = static_cast<int>(point_0.x_ - point_1.x_);
          deltaY = static_cast<int>(point_0.y_ - point_1.y_);
          for (int i = originalPoint0Y; i <= originalPoint1Y; i++) {
            DrawPoint(x0, y0, drawing_color);
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
          deltaX = static_cast<int>(point_0.x_ - point_1.x_);
          deltaY = static_cast<int>(point_0.y_ - point_1.y_);
          for (int i = originalPoint0Y; i <= originalPoint1Y; i++) {
            DrawPoint(x0, y0, drawing_color);
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
              DrawPoint(x0, y0, drawing_color);
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
              DrawPoint(x0, y0, drawing_color);
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
            DrawPoint(i, copyPoint0.y_, drawing_color);
          }
        }
      }
    }
  } else {
    // deltaX is equals deltaY
    if (deltaX == 0 && deltaY == 0) {
      // if both are equals 0 just draw point.

      DrawPoint(x0, y0, drawing_color);
    } else {
      int absDeltaX = abs(copyPoint1.x_ - copyPoint0.x_);
      // Positive line
      int i = 0;
      if (copyPoint0.x_ < copyPoint1.x_ && copyPoint0.y_ < copyPoint1.y_) {
        while (i < absDeltaX) {
          DrawPoint(copyPoint0.x_ + i, copyPoint0.y_ + i, drawing_color);
          i++;
        }
      }
      if (copyPoint1.x_ < copyPoint0.x_ && copyPoint0.y_ > copyPoint1.y_) {
        while (i < absDeltaX) {
          DrawPoint(copyPoint1.x_ + i, copyPoint1.y_ + i, drawing_color);
          i++;
        }
      }

      // Negative line
      if (copyPoint0.x_ < copyPoint1.x_ && copyPoint0.y_ > copyPoint1.y_) {
        while (i < absDeltaX) {
          DrawPoint(copyPoint0.x_ + i, copyPoint0.y_ - i, drawing_color);
          i++;
        }
      }
      if (copyPoint1.x_ < copyPoint0.x_ && copyPoint1.y_ > copyPoint0.y_) {
        while (i < absDeltaX) {
          DrawPoint(copyPoint1.x_ + i, copyPoint1.y_ - i, drawing_color);
          i++;
        }
      }
    }
  }
}

void MathematicsGraphsSurface::DrawNumbersAsGroupOfLines(
    Vector2D<float>* vertices, int maximum_number_of_vertices,
    int& current_number_of_vertices, const Vector4D<Uint8>& color,
    bool are_lines_continuous) {
  int step = 1;
  if (!are_lines_continuous) {
    step = 2;
  }

  if (current_number_of_vertices > 1) {
    if (current_number_of_vertices <= 3) {
      DrawLine(vertices[0], vertices[1], color);
    } else {
      for (int i = 0; i < current_number_of_vertices; i += step) {
        DrawLine(vertices[i], vertices[i + 1], color);
      }
    }
  }
}

void MathematicsGraphsSurface::DrawPolygon(GameObject* polygon) {}

void MathematicsGraphsSurface::CopyPixelsInToPIxelTable(
    PixelsTable& pixels_table) {
  int posX = position_.x_;
  int posY = position_.y_;

  pixels_table.CartesianPositionToWindow(posX, posY);

  int startPoint =
      kNumberOfColors * (posY * pixels_table.window_dimensions_.x_ + posX);
  int viewportIndex = 0;
  for (int i = 0; i < view_port_sizes_.y_; i++) {
    for (int j = 0; j < view_port_sizes_.x_; j++) {
      pixels_table.pixels_[kNumberOfColors *
                              ((posY + i) * pixels_table.window_dimensions_.x_ +
                               posX + j) +
                          kRedPosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kRedPosition];
      pixels_table.pixels_[kNumberOfColors *
                              ((posY + i) * pixels_table.window_dimensions_.x_ +
                               posX + j) +
                          kGreenPosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kGreenPosition];
      pixels_table.pixels_[kNumberOfColors *
                              ((posY + i) * pixels_table.window_dimensions_.x_ +
                               posX + j) +
                          kBluePosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kBluePosition];
      pixels_table.pixels_[kNumberOfColors *
                              ((posY + i) * pixels_table.window_dimensions_.x_ +
                               posX + j) +
                          kAlphaPosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kAlphaPosition];
      viewportIndex = viewportIndex + 1;
    }
    startPoint = startPoint + view_port_sizes_.x_;
  }
}

void MathematicsGraphsSurface::DrawCartesianAxies() {
  HorizontalLineOnSurface(0, kRed);
  VerticalLineOnSurface(0, kGreen);
}
