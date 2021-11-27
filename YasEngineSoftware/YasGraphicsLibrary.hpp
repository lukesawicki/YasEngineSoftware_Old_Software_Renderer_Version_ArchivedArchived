#ifndef YASGRAPHICSLIBRARY_HPP
#define YASGRAPHICSLIBRARY_HPP
#include<cmath>
#include<iostream>
#include <GLFW/glfw3.h>
#include"Vector2D.hpp"
#include"Vector3D.hpp"
#include"Vector4D.hpp"


namespace YasGL
{
    const uint8_t NUMBER_OF_COLORS = 4;
    const uint8_t RGB_FORMAT = 3;
    const uint8_t RGBA_FORMAT = 4;

    const uint8_t RED_POSITION = 0;
    const uint8_t GREEN_POSITION = 1;
    const uint8_t BLUE_POSITION = 2;
    const uint8_t ALPHA_POSITION = 3;

	const Vector4D<uint8_t> RED(255, 0, 0, 0);
	const Vector4D<uint8_t> GREEN(0, 255, 0, 0);
	const Vector4D<uint8_t> BLUE(0, 0, 255, 0);
	const Vector4D<uint8_t> BLACK(0, 0, 0, 0);

    const float dl = 3.125e-3F;

    enum class LineSlope { GENTLE, STEEP, HORIZONTAL, VERTICAL };
	enum class PointsOrder { NORMAL, REVERSE };
	enum class PositionInSpace { Q0, Q1, Q2, Q3, Q10, Q23, Q12, Q03, Q123_230, Q12_V, Q10_H };

	void prepareTestLines(LineSlope lineSlope, PositionInSpace whichSpace, PointsOrder order, Vector2D<int>*& positivePointA, Vector2D<int>*& positivePointB, Vector2D<int>*& negativePointA, Vector2D<int>*& negativePointB, Vector2D<int>* windowDimensions);
    void modifyTestPoints(Vector2D<int>* positivePointA, Vector2D<int>* positivePointB, Vector2D<int>* negativePointA, Vector2D<int>* negativePointB, int positiveXmodifier, int positiveYmodifier, int negativeXmodifier, int negativeYmodifier);
    void deleteTestLines(Vector2D<int>*& positivePointA, Vector2D<int>*& positivePointB, Vector2D<int>*& negativePointA, Vector2D<int>*& negativePointB);

    void clearColor(uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void cartesianPositionToWindow(Vector2D<int>* point, Vector2D<int>* windowDimenstions);
    void cartesianPositionToWindow(int& x, int& y, Vector2D<int>* windowDimenstions);
    
    uint8_t* createPixelsTable(Vector2D<int>* windowDimensions, Vector4D<uint8_t>* defaultColor);

    void drawPoint(Vector2D<int>* point, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);
    void drawPoint(int x, int y, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void lukeDrawLineOctan0V1(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);
    void drawNotSteepLine(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);
    void lukeDrawLineFullUnderstandingVersion(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);
    void lukeDrawLineOctanNEWEST(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);
    void swapVectors(Vector2D<int>*& point0, Vector2D<int>*& point1);
    void lukeDrawLineOctan7(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void helsinkiDraw(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void simplestNiveLineDraw(Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions);

    void drawCartesianAxies(Vector2D<int>* windowDimensions, uint8_t* pixels);
    int xyPixelToArrayPosition(Vector2D<int>* point, int windowWidth);
    int xyPixelToArrayPosition(int x, int y, int windowWidth);
    void drawCircle(Vector2D<int>* position, int& radius, uint8_t* pixels, Vector4D<uint8_t>* drawingColor, Vector2D<int>* windowDimensions); //Vector2D<int>* windowDimensions
}

#endif
