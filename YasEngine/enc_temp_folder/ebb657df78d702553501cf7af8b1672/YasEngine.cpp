#include"YasEngine.hpp"
//#include<SDL_endian.h>
#include<bit>
#include<SDL_mixer.h>
#include <set>

#include"VariousTools.hpp"
#include"Circle.hpp"
#include "Collider.hpp"
#include "CosinusPointsGenerator.hpp"
#include "FibonacciPointsGenerator.hpp"
#include"PrimeNumbersPointsGenerator.hpp"
#include"SinusPointsGenerator.hpp"

YasEngine* YasEngine::instance = nullptr;

void YasEngine::initialize()
{

    srand(clock());

    prepareBasicSettings();
    prepareRendering();
    preparePlayer();
    prepareGameWorld();
    prepareSoundAndMusic();
    prepareInterface();

    writer.initialize();

    surfaceWithMathBasedEffects = new SurfaceWithMathBasedEffects(0, static_cast<int>(windowDimensions->y * 0.5F), static_cast<int>(windowDimensions->x * 0.5F), static_cast<int>(windowDimensions->y), BLACK);

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
    delete surfaceWithMathBasedEffects;
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
    checkEndianness();

    SDL_Init(SDL_INIT_EVERYTHING);

    windowDimensions    =   new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);
    window              =   SDL_CreateWindow("YasEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    SDL_SetWindowMinimumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_ShowCursor(SDL_DISABLE);
}

void YasEngine::checkEndianness()
{
    if constexpr (std::endian::native == std::endian::big)
    {
        std::cout << "BIG ENDIAN" << std::endl;
        endianness = 0;
    }
    else
    {
        if (std::endian::native == std::endian::little)
        {
            std::cout << "LITTLE ENDIAN" << std::endl;
            endianness = 1;
        }
        else
        {
            std::cout << "MIXED ENDIAN" << std::endl;
            endianness = 2;
        }
    }
}

void YasEngine::drawHudElements(double& deltaTime)
{
    drawCartesianAxies(*pixelsTable);
    drawCrossHair(mouseX, mouseY, *pixelsTable, false);

    drawHorizontalLine(*pixelsTable, mapFrame.topLineSegment.point0.x, mapFrame.topLineSegment.point1.x, mapFrame.topLineSegment.point0.y, RED);
    drawHorizontalLine(*pixelsTable, mapFrame.bottomLineSegment.point0.x, mapFrame.bottomLineSegment.point1.x, mapFrame.bottomLineSegment.point0.y, GREEN);

    drawVerticalLine(*pixelsTable, mapFrame.leftLineSegment.point0.y, mapFrame.leftLineSegment.point1.y, mapFrame.leftLineSegment.point0.x, YELLOW);
    drawVerticalLine(*pixelsTable, mapFrame.rightLineSegment.point0.y, mapFrame.rightLineSegment.point1.y, mapFrame.rightLineSegment.point0.x, YELLOW);


    drawVerticalLine(*pixelsTable, 300, -20, -400, YELLOW);
}

void YasEngine::handleInput(SDL_Event& event)
{
    if (event.type == SDL_QUIT)
    {
        quit = true;
    }
    else
    {
        handleKeyboardInput(event);
        handleMouseInput(event);
    }
}

void YasEngine::handleKeyboardInput(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            handleGameStateWhenESCbuttonPushed();
            break;
        case SDLK_SPACE:
            handleGameStateWhenSPACEbuttonPushed();
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
}

void YasEngine::handleMouseInput(SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        handleMouseMovement();
    }
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        switch (gameState)
        {
        case GAMEPLAY:
            player->isShooting = true;
            break;
        case MAIN_MENU_RESTART:
            handleClickedButtons();
            break;
        case INTRO:
            gameState = GameState::MAIN_MENU_RESTART;
            break;
        case OUTRO:
            quit = true;
            break;
        default:
            ;
        }
    }

    if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
    {
        switch (gameState)
        {
        case GAMEPLAY:
            player->isShooting = false;
            break;
        }
    }
}

void YasEngine::handleMouseMovement()
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    mousePositionChangeInformation->mouseMoved = true;
    mousePositionChangeInformation->x = x;
    mousePositionChangeInformation->y = y;
    mouseX = static_cast<float>(mousePositionChangeInformation->x);
    mouseY = static_cast<float>(mousePositionChangeInformation->y);

    // TODO sprawdzenie ktory Button zostal klikniety i obsluga tego

    windowPositionToCartesianPosition(mouseX, mouseY, windowDimensions);
}

void YasEngine::handleSpawningCollectibles()
{
    // timePicker.getMiliseconds();
    for (int i = 0; i < 8; i++)
    {
        // LOSUJ 4 razy liczbe z 16 spawnerPostions
        int randomSpawner = Randomizer::drawNumberClosedInterval(0, 15);

        int firstLevelNodeIndex = spawnersPositions[randomSpawner]->firstLevelNode;
        int secondLevelNodeIndex = spawnersPositions[randomSpawner]->secondLevelNode;

        spawners->childNodes[firstLevelNodeIndex]->childNodes[secondLevelNodeIndex]->spawner->spawnObject(go);
        if (go != nullptr)
        {
            objectsToDraw.push_back(go);
            go = nullptr;
        }
    }
}

void YasEngine::handleProjectiles()
{
    Projectile* projectile = player->shoot();

    if (projectile != nullptr)
    {
        Mix_PlayChannel(-1, shootSound, 0);
        objectsToDraw.push_back(projectile);
    }

    if (projectile != nullptr)
    {
        projectile = nullptr;
    }
}

void YasEngine::handlePlayer()
{
    if (mousePositionChangeInformation->mouseMoved || input->up || input->down || input->left || input->right)
    {
        player->rotateToMousePositionInLocalCoordinateSystem(static_cast<float>(mousePositionChangeInformation->x), static_cast<float>(mousePositionChangeInformation->y), windowDimensions);
    }
}

void YasEngine::preparePlayer()
{
    srand(clock());
    int sizeOfGameplaySpace = windowDimensions->x * 0.25F;
    int x = Randomizer::drawNumberClosedInterval(0, sizeOfGameplaySpace) - 64;
    int y = Randomizer::drawNumberClosedInterval(0, sizeOfGameplaySpace) - 64;

    player = new Player(( -sizeOfGameplaySpace)+x, 0+y);
    player->setColor(YELLOW);
    player->setInput(input);
    player->setInput(mousePositionChangeInformation);
    objectsToDraw.push_back(player);
}

void YasEngine::update(double& deltaTime)
{
    // TODO switch with handling different things
    if(gameState==GameState::GAMEPLAY)
    {
        handleSpawningCollectibles();
	    handlePhysics();
        moveObjects();
        handleProjectiles();
        handlePlayer();
    }
}

void YasEngine::render(double& deltaTime) {
    pixelsTable->clearColor(BLACK);
    surfaceWithMathBasedEffects->clearColor(BLACK);

    switch (gameState)
    {
    case INTRO:
        writer.write(0, 100, "THE BEOUTY OF MATH       POWERED BY YASENGINE", YELLOW, *pixelsTable); // TODO write title and version and tha game is powered by YasEngine
        break;
    case MAIN_MENU_RESTART:
        drawButtons();
        break;
    case GAMEPLAY:
        renderGameObjects(deltaTime);
        renderViewports(deltaTime);
        break;
    case OUTRO:
        writer.write(0, 100, "CREDITS       CODE DESIGN LUKASZ LUKE SAWICKI       SOUND AND MUSIC FROM INTERNET WITH FRE LICENSE", BLUE, *pixelsTable); // TODO Write creators, thank you for playing and see you in other games
        break;
    default:
        ;
    }

    // lukesawicki 2023-08-14
//    drawCrossHair(mouseX, mouseY, *pixelsTable, false);
//    for (int i = 0; i < 3; i++)
//    {
//        //exception here lukesawicki
//        int x = spawners->childNodes[fourRandomPositions[i]->firstLevelNode]->childNodes[fourRandomPositions[i]->secondLevelNode]->spawner->position.x;
//        int y = spawners->childNodes[fourRandomPositions[i]->firstLevelNode]->childNodes[fourRandomPositions[i]->secondLevelNode]->spawner->position.y;
//        drawCrossHair(x, y, *pixelsTable, false);
//    }

    // for(int i=0; i<testPositions.size(); i++)
    // {
    //     drawCrossHair(testPositions.at(i)->x, testPositions.at(i)->y, *pixelsTable, false, BLUE );
    // }

//    testPositions

    drawHudElements(deltaTime);

    SDL_UpdateTexture(screenTexture , NULL, pixelsTable->pixels, WINDOW_WIDTH * 4);
    SDL_RenderCopyExF(renderer, screenTexture, NULL, NULL, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE); //SDL_FLIP_VERTICAL);
    SDL_RenderPresent(renderer);
}

void YasEngine::renderGameObjects(double& deltaTime)
{
    for (auto object : objectsToDraw)
    {
        if (object->isAlive) // TODO if gamestate == gameplay
        {
            drawPolygon(object, *pixelsTable);
        }
    }

    // drawLine(testPoint0, testPoint1, *pixelsTable, YELLOW);
}

void YasEngine::renderViewports(double& deltaTime)
{
    surfaceWithMathBasedEffects->verticalLineOnSurface(0, GREEN);
    surfaceWithMathBasedEffects->horizontalLineOnSurface(0, RED);//-WINDOW_HEIGHT * 0.25F
    surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(cosinusPoints->points, cosinusPoints->pointsNumber, YELLOW, true);
    surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(sinusPoints->points, sinusPoints->pointsNumber, BLUE, true);
    surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(fibonacciePoints->points, fibonacciePoints->pointsNumber, RED, false);
    // surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(primeNumbersPoints->points, primeNumbersPoints->pointsNumber, YELLOW, false);

	surfaceWithMathBasedEffects->copyPixelsInToPIxelTable(*pixelsTable);
}

void YasEngine::handlePhysics()
{
    if (objectsToDraw.size() >= 3)
    {
        for (int i = 0; i < static_cast<int>(objectsToDraw.size() - 2); i++)
        {

            if (!objectsToDraw[i]->isAlive || (objectsToDraw[i]->iAm == GameObject::PROTAGONIST))
            {
                continue;
            }

            // lukesawicki 2024-01-06_1027 here was error
            // I was doing checking collision in if() in method isCollidingWithcustomWalls(...)
            if((objectsToDraw[i]->iAm == GameObject::PROTAGONIST || objectsToDraw[i]->iAm == GameObject::COLLECTIBLE) )// 2024-01-06_1027 && Collider::isCollidingWithCustomWalls(objectsToDraw[i]->collider, *windowDimensions))
            {
                // float leftWall = -static_cast<float>(windowDimensions->x) * 0.5F;
                // float rightWall = static_cast<float>(windowDimensions->x) * 0.0F;
                // float topWall = static_cast<float>(windowDimensions->y) * 0.5F;
                // float bottomWall = -static_cast<float>(windowDimensions->y) * 0.5F;

                float leftWall = mapFrame.leftLineSegment.point0.x;//-static_cast<float>(windowDimensions->x) * 0.5F;
                float rightWall = mapFrame.rightLineSegment.point0.x;//static_cast<float>(windowDimensions->x) * 0.0F;
                float topWall = mapFrame.topLineSegment.point0.y;//static_cast<float>(windowDimensions->y) * 0.5F;
                float bottomWall = mapFrame.bottomLineSegment.point0.y;//-static_cast<float>(windowDimensions->y) * 0.5F;

                // If there is size of PROTAGONIST < SIZE OF WORLD/SCREEN THEN you not have to check collision with to opposite walls

                // if(objectsToDraw[i]->getPosition().x - objectsToDraw[i]->collider.radius <  leftWall)
                // {
                //     objectsToDraw[i]->setX(leftWall + objectsToDraw[i]->collider.radius + 1);
                // }

                if(  static_cast<int>(objectsToDraw[i]->getPosition().x + objectsToDraw[i]->collider.radius) >  static_cast<int>(rightWall) ) //
                {
                    // if (objectsToDraw[i]->iAm == GameObject::COLLECTIBLE)
                    // {
                    //     // objectsToDraw[i]->velocity.y *= -1;
                    //     // objectsToDraw[i]->velocity.x *= -1;
                    //     Vector2D<float> normalVector;
                    //
                    //     normalVector.x = 0;//objectsToDraw[i]->velocity.y * -1;
                    //     normalVector.y = 0;//objectsToDraw[i]->velocity.x;
                    //
                    //         Vector2D<float>::normalizedVector(normalVector);
                    //     // objectsToDraw[i]->velocity.x = objectsToDraw[i]->velocity.x * normalVector.x;
                    //     // objectsToDraw[i]->velocity.y = objectsToDraw[i]->velocity.y * normalVector.y;
                    //     //objectsToDraw[i]->velocity.x *= -1 * objectsToDraw[i]->velocity.y;
                    //
                    // }

                    if (objectsToDraw[i]->iAm == GameObject::COLLECTIBLE)
                    {
                        // // objectsToDraw[i]->velocity.y *= -1;
                        // // objectsToDraw[i]->velocity.x *= -1;
                        // Vector2D<float> normalVector;
                        //
                        // normalVector.x = 0;//objectsToDraw[i]->velocity.y * -1;
                        // normalVector.y = 0;//objectsToDraw[i]->velocity.x;
                        //
                        //     Vector2D<float>::normalizedVector(normalVector);
                        // // objectsToDraw[i]->velocity.x = objectsToDraw[i]->velocity.x * normalVector.x;
                        // // objectsToDraw[i]->velocity.y = objectsToDraw[i]->velocity.y * normalVector.y;
                        // //objectsToDraw[i]->velocity.x *= -1 * objectsToDraw[i]->velocity.y;

                        // ********** There is no time for implementing calculating normal faster is to hard code it for now because these are simple cases
                        // ********** so for right wall the normal vector is (-1, 0);

                        // calculate angle betwen normal vector and velocity vector
                        // rotate velocity vector around that angle
                        Vector2D<float> normal(-1, 0);
                        float angle = Vector2D<float>::angleBetweenVectors(normal, objectsToDraw[i]->velocity);
                        Vector2D<float>::rotateVectorOverTheAngle(&objectsToDraw[i]->velocity, 1.5708+angle);
                    }

                    objectsToDraw[i]->setX(rightWall - objectsToDraw[i]->collider.radius-1);
}
                //
                // if(objectsToDraw[i]->getPosition().y + objectsToDraw[i]->collider.radius > topWall)
                                // {
                //     objectsToDraw[i]->setY(topWall - objectsToDraw[i]->collider.radius - 1);
                // }
                //
                // if(objectsToDraw[i]->getPosition().y - objectsToDraw[i]->collider.radius < bottomWall)
                // {
                //     objectsToDraw[i]->setY(bottomWall + objectsToDraw[i]->collider.radius + 1);
                // }


                // x' = -y
                    // y' = +x

                // collided = true;
            }
            // big comment COMMENT WAS HERE

           // if (Collider::isCollidingWithCustomWalls(objectsToDraw[i]->collider, *windowDimensions))
           //  {
           //      objectsToDraw[i]->isAlive = false;
           //      if(objectsToDraw[i]->iAm == GameObject::PROTAGONIST)
           //      {
           //          writer.write(0, 0, "PLAYER COLLIDING",BLUE, *pixelsTable);
           //      }
           //      //std::cout << "HIT" << std::endl;
           //      continue;
           //  }

            for (int j = i; j < static_cast<int>(objectsToDraw.size()); j++)
            {
                if ((objectsToDraw[i]->iAm == GameObject::PROJECTILE && objectsToDraw[j]->iAm == GameObject::PROJECTILE) ||
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

    //big comment luke
    //              DO NOT DELETE IT IS COLLISION WITH NORMAL WALLS WHICH MEANS WINDOWS BOUNDRIES
//            if((objectsToDraw[i]->iAm == GameObject::PROTAGONIST) && Collider::isCollidingWithWall(objectsToDraw[i]->collider, *windowDimensions))
//            {
//                float leftWall = -static_cast<float>(windowDimensions->x) * 0.5F;
//                float rightWall = static_cast<float>(windowDimensions->x) * 0.5F;
//                float topWall = static_cast<float>(windowDimensions->y) * 0.5F;
//                float bottomWall = -static_cast<float>(windowDimensions->y) * 0.5F;
//                if(objectsToDraw[i]->getPosition().x - objectsToDraw[i]->collider.radius <  leftWall)
//                {
//                    objectsToDraw[i]->setX(leftWall + objectsToDraw[i]->collider.radius + 1);
//                }
//                if(objectsToDraw[i]->getPosition().x + objectsToDraw[i]->collider.radius >  rightWall)
//                {
//                    objectsToDraw[i]->setX(rightWall - objectsToDraw[i]->collider.radius - 1);
//                }
//                if(objectsToDraw[i]->getPosition().y + objectsToDraw[i]->collider.radius > topWall)
//                {
//                    objectsToDraw[i]->setY(topWall - objectsToDraw[i]->collider.radius - 1);
//                }
//                if(objectsToDraw[i]->getPosition().y - objectsToDraw[i]->collider.radius < bottomWall)
//                {
//                    objectsToDraw[i]->setY(bottomWall + objectsToDraw[i]->collider.radius + 1);
//                }
//            }
}

void YasEngine::moveObjects()
{
    for (auto object : objectsToDraw)
    {
        if (object->isAlive)
        {
            object->move(static_cast<float>(deltaTime));
            object->regeneratePolygon();
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
    std::cout << "Base path is: " << basePath << std::endl;

    std::string musicFilePath;
    musicFilePath.append(basePath);
    musicFilePath.append("music.wav");

    std::string shootSoundFilePath;
    shootSoundFilePath.append(basePath);
    shootSoundFilePath.append("shoot.wav");

    std::string hitSoundFilePath;
    hitSoundFilePath.append(basePath);
    hitSoundFilePath.append("hit.wav");
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
    // srand(clock());

    int mainNodeX = -(windowDimensions->x / 4);
    int mainNodeY = 0;

    std::cout << "Main node X: " << mainNodeX << "\n";
    std::cout << "Main node Y: " << mainNodeY << "\n";

    spawners = new Node(new Vector2D<int>(-(windowDimensions->x / 4), 0), windowDimensions->x / 2, nullptr);

    // adding nodes(first level) to head node
    Node::addNodes(*spawners);
    for(int i=0; i<4; i++)
    {
        // adding nodes(second level) to nodes
        Node::addNodes(*spawners->childNodes[i]);
    }

    for(int i=0; i<4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            spawnersPositions.push_back(new NodeNumbersOnTwoProceedingLevels(i, j));
        }
    }

    int drawnNumbers=0; // PL - wylosowane a nie narysowane w tym kontekscie
    int iteration = 0;
    bool drawn = false; // PL - bylo wylosowane
    NodeNumbersOnTwoProceedingLevels playerPosition;

//                   H
//    0         1         2          3
// 0 1 2 3   0 1 2 3___0 1 2 3   0 1 2 3

//    |````` `````|
//    |           |
//    |     H     |
//    |           |
//    |           |
//    |___________|
//    |`````|`````|
//    |  0  |  1  |
//    |_____|_____|
//    |     |     |
//    |  2  |  3  |
//    |_____|_____|
//     ___________
//    | 0|1 | 0|1 |
//    |--|--|--|--|
//    | 2|3 | 2|3 |
//    -------------
//    | 0|1 | 0|1 |
//    |--|--|--|--|
//    | 2|3 | 2|3 |
//     ```````````
    // TO READ -----------> Latice

    // calculate position of player on tree 1 - level of nodes and number of node and 2 level of node and number
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if (
                player->getPosition().x >= (spawners->childNodes[i]->childNodes[j]->position->x - spawners->childNodes[i]->childNodes[j]->size * 0.5) &&
                player->getPosition().x < (spawners->childNodes[i]->childNodes[j]->position->x + spawners->childNodes[i]->childNodes[j]->size * 0.5) &&
                player->getPosition().y <= (spawners->childNodes[i]->childNodes[j]->position->y + spawners->childNodes[i]->childNodes[j]->size * 0.5) &&
                player->getPosition().y > (spawners->childNodes[i]->childNodes[j]->position->y - spawners->childNodes[i]->childNodes[j]->size * 0.5)
                )
            {
                playerPosition.firstLevelNode = i;
                playerPosition.secondLevelNode = j;
                goto afterFor;
            }
        }
    }
    afterFor:

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            spawners->childNodes[i]->childNodes[j]->spawner = new Spawner(spawners->childNodes[i]->childNodes[j]->position->x, spawners->childNodes[i]->childNodes[j]->position->y);
        }
    }

    numberOfGivenColors.insert({"RED", 0});
    numberOfGivenColors.insert({"GREEN", 0});
    numberOfGivenColors.insert({"BLUE", 0});
    numberOfGivenColors.insert({"YELLOW", 0});

    prepareDataForDrawingGraphs();
}

void YasEngine::setFrameAroundGameplaySpace()
{
    // struct MapFrame
    // {
    //     LineSegment leftLineSegment;
    //     LineSegment rightLineSegment;
    //     LineSegment topLineSegment;
    //     LineSegment bottomLineSegment;
    // };
    // lukesawicki

    const int VERTHICAL_SHIFT=10;
    const int HORIZONTAL_SHIFT=10;

    // HORIZONTAL LINE SEGMENTS

    // Top              ---->
	// Left point     
    mapFrame.topLineSegment.point0.x = (-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT;
    mapFrame.topLineSegment.point0.y = (windowDimensions->y / 2) - VERTHICAL_SHIFT;
    // Right point
    mapFrame.topLineSegment.point1.x = -1 - HORIZONTAL_SHIFT;
    mapFrame.topLineSegment.point1.y = (windowDimensions->y / 2) - VERTHICAL_SHIFT;

    // Bottom
    // Left point
    mapFrame.bottomLineSegment.point0.x = (-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT;
    mapFrame.bottomLineSegment.point0.y = (-(windowDimensions->y / 2)) + VERTHICAL_SHIFT;

    // Right point
    mapFrame.bottomLineSegment.point1.x = -HORIZONTAL_SHIFT;
    mapFrame.bottomLineSegment.point1.y = (-(windowDimensions->y / 2)) + VERTHICAL_SHIFT;

    // VERTICAL LINE SEGMENTS
	// Left
    // Top point
    mapFrame.leftLineSegment.point0.x = (-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT;
    mapFrame.leftLineSegment.point0.y = (windowDimensions->y / 2) - VERTHICAL_SHIFT;
    // Bottom point
    mapFrame.leftLineSegment.point1.x = (-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT;
    mapFrame.leftLineSegment.point1.y = (-(windowDimensions->y / 2)) + VERTHICAL_SHIFT;

    // Right
    // Top point
    mapFrame.rightLineSegment.point0.x = -1 - HORIZONTAL_SHIFT;
    mapFrame.rightLineSegment.point0.y = (windowDimensions->y / 2) - VERTHICAL_SHIFT;
    // Bottom point
    mapFrame.rightLineSegment.point1.x = -1 - HORIZONTAL_SHIFT;
    mapFrame.rightLineSegment.point1.y = (-(windowDimensions->y / 2)) + VERTHICAL_SHIFT;
}

void YasEngine::prepareDataForDrawingGraphs()
{
    SinusPointsGenerator sinusPointsGenerator;
    CosinusPointsGenerator cosinusPointsGenerator;
    FibonacciPointsGenerator fibonacciPointsGenerator;
    PrimeNumbersPointsGenerator primeNumberPointsGenerator;

    sinusPoints = sinusPointsGenerator.generatePoints();
    cosinusPoints = cosinusPointsGenerator.generatePoints();
    fibonacciePoints = fibonacciPointsGenerator.generatePoints();
    primeNumbersPoints = primeNumberPointsGenerator.generatePoints();

    for(unsigned int i=0; i<SinusPointsGenerator::numbers.size(); i++)
    {
        sinusNumbers.insert({SinusPointsGenerator::numbers.at(i),0});
    }
    for(unsigned int i=0; i<CosinusPointsGenerator::numbers.size(); i++)
    {
        cosinusNumbers.insert({ CosinusPointsGenerator::numbers.at(i),0});
    }
    for(unsigned int i=0; i<FibonacciPointsGenerator::numbers.size(); i++)
    {
        fibonacciNumbers.insert({ FibonacciPointsGenerator::numbers.at(i), 0 });
    }
    for(unsigned int i=0; i<PrimeNumbersPointsGenerator::numbers.size(); i++)
    {
        primeNumbers.insert({ PrimeNumbersPointsGenerator::numbers.at(i),0 });
    }
}

void YasEngine::prepareInterface()
{
    //Button 1
    buttons.push_back(new Button(Button::RESTART_START, "START RESTART", RED));
    buttons.at(0)->setPosition(0, 50);
    dynamic_cast<Button*>(buttons.at(0))->horizontalMargin = 10;
    dynamic_cast<Button*>(buttons.at(0))->verticalMargin = 5;
    dynamic_cast<Button*>(buttons.at(0))->buttonWidth = writer.FONT_WIDTH * dynamic_cast<Button*>(buttons.at(0))->text.size() + 2*dynamic_cast<Button*>(buttons.at(0))->horizontalMargin;
    dynamic_cast<Button*>(buttons.at(0))->buttonHeight = writer.FONT_HEIGHT + 2*dynamic_cast<Button*>(buttons.at(0))->verticalMargin;
    buttons.at(0)->localVertices = new Vector2D<float>[4];
    buttons.at(0)->worldVertices = new Vector2D<float>[4];
    buttons.at(0)->localVertices[0].x = 0 - dynamic_cast<Button*>(buttons.at(0))->buttonWidth * 0.5F;
    buttons.at(0)->localVertices[0].y = 0 + dynamic_cast<Button*>(buttons.at(0))->buttonHeight * 0.5F;
    buttons.at(0)->localVertices[1].x = 0 + dynamic_cast<Button*>(buttons.at(0))->buttonWidth * 0.5F;
    buttons.at(0)->localVertices[1].y = 0 + dynamic_cast<Button*>(buttons.at(0))->buttonHeight * 0.5F;
    buttons.at(0)->localVertices[2].x = 0 + dynamic_cast<Button*>(buttons.at(0))->buttonWidth * 0.5F;
    buttons.at(0)->localVertices[2].y = 0 - dynamic_cast<Button*>(buttons.at(0))->buttonHeight * 0.5F;
    buttons.at(0)->localVertices[3].x = 0 - dynamic_cast<Button*>(buttons.at(0))->buttonWidth * 0.5F;
    buttons.at(0)->localVertices[3].y = 0 - dynamic_cast<Button*>(buttons.at(0))->buttonHeight * 0.5F;
    buttons.at(0)->generate();

    //Button 2
    buttons.push_back(new Button(Button::QUIT, "QUIT", YELLOW));
    buttons.at(1)->setPosition(0, -50);
    dynamic_cast<Button*>(buttons.at(1))->horizontalMargin = 10;
    dynamic_cast<Button*>(buttons.at(1))->verticalMargin = 5;
    dynamic_cast<Button*>(buttons.at(1))->buttonWidth = writer.FONT_WIDTH * dynamic_cast<Button*>(buttons.at(1))->text.size() + 2*dynamic_cast<Button*>(buttons.at(1))->horizontalMargin;
    dynamic_cast<Button*>(buttons.at(1))->buttonHeight = writer.FONT_HEIGHT + 2*dynamic_cast<Button*>(buttons.at(1))->verticalMargin;
    buttons.at(1)->localVertices = new Vector2D<float>[4];
    buttons.at(1)->worldVertices = new Vector2D<float>[4];
    buttons.at(1)->localVertices[0].x = 0 - dynamic_cast<Button*>(buttons.at(1))->buttonWidth * 0.5F;
    buttons.at(1)->localVertices[0].y = 0 + dynamic_cast<Button*>(buttons.at(1))->buttonHeight * 0.5F;
    buttons.at(1)->localVertices[1].x = 0 + dynamic_cast<Button*>(buttons.at(1))->buttonWidth * 0.5F;
    buttons.at(1)->localVertices[1].y = 0 + dynamic_cast<Button*>(buttons.at(1))->buttonHeight * 0.5F;
    buttons.at(1)->localVertices[2].x = 0 + dynamic_cast<Button*>(buttons.at(1))->buttonWidth * 0.5F;
    buttons.at(1)->localVertices[2].y = 0 - dynamic_cast<Button*>(buttons.at(1))->buttonHeight * 0.5F;
    buttons.at(1)->localVertices[3].x = 0 - dynamic_cast<Button*>(buttons.at(1))->buttonWidth * 0.5F;
    buttons.at(1)->localVertices[3].y = 0 - dynamic_cast<Button*>(buttons.at(1))->buttonHeight * 0.5F;
    buttons.at(1)->generate();

    setFrameAroundGameplaySpace();
}

void YasEngine::drawButtons()
{
    for(unsigned int i=0; i<buttons.size(); i++)
    {
        drawPolygon(buttons.at(i), *pixelsTable);
        writer.write(static_cast<int>(buttons.at(i)->getPosition().x - dynamic_cast<Button*>(buttons.at(i))->buttonTextWidth * 0.5F + ScreenWriter::FONT_WIDTH * 0.5F), static_cast<int>(buttons.at(i)->getPosition().y), dynamic_cast<Button*>(buttons.at(i))->text,dynamic_cast<Button*>(buttons.at(i))->color, *pixelsTable);
    }
}

Button::ButtonId YasEngine::checkWhichButtonClicked()
{
    float x = static_cast<float>(mousePositionChangeInformation->x);
    float y = static_cast<float>(mousePositionChangeInformation->y);
    windowPositionToCartesianPosition(x, y, windowDimensions);
    for(unsigned int i=0; i<buttons.size(); i++)
    {
        if(
        // mouse cursor under top Y
        y <= (buttons.at(i)->getPosition().y + dynamic_cast<Button*>(buttons.at(i))->buttonHeight * 0.5F) &&
        // mouser cursor above bottom Y
        y >= (buttons.at(i)->getPosition().y - dynamic_cast<Button*>(buttons.at(i))->buttonHeight * 0.5F) &&
        // cursor to the right of left X
        x >= (buttons.at(i)->getPosition().x - dynamic_cast<Button*>(buttons.at(i))->buttonWidth * 0.5F) &&
        // cursor to the left of X
        x <= (buttons.at(i)->getPosition().x + dynamic_cast<Button*>(buttons.at(i))->buttonWidth * 0.5F)
        )
        {
            return dynamic_cast<Button*>(buttons.at(i))-> buttonId;
        }
    }
    return Button::NONE;
}

void YasEngine::handleClickedButtons()
{
    switch(checkWhichButtonClicked())
    {
        case Button::RESTART_START:
            gameState = GameState::GAMEPLAY;
            break;
        case Button::QUIT:
            gameState = GameState::OUTRO;
            break;
        default:
            ;
    }
}

void YasEngine::handleGameStateWhenESCbuttonPushed()
{
    switch(gameState)
    {            
        case INTRO:
            gameState = GameState::MAIN_MENU_RESTART;
            break;
        case MAIN_MENU_RESTART:
            gameState = GameState::OUTRO;
            break;
        case GAMEPLAY:
            gameState = GameState::MAIN_MENU_RESTART;
            break;
        case OUTRO:
            quit = true;
            break;
        default:
            ;
    }
}

void YasEngine::handleGameStateWhenSPACEbuttonPushed()
{
    switch(gameState)
    {
        case INTRO:
            gameState = GameState::MAIN_MENU_RESTART;
            break;
        case OUTRO:
            quit = true;
            break;
        default:
            ;
    }
}
