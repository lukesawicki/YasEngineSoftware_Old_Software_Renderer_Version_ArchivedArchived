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
  position_.x_ = position.x_;
  position_.y_ = position.y_;
  view_port_sizes_.x_ = width;
  view_port_sizes_.y_ = height;
  pixels_ =
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
  int x_0 = static_cast<int>(point_0.x_);
  int y_0 = static_cast<int>(point_0.y_);

  int original_point_0_x = static_cast<int>(point_0.x_);
  int original_point_0_y = static_cast<int>(point_0.y_);

  int original_point_1_x = static_cast<int>(point_1.x_);
  int original_point_1_y = static_cast<int>(point_1.y_);

  Vector2D<int> copy_point_0(static_cast<int>(point_0.x_),
                           static_cast<int>(point_0.y_));
  Vector2D<int> copy_point_1(static_cast<int>(point_1.x_),
                           static_cast<int>(point_1.y_));

  int delta_x = static_cast<int>(point_1.x_ - point_0.x_);
  int delta_y = static_cast<int>(point_1.y_ - point_0.y_);
  int cumulative_error = 0;

  if (abs(delta_x) != abs(delta_y)) {
    // START GENTLE LINE IF
    if (abs(delta_x) > abs(delta_y)) {
      // DELTAS CONDITION DX > DY

      if (delta_x < 0) {
        // DELTA X < 0 CONDITION (IT MEANS WRONG ORDER)

        original_point_0_x = static_cast<int>(point_1.x_);
        original_point_1_x = static_cast<int>(point_0.x_);

        // switch x_ for drawing
        x_0 = static_cast<int>(point_1.x_);
        y_0 = static_cast<int>(point_1.y_);

        // NEGATIVE SLOPE)
        if (delta_y > 0) {
          // && (DELTAS CONDITION DX > DY) && (DELTA X < 0 CONDITION) -> IT
          // MEANS OCTAN 3(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
          delta_x = static_cast<int>(point_0.x_ - point_1.x_);
          delta_y = static_cast<int>(point_0.y_ - point_1.y_);
          for (int i = original_point_0_x; i <= original_point_1_x; i++) {
            DrawPoint(x_0, y_0, drawing_color);
            x_0++;
            if ((2 * (cumulative_error + delta_y)) > -delta_x) {
              // y_ stays the same
              cumulative_error = cumulative_error + delta_y;
            } else {
              y_0--;
              cumulative_error = cumulative_error + delta_y + delta_x;
            }
          }
        } else {
          // POSITIVE SLOPE // (deltaY < 0) && (DELTAS CONDITION DX > DY) &&
          // (DELTA X < 0 CONDITION) -> IT MEANS OCTAN 4(POSITIVE SLOPE, POINTS
          // IN "WRONG ORDER")

          if (delta_x != 0) {
            delta_x = static_cast<int>(point_0.x_ - point_1.x_);
            delta_y = static_cast<int>(point_0.y_ - point_1.y_);
            for (int i = original_point_0_x; i <= original_point_1_x; i++) {
              DrawPoint(x_0, y_0, drawing_color);
              x_0++;
              if ((2 * (cumulative_error + delta_y)) < delta_x) {
                // y_ stays the same
                cumulative_error = cumulative_error + delta_y;
              } else {
                y_0++;
                cumulative_error = cumulative_error + delta_y - delta_x;
              }
            }
          }
        }
      } else {
        // DELTA X > 0 CONDITION  (IT MEANS CORRECT ORDER)

        if (delta_x != 0) {
          // POSITIVE SLOPE
          if (delta_y > 0) {
            // && (DELTAS CONDITION DX > DY) && (DELTA X > 0 CONDITION) -> IT
            // MEANS OCTAN 0(POSITIVE SLOPE, POINTS IN "CORRECT ORDER")

            for (int i = original_point_0_x; i <= original_point_1_x; i++) {
              DrawPoint(x_0, y_0, drawing_color);
              x_0++;
              if ((2 * (cumulative_error + delta_y)) < delta_x) {
                // y_ stays the same
                cumulative_error = cumulative_error + delta_y;
              } else {
                y_0++;
                cumulative_error = cumulative_error + delta_y - delta_x;
              }
            }
          } else {
            // NEGATIVE SLOPE // (deltaY < 0) && (DELTAS CONDITION DX > DY) &&
            // (DELTA X > 0 CONDITION) -> IT MEANS OCTAN 7(NEGATIVE SLOPE,
            // POINTS IN "CORRECT ORDER")
            for (int i = original_point_0_x; i <= original_point_1_x; i++) {
              DrawPoint(x_0, y_0, drawing_color);
              x_0++;
              if ((2 * (cumulative_error + delta_y)) > -delta_x) {
                // y_ stays the same
                cumulative_error = cumulative_error + delta_y;
              } else {
                y_0--;
                cumulative_error = cumulative_error + delta_y + delta_x;
              }
            }
          }
        } else {
          // if (deltaX == 0) // It is straight line where x_ is constant. So
          // draw simple line from y0 to y1
          if (copy_point_0.y_ > copy_point_1.y_) {
            SwapVectors(copy_point_0, copy_point_1);
          }
          for (int i = copy_point_0.y_; i <= copy_point_1.y_; i++) {
            DrawPoint(copy_point_0.x_, i, drawing_color);
          }
        }
      }
    }  // END GENTLE LINE IF
    else {
      // abs(deltaX) < abs(deltaY) // DELTAS CONDITION DX < DY  // STEEP SLOPE
      if (delta_y < 0) {
        // DELTA Y < 0 CONDITION (IT MEANS WRONG ORDER (BECAUSE IN HERE Y IS
        // LEADING AXIES)
        original_point_0_y = static_cast<int>(point_1.y_);
        original_point_1_y = static_cast<int>(point_0.y_);

        // switch x_ for drawing
        x_0 = static_cast<int>(point_1.x_);
        y_0 = static_cast<int>(point_1.y_);

        // NEGATIVE SLOPE
        if (delta_x > 0) {
          // && (DELTAS CONDITION DX < DY) && (DELTA Y < 0 CONDITION) IT MEANS
          // OCTAN 6(NEGATIVE SLOPE, POINTS IN "WRONG ORDER")
          delta_x = static_cast<int>(point_0.x_ - point_1.x_);
          delta_y = static_cast<int>(point_0.y_ - point_1.y_);
          for (int i = original_point_0_y; i <= original_point_1_y; i++) {
            DrawPoint(x_0, y_0, drawing_color);
            y_0++;
            if ((2 * (cumulative_error + delta_x)) > -delta_y) {
              // y_ stays the same
              cumulative_error = cumulative_error + delta_x;
            } else {
              x_0--;
              cumulative_error = cumulative_error + delta_x + delta_y;
            }
          }
        } else {
          // POSITIVE SLOPE  // deltaX < 0 && (DELTAS CONDITION DX < DY) &&
          // (DELTA Y < 0 CONDITION) IT MEANS OCTAN 5(POSITIVE SLOPE, POINTS IN
          // "WRONG ORDER")
          delta_x = static_cast<int>(point_0.x_ - point_1.x_);
          delta_y = static_cast<int>(point_0.y_ - point_1.y_);
          for (int i = original_point_0_y; i <= original_point_1_y; i++) {
            DrawPoint(x_0, y_0, drawing_color);
            y_0++;
            if ((2 * (cumulative_error + delta_x)) < delta_y) {
              // y_ stays the same
              cumulative_error = cumulative_error + delta_x;
            } else {
              x_0++;
              cumulative_error = cumulative_error + delta_x - delta_y;
            }
          }
        }
      } else {
        // DELTA Y > 0 CONDITION  (IT MEANS CORRECT ORDER)
        if (delta_y != 0) {
          // POSITIVE SLOPE
          if (delta_x > 0) {
            // && (DELTAS CONDITION DX < DY) && (DELTA Y > 0 CONDITION) -> IT
            // MEANS OCTAN 1(POSITIVE SLOPE, POINT IN "CORRECT ORDER")

            for (int i = original_point_0_y; i <= original_point_1_y; i++) {
              DrawPoint(x_0, y_0, drawing_color);
              y_0++;
              if ((2 * (cumulative_error + delta_x)) < delta_y) {
                // y_ stays the same
                cumulative_error = cumulative_error + delta_x;
              } else {
                x_0++;
                cumulative_error = cumulative_error + delta_x - delta_y;
              }
            }
          } else {
            // NEGATIVE SLOPE // (deltaX < 0) && (DELTAS CONDITION DX < DY) &&
            // (DELTA Y > 0 CONDITION) -> IT MEANS OCTAN 2(NEGATIVE SLOPE POINTS
            // IN "CORRECT ORDER")
            for (int i = original_point_0_y; i <= original_point_1_y; i++) {
              DrawPoint(x_0, y_0, drawing_color);
              y_0++;
              if ((2 * (cumulative_error + delta_x)) > -delta_y) {
                // y_ stays the same
                cumulative_error = cumulative_error + delta_x;
              } else {
                x_0--;
                cumulative_error = cumulative_error + delta_x + delta_y;
              }
            }
          }
        } else {
          // deltaY == 0 It is straight line where y_ is constant. So draw
          // simple line from x0 to x1
          if (copy_point_0.x_ > copy_point_1.x_) {
            SwapVectors(copy_point_0, copy_point_1);
          }
          for (int i = copy_point_0.x_; i <= copy_point_1.x_; i++) {
            DrawPoint(i, copy_point_0.y_, drawing_color);
          }
        }
      }
    }
  } else {
    // deltaX is equals deltaY
    if (delta_x == 0 && delta_y == 0) {
      // if both are equals 0 just draw point.

      DrawPoint(x_0, y_0, drawing_color);
    } else {
      int absolute_value_of_delta_x = abs(copy_point_1.x_ - copy_point_0.x_);
      // Positive line
      int i = 0;
      if (copy_point_0.x_ < copy_point_1.x_ && copy_point_0.y_ < copy_point_1.y_) {
        while (i < absolute_value_of_delta_x) {
          DrawPoint(copy_point_0.x_ + i, copy_point_0.y_ + i, drawing_color);
          i++;
        }
      }
      if (copy_point_1.x_ < copy_point_0.x_ && copy_point_0.y_ > copy_point_1.y_) {
        while (i < absolute_value_of_delta_x) {
          DrawPoint(copy_point_1.x_ + i, copy_point_1.y_ + i, drawing_color);
          i++;
        }
      }

      // Negative line
      if (copy_point_0.x_ < copy_point_1.x_ && copy_point_0.y_ > copy_point_1.y_) {
        while (i < absolute_value_of_delta_x) {
          DrawPoint(copy_point_0.x_ + i, copy_point_0.y_ - i, drawing_color);
          i++;
        }
      }
      if (copy_point_1.x_ < copy_point_0.x_ && copy_point_1.y_ > copy_point_0.y_) {
        while (i < absolute_value_of_delta_x) {
          DrawPoint(copy_point_1.x_ + i, copy_point_1.y_ - i, drawing_color);
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
  int position_x = position_.x_;
  int position_y = position_.y_;

  pixels_table.CartesianPositionToWindow(position_x, position_y);

  int start_point =
      kNumberOfColors * (position_y * pixels_table.window_dimensions_.x_ + position_x);
  int viewport_index = 0;
  for (int i = 0; i < view_port_sizes_.y_; i++) {
    for (int j = 0; j < view_port_sizes_.x_; j++) {
      pixels_table.pixels_[kNumberOfColors *
                              ((position_y + i) * pixels_table.window_dimensions_.x_ +
                               position_x + j) +
                          kRedPosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kRedPosition];
      pixels_table.pixels_[kNumberOfColors *
                              ((position_y + i) * pixels_table.window_dimensions_.x_ +
                               position_x + j) +
                          kGreenPosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kGreenPosition];
      pixels_table.pixels_[kNumberOfColors *
                              ((position_y + i) * pixels_table.window_dimensions_.x_ +
                               position_x + j) +
                          kBluePosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kBluePosition];
      pixels_table.pixels_[kNumberOfColors *
                              ((position_y + i) * pixels_table.window_dimensions_.x_ +
                               position_x + j) +
                          kAlphaPosition] =
          pixels_[kNumberOfColors * (i * view_port_sizes_.x_ + j) +
                  kAlphaPosition];
      viewport_index = viewport_index + 1;
    }
    start_point = start_point + view_port_sizes_.x_;
  }
}

void MathematicsGraphsSurface::DrawCartesianAxies() {
  HorizontalLineOnSurface(0, kRed);
  VerticalLineOnSurface(0, kGreen);
}
