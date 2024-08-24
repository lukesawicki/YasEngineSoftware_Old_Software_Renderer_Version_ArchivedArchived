#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>

#include "game_object.hpp"

class Button : public GameObject {
 public:
  enum ButtonId { kRestartStart, kQuit, kNone };

  std::string text_;
  int button_width_;
  int button_text_width_;
  int button_height_;
  int vertical_margin_;
  int horizontal_margin_;

  ButtonId button_id_;

  Button(const ButtonId& buttonId, std::string text,
         const Vector4D<Uint8>& color);
  ~Button();

  void Generate() override;
  void GenerateRegularPolygonVertices(float circumscribed_circle_radius,
                                      int number_of_vertices) override;
  void RegeneratePolygon() override;
  void Move(float delta_time) override;

  void set_position(float x, float y) { GameObject::set_position(x, y); }

  void set_position(const Vector2D<float>& position) {
    GameObject::set_position(position);
  }
};

#endif  // BUTTON_HPP
