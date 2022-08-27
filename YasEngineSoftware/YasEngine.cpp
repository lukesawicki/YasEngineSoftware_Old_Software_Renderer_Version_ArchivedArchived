#include "YasEngine.hpp"
#include <cstdlib>     /* srand, rand */
#include <ctime> 
#include<SDL_endian.h>
#include"VariousTools.hpp"
#include"Circle.hpp"
#include "CosinusPointsGenerator.hpp"
#include"Math.hpp"
#include "SinusPointsGenerator.hpp"
YasEngine* YasEngine::instance = nullptr;

void YasEngine::initialize()
{
    prepareBasicSettings();
    prepareRendering();
    prepareGameWorld();
    preparePlayer();

    mathPlay = new MathematicsFunSurface(0, 0, static_cast<int>(windowDimensions->x * 0.5F), static_cast<int>(windowDimensions->y * 0.5F), BLACK);

    SinusPointsGenerator sinusPointsGenerator;
    CosinusPointsGenerator cosinusPointsGenerator;

    //sinusPoints = sinusPointsGenerator.generatePoints();

    // cosinusPoints = new Vector2D<float>[6];//cosinusPointsGenerator.generatePoints();
    //
    // cosinusPoints[0].x = 10;
    // cosinusPoints[0].y = 10;
    //
    // cosinusPoints[1].x = 30;
    // cosinusPoints[1].y = 20;
    //
    // cosinusPoints[2].x = 60;
    // cosinusPoints[2].y = 20;
    //
    // cosinusPoints[3].x = 70;
    // cosinusPoints[3].y = 50;
    //
    // cosinusPoints[4].x = 90;
    // cosinusPoints[4].y = 100;
    //
    // cosinusPoints[5].x = 120;
    // cosinusPoints[5].y = 140;

    // Odtworzyc tworzenie generatorow
    // wrzucanie punktow

}

void YasEngine::YasEnginStart()
{
    TimePicker timePicker = TimePicker();
    time = timePicker.getSeconds();
    fpsTime = 0.0F;
    frames = 0;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            handleInput(event);
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

        update(deltaTime);
        render(deltaTime);
    }

    for (auto drawableObject : objectsToDraw)
    {
        delete drawableObject;
    }

    return;
}

void YasEngine::drawMathArt()
{
}

void YasEngine::prepareRendering()
{
    pixelsTable     =   new PixelsTable(WINDOW_WIDTH, WINDOW_HEIGHT, BLACK);
    renderer        =   SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

    screenTexture   =   SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void YasEngine::prepareBasicSettings()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    windowDimensions    =   new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);
    window              =   SDL_CreateWindow("YasEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    SDL_SetWindowMinimumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void YasEngine::drawHudElements(double& deltaTime)
{
    #ifdef DEBUG_DRAWINGS
        drawCartesianAxies(*pixelsTable);
    #endif // DEBUG_DRAWINGS

    drawCrossHair(mouseX, mouseY, *pixelsTable);
}

void YasEngine::handleInput(SDL_Event& event)
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
        if (event.type == SDL_MOUSEMOTION)
        {
            int x;
            int y;
            mousePositionChangeInformation->mouseMoved = true;
            SDL_GetMouseState(&x, &y);
            mousePositionChangeInformation->x = x;
            mousePositionChangeInformation->y = y;

        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            player->isShooting      = true;
        }
        if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
        {
            player->isShooting      = false;
        }
    }
}

void YasEngine::preparePlayer()
{
    player = new Player(0, 0);
    player->setColor(YELLOW);
    player->setInput(input);
    player->setInput(mousePositionChangeInformation);
    objectsToDraw.push_back(player);
}

void YasEngine::update(double& deltaTime)
{
    for (auto object : objectsToDraw)
    {
        object->move(static_cast<float>(deltaTime));
        object->regeneratePolygon();
    }

    Projectile* projectile = player->shoot();
    if (projectile != nullptr)
    {
        objectsToDraw.push_back(projectile);
    }

    if (mousePositionChangeInformation->mouseMoved || input->up || input->down || input->left || input->right)
    {
        player->rotateToMousePositionInLocalCoordinateSystem(static_cast<float>(mousePositionChangeInformation->x), static_cast<float>(mousePositionChangeInformation->y), windowDimensions);
    }

    mouseX = static_cast<float>(mousePositionChangeInformation->x);
    mouseY = static_cast<float>(mousePositionChangeInformation->y);

    windowPositionToCartesianPosition(mouseX, mouseY, windowDimensions);

    projectile = nullptr;



}

void YasEngine::render(double& deltaTime)
{
    pixelsTable->clearColor(BLACK);
    mathPlay->clearColor(BLACK);

    for (auto object : objectsToDraw)
    {
        drawPolygon(object, *pixelsTable);
    }
    drawHudElements(deltaTime);

    int vertical = static_cast<int>(-WINDOW_WIDTH * 0.25F);
    int horizontal = static_cast<int>(-WINDOW_HEIGHT * 0.25F);

    mathPlay->verticalLineOnScreen(0, GREEN);
    mathPlay->horizontalLineOnScreen(0, RED);//-WINDOW_HEIGHT * 0.25F

   // mathPlay->drawNumbersAsGroupOfNotConnectedLines(sinusPoints, 100, YELLOW);

    mathPlay->drawNumbersAsGroupOfLines(cosinusPoints.points, cosinusPoints.pointsNumber, YELLOW, true);
    mathPlay->drawNumbersAsGroupOfLines(sinusPoints.points, sinusPoints.pointsNumber, BLUE, true);

    mathPlay->copyPixelsInToPIxelTable(*pixelsTable);

    verticalLineOnScreen(*pixelsTable, 0, GREEN);
    horizontalLineOnScreen(*pixelsTable, 0, RED);

    //mathPlay->

    SDL_UpdateTexture(screenTexture , NULL, pixelsTable->pixels, WINDOW_WIDTH * 4);
    SDL_RenderCopyExF(renderer, screenTexture, NULL, NULL, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE); //SDL_FLIP_VERTICAL);
    SDL_RenderPresent(renderer);
}

void YasEngine::prepareGameWorld()
{
    #ifdef DEBUG_DRAWINGS
        Circle* circle = new Circle(100, 0, 0);
        circle->setColor(BLUE);
        objectsToDraw.push_back(circle);
    #endif
        SinusPointsGenerator sinusPointsGenerator;
        CosinusPointsGenerator cosinusPointsGenerator;

        sinusPoints.points = sinusPointsGenerator.generatePoints();
        sinusPoints.pointsNumber = sinusPointsGenerator.pointsNumber;

        cosinusPoints.points = cosinusPointsGenerator.generatePoints();
        cosinusPoints.pointsNumber = cosinusPointsGenerator.pointsNumber;

}
