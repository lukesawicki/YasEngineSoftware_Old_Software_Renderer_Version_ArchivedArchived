//#include<Windows.h>
#define SDL_MAIN_HANDLED
#include<SDL.h>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<cmath>
#include<bitset>
#include"YasVector2D.hpp"
#include"YasGraphicsLibrary.hpp"
#include"TimePicker.hpp"
#include"PixelsTable.hpp"
#include"Circle.hpp"
#include"YasPolygon.hpp"
#include"Player.hpp"
#include"InputOutputHandler.hpp"

#define DEBUG_DRAWINGS

bool shouldApplicationStopRunning = false;
YasInOut::Input* input = new YasInOut::Input();
YasInOut::MousePositionChangeInformation* mousePositionChangeInformation = new YasInOut::MousePositionChangeInformation();

void windowToCartesian(double& x, double& y, YasVector2D<int>& windowDimensions)
{
	x = x - static_cast<int>(0.5 * windowDimensions.x);
	y = (-(y - static_cast<int>(0.5 * windowDimensions.y)));
}

// mocks
int GLFW_KEY_ESCAPE;
int GLFW_PRESS;
bool GL_TRUE;
int GLFW_KEY_W;
int GLFW_KEY_S;
int GLFW_KEY_A;
int GLFW_KEY_D;
int GLFW_KEY_R;
int GLFW_KEY_SPACE;
int GLFW_RELEASE;
int GLFW_MOUSE_BUTTON_LEFT;
int GLFW_MOUSE_BUTTON_RIGHT;

// end of mocks

void keysHandleCallbackFunction(SDL_Window* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
        shouldApplicationStopRunning = true;
        //glfwSetWindowShouldClose(window, GL_TRUE);
	}

    // PRESS KEY

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
		input->rotateCounterClockwise = true;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		input->shoot = true;
	}

    // RELEASE KEY

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
		input->rotateCounterClockwise = false;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		input->shoot = false;
	}
}

void mouseButtonsCallbackFunction(SDL_Window* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        mousePositionChangeInformation->leftMouseButton = true;
    }

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
        mousePositionChangeInformation->rightMouseButton = true;
	}

    // RELEASE KEY

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
        mousePositionChangeInformation->leftMouseButton = false;
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
        mousePositionChangeInformation->rightMouseButton = false;
	}
}

void mouseMoveHandleCallbackFunction(SDL_Window* window, double x, double y)
{
    if (abs(mousePositionChangeInformation->x - x) > 0.01F || abs(mousePositionChangeInformation->y - y) > 0.01F)
    {
        mousePositionChangeInformation->mouseMoved = true;
    }
    else
    {
        mousePositionChangeInformation->mouseMoved = false;
        return;
    }

	mousePositionChangeInformation->x = x;
	mousePositionChangeInformation->y = y;

}


std::vector<int> generatePrimeNumberLessThanN(int n)
{
    std::vector<int> primeNumbers;
    std::map<int, bool> numbers;

    for (int i = 2; i <= n; i++)
    {
        numbers.insert(std::pair<int, bool>(i, true));
    }
    int k = 0;
    int j = 0;
    for (int i = 2; i < sqrt(n); i++)
    {
        
        if (numbers.at(i))
        {
            while (true)//j < n)
            {
                
                j = (i * i) + (k*i);
                if (j <= n)
                {
                    numbers.at(j) = false;
                }
                else
                {
                    break;
                }
                k++;
            }
            k = 0;
            j = 0;
        }
    }

    for (int i = 2; i < numbers.size(); i++)
    {
        if (numbers.at(i))
        {
            //std::cout << i << std::endl;
            primeNumbers.push_back(i);
        }
    }
    return primeNumbers;
}

int main(int argc, char* argv[])
{
    const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 768;

    YasVector2D<int>* windowDimensions = new YasVector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_Init(SDL_INIT_VIDEO);

    //GLFWwindow* window;

    SDL_Window* window = SDL_CreateWindow("YasEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    // Since we are going to display a low resolution buffer,
    // it is best to limit the window size so that it cannot
    // be smaller than our internal buffer size.
    SDL_SetWindowMinimumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

    SDL_Texture* screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

    //if (!glfwInit())
    //{
    //    return 1;
    //}

    //window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
    
    //if (!window)
    //{
    //    glfwTerminate();
    //    return 1;
    //}

    //glfwMakeContextCurrent(window);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    //glfwSetKeyCallback(window, keysHandleCallbackFunction);

    //glfwSetCursorPosCallback(window, mouseMoveHandleCallbackFunction);

    //if(glfwRawMouseMotionSupported())
    //{
    //    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    //}

    //glfwSetMouseButtonCallback(window, mouseButtonsCallbackFunction);

    /////////

    //lukesawicki

    //SDL_SetTextureBlendMode(screenTexture, SDL_BLENDMODE_BLEND);

    std::vector<int> groupOfPrimeNumbers = generatePrimeNumberLessThanN(2000);

    int numberOfVerticesFromPrimeNumbers = groupOfPrimeNumbers.size() / 2;

    YasVector2D<float>* verticesForPrimeNumbersSegments = generateVerticesFromNumbers(groupOfPrimeNumbers);

    std::cout << "NUMBER OF PRIME NUMBERS: " << groupOfPrimeNumbers.size() << std::endl;

    //for (int i = 0; i < groupOfPrimeNumbers.size(); i++)
    //{
    //    std::cout << groupOfPrimeNumbers.at(i) << std::endl;
    //}

    /////////

    PixelsTable pixelsTable(WINDOW_WIDTH, WINDOW_HEIGHT, BLACK);

    YasVector2D<int> zeroVector;
    YasVector2D<int> direction;

	YasVector2D<int> testA;
	YasVector2D<int> testB;

	std::vector<YasPolygon*> objectsToDraw;

    Player* player = new Player(0, 0);
    player->setColor(YELLOW);
    player->setInput(input);
    player->setInput(mousePositionChangeInformation);

#ifdef DEBUG_DRAWINGS
    Circle* circle = new Circle(100, 0, 0);
    circle->setColor(BLUE);
    objectsToDraw.push_back(circle);
#endif // DEBUG_DRAWINGS

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
    bool firstTime = true;

    //while (!shouldApplicationStopRunning)
    //{
        //while (!glfwWindowShouldClose(window))
        //{

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) exit(0);
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
            
            pixelsTable.clearColor(BLACK);
            
#ifdef DEBUG_DRAWINGS
			drawCartesianAxies(pixelsTable);
#endif // DEBUG_DRAWINGS


//          ########  BEGINT TEST CODE  ################

            if (mousePositionChangeInformation->mouseMoved || input->up || input->down || input->left || input->right)
            {
                player->rotateToMousePositionInLocalCoordinateSystem(mousePositionChangeInformation->x, mousePositionChangeInformation->y, windowDimensions);
            }

            float mouseX = mousePositionChangeInformation->x;
            float mouseY = mousePositionChangeInformation->y;

            windowPositionToCartesianPosition(mouseX, mouseY, windowDimensions);
            drawCrossOnScreen(mouseX, mouseY, pixelsTable);

            for (auto object : objectsToDraw)
            {
                object->move(static_cast<float>(deltaTime));
                object->regeneratePolygon();
                drawPolygon(object, pixelsTable);
            }

#ifdef DEBUG_DRAWINGS
            // DRAW YELLOW LINE WHICH SHOWING THE DIRECTION OF MOUSE(PREVIOUSLY PLAYER)
            drawPolygonDirection(player, pixelsTable);
#endif // DEBUG_DRAWINGS


            Projectile* projectile = player->shoot();
            if (projectile != nullptr)
            {
                objectsToDraw.push_back(projectile);
            }

            projectile = nullptr;

            //for (auto object : objectsToDraw)
            //{
            //    if (object->position.x > (2 * WINDOW_WIDTH) || object->position.y > (2 * WINDOW_HEIGHT))
            //    {

            //    }
            //}
            
            
            //drawNumbersAsLineSegmentsNotContinuous(verticesForPrimeNumbersSegments, numberOfVerticesFromPrimeNumbers, pixelsTable);
            drawNumbersAsPolyline(verticesForPrimeNumbersSegments, numberOfVerticesFromPrimeNumbers, pixelsTable);
            for (int i = 0; i < groupOfPrimeNumbers.size(); i++)
            {
                std::string str = std::bitset<10>(groupOfPrimeNumbers.at(i)).to_string();
                for (int j = 0; j < 10; j++)
                {
                    if (str.at(j) == '1')
                    {
                        pixelsTable.drawPoint(j, i, YELLOW);
                    }
                    else
                    {
                        pixelsTable.drawPoint(j, i, BLUE);
                    }
                }
                str.clear();
            }
            //drawPrimeNumbers(groupOfPrimeNumbers, pixelsTable);

//          ########  END TEST CODE  ################

            //glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixelsTable.pixels);
            //glfwSwapBuffers(window);
            //glfwPollEvents();
        //}
            SDL_RenderClear(renderer);
            SDL_UpdateTexture(screenTexture, NULL, pixelsTable.pixels, WINDOW_WIDTH * 4);
            SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
            SDL_RenderPresent(renderer);

    }

    for (auto drawableObject : objectsToDraw)
    {
        delete drawableObject;
    }

    delete[] verticesForPrimeNumbersSegments;

    //        glfwTerminate();
    return 0;
}


//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
