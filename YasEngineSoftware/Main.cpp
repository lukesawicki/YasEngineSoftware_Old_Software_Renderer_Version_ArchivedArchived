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

float aspect;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

const int RGB = 3;
const int RGBA = 4;

int pixelCounter = 0;

GLFWwindow* window;

struct Four
{
    uint8_t x = 0;
    uint8_t y = 0;
    uint8_t z = 0;
    uint8_t w = 0;
};


    //-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120
int main(int argc, char* argv[])
{
    if (!glfwInit())
    {
        return 1;
    }

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    Vector2D<int>* windowDimensions = new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    Vector4D<uint8_t>* red = new Vector4D<uint8_t>(255, 0, 0, 255);
    Vector4D<uint8_t>* green = new Vector4D<uint8_t>(0, 255, 0, 255);
    Vector4D<uint8_t>* blue = new Vector4D<uint8_t>(0, 0, 255, 255);
    Vector4D<uint8_t>* black = new Vector4D<uint8_t>(0, 0, 0, 255);

    bool leftMouseButtonDown = false;
    bool quit = false;

    int circleSpeedFactor = 255;
    int circleSpeed = 2 * circleSpeedFactor;
    Vector2D<int>* circlePosition = new Vector2D<int>(0, 0);
    YasGL::cartesianPositionToWindow(circlePosition, windowDimensions);
    Vector4D<uint8_t>* circleColor = new Vector4D<uint8_t>(255, 255, 255, 255);
    int circleRadius = 50;

    int circleX = 0;
    int circleY = 0;

    Vector2D<int>* xAxiesBegin = new Vector2D<int>(0, WINDOW_HEIGHT / 2);
    Vector2D<int>* xAxiesEnd = new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT / 2);
    Vector2D<int>* yAxiesBegin = new Vector2D<int>(WINDOW_WIDTH / 2, 0);
    Vector2D<int>* yAxiesEnd = new Vector2D<int>(WINDOW_WIDTH / 2, WINDOW_HEIGHT);

    float canvasWidth = 2, canvasHeight = 2;
    uint32_t imageWidth = 512, imageHeight = 512;

    Vector2D<int>* line1_A = new Vector2D<int>(0, 10);
    Vector2D<int>* line1_B = new Vector2D<int>(400, 60);

    Vector2D<int>* line2_A = new Vector2D<int>(30, 40);
    Vector2D<int>* line2_B = new Vector2D<int>(430, 90);

    constexpr int PIXELS_TABLE_SIZE = WINDOW_WIDTH * WINDOW_HEIGHT * RGBA;

    uint8_t* pixels = YasGL::createPixelsTable(windowDimensions, black);

    if (!window)
    {
        std::cerr << "Error failed to create window!\n";
        return 1;
    }

	Vector4D<uint8_t> *squareColor = new Vector4D<uint8_t>(0, 0, 255, 255);
	Vector2D<int> *positions = new Vector2D<int>(0, 0);

    bool running = true;

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

    bool switched = false;
    bool close = false;

    while (running)
    {

        while (!glfwWindowShouldClose(window))
        {

            if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
            {
                running = false;
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

            YasGL::clearColor(pixels, black, windowDimensions);

            YasGL::drawCartesianAxies(windowDimensions, pixels);

			for (int i = 0; i < 100; i++)
            {
				for (int j = 0; j < 100; j++)
                {
                    positions->x = i;
                    positions->y = j;
					YasGL::drawPoint(positions, pixels, squareColor, windowDimensions);
				}
			}

            YasGL::drawCircle(circlePosition, circleRadius, pixels, circleColor, windowDimensions);\

            YasGL::lukeDrawLineOctan0V2(line2_A, line2_B, pixels, red, windowDimensions);

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