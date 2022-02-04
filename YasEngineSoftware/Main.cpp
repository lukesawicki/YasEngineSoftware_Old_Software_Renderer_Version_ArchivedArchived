
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

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

bool up = false;
bool down = false;
bool left = false;
bool right = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        up = true;
    }
		
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
        down = true;
	}
	
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
        left = true;
	}
	
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
        right = true;
	}


	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		up = false;
	}

	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		down = false;
	}

	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		left = false;
	}

	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		right = false;
	}
}

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

    Vector2D<int> start(500, 500);
    Vector2D<int> stop(-500, -500);

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
    objectsToDraw.push_back(new YasGL::Circle(100, 0, 0));
    objectsToDraw.push_back(player);

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

    //Vector2D<int> point0(-500, 500);
    //Vector2D<int> point1(500, -500 );

    while (!shouldApplicationStopRunning)
    {
        while (!glfwWindowShouldClose(window))
        {
            // ESCAPE
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            {
                shouldApplicationStopRunning = true;
            }

            // LEFT
			if (left) //glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
                //player->xDirection = -1;
                player->xDirection = -1;
				player->position.x = static_cast<int>(player->position.x + deltaTime * (-player->speed));
				//player->position.y = static_cast<int>(player->position.y + deltaTime * player->speed) * player->yDirection;

			}

			
            // RIGHT
            if (right) //glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
                player->xDirection = 1;
				player->position.x = static_cast<int>(player->position.x + deltaTime * player->speed);
				//player->position.y = static_cast<int>(player->position.y + deltaTime * player->speed) * player->yDirection;
			}


            // UP
			if (up) //glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
                player->yDirection = 1;
                //player->position.y = player->position.y + 2;
				//player->position.x = static_cast<int>(player->position.x + deltaTime * player->speed) * player->xDirection;
				player->position.y = static_cast<int>(player->position.y + deltaTime * player->speed);
			}


            // DOWN
			if (down) //glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
                player->yDirection = -1;
				//player->position.x = static_cast<int>(player->position.x + deltaTime * player->speed) * player->xDirection;
				player->position.y = static_cast<int>(player->position.y + deltaTime * (-player->speed));
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
            
			//YasGL::drawCartesianAxies(pixelsTable);

//          ########  BEGINT TEST CODE  ################

            YasGL::drawLine(start, stop, pixelsTable, YasGL::YELLOW);
            for (auto object : objectsToDraw)
            {
                //object->move(deltaTime);
                object->regeneratePolygon();
                YasGL::drawPolygon(object, YasGL::GREEN, pixelsTable);
            }
			//player->position.x = static_cast<int>(player->position.x + deltaTime * player->speed) * player->xDirection;
			//player->position.y = static_cast<int>(player->position.y + deltaTime * player->speed) * player->yDirection;
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
