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
    Vector4D<uint8_t>* testObjectsColor = new Vector4D<uint8_t>(255, 242, 0, 255);

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
    int circleRadius = 50;
    int circleSpeedFactor = 255;
    int circleSpeed = 2 * circleSpeedFactor;
    Vector4D<uint8_t>* circleColor = new Vector4D<uint8_t>(255, 255, 255, 255);

	Vector2D<int>* circlePosition = new Vector2D<int>(250, 300);

    ////
    //Vector2D<int>* circlePosition = new Vector2D<int>(250, 50); // defined in Cartesian coordination system it's mean the center of window is 0,0. The x increasing to right and y up.
    //YasGL::cartesianPositionToWindow(circlePosition, windowDimensions);
    ////

    bool switched = false;
    // End of data defined Circle for drawing circle for varied tests

    // Points representing test line for Octan 0
    Vector2D<int>* testLine0PointA = new Vector2D<int>(0, 0); //(25, 40);
    Vector2D<int>* testLine0PointB = new Vector2D<int>(384, 20); //(256, 192);
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
            if (circlePosition->x < 0 && !switched)
            {
                circleSpeed = circleSpeed * -1;
                circlePosition->x = 0;
            }

            if (circlePosition->x > 1024)
            {
                circleSpeed = circleSpeed * -1;
                circlePosition->x = 1024;
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

            YasGL::drawCircle(circlePosition, circleRadius, pixels, circleColor, windowDimensions);\

            YasGL::lukeDrawLineOctan0V2(testLine0PointA, testLine0PointB, pixels, testObjectsColor, windowDimensions);
            //
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