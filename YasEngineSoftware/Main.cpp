//#include<Windows.h>
#define SDL_MAIN_HANDLED
#include<SDL.h>
#include<SDL_endian.h>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<cmath>
#include<bitset>
#include"VariousTools.hpp"
#include"YasVector2D.hpp"
#include"YasGraphicsLibrary.hpp"
#include"TimePicker.hpp"
#include"PixelsTable.hpp"
#include"Circle.hpp"
#include"YasPolygon.hpp"
#include"Player.hpp"
#include"InputOutputHandler.hpp"

//Strange World by Darkroom (c) copyright 2022 Licensed under a Creative Commons Attribution Noncommercial  (3.0) license. http://dig.ccmixter.org/files/mactonite/64736 Ft: Martin Cee

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

    SDL_Window* window = SDL_CreateWindow("YasEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    
    listRenderersInformation();

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // SDL_RENDERER_PRESENTVSYNC);

    SDL_SetWindowMinimumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

    SDL_Texture* screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    


    std::vector<int> groupOfPrimeNumbers = generatePrimeNumberLessThanN(2000);

    int numberOfVerticesFromPrimeNumbers = groupOfPrimeNumbers.size() / 2;

    YasVector2D<float>* verticesForPrimeNumbersSegments = generateVerticesFromNumbers(groupOfPrimeNumbers);

    std::cout << "NUMBER OF PRIME NUMBERS: " << groupOfPrimeNumbers.size() << std::endl;


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

    if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
        std::cout << "Endianness: BIG_ENDIAN " << std::endl;
    }

    if (SDL_BYTEORDER == SDL_LIL_ENDIAN)
    {
        std::cout << "Endianness: LITTLE_ENDIAN " << std::endl;
    }

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event event;


    while (!quit)
    {
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else
            {
                if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            quit = true;
                        break;
                        case SDLK_w:
                            input->up = true;
                            break;
                        case SDLK_s:
                            input->down = true;
                                break;
                        case SDLK_a:
                            input->left = true;
                                break;
                        case SDLK_d:
                            input->right = true;
                                break;
                        default:
                            ;
                    }
                }
                if (event.type == SDL_KEYUP)
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_w:
                            input->up = false;
                        break;
                        case SDLK_s:
                            input->down = false;
                        break;
                        case SDLK_a:
                            input->left = false;
                        break;
                        case SDLK_d:
                            input->right = false;
                        break;
                        default:
                        ;
                    }
                }
                if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
                {
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
                    {
                        input->mouseLeftButton = true;
                        player->isShooting = true;
                    }
                    if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
                    {
                        input->mouseLeftButton = false;
                        player->isShooting = false;
                    }

                                        //case SDL_MOUSEBUTTONDOWN:
                                        //    mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                                        //    break;

                                        //case SDL_MOUSEBUTTONUP:
                                        //    mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                                        //    break;
                    mousePositionChangeInformation->mouseMoved = true;
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    mousePositionChangeInformation->x = x;
                    mousePositionChangeInformation->y = y;

                }
            }
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
            
            pixelsTable.clearColor(ALT_BLACK);
           // SDL_RenderClear(renderer);
            
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
            
            //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            

            /*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            for (int i = 0; i < WINDOW_HEIGHT/2; i++)
            {
                for (int j = 0; j < WINDOW_WIDTH/2; j++)
                {
                    if (i == j)
                    {
                        SDL_RenderDrawPoint(renderer, j, i);
                    }
                }
            }*/

            for (int i = 0; i < WINDOW_HEIGHT / 3; i++)
            {
                //for (int j = 0; j < WINDOW_WIDTH / 2; j++)
                //{
                //    if (i == j)
                //    {
                        pixelsTable.drawPoint(50, i, YELLOW);
                //    }
                //}
            }

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

            SDL_UpdateTexture(screenTexture, NULL, pixelsTable.pixels, WINDOW_WIDTH * 4);
            SDL_RenderCopyExF(renderer, screenTexture, NULL, NULL, 0, NULL, SDL_RendererFlip::SDL_FLIP_VERTICAL);
            SDL_RenderPresent(renderer);


    }

    for (auto drawableObject : objectsToDraw)
    {
        delete drawableObject;
    }

    delete[] verticesForPrimeNumbersSegments;
    return 0;
}


//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
