#include "YasEngine.hpp"

YasEngine* YasEngine::instance = nullptr;

void YasEngine::initialize()
{
    prepareBasicSettings();
    prepareRendering();
    prepareGameWorld();
    preparePlayer();
}

void YasEngine::YasEnginStart()
{
    //std::cout << fib(10) << std::endl;
    //generateNfibonaccinumbers(10);
    //fib(10);

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

    for (auto object : objectsToDraw)
    {
        drawPolygon(object, *pixelsTable);
    }

    //for (int i = -300; i < -150; i++)
    //{
    //    for (int j = -200; j < -50; j++)
    //    {
    //        pixelsTable->drawPoint(i, j, YELLOW);
    //    }
    //}

    drawLine(A, B, *pixelsTable, YELLOW);

    drawHudElements(deltaTime);

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

}
