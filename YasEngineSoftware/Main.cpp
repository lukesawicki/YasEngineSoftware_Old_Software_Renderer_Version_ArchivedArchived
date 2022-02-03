
#include<Windows.h>
#include<GLFW/glfw3.h>
#include<gl/gl.h>
#include<glext.h>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<cmath>
#include"Vector2D.hpp"
#include"YasGraphicsLibrary.hpp"
#include"TimePicker.hpp"
#include"PixelsTable.hpp"
#include"Circle.hpp"

#include<vector>

#include"Polygonn.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120


int main(int argc, char* argv[])
{
    const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 768;

    Vector2D<int>* windowDimensions = new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);

    GLFWwindow* window;

    // Points that to draw axes
	Vector2D<int>* xAxisBegin = new Vector2D<int>(0, WINDOW_HEIGHT / 2);
	Vector2D<int>* xAxisEnd = new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
	Vector2D<int>* yAxisBegin = new Vector2D<int>(WINDOW_WIDTH / 2, 0);
	Vector2D<int>* yAxisEnd = new Vector2D<int>(WINDOW_WIDTH / 2, WINDOW_HEIGHT);

    //Vector2D<int> start(0, 100);
    //Vector2D<int> stop(100, 100);

    Vector2D<int> start(100, 100);
    Vector2D<int> stop(0, 100);


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

    PixelsTable pixelsTable(WINDOW_WIDTH, WINDOW_HEIGHT, YasGL::BLACK);

    // Test objects definitions
    //Circle(int radius, int x, int y);
    YasGL::Polygonn* testCircle01;
    testCircle01 = new YasGL::Circle(100, 0, 0);
    // End of test objects definitions


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

    Vector2D<int> point0(100, 0);
    Vector2D<int> point1(50, 86);

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
            
            pixelsTable.clearColor(YasGL::BLACK);
            
			YasGL::drawCartesianAxies(pixelsTable);

//          ########  BEGINT TEST CODE  ################

            //testCircle01->move(deltaTime);
            YasGL::drawLine(start, stop, pixelsTable, YasGL::YELLOW);
            YasGL::drawLine(point0, point1, pixelsTable, YasGL::GREEN);
            //YasGL::drawPolygon(testCircle01, YasGL::BLUE, pixelsTable);

            //testCircle01.draw(YasGL::WHITE, pixelsTable);

//          ########  END TEST CODE  ################

            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixelsTable.pixels);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }
}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
