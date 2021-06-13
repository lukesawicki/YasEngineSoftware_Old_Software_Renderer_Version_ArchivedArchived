#include <GLFW/glfw3.h>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<cmath>
//#include<SDL.h>

#include"Vector2D.hpp"
#include"YasGraphicsLibrary.hpp"
#include"TimePicker.hpp"


//void drawGentleSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
//void drawSteepSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
//void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
//void render(float dt, SDL_Renderer *renderer);

float aspect;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

const int RGB = 3;

int pixelCounter = 0;
//Vector3D<int> axiesColor = Vector3D<int>(0, 255, 0);

const uint8_t RED_POSITION = 0;
const uint8_t GREEN_POSITION = 1;
const uint8_t BLUE_POSITION = 2;

GLFWwindow* window;

    //-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120
int main(int argc, char* argv[])
{
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

    Vector2D<int>* windowDimensions = new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);
    //Vector3D<int> drawingColor = Vector3D<int>(0, 255, 0);

    Vector3D<uint8_t> red(255, 0, 0);
    Vector3D<uint8_t> green(0, 255, 0);
    Vector3D<uint8_t> blue(0, 0, 255);
    Vector3D<uint8_t> BLACK(0, 0, 0);

    bool leftMouseButtonDown = false;
    bool quit = false;

    int circleSpeedFactor = 255;
    int circleSpeed = 2 * circleSpeedFactor;
    Vector2D<int>* circlePosition = new Vector2D<int>(0, 0);
    YasGL::cartesianPositionToWindow(circlePosition, windowDimensions);
    Vector3D<uint8_t>* circleColor = new Vector3D<uint8_t>(255, 255, 255);
    int circleRadius = 50;
    //int circleCenterX = 50
    //int circleCenterY = 300;
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

    constexpr int PIXELS_TABLE_SIZE = WINDOW_WIDTH * WINDOW_HEIGHT * RGB;

//    unsigned char* data = new unsigned char[100 * 100 * 3];
//    for (int y = 0; y < 100; y++)
//    {
//        for (int x = 0; x < 100; x++)
//        {
//            data[3 * (y * 100 + x) + RED_POSITION] = 255;
//            data[3 * (y * 100 + x) + GREEN_POSITION] = 0;
//            data[3 * (y * 100 + x) + BLUE_POSITION] = 0;
//        }
//    }

    uint8_t* pixels = new uint8_t[PIXELS_TABLE_SIZE];

    for (int y = 0; y < WINDOW_HEIGHT; y++)
    {
        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            pixels[3 * (y * WINDOW_WIDTH + x) + RED_POSITION] = 0;
            pixels[3 * (y * WINDOW_WIDTH + x) + GREEN_POSITION] = 0;
            pixels[3 * (y * WINDOW_WIDTH + x) + BLUE_POSITION] = 0;
        }
    }



    for (int i = 0; i < PIXELS_TABLE_SIZE; i++)
    {
        //std::cout << i << std::endl;
    }

    //memset(pixels, 255, windowWidth * windowHeight * sizeof(Uint32));

    if (!window)
    {
        std::cerr << "Error failed to create window!\n";
        return 1;
    }

    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    //SDL_RenderClear(renderer);

    //SDL_Event event;
    bool running = true;

    double time;
    double newTime;
    double deltaTime;
    double fps;
    double fpsTime;
    unsigned int frames;
    //MSG message;

    TimePicker timePicker = TimePicker();
    time = timePicker.getSeconds();

    fpsTime = 0.0F;
    frames = 0;


    // One of many formats which I found
    //SDL_PIXELFORMAT_RGBA8888

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
            if (circlePosition->x < 0 && !switched) {
                circleSpeed = circleSpeed * -1;
                circlePosition->x = 0;

            }

            if (circlePosition->x > 1024) {
                circleSpeed = circleSpeed * -1;
                circlePosition->x = 1024;
            }

            YasGL::clearColor(pixels, &BLACK, windowDimensions);

            //SDL_RenderPresent(renderer);
            //Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
            //void drawLine(Vector2D<int>*point0, Vector2D<int>*point1, Uint32 * pixels, Vector3D<int>*drawingColor, SDL_PixelFormat * pixelFormat, int windowWidth)


            for (int i = 0; i < PIXELS_TABLE_SIZE; i++) {
                //pixels[i] = SDL_MapRGBA(pixelFormat, 0, 0, 0, 255);
            }
            //YasGL::drawLine(xAxiesBegin, xAxiesEnd, pixels, &red, pixelFormat, windowWidth);
            //YasGL::drawLine(yAxiesBegin, yAxiesEnd, pixels, &green, pixelFormat, windowWidth);
            YasGL::drawCircle(circlePosition, circleRadius, pixels, circleColor, windowDimensions);\

            //YasGL::lukeDrawLine(line1_A, line1_B, pixels, &red, pixelFormat, windowWidth);

            //YasGL::helsinkiDraw(line1_A, line1_B, pixels, &red, pixelFormat, windowWidth);
            //YasGL::lukeDrawLineOctan0V1(line2_A, line2_B, pixels, &red, pixelFormat, windowWidth);



            //Vector2D<int>* point0, Vector2D<int>* point1, uint8_t* pixels, Vector3D<uint8_t>* drawingColor, int windowWidth
            YasGL::lukeDrawLineOctan0V2(line2_A, line2_B, pixels, &red, windowDimensions);
            
            //uint8_t some8Int;

            //Vector2D<int>* line1_A = new Vector2D<int>(50, 50);
            //Vector2D<int>* line1_B = new Vector2D<int>(400, 60);

            //lukeDrawLine

            glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
            /*
            SDL_UpdateTexture(texture, NULL, pixels, WINDOW_WIDTH * sizeof(Uint32));

            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            */
        }

        delete[] pixels;
        glfwTerminate();
        return 0;
    }
}
//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|




//#include <GLFW/glfw3.h>
//#include<iostream>
//
//void update(unsigned char* data, unsigned char color)
//{
//    for (int y = 0; y < 100; y++)
//    {
//        for (int x = 0; x < 100; x++)
//        {
//            data[y * 100 * 3 + x * 3] = 255;
//            data[y * 100 * 3 + x * 3 + 1] = color;
//            data[y * 100 * 3 + x * 3 + 2] = 0;
//        }
//    }
//}
//
//void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
//{
//    std::cout << "KEY: " << key << std::endl;
//}
//
//int main(void)
//{
//    const unsigned char RED_POSITION = 0;
//    const unsigned char GREEN_POSITION = 1;
//    const unsigned char BLUE_POSITION = 2;
//
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//    {
//        return -1;
//    }
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwSetKeyCallback(window, keyCallback);
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//
//    unsigned char* data = new unsigned char[640 * 480 * 3];
//    for (int y = 0; y < 480; y++)
//    {
//        for (int x = 0; x < 640; x++)
//        {
//            data[3 * (y * 640 + x) + RED_POSITION] = 255;
//            data[3 * (y * 640 + x) + GREEN_POSITION] = 0;
//            data[3 * (y * 640 + x) + BLUE_POSITION] = 0;
//        }
//    }
//
//    unsigned char color = 0;
//
//    /* Loop until the user closes the window */
//    bool changeColor = false;
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
//            changeColor = true;
//        }
//
//        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
//            changeColor = false;
//        }
//        if (changeColor)
//        {
//            std::cout << "CHANGING COLOR" << std::endl;
//            color = color + 1;
//            update(data, color);
//            //for (color; color < 255; color++)
//            //{
//            //    update(data, color);
//            //}
//        }
//        glDrawPixels(640, 480, GL_RGB, GL_UNSIGNED_BYTE, data);
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}
