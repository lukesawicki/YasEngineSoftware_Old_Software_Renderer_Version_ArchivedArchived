#include <GLFW/glfw3.h>


void update(unsigned char* data, unsigned char color)
{
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            data[y * 100 * 3 + x * 3] = 255;
            data[y * 100 * 3 + x * 3 + 1] = color;
            data[y * 100 * 3 + x * 3 + 2] = 0;
        }
    }
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if( !glfwInit() )
    {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    unsigned char* data = new unsigned char[100 * 100 * 3];
    for(int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            data[y * 100 * 3 + x * 3 ] = 255;
            data[y * 100 * 3 + x * 3 + 1] = 0;
            data[y * 100 * 3 + x * 3 + 2] = 0;
        }
    }

    unsigned char color = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (color; color < 255; color++)
        {
            update(data, color);
        }
        glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include<cstdlib>
//#include<iostream>
//#include<vector>
//#include<cmath>
//#include<SDL.h>
//#include"Vector2D.hpp"
//#include"YasGraphicsLibrary.hpp"
//#include"TimePicker.hpp"
//
//
////void drawGentleSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
////void drawSteepSlopeLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
////void drawLine(Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
////void render(float dt, SDL_Renderer *renderer);
//
//float aspect;
//
//int windowWidth = 1024;
//int windowHeight = 768;
//
//int pixelCounter = 0;
////Vector3D<int> axiesColor = Vector3D<int>(0, 255, 0);
//
//SDL_Window* window;
//SDL_Renderer* renderer;
//
////-----------------------------------------------------------------------------|---------------------------------------|
////                                                                            80                                     120
//int main(int argc, char * argv[])
//{
//    Vector2D<int>* screenDimensions = new Vector2D<int>(windowWidth, windowHeight);
//    //Vector3D<int> drawingColor = Vector3D<int>(0, 255, 0);
//
//    Vector3D<Uint8> red(255, 0, 0);
//    Vector3D<Uint8> green(0, 255, 0);
//    Vector3D<Uint8> blue(0, 0, 255);
//
//    bool leftMouseButtonDown = false;
//    bool quit = false;
//    SDL_Event event;
//
//    int circleSpeedFactor = 255;
//    int circleSpeed = 2 * circleSpeedFactor;
//    Vector2D<int>* circlePosition = new Vector2D<int>(0, 0);
//    YasGL::cartesianPositionToWindow(circlePosition, screenDimensions);
//    Vector3D<int>* circleColor = new Vector3D<int>(255, 255, 255);
//    int circleRadius = 50;
//    //int circleCenterX = 50
//    //int circleCenterY = 300;
//    int circleX = 0;
//    int circleY = 0;
//
//    Vector2D<int>* xAxiesBegin = new Vector2D<int>(0, windowHeight / 2);
//    Vector2D<int>* xAxiesEnd = new Vector2D<int>(windowWidth, windowHeight / 2);
//    Vector2D<int>* yAxiesBegin = new Vector2D<int>(windowWidth / 2, 0);
//    Vector2D<int>* yAxiesEnd = new Vector2D<int>(windowWidth / 2, windowHeight);
//
//    float canvasWidth = 2, canvasHeight = 2;
//    uint32_t imageWidth = 512, imageHeight = 512;
//
//    Vector2D<int>* line1_A = new Vector2D<int>(0, 10);
//    Vector2D<int>* line1_B = new Vector2D<int>(400, 60);
//
//    Vector2D<int>* line2_A = new Vector2D<int>(30, 40);
//    Vector2D<int>* line2_B = new Vector2D<int>(430, 90);
//
//    SDL_Init(SDL_INIT_VIDEO);
//
//    window = SDL_CreateWindow("YasEngine with software renderer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
//    //screen = SDL_SetVideoMode(screen_width, screen_height, 8, videoflags);
//    //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    //SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer);
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
//
//    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, windowWidth, windowHeight);
//
//    const int PIXELS_TABLE_SIZE = windowWidth * windowHeight;
//
//    Uint32* pixels = new Uint32[PIXELS_TABLE_SIZE];
//
//    memset(pixels, 255, windowWidth * windowHeight * sizeof(Uint32));
//
//    if(!window)
//    {
//        std::cerr << "Error failed to create window!\n";
//        return 1;
//    }
//    
//    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//    //SDL_RenderClear(renderer);
//    
//    //SDL_Event event;
//    bool running = true;
//
//    double time;
//    double newTime;
//    double deltaTime;
//    double fps;
//    double fpsTime;
//    unsigned int frames;
//    MSG message;
//
//    TimePicker timePicker = TimePicker();
//    time = timePicker.getSeconds();
//
//    fpsTime = 0.0F;
//    frames = 0;
//    message.message = WM_NULL;
//
//    SDL_PixelFormat* pixelFormat = nullptr;
//    Uint32 windowPixelFormat = SDL_GetWindowPixelFormat(window);
//    pixelFormat = SDL_AllocFormat(windowPixelFormat);
//    std::cout << "Bites per pixel: " << pixelFormat->BitsPerPixel << std::endl;
//    std::cout << "Bytes per pixel: " << pixelFormat->BytesPerPixel << std::endl;
//    std::cout << "Format: " << pixelFormat->format << std::endl;
//
//
//
//    // One of many formats which I found
//    //SDL_PIXELFORMAT_RGBA8888
//
//    bool switched = false;
//
//    while(running)
//    {
//        
//
//        while(SDL_PollEvent(&event))
//        {
//            //running = event.type != SDL_QUIT;
//            switch (event.type)
//            {
//                case SDL_QUIT:
//                    running = false;
//                    break;
//                case SDL_KEYDOWN:
//                    if (event.key.keysym.sym == SDLK_SPACE)
//                    {
//                        //drawingColor.x = 255;
//                        //drawingColor.y = 0;
//                        //drawingColor.z = 0;
//                    }
//                case SDL_MOUSEBUTTONUP:
//                    if (event.button.button == SDL_BUTTON_LEFT)
//                    {
//                        leftMouseButtonDown = false;
//                    }
//                    break;
//                case SDL_MOUSEBUTTONDOWN:
//                    if (event.button.button == SDL_BUTTON_LEFT)
//                    {
//                        leftMouseButtonDown = true;
//                    }
//                    break;
//                case SDL_MOUSEMOTION:
//                    if (leftMouseButtonDown)
//                    {
//                        int mouseX = event.motion.x;
//                        int mouseY = event.motion.y;
//                    }
//                    break;
//            }
//        }
//
//        
//
//        newTime = timePicker.getSeconds();  
//        deltaTime = newTime - time;
//        time = newTime;
//
//      
//
//        ++frames;
//        fpsTime = fpsTime + deltaTime;
//        if(fpsTime >= 1.0F)
//        {
//            fps = frames / fpsTime;
//            frames = 0;
//            fpsTime = 0.0F;
//        }
//
//        circlePosition->x = static_cast<int>(circlePosition->x + deltaTime * circleSpeed);
//        if (circlePosition->x < 0 && !switched) {
//            circleSpeed = circleSpeed * -1;
//            circlePosition->x = 0;
//
//        }
//
//        if (circlePosition->x > 1024) {
//            circleSpeed = circleSpeed * -1;
//            circlePosition->x = 1024;
//        }
//
//        //SDL_RenderPresent(renderer);
//        //Vector2D<int>* point0, Vector2D<int>* point1, SDL_Renderer* renderer);
//        //void drawLine(Vector2D<int>*point0, Vector2D<int>*point1, Uint32 * pixels, Vector3D<int>*drawingColor, SDL_PixelFormat * pixelFormat, int windowWidth)
//
//
//        for (int i = 0; i < PIXELS_TABLE_SIZE; i++) {
//            pixels[i] = SDL_MapRGBA(pixelFormat, 0, 0, 0, 255);
//        }
//        //YasGL::drawLine(xAxiesBegin, xAxiesEnd, pixels, &red, pixelFormat, windowWidth);
//        //YasGL::drawLine(yAxiesBegin, yAxiesEnd, pixels, &green, pixelFormat, windowWidth);
//        //YasGL::drawCircle(pixels, circlePosition, circleRadius, windowWidth, circleColor, pixelFormat);\
//
//        //YasGL::lukeDrawLine(line1_A, line1_B, pixels, &red, pixelFormat, windowWidth);
//
//        //YasGL::helsinkiDraw(line1_A, line1_B, pixels, &red, pixelFormat, windowWidth);
//        //YasGL::lukeDrawLineOctan0V1(line2_A, line2_B, pixels, &red, pixelFormat, windowWidth);
//        YasGL::lukeDrawLineOctan0V2(line2_A, line2_B, pixels, &red, pixelFormat, windowWidth);
//        //Vector2D<int>* line1_A = new Vector2D<int>(50, 50);
//        //Vector2D<int>* line1_B = new Vector2D<int>(400, 60);
//        
//        //lukeDrawLine
//
//        SDL_UpdateTexture(texture, NULL, pixels, windowWidth * sizeof(Uint32));
//
//        SDL_RenderClear(renderer);
//        SDL_RenderCopy(renderer, texture, NULL, NULL);
//        SDL_RenderPresent(renderer);
//    }
//
//    delete[] pixels;
//    SDL_DestroyTexture(texture);
//
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//
//    SDL_Quit();
//    return 0;
//}
////                                                                            80                                     120
////-----------------------------------------------------------------------------|---------------------------------------|
