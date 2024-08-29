#include "button.hpp"

#include "screen_writer.hpp"

void Button::Generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x_ = position.x_ + local_vertices_[i].x_;
    world_vertices_[i].y_ = position.y_ + local_vertices_[i].y_;
  }
}

void Button::GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                            int number_of_vertices) {}

void Button::RegeneratePolygon() { Generate(); }

void Button::Move(float delta_time) {}

Button::Button(const ButtonId& button_id, std::string text,
               const Vector4D<Uint8>& color, ScreenWriter* screen_writer) {
  this->button_id_ = button_id;
  this->text_.assign(text);
  screen_writer_ = screen_writer;
  this->button_text_width_ =
      screen_writer_->kfont_width_ * static_cast<int>(text.size());
  this->color_ = color;
  number_of_vertices_ = 4;
}

Button::~Button() {}
