#include"LineDrawingTester.hpp"

LineDrawingTester::LineDrawingTester()
{
	Vector2D<int>* line45degreePointA = new Vector2D<int>(90, 80);
	Vector2D<int>* line45degreePointB = new Vector2D<int>(-10, -20);

	Vector2D<int>* lineB45degreePointA = new Vector2D<int>(250, -350);
	Vector2D<int>* lineB45degreePointB = new Vector2D<int>(50, -150);
}

LineDrawingTester::~LineDrawingTester()
{
}

void LineDrawingTester::prepareTestLines(LineSlope lineSlope, PositionInSpace whichSpace, PointsOrder order, Vector2D<int>* windowDimensions)
{
	// Q1 | Q0
	//---------
	// Q2 | Q3
	int quadrantsWidth = windowDimensions->x / 2;
	int quadrantsHeight = windowDimensions->y / 2;

	switch (lineSlope)
	{
		case LineSlope::GENTLE:
		{
			linePoint0 = new Vector2D<int>(10, 5); //(25, 40);
			linePoint1 = new Vector2D<int>(370, 25);
			break;
		}

		case LineSlope::STEEP:
		{
			linePoint0 = new Vector2D<int>(7, 10); //(25, 40);
			linePoint1 = new Vector2D<int>(260, 360);
			break;
		}

		case LineSlope::HORIZONTAL:
		{

			linePoint0 = new Vector2D<int>(-30, 20);  //(-windowDimensions->x / 8, windowDimensions->y / 8);
			linePoint1 = new Vector2D<int>(200, 20);  //(windowDimensions->x / 8, windowDimensions->y / 8);
			break;
		}

		case LineSlope::VERTICAL:
		{
			linePoint0 = new Vector2D<int>(-60, 30);//(windowDimensions->x / 4, windowDimensions->y / 4);
			linePoint1 = new Vector2D<int>(-60, -200);//(windowDimensions->x / 4, -windowDimensions->y / 4);

			break;
		}
	}

	switch (whichSpace)
	{
		case PositionInSpace::Q0:
		{
			// This is the same as Default value
			break;
		}

		case PositionInSpace::Q1:
		{
			// This is the same as Default value
			modifyTestPoints(linePoint0, linePoint1, -quadrantsWidth, 0, -quadrantsWidth, 0);
			break;
		}

		case PositionInSpace::Q2:
		{
			// This is the same as Default value
			modifyTestPoints(linePoint0, linePoint1, -quadrantsWidth, -quadrantsHeight, -quadrantsWidth, -quadrantsHeight);
			break;
		}

		case PositionInSpace::Q3:
		{
			// This is the same as Default value
			modifyTestPoints(linePoint0, linePoint1, 0, -quadrantsHeight, 0, -quadrantsHeight);
			break;
		}

		case PositionInSpace::Q10:
		{
			// This is the same as Default value
			modifyTestPoints(linePoint0, linePoint1, -quadrantsWidth / 2, 0, -quadrantsWidth / 2, 0);
			break;
		}

		case PositionInSpace::Q23:
		{
			// This is the same as Default value
			modifyTestPoints(linePoint0, linePoint1, -quadrantsWidth / 2, -quadrantsHeight, -quadrantsWidth / 2, -quadrantsHeight);
			break;
		}

		case PositionInSpace::Q123_230:
		{
			negativePointA->x = negativePointA->x - quadrantsWidth / 2;
			negativePointA->y = negativePointA->y - quadrantsHeight / 18;
			negativePointB->x = negativePointB->x - quadrantsWidth / 2;
			negativePointB->y = negativePointB->y - quadrantsHeight / 18;

			linePoint0->x = linePoint0->x - quadrantsWidth / 2;
			linePoint0->y = linePoint0->y - quadrantsHeight / 18;
			linePoint1->x = linePoint1->x - quadrantsWidth / 2;
			linePoint1->y = linePoint1->y - quadrantsHeight / 18;
			break;
		}

		case PositionInSpace::Q10_H:
		{

			break;
		}

		case PositionInSpace::Q12_V:
		{

			break;
		}

		default:
		{
			// Positive slope
			linePoint0 = new Vector2D<int>(10, 5); //(25, 40);
			linePoint1 = new Vector2D<int>(370, 25);
			break;
		}
	}

	Vector2D<int>* temporaryVector = nullptr;
	if (order == PointsOrder::REVERSE)
	{
		temporaryVector = linePoint0;
		linePoint0 = linePoint1;
		linePoint1 = temporaryVector;

		temporaryVector = negativePointA;
		negativePointA = negativePointB;
		negativePointB = temporaryVector;
		temporaryVector = nullptr;
	}
}

void LineDrawingTester::modifyTestPoints(Vector2D<int>* point0, Vector2D<int>* point1, int x0Modifier, int y0Modifier, int x1Modifier, int y1Modifier)
{
	point0->x = point0->x + x0Modifier;
	point0->y = point0->y + y0Modifier;
	point1->x = point1->x + x1Modifier;
	point1->y = point1->y + y1Modifier;
}