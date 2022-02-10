
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
#include"Polygon.hpp"
#include"Player.hpp"
#include"InputOutputHandler.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120
bool shouldApplicationStopRunning = false;
YasInOut::Input* input = new YasInOut::Input();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
        shouldApplicationStopRunning = true;
        glfwSetWindowShouldClose(window, GL_TRUE);
	}

    // PRESS

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		input->up = true;
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		input->down = true;
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		input->left = true;
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		input->right = true;
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		input->rotateClocwise = true;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		input->shoot = true;
	}

    // RELEASE

	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		input->up = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		input->down = false;
	}

	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		input->left = false;
	}

	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		input->right = false;
	}

	if (key == GLFW_KEY_R && action == GLFW_RELEASE)
	{
		input->rotateClocwise = false;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		input->shoot = false;
	}
}

int main(int argc, char* argv[])
{
    const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 768;

    Vector2D<int>* windowDimensions = new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);

    GLFWwindow* window;

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

    glfwSetKeyCallback(window, key_callback);

    PixelsTable pixelsTable(WINDOW_WIDTH, WINDOW_HEIGHT, YasGL::BLACK);

    // Test objects definitions

	std::vector<YasGL::Polygon*> objectsToDraw;

    YasGL::Player* player = new YasGL::Player(0, 0);
    player->setColor(YasGL::YELLOW);
    player->setInput(input);

    YasGL::Circle* circle = new YasGL::Circle(100, 0, 0);
    circle->setColor(YasGL::BLUE);

    objectsToDraw.push_back(circle);
    objectsToDraw.push_back(player);

    // End of test objects definitions

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

    while (!shouldApplicationStopRunning)
    {
        while (!glfwWindowShouldClose(window))
        {
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

            player->rotate(deltaTime);
            
            for (auto object : objectsToDraw)
            {
                object->move(deltaTime);
                object->regeneratePolygon();
                YasGL::drawPolygon(object, pixelsTable);
            }
            objectsToDraw.push_back(player->shoot());
//          ########  END TEST CODE  ################

            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixelsTable.pixels);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        
        for (auto drawableObject : objectsToDraw)
        {
            delete drawableObject;
        }

        glfwTerminate();
        return 0;
    }
}

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
