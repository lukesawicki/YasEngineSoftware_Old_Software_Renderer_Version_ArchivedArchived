#include<Windows.h>
#include <GLFW/glfw3.h>
#include<gl/gl.h>
#include<glext.h>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<cmath>
#include"Vector2D.hpp"
#include"Vector3D.hpp"
#include"YasGraphicsLibrary.hpp"
#include"TimePicker.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120
int main(int argc, char* argv[])
{
	const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 768;
    Vector2D<int>* windowDimensions = new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);
    GLFWwindow* window;

	const int RGBA = 4;
	Vector4D<uint8_t>* red = new Vector4D<uint8_t>(255, 0, 0, 255);
	Vector4D<uint8_t>* green = new Vector4D<uint8_t>(0, 255, 0, 255);
	Vector4D<uint8_t>* blue = new Vector4D<uint8_t>(0, 0, 255, 255);
	Vector4D<uint8_t>* black = new Vector4D<uint8_t>(0, 0, 0, 255);
    Vector4D<uint8_t>* white = new Vector4D<uint8_t>(255, 255, 255, 255);
    Vector4D<uint8_t>* yellow = new Vector4D<uint8_t>(255, 255, 0, 255);
    Vector4D<uint8_t>* testObjectsColor = new Vector4D<uint8_t>(255, 242, 0, 255);
    Vector4D<uint8_t>* testObjectsColor2 = new Vector4D<uint8_t>(255, 174, 201, 255);

    // Points that to draw axies
	Vector2D<int>* xAxiesBegin = new Vector2D<int>(0, WINDOW_HEIGHT / 2);
	Vector2D<int>* xAxiesEnd = new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	Vector2D<int>* yAxiesBegin = new Vector2D<int>(WINDOW_WIDTH / 2, 0);
	Vector2D<int>* yAxiesEnd = new Vector2D<int>(WINDOW_WIDTH / 2, WINDOW_HEIGHT);

    if (!glfwInit())
    {
        return 1;
    }

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    uint8_t* pixels = YasGL::createPixelsTable(windowDimensions, black);

    // Data defined Circle for drawing circle for varied tests
	int circleX = 0;
	int circleY = 0;
    int circleRadius = 80;
    int circleSpeedFactor = 255;
    int circleSpeed = 2 * circleSpeedFactor;
    Vector4D<uint8_t>* circleColor = new Vector4D<uint8_t>(255, 255, 255, 255);

	Vector2D<int>* circlePosition = new Vector2D<int>(0, 0);

    bool switched = false;
    // End of data defined Circle for drawing circle for varied tests

    // Positive slope;
    Vector2D<int>* positiveGentlePointA = nullptr;
    Vector2D<int>* positiveGentlePointB = nullptr;

	// Negative slope
	Vector2D<int>* negativeGentlePointA = nullptr;
	Vector2D<int>* negativeGentlePointB = nullptr;

	// Positive slope;
    Vector2D<int>* positiveSteepPointA = nullptr;
    Vector2D<int>* positiveSteepPointB = nullptr;

	// Negative slope
	Vector2D<int>* negativeSteepPointA = nullptr;
	Vector2D<int>* negativeSteepPointB = nullptr;

    // Horizontal line
	Vector2D<int>* horizontalLinePointA = nullptr;
	Vector2D<int>* horizontalLinePointB = nullptr;

	Vector2D<int>* horizontalLineBPointA = nullptr;
	Vector2D<int>* horizontalLineBPointB = nullptr;

    // Vertical line
	Vector2D<int>* verticalLinePointA = nullptr;
	Vector2D<int>* verticalLinePointB = nullptr;

	Vector2D<int>* verticalLineBPointA = nullptr;
	Vector2D<int>* verticalLineBPointB = nullptr;

    // 45 degree line RED
	Vector2D<int>* line45degreePointA = new Vector2D<int>(90, 80);
	Vector2D<int>* line45degreePointB = new Vector2D<int>(-10, -20);

    // 45 degree line GREEN
	Vector2D<int>* lineB45degreePointA = new Vector2D<int>(250, -350);
	Vector2D<int>* lineB45degreePointB = new Vector2D<int>(50, -150);
	//Vector2D<int>* lineB45degreePointA = new Vector2D<int>(250, -350);
	//Vector2D<int>* lineB45degreePointB = new Vector2D<int>(50, -150);

    // Data required to draw simple square filled with color for tests
	Vector4D<uint8_t> *squareColor = new Vector4D<uint8_t>(0, 0, 255, 255);
	Vector2D<int> *positions = new Vector2D<int>(0, 0);
    // End of data required to draw simple square filled with color for tests

    bool shouldApplicationStopRunning = false;

    double time;
    double newTime;
    double deltaTime;
    double fps;
    double fpsTime;
    unsigned int frames;

    TimePicker timePicker = TimePicker();
    time = timePicker.getSeconds();

    fpsTime = 0.0F;
    frames = 0;
    bool close = false;

    

    //prepareTestLines(YasGL::LineSlope::GENTLE, YasGL::PositionInSpace::Q123_230, YasGL::PointsOrder::REVERSE, positiveGentlePointA, positiveGentlePointB, negativeGentlePointA, negativeGentlePointB, windowDimensions);
    //prepareTestLines(YasGL::LineSlope::STEEP, YasGL::PositionInSpace::Q123_230, YasGL::PointsOrder::NORMAL, positiveSteepPointA, positiveSteepPointB, negativeSteepPointA, negativeSteepPointB, windowDimensions);
    prepareTestLines(YasGL::LineSlope::HORIZONTAL, YasGL::PositionInSpace::Q10_H, YasGL::PointsOrder::NORMAL, horizontalLinePointA, horizontalLinePointB, horizontalLineBPointA, horizontalLineBPointB, windowDimensions);
    prepareTestLines(YasGL::LineSlope::VERTICAL, YasGL::PositionInSpace::Q12_V, YasGL::PointsOrder::NORMAL, verticalLinePointA, verticalLinePointB, verticalLineBPointA, verticalLineBPointB, windowDimensions);

    while (!shouldApplicationStopRunning)
    {

        while (!glfwWindowShouldClose(window))
        {

            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                shouldApplicationStopRunning = true;
                break;
            }

            newTime = timePicker.getSeconds();
            deltaTime = newTime - time;
            time = newTime;

            ++frames;
            fpsTime = fpsTime + deltaTime;
            if (fpsTime >= 1.0F)
            {
                fps = frames / fpsTime;
                frames = 0;
                fpsTime = 0.0F;
            }
            
            YasGL::clearColor(pixels, black, windowDimensions);

			YasGL::drawCartesianAxies(windowDimensions, pixels);

            // In real-time Generating CIRCLE
            circlePosition->x = static_cast<int>(circlePosition->x + deltaTime * circleSpeed);
            if (circlePosition->x < circleRadius && !switched)
            {
                circleSpeed = circleSpeed * -1;
                circlePosition->x = circleRadius;
            }

            if (circlePosition->x > 512 - circleRadius)
            {
                circleSpeed = circleSpeed * -1;
                circlePosition->x = 512 - circleRadius;
            }

			for (int i = 0; i < 100; i++)
            {
				for (int j = 0; j < 100; j++)
                {
                    positions->x = i;
                    positions->y = j;
					YasGL::drawPoint(positions, pixels, squareColor, windowDimensions);
				}
			}

            YasGL::drawCircle(circlePosition, circleRadius, pixels, circleColor, windowDimensions);

            YasGL::lukeDrawLineOctanNEWEST(horizontalLinePointA, horizontalLinePointB, pixels, red, windowDimensions);
            YasGL::lukeDrawLineOctanNEWEST(horizontalLineBPointA, horizontalLineBPointB, pixels, red, windowDimensions);

            YasGL::lukeDrawLineOctanNEWEST(verticalLinePointA, verticalLinePointB, pixels, yellow, windowDimensions);
            YasGL::lukeDrawLineOctanNEWEST(verticalLineBPointA, verticalLineBPointB, pixels, white, windowDimensions);

            YasGL::lukeDrawLineOctanNEWEST(line45degreePointA, line45degreePointB, pixels, red, windowDimensions);
            YasGL::lukeDrawLineOctanNEWEST(lineB45degreePointA, lineB45degreePointB, pixels, green, windowDimensions);

            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

            glfwSwapBuffers(window);

            glfwPollEvents();

        }

        YasGL::deleteTestLines(positiveGentlePointA, positiveGentlePointB, negativeGentlePointA, negativeGentlePointB);
        YasGL::deleteTestLines(positiveSteepPointA, positiveSteepPointB, negativeSteepPointA, negativeSteepPointB);

		YasGL::deleteTestLines(horizontalLinePointA, horizontalLinePointB, horizontalLineBPointA, horizontalLineBPointB);
		YasGL::deleteTestLines(verticalLinePointA, verticalLinePointB, verticalLineBPointA, verticalLineBPointB);

		delete line45degreePointA;
		delete line45degreePointB;

		delete lineB45degreePointA;
		delete lineB45degreePointB;


        delete[] pixels;
        glfwTerminate();
        return 0;
    }
}
//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|