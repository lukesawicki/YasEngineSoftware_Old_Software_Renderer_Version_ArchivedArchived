#include"YasEngine.hpp"
#include<cstdlib>     /* srand, rand */
#include<ctime>
#include<bit>
#include<SDL_endian.h>
#include"VariousTools.hpp"
#include"Circle.hpp"
#include"Collider.hpp"
#include"CosinusPointsGenerator.hpp"
#include"FibonacciPointsGenerator.hpp"
#include"Math.hpp"
#include"PrimeNumbersPointsGenerator.hpp"
#include"SinusPointsGenerator.hpp"

YasEngine* YasEngine::instance = nullptr;

void YasEngine::initialize()
{
    prepareBasicSettings();
    prepareRendering();
    prepareGameWorld();
    preparePlayer();
    prepareSoundAndMusic();

    mathPlay = new MathematicsFunSurface(0, 0, static_cast<int>(windowDimensions->x * 0.5F), static_cast<int>(windowDimensions->y * 0.5F), BLACK);

    SinusPointsGenerator sinusPointsGenerator;
    CosinusPointsGenerator cosinusPointsGenerator;
}

void YasEngine::clean()
{
    for (auto drawableObject : objectsToDraw)
    {
        delete drawableObject;
    }

    delete sinusPoints;
    delete cosinusPoints;
    delete fibonacciePoints;
    delete primeNumbersPoints;
    delete mathPlay;
    delete pixelsTable;
    delete windowDimensions;

    // clean up our resources
    Mix_FreeChunk(shootSound);
    Mix_FreeChunk(hitSound);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
	Mix_Quit();
    SDL_DestroyTexture(screenTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void YasEngine::YasEnginStart()
{
    TimePicker timePicker = TimePicker();
    time = timePicker.getSeconds();
    fpsTime = 0.0F;
    frames = 0;

    spawner.spawnObject(go);

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

    clean();

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
	// old SDL_Image

    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;

    }

    
    std::string basePath = SDL_GetBasePath();

    std::string pictureFilePath;
    pictureFilePath.append(basePath);
    pictureFilePath.append("\\map00.png");
    


    ////////////////////
    customImageSurface = IMG_Load(pictureFilePath.c_str());

    if(customImageSurface == NULL)
    {
        std::cout << "Error during loading image file: " << SDL_GetError() << std::endl;
    }

    windowSurface = SDL_GetWindowSurface(window);
    windowsSurfaceFormat = windowSurface->format;//SDL_AllocFormat(SDL_PIXELFORMAT_ABGR8888);
    
    optimizedSurface = SDL_ConvertSurface(customImageSurface, windowsSurfaceFormat, 0);


    // HERE WRZUCIC LADOWANIE OBRAZKOW bo jest po pobraniu windowsSurfaceFormat


    //timizedSurface->pixels

	if (optimizedSurface != NULL)
    {
        SDL_FreeSurface(customImageSurface);

        map = new SDL_Rect();
        map->x = 0;
        map->y = 0;
        map->w = WINDOW_WIDTH;
        map->h = WINDOW_HEIGHT;

    }
    else
    {
        std::cout << "Unable to optimize image SDL Error-> " << SDL_GetError() << std::endl;
    }

    SDL_Color rgb;
    Uint32 data = getpixel(optimizedSurface, 1, 1);
    SDL_GetRGBA(data, optimizedSurface->format, &rgb.r, &rgb.g, &rgb.b, &rgb.a);
	// end old SDL_Image

    loadMonsters();
}

void YasEngine::prepareBasicSettings()
{
    if (endianness)
    {
        std::cout << "BIG ENDIAN" << std::endl;
    }
    else
    {
        std::cout << "LITTLE ENDIAN" << std::endl;
    }

    SDL_Init(SDL_INIT_EVERYTHING);

    windowDimensions    =   new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);
    window              =   SDL_CreateWindow("YasEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    SDL_SetWindowMinimumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_ShowCursor(SDL_DISABLE);
}

void YasEngine::drawHudElements(double& deltaTime)
{
    #ifdef DEBUG_DRAWINGS
        drawCartesianAxies(*pixelsTable);
    #endif // DEBUG_DRAWINGS

    drawCrossHair(mouseX, mouseY, *pixelsTable, false);
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
    handlePhysics();
    for (auto object : objectsToDraw)
    {
        if (object->isAlive)
        {
            object->move(static_cast<float>(deltaTime));
            object->regeneratePolygon();
        }
    }

    Projectile* projectile = player->shoot();
    if (projectile != nullptr)
    {
        Mix_PlayChannel(-1, shootSound, 0);
        objectsToDraw.push_back(projectile);
    }

    if(go != nullptr)
    {
        objectsToDraw.push_back(go);
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
        if (object->isAlive)
        {
            drawPolygon(object, *pixelsTable);
        }
    }
    
    int vertical = static_cast<int>(-WINDOW_WIDTH * 0.25F);
    int horizontal = static_cast<int>(-WINDOW_HEIGHT * 0.25F);

    mathPlay->verticalLineOnScreen(0, GREEN);
    mathPlay->horizontalLineOnScreen(0, RED);//-WINDOW_HEIGHT * 0.25F

	// mathPlay->drawNumbersAsGroupOfNotConnectedLines(sinusPoints, 100, YELLOW);

    mathPlay->drawNumbersAsGroupOfLines(cosinusPoints->points, cosinusPoints->pointsNumber, YELLOW, true);
    mathPlay->drawNumbersAsGroupOfLines(sinusPoints->points, sinusPoints->pointsNumber, BLUE, false);
    mathPlay->drawNumbersAsGroupOfLines(fibonacciePoints->points, fibonacciePoints->pointsNumber, RED, false);

    mathPlay->drawNumbersAsGroupOfLines(primeNumbersPoints->points, primeNumbersPoints->pointsNumber, YELLOW, false);

    //mathPlay->copyPixelsInToPIxelTable(*pixelsTable);

    verticalLineOnWholeScreen(*pixelsTable, 0, GREEN);
    horizontalLineOnWholeScreen(*pixelsTable, 0, RED);

    drawHudElements(deltaTime);

	// old SDL_Image
    //SDL_BlitSurface(optimizedSurface, NULL, windowSurface, pictureRect);

    SDL_BlitSurface(optimizedMonstersSurfaces.at(2), NULL, windowSurface, monsterRectangle);

    SDL_UpdateTexture(screenTexture , NULL, pixelsTable->pixels, WINDOW_WIDTH * 4);
    SDL_RenderCopyExF(renderer, screenTexture, NULL, NULL, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE); //SDL_FLIP_VERTICAL);
	SDL_RenderPresent(renderer);

	// old SDL_Image
    ///////////////

                    //Apply the PNG image
    

    //Update the surface
     SDL_UpdateWindowSurface(window);

    ///////////////
    // end old SDL_Image
}

void YasEngine::handlePhysics()
{
    if (objectsToDraw.size() >= 3)
    {
        for (int i = 0; i < static_cast<int>(objectsToDraw.size() - 2); i++)
        {
            if (!objectsToDraw[i]->isAlive || objectsToDraw[i]->iAm == GameObject::PROTAGONIST)
            {
                continue;
            }

            if (Collider::isCollidingWithWall(objectsToDraw[i]->collider, *windowDimensions))
            {
                objectsToDraw[i]->isAlive = false;
                continue;
            }

            for (int j = i; j < static_cast<int>(objectsToDraw.size()); j++)
            {
                if (!objectsToDraw[j]->isAlive || objectsToDraw[j]->iAm == GameObject::PROTAGONIST ||
                    (objectsToDraw[i]->iAm == GameObject::PROJECTILE && objectsToDraw[j]->iAm == GameObject::PROJECTILE) ||
                    (objectsToDraw[i]->iAm == GameObject::COLLECTIBLE && objectsToDraw[j]->iAm == GameObject::COLLECTIBLE))
                {
                    continue;
                }

                if (!(objectsToDraw[i] == objectsToDraw[j]) && objectsToDraw[i]->isAlive && objectsToDraw[j]->isAlive)
                {
                    if (Collider::isInCollision(objectsToDraw[i]->collider, objectsToDraw[j]->collider))
                    {
                        objectsToDraw[i]->isAlive = false;
                        objectsToDraw[j]->isAlive = false;
                        Mix_PlayChannel(-1, hitSound, 0);
                    }
                }
            }
        }
    }
}

void YasEngine::prepareSoundAndMusic()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
    {
        std::cout << "Error cannot open audio device" << std::endl;
    }

    std::string basePath = SDL_GetBasePath();

    std::string musicFilePath;
    musicFilePath.append(basePath);
    musicFilePath.append("\music.wav");

    std::string shootSoundFilePath;
    shootSoundFilePath.append(basePath);
    shootSoundFilePath.append("\shoot.wav");

    std::string hitSoundFilePath;
    hitSoundFilePath.append(basePath);
    hitSoundFilePath.append("\hit.wav");
    std::cout << "hit.wav path: -> " << hitSoundFilePath << std::endl;

    Mix_Init(MIX_DEFAULT_FORMAT);

    music = Mix_LoadMUS(musicFilePath.c_str());
    if (music == NULL)
    {
        std::cout << "Error while loading music. Cannot load music." << std::endl;
        std::cout << "SDL message: " << SDL_GetError() << std::endl << " | Mix library error: " << Mix_GetError() << std::endl;
        quit = true;
    }

    shootSound = Mix_LoadWAV(shootSoundFilePath.c_str());
    hitSound = Mix_LoadWAV(hitSoundFilePath.c_str());

    if (shootSound == NULL || hitSound == NULL)
    {
        std::cout << "Error while loading sounds. Cannot load sounds." << std::endl;
        std::cout << "SDL message: " << SDL_GetError() << std::endl << " | Mix library error: " << Mix_GetError() << std::endl;
        quit = true;
    }
    Mix_PlayMusic(music, 999);
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
        FibonacciPointsGenerator fibonacciPointsGenerator;
        PrimeNumbersPointsGenerator primeNumberPointsGenerator;

        sinusPoints = sinusPointsGenerator.generatePoints();
        cosinusPoints = cosinusPointsGenerator.generatePoints();
        fibonacciePoints = fibonacciPointsGenerator.generatePoints();
        primeNumbersPoints = primeNumberPointsGenerator.generatePoints();

        spawner.position.x = -200;
        spawner.position.y = 0;
}


// old SDL_Image
Uint32 YasEngine::getpixel(SDL_Surface* surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16*)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32*)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}
// End old SDL_Image


