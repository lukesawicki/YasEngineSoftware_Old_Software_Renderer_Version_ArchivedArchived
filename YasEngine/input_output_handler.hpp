#ifndef INPUTOUTPUTHANDLER_HPP
#define INPUTOUTPUTHANDLER_HPP

namespace YasInOut {
struct Input {
  bool left;
  bool right;
  bool up;
  bool down;
  bool shoot;
  bool rotate_counter_clockwise;
  bool test_o_button;
};

struct MousePositionChangeInformation {
  double x = 0.0;
  double y = 0.0;
  bool mouseMoved = false;
  bool left_mouse_button;
  bool right_mouse_button;
};
}  // namespace YasInOut

#endif
