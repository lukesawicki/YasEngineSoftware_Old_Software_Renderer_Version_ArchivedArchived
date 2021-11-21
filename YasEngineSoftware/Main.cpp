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
	const int RGBA = 4;
	Vector4D<uint8_t>* red = new Vector4D<uint8_t>(255, 0, 0, 255);
	Vector4D<uint8_t>* green = new Vector4D<uint8_t>(0, 255, 0, 255);
	Vector4D<uint8_t>* blue = new Vector4D<uint8_t>(0, 0, 255, 255);
	Vector4D<uint8_t>* black = new Vector4D<uint8_t>(0, 0, 0, 255);
    Vector4D<uint8_t>* white = new Vector4D<uint8_t>(255, 255, 255, 255);
    Vector4D<uint8_t>* yellow = new Vector4D<uint8_t>(255, 255, 0, 255);
    Vector4D<uint8_t>* testObjectsColor = new Vector4D<uint8_t>(255, 242, 0, 255);

    Vector4D<uint8_t>* testObjectsColor2 = new Vector4D<uint8_t>(255, 174, 201, 255);

	GLFWwindow* window;
    
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

    ////
    //Vector2D<int>* circlePosition = new Vector2D<int>(250, 50); // defined in Cartesian coordination system it's mean the center of window is 0,0. The x increasing to right and y up.
    //YasGL::cartesianPositionToWindow(circlePosition, windowDimensions);
    ////

    bool switched = false;
    // End of data defined Circle for drawing circle for varied tests

    // Positive slope;
    Vector2D<int>* positiveGentlePointA = nullptr;
    Vector2D<int>* positiveGentlePointB = nullptr;

	// Negative slope
	Vector2D<int>* negativeGentlePointA = nullptr;
	Vector2D<int>* negativeGentlePointB = nullptr;

    // STEEP

	// Positive slope;
    Vector2D<int>* positiveSteepPointA = nullptr;
    Vector2D<int>* positiveSteepPointB = nullptr;

	// Negative slope
	Vector2D<int>* negativeSteepPointA = nullptr;
	Vector2D<int>* negativeSteepPointB = nullptr;

    // End of points representing test line for Octan 0

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

    //int temporary = 0;
    // Green positive ,-*` Red negative `*-,
    prepareTestLines(YasGL::LineSlope::GENTLE, YasGL::PositionInSpace::Q123_230, YasGL::PointsOrder::REVERSE, positiveGentlePointA, positiveGentlePointB, negativeGentlePointA, negativeGentlePointB, windowDimensions);
    prepareTestLines(YasGL::LineSlope::STEEP, YasGL::PositionInSpace::Q123_230, YasGL::PointsOrder::NORMAL, positiveSteepPointA, positiveSteepPointB, negativeSteepPointA, negativeSteepPointB, windowDimensions);

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

			// Drawing AXIES
			YasGL::drawCartesianAxies(windowDimensions, pixels);
			// END Drawing AXIES

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
            // END Generating CIRCLE
            // 

			for (int i = 0; i < 100; i++)
            {
				for (int j = 0; j < 100; j++)
                {
                   /* ++temporary;
                    if (i == j) {
                        std::cout << "I: " << i << " J: " << j << " Pixel value on first position (RGBA): " << pixels[i] << " temporary " << temporary;
                    }*/
                    positions->x = i;
                    positions->y = j;
					YasGL::drawPoint(positions, pixels, squareColor, windowDimensions);
				}
			}

            YasGL::drawCircle(circlePosition, circleRadius, pixels, circleColor, windowDimensions);

             //Gentle lines
             //Positive
            YasGL::lukeDrawLineOctanNEWEST(positiveGentlePointA, positiveGentlePointB, pixels, red, windowDimensions);

             //Negative
			YasGL::lukeDrawLineOctanNEWEST(negativeGentlePointA, negativeGentlePointB, pixels, green, windowDimensions);

            // Steep lines
			// Positive
			YasGL::lukeDrawLineOctanNEWEST(positiveSteepPointA, positiveSteepPointB, pixels, red, windowDimensions);

			// Negative
			YasGL::lukeDrawLineOctanNEWEST(negativeSteepPointA, negativeSteepPointB, pixels, green, windowDimensions);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //YasGL::drawLine(testLinePos_slope_Oct_7PointA, testLinePos_slope_Oct_7PointB, pixels, testObjectsColor, windowDimensions);
            //YasGL::lukeDrawLineOctan0_V2(mirroredA, mirroredB, pixels, testObjectsColor, windowDimensions);
            ////////////////////////YasGL::drawLine(testLinePos_slope_Oct_7PointA, testLinePos_slope_Oct_7PointB, pixels, yellow, windowDimensions); // Same as above but it is working
            //YasGL::simplestNiveLineDraw(pointA, pointB, pixels, yellow, windowDimensions);
            //YasGL::simplestNiveLineDraw(testLinePos_slope_Oct_4PointA, testLinePos_slope_Oct_4PointB, pixels, yellow, windowDimensions);


            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

            glfwSwapBuffers(window);

            glfwPollEvents();

        }


        YasGL::deleteTestLines(positiveGentlePointA, positiveGentlePointB, negativeGentlePointA, negativeGentlePointB);
        YasGL::deleteTestLines(positiveSteepPointA, positiveSteepPointB, negativeSteepPointA, negativeSteepPointB);

        delete[] pixels;
        glfwTerminate();
        return 0;
    }
}
//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|