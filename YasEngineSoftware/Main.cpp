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

    // Points representing test line for Octan 0 // positive slope
    Vector2D<int>* testLinePos_slope_Oct_0PointA = new Vector2D<int>(10, 5); //(25, 40);
    Vector2D<int>* testLinePos_slope_Oct_0PointB = new Vector2D<int>(384, 25); //(256, 192);

    // MIRROR Same as testLinePos_slope_Oct_0Point* but points order inverted
    Vector2D<int>* testLinePos_slope_Oct_4PointA = new Vector2D<int>(250, 25); //(25, 40); testLinePos_slope_Oct_4PointA;
	Vector2D<int>* testLinePos_slope_Oct_4PointB = new Vector2D<int>(10, 5); //(256, 192); testLinePos_slope_Oct_4PointB;

	// Points representing test line for Octan 0 // positive slope
	Vector2D<int>* testLinePos_slope_Oct_0APointA = new Vector2D<int>(10, -25); //(25, 40);
	Vector2D<int>* testLinePos_slope_Oct_0APointB = new Vector2D<int>(384, -5); //(256, 192);

	// Points representing test line for Octan 7 // negative slope
	Vector2D<int>* testLinePos_slope_Oct_7PointA = new Vector2D<int>(10, 25); //(25, 40);
	Vector2D<int>* testLinePos_slope_Oct_7PointB = new Vector2D<int>(384, 5); //(256, 192);

    // Points representing test line for Octan 7 // negative slope
	Vector2D<int>* testLinePos_slope_Oct_7APointA = new Vector2D<int>(10, -5); //(25, 40);
	Vector2D<int>* testLinePos_slope_Oct_7APointB = new Vector2D<int>(384, -25); //(256, 192);

    // Points representing test line for Octan 0 // negative slope
	//Vector2D<int>* testLineNeg_slope_Oct_0PointA = new Vector2D<int>(0, 50); //(25, 40);
	//Vector2D<int>* testLineNeg_slope_Oct_0PointB = new Vector2D<int>(512, -30); //(256, 192);

	//Vector2D<int>* testLineBpos_slope_Oct_0PointA = new Vector2D<int>(-256, -400); //(25, 40);
	//Vector2D<int>* testLineBpos_slope_Oct_0PointB = new Vector2D<int>(256, -450); //(256, 192);

	//Vector2D<int>* testLineBpos_slope_Oct_0PointA = new Vector2D<int>(-256, -300); //(25, 40);
	//Vector2D<int>* testLineBpos_slope_Oct_0PointB = new Vector2D<int>(-240, 150); //(256, 192);

	Vector2D<int>* testLine_slope_Oct_1PointA = new Vector2D<int>(2, 2); //(25, 40);
	Vector2D<int>* testLine_slope_Oct_1PointB = new Vector2D<int>(20, 400); //(256, 192);

    // Test points for naive version:
	Vector2D<int>* pointA = new Vector2D<int>(30, 30); //(25, 40);
	Vector2D<int>* pointB = new Vector2D<int>(500, 220); //(256, 192);

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


            // Test Octan 0 (positive slope line / )
            YasGL::lukeDrawLineOctanNEWEST(testLinePos_slope_Oct_0PointA, testLinePos_slope_Oct_0PointB, pixels, green, windowDimensions); // ok
            
            // Test Octan 4 (positive slope line / but direction to the left or Point A swaped with point B
            YasGL::lukeDrawLineOctanNEWEST(testLinePos_slope_Oct_4PointA, testLinePos_slope_Oct_4PointB, pixels, white, windowDimensions); // ok
            //YasGL::lukeDrawLineOctan4(mirroredA, mirroredB, pixels, white, windowDimensions);

			// Test Octan 7 (negative slope line \ )
			YasGL::lukeDrawLineOctanNEWEST(testLinePos_slope_Oct_7PointA, testLinePos_slope_Oct_7PointB, pixels, red, windowDimensions); // failing
            //YasGL::drawLine(testLinePos_slope_Oct_7PointA, testLinePos_slope_Oct_7PointB, pixels, testObjectsColor, windowDimensions);
            //YasGL::lukeDrawLineOctan0_V2(mirroredA, mirroredB, pixels, testObjectsColor, windowDimensions);

            ////////////////////////YasGL::drawLine(testLinePos_slope_Oct_7PointA, testLinePos_slope_Oct_7PointB, pixels, yellow, windowDimensions); // Same as above but it is working

			//// Octan 0A // here failing
			//YasGL::lukeDrawLineOctan0_V2(testLinePos_slope_Oct_0APointA, testLinePos_slope_Oct_0APointB, pixels, testObjectsColor, windowDimensions);

			//// Octan 7
			//YasGL::lukeDrawLineOctan0_V2(testLinePos_slope_Oct_7PointA, testLinePos_slope_Oct_7PointB, pixels, testObjectsColor, windowDimensions);

			//// Octan 7A
			//YasGL::lukeDrawLineOctan0_V2(testLinePos_slope_Oct_7APointA, testLinePos_slope_Oct_7APointB, pixels, testObjectsColor, windowDimensions);

   //         //testLine_slope_Oct_1PointA
   //         YasGL::lukeDrawLineOctan0_V2(testLine_slope_Oct_1PointA, testLine_slope_Oct_1PointB, pixels, testObjectsColor, windowDimensions);



            //YasGL::lukeDrawLineOctan0_V2(testLineNeg_slope_Oct_0PointA, testLineNeg_slope_Oct_0PointB, pixels, testObjectsColor, windowDimensions);
            //
            //YasGL::lukeDrawLineOctan0_V2(testLineBpos_slope_Oct_0PointA, testLineBpos_slope_Oct_0PointB, pixels, testObjectsColor2, windowDimensions);


            //YasGL::simplestNiveLineDraw(pointA, pointB, pixels, yellow, windowDimensions);
            //YasGL::simplestNiveLineDraw(testLinePos_slope_Oct_4PointA, testLinePos_slope_Oct_4PointB, pixels, yellow, windowDimensions);


            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

            glfwSwapBuffers(window);

            glfwPollEvents();

        }

        delete[] pixels;
        glfwTerminate();
        return 0;
    }
}
//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|