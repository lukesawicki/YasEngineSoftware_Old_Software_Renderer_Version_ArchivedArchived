#ifndef INPUTOUTPUTHANDLER_HPP
#define INPUTOUTPUTHANDLER_HPP

namespace YasInOut {
struct Input {
  bool left;
  bool right;
  bool up;
  bool down;
  bool shoot;
  bool rotateCounterClockwise;
  bool test_o_button;
};

struct MousePositionChangeInformation {
  double x = 0.0;
  double y = 0.0;
  bool mouseMoved = false;
  bool leftMouseButton;
  bool rightMouseButton;
};
}  // namespace YasInOut

#endif
