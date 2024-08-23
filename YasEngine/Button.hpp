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

  void generate() override;
  void generateRegularPolygonVertices(float circumscribedCircleRadius,
                                      int numberOfVertices) override;
  void regeneratePolygon() override;
  void move(float deltaTime) override;

  void setPosition(float x, float y) { GameObject::setPosition(x, y); }

  void setPosition(const Vector2D<float>& position) {
    GameObject::setPosition(position);
  }
};

#endif  // BUTTON_HPP
