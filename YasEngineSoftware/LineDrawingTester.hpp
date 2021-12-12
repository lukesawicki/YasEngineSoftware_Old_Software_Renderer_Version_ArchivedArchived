#ifndef LINEDRAWINGTESTER_HPP
#define LINEDRAWINGTESTER_HPP

#include"YasGraphicsLibrary.hpp"

class LineDrawingTester
{
	public:
		enum class LineSlope { GENTLE, STEEP, HORIZONTAL, VERTICAL };
		enum class PointsOrder { NORMAL, REVERSE };
		enum class PositionInSpace { Q0, Q1, Q2, Q3, Q10, Q23, Q12, Q03, Q123_230, Q12_V, Q10_H };

		LineDrawingTester();
		~LineDrawingTester();

		Vector2D<int>* linePoint0 = nullptr;
		Vector2D<int>* linePoint1 = nullptr;
			
		void prepareTestLines(LineSlope lineSlope, PositionInSpace whichSpace, PointsOrder order, Vector2D<int>* windowDimensions);

	private:
		void modifyTestPoints(Vector2D<int>* point0, Vector2D<int>* point1, int x0Modifier, int y0Modifier, int x1Modifier, int y1Modifier);
};

#endif LINEDRAWINGTESTER_HPP
