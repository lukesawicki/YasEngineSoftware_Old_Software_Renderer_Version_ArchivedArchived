#ifndef INPUTOUTPUTHANDLER_HPP
#define INPUTOUTPUTHANDLER_HPP

namespace YasInOut
{
	struct Input {
		bool left;
		bool right;
		bool up;
		bool down;
		bool shoot;
		bool rotateClocwise;
		bool mouseLeftButton;
	};

	struct MousePositionChangeInformation {
		double x = 0.0;
		double y = 0.0;
		double oldX = 0.0;
		double oldY = 0.0;
		double angle = 0.0;
		bool mouseMoved = false;
		bool leftMouseButton;
		bool rightMouseButton;
	};
}



#endif
