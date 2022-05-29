#include "YasEngine.hpp"
#include <cstdlib>     /* srand, rand */
#include <ctime> 
#include<SDL_endian.h>

#include"VariousTools.hpp"

#include"Circle.hpp"

#include"Math.hpp"
YasEngine* YasEngine::instance = nullptr;

void YasEngine::initialize()
{
    prepareBasicSettings();
    prepareRendering();
    prepareGameWorld();
    preparePlayer();

    //mathPlay = new Tile(0, 0, windowDimensions->x * 0.5F, windowDimensions->y * 0.5F, BLACK);
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


//
// for (int i = 0; i < 20; i++)
// {
//     for (int j = 0; j < 40; j++)
//     {
//         simplifiedMap[i][j] = rand() % 3;

void YasEngine::drawTiles()
{
    for(int i=0; i<25; i++)
    {
	    for(int j=0; j<40; j++)
	    {
            if (simplifiedMap[i][j] != -1)
            {
                tiles[simplifiedMap[i][j]].setPositions(j * 32, (i * 32));// -32); // In old version the origin point is bottom left
                tiles[simplifiedMap[i][j]].copyPixelsInToPIxelTable(*pixelsTable, false);
            }
	    }
    }

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
        player->rotateToMousePositionInLocalCoordinateSystem(mousePositionChangeInformation->x, mousePositionChangeInformation->y, windowDimensions);
    }

    mouseX = mousePositionChangeInformation->x;
    mouseY = mousePositionChangeInformation->y;

    windowPositionToCartesianPosition(mouseX, mouseY, windowDimensions);

    projectile = nullptr;



}

void YasEngine::render(double& deltaTime)
{
    pixelsTable->clearColor(BLACK);
    //mathPlay->clearColor(BLACK);

    for (auto object : objectsToDraw)
    {
        drawPolygon(object, *pixelsTable);
    }
    drawHudElements(deltaTime);

    int vertical = -WINDOW_WIDTH * 0.25F;
    int horizontal = -WINDOW_HEIGHT * 0.25F;

    // mathPlay->copyPixelsInToPIxelTable(*pixelsTable);

    drawTiles();

    verticalLineOnScreen(*pixelsTable, -WINDOW_WIDTH * 0.5F, RED);
    horizontalLineOnScreen(*pixelsTable, -WINDOW_HEIGHT * 0.5F + 1, RED);

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

        /* initialize random seed: */
        srand(std::time(NULL));

        /* generate secret number between 1 and 10: */
        //Tile(int x, int y, int width, int height, const Vector4D<Uint8>&defaultColor);
        tiles = new Tile[11];
        for(int i=0; i<9; i++)
        {
            tiles[i].setPositions(0, 0);
            tiles[i].setSizes(32, 32);
            tiles[i].createPixelsTable();
            tiles[i].clearColor(BLACK);
            tiles[i].drawPattern(i, BLUE);
        }

        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 40; j++)
            {
                simplifiedMap[i][j] = -1;
            }
        }

        for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 40; j++)
            {
                //if((i<10 || i>14) || (j < 17 || j>22))
                if ((i < numberOfWallsTop || i> numberOfWallsVertically - (numberOfWallsTop + 1))  || (j < numberOfWallsLeft || j>numberOfWallsHorizontally - (numberOfWallsRight + 1)))
                {
                    simplifiedMap[i][j] = rand() % 8;
                }
            }
        }

}
