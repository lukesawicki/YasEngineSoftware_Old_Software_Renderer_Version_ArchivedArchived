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

Button::Button(const ButtonId& buttonId, std::string text,
               const Vector4D<Uint8>& color) {
  this->button_id_ = buttonId;
  this->text_.assign(text);
  this->button_text_width_ =
      ScreenWriter::kfont_width * static_cast<int>(text.size());
  this->color_ = color;
  number_of_vertices_ = 4;
}

Button::~Button() {}
