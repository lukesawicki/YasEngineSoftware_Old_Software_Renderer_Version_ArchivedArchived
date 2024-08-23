#include "button.hpp"

#include "screen_writer.hpp"

void Button::generate() {
  for (int i = 0; i < number_of_vertices_; i++) {
    world_vertices_[i].x = position.x + local_vertices_[i].x;
    world_vertices_[i].y = position.y + local_vertices_[i].y;
  }
}

void Button::generateRegularPolygonVertices(float circumscribedCircleRadius,
                                            int numberOfVertices) {}

void Button::regeneratePolygon() { generate(); }

void Button::Move(float deltaTime) {}

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
