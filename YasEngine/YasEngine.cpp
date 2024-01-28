#include"YasEngine.hpp"
//#include<SDL_endian.h>

// #include "document.h"     // rapidjson's DOM-style API
#include "prettywriter.h" // for stringify JSON

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

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

// In version 1.9.0.1:
//
// 1 : Major revision(new UI, lots of new features, conceptual change, etc.)
//
// 9 : Minor revision(maybe a change to a search box, 1 feature added, collection of bug fixes)
//
// 0 : Bug fix release
//
// 1 : Build number(if used) that's why you see the .NET framework using something like 2.0.4.2709

YasEngine* YasEngine::instance = nullptr;

void YasEngine::initialize()
{
    readSettingsFromFile();

    srand(clock());

    prepareBasicSettings();
    prepareRendering();
    preparePlayer();
    prepareGameWorld();
    prepareSoundAndMusic();
    prepareInterface();

    writer.initialize();

    surfaceWithMathBasedEffects = new SurfaceWithMathBasedEffects(0, static_cast<int>(windowDimensions->y * 0.5F), static_cast<int>(windowDimensions->x * 0.5F), static_cast<int>(windowDimensions->y), BLACK);

}

void YasEngine::clean()
{
    for (auto drawableObject : objectsToDraw)
    {
        delete drawableObject;
    }

    // delete sinusPoints;
    // delete cosinusPoints;
    // delete fibonacciePoints;
    // delete primeNumbersPoints;
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

void YasEngine::readSettingsFromFile()
{
    std::ifstream settingsFile("settings.json");
    if (!settingsFile.is_open()) {
        std::cerr << "Error opening JSON file" << std::endl;
        exit(1);
    }

    std::string settingsString((std::istreambuf_iterator<char>(settingsFile)), std::istreambuf_iterator<char>());
    settingsFile.close();

    
    settings.Parse(settingsString.c_str());

    if (settings.HasParseError()) {
        std::cerr << "Error parsing JSON" << std::endl;
        exit(1);
    }

    const rapidjson::Value& soundSettings = settings["SOUND_MUSIC"];

    musicVolume = soundSettings["MUSIC_VOLUME"].GetInt();
    shootVolume = soundSettings["SHOOT_VOLUME"].GetInt();
    hitVolume = soundSettings["HIT_VOLUME"].GetInt();
    otherVolume = soundSettings["OTHER_VOLUME"].GetInt();
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
    Uint32 windowFlags = SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_ALWAYS_ON_TOP;
    window              =   SDL_CreateWindow("YasEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);

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
    drawCrossHair(mouseX, mouseY, *pixelsTable, false);



}

void YasEngine::drawFrame(double& deltaTime)
{
    drawHorizontalLine(*pixelsTable, mapFrame.topLineSegment.point0.x, mapFrame.topLineSegment.point1.x, mapFrame.topLineSegment.point0.y, RED);
    drawHorizontalLine(*pixelsTable, mapFrame.bottomLineSegment.point0.x, mapFrame.bottomLineSegment.point1.x, mapFrame.bottomLineSegment.point0.y, GREEN);

    drawVerticalLine(*pixelsTable, mapFrame.leftLineSegment.point0.y, mapFrame.leftLineSegment.point1.y, mapFrame.leftLineSegment.point0.x, YELLOW);
    drawVerticalLine(*pixelsTable, mapFrame.rightLineSegment.point0.y, mapFrame.rightLineSegment.point1.y, mapFrame.rightLineSegment.point0.x, YELLOW);
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
        case SDLK_o:
            input->test_o_button = true;
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
        case SDLK_o:
            if(input->test_o_button == true)
            {
                Mix_PlayChannel(-1, otherSound, 0);
                input->test_o_button = false;
            }
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
        {
            player->isShooting = true;
            int randNumb = Randomizer::drawNumberClosedInterval(1, 8);
            if (randNumb <= 4)\
        	{
                changeAllCollectibleDirection(randNumb);
            }
                if(player->wasHit)
                {
                    healthPoints--;
                }
        }
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
        for (int i = 0; i < 8; i++)
        {
            // LOSUJ 4 razy liczbe z 16 spawnerPostions
            int randomSpawner = Randomizer::drawNumberClosedInterval(0, 15);

            int firstLevelNodeIndex = spawnersPositions[randomSpawner]->firstLevelNode;
            int secondLevelNodeIndex = spawnersPositions[randomSpawner]->secondLevelNode;
            if (Spawner::numberOfSpawnedObjects < MAX_COLLECTIBLES_TO_SPAWN)
            {
	            if (isObjectInSameQuarterAsProtagonist(randomSpawner))
	            {
	                continue;
	            }
	            
	            spawners->childNodes[firstLevelNodeIndex]->childNodes[secondLevelNodeIndex]->spawner->spawnObject(go);
	            if (go != nullptr)
	            {
	                Spawner::numberOfSpawnedObjects++;
	                objectsToDraw.push_back(go);
	                go = nullptr;
				}
            }
            else
            {
                spawners->childNodes[firstLevelNodeIndex]->childNodes[secondLevelNodeIndex]->spawner->resetTimes();
            }
        }
}

bool YasEngine::isObjectInSameQuarterAsProtagonist(int randomSpawner)
{
    int quarterSize = spawners->childNodes[spawnersPositions[randomSpawner]->firstLevelNode]->childNodes[spawnersPositions[randomSpawner]->secondLevelNode]->size;

    return (
        (player->getPosition().x < (spawners->childNodes[spawnersPositions[randomSpawner]->firstLevelNode]->childNodes[spawnersPositions[randomSpawner]->secondLevelNode]->position->x +
        quarterSize / 2)) &&
        (player->getPosition().x > (spawners->childNodes[spawnersPositions[randomSpawner]->firstLevelNode]->childNodes[spawnersPositions[randomSpawner]->secondLevelNode]->position->x -
        quarterSize / 2)) &&
        (player->getPosition().y < (spawners->childNodes[spawnersPositions[randomSpawner]->firstLevelNode]->childNodes[spawnersPositions[randomSpawner]->secondLevelNode]->position->y +
        quarterSize / 2)) &&
        (player->getPosition().y > (spawners->childNodes[spawnersPositions[randomSpawner]->firstLevelNode]->childNodes[spawnersPositions[randomSpawner]->secondLevelNode]->position->y -
        quarterSize / 2)));
	
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
        writer.write( (-238)/2, 200, "THE.GLITCH", LIGHT_BLUE, *pixelsTable); // TODO write title and version and tha game is powered by YasEngine
        writer.write((-170)/2, 100, "POWERED.BY", RED, *pixelsTable);
        writer.write((-170)/2, 0, "YAS.ENGINE", YELLOW, *pixelsTable);
        break;
    case MAIN_MENU_RESTART:
        drawButtons();
        break;
    case GAMEPLAY:
        renderGameObjects(deltaTime);
        renderOnViewports(deltaTime);
        drawFrame(deltaTime);
        writer.write(350, 375, "POINTS", LIGHT_BLUE, *pixelsTable);
        writer.write(350, 350, std::to_string(points), LIGHT_BLUE, *pixelsTable);
        writer.write(350, 275, "HEALTH POINTS", LIGHT_BLUE, *pixelsTable);
        writer.write(350, 250, std::to_string(healthPoints), LIGHT_BLUE, *pixelsTable);
        break;
    case OUTRO://                                 123456789_123456789_123456789_123456789_123456789_123456789_

        writer.write((-37 * 17) / 2, 350, "GAME.DESIGN.PROGRAMMING.AND.MARKETING", LIGHT_BLUE, *pixelsTable);
        writer.write((-14 * 17) / 2, 325,               "LUKE.AND.BEJPASTAN", PURPLE, *pixelsTable);
        writer.write((-22 * 17) / 2, 275,               "SOUND.DESIGN.AND.MUSIC", LIGHT_BLUE, *pixelsTable);
        writer.write((-17 * 17) / 2, 250,               "JAKUB.TWAROGOWSKI", PURPLE, *pixelsTable);
        writer.write((-17 * 17) / 2, 200,               "QUALITY.ASSURANCE", LIGHT_BLUE, *pixelsTable);
        writer.write((-15 * 17) / 2, 175,               "....MY", PURPLE, *pixelsTable);
        writer.write((-15 * 17) / 2, 125,               "SPECIAL.THANKS:", GREEN, *pixelsTable);
        writer.write((-22 * 17) / 2, 75,                "...WY", YELLOW, *pixelsTable);

        break;
    default:
        ;
    }

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
}

void YasEngine::renderOnViewports(double& deltaTime)
{
    if (tests)
    {
        surfaceWithMathBasedEffects->drawCartesianAxies();
    }

	surfaceWithMathBasedEffects->copyPixelsInToPIxelTable(*pixelsTable);
}

void YasEngine::handlePhysics()
{
    if (objectsToDraw.size() >= 3)
    {
        for (int i = 0; i < static_cast<int>(objectsToDraw.size() - 2); i++)
        {

            if (objectsToDraw[i]->iAm == GameObject::COLLECTIBLE)
            {
                handleCollectiblesWithWallsCollisions(objectsToDraw[i]);
            }

            if (objectsToDraw[i]->iAm == GameObject::PROTAGONIST)
            {
                handleProtagonistWithWallsCollisions(objectsToDraw[i]);
            }

            // ****    SKIP HANDLING SHIP    ****
            // if (objectsToDraw[i]->iAm == GameObject::PROTAGONIST)// || objectsToDraw[j]->iAm == GameObject::PROTAGONIST)
            // {
            //     continue;
            // }

            for (int j = i; j < static_cast<int>(objectsToDraw.size()); j++)
            {
                if (
					objectsToDraw[i] == objectsToDraw[j]                                                                    || 
                    (objectsToDraw[i]->iAm == GameObject::PROJECTILE && objectsToDraw[j]->iAm == GameObject::PROJECTILE)    ||
                    (objectsToDraw[i]->iAm == GameObject::PROJECTILE && objectsToDraw[j]->iAm == GameObject::PROTAGONIST)   ||
                    (objectsToDraw[i]->iAm == GameObject::PROTAGONIST && objectsToDraw[j]->iAm == GameObject::PROJECTILE)   ||
                    (objectsToDraw[i]->iAm == GameObject::COLLECTIBLE && objectsToDraw[j]->iAm == GameObject::COLLECTIBLE)
                    )
                {
                    continue;
                }

                // LEFT Projectile <-> Collectible && Protagonist <-> Collectible)
                if (objectsToDraw[i]->isAlive && objectsToDraw[j]->isAlive)
                {
                    bool isOneProtagonist = objectsToDraw[i]->iAm == GameObject::PROTAGONIST || objectsToDraw[j]->iAm == GameObject::PROTAGONIST;
                    if(isOneProtagonist && Collider::isInCollision(objectsToDraw[i]->collider, objectsToDraw[j]->collider))
                    {
                        
                        if(objectsToDraw[i]->iAm == GameObject::COLLECTIBLE)
                        {
                            healthPoints -= objectsToDraw[i]->numberOfVertices;
                            objectsToDraw[i]->isAlive = false;
                            // healthPoints -= objectsToDraw[i]->numberOfVertices;
                        }

                        if (objectsToDraw[j]->iAm == GameObject::COLLECTIBLE)
                        {
                            // healthPoints -= objectsToDraw[j]->numberOfVertices;
                            healthPoints -= objectsToDraw[j]->numberOfVertices;
                            objectsToDraw[j]->isAlive = false;
                        }
                        if(healthPoints<=0)
                        {
                            player->isAlive = false;
                        }

                    }

                    // if (player->wasHit && isOneProtagonist && !Collider::isInCollision(objectsToDraw[i]->collider, objectsToDraw[j]->collider))
                    // {
                    //     player->wasHit = false;
                    // }

                    // if (player->wasHit)
                    // {
                    //     player->wasHit = false;
                    // }

                    if ( (!isOneProtagonist) && Collider::isInCollision(objectsToDraw[i]->collider, objectsToDraw[j]->collider))
                    {
                        if (objectsToDraw[i]->isAlive && !objectsToDraw[i]->collider.isCollieded)
                        {
                            objectsToDraw[i]->collider.isCollieded = true;
                            points += objectsToDraw[i]->numberOfVertices;
                        }
                        objectsToDraw[i]->isAlive = false;
                        objectsToDraw[j]->isAlive = false;
                        Mix_PlayChannel(-1, hitSound, 0);


                        if(objectsToDraw[i]->iAm == GameObject::COLLECTIBLE)
                        {

                            int randomnumber = Randomizer::drawNumberClosedInterval(1, 5);

                            if(randomnumber == 4)
                            {
                                int vertex = objectsToDraw[i]->numberOfVertices;
                                int radius = objectsToDraw[i]->circumscribedCircleRadius;
                                player->switchPolygon(vertex, radius);
	                            // podmieniamy
                            }

                            --Spawner::numberOfSpawnedObjects;

                        }
                        if (objectsToDraw[j]->iAm == GameObject::COLLECTIBLE)
                        {
                            int randomnumber = Randomizer::drawNumberClosedInterval(1, 5);

                            if (randomnumber == 4)
                            {
                                int vertex = objectsToDraw[j]->numberOfVertices;
                                int radius = objectsToDraw[j]->circumscribedCircleRadius;
                                player->switchPolygon(vertex, radius);
                                // podmieniamy
                            }
                            --Spawner::numberOfSpawnedObjects;
                        }
					}
				}
			}
		}
    }
} // END OF handlePhysics()


void YasEngine::handleCollectiblesWithWallsCollisions(GameObject* object)
{
    float leftWall = mapFrame.leftLineSegment.point0.x;
    float rightWall = mapFrame.rightLineSegment.point0.x;
    float topWall = mapFrame.topLineSegment.point0.y;
    float bottomWall = mapFrame.bottomLineSegment.point0.y;


    if (object->iAm == GameObject::COLLECTIBLE)
    {

        if (object->getColliderLeftSide() < static_cast<int>(leftWall))
        {
            bounceCollectibles(object, LEFT);
        }

        if (object->getColliderRightSide() > static_cast<int>(rightWall))
        {
            bounceCollectibles(object, RIGHT);
        }


        if (object->getColliderTopSide() < static_cast<int>(topWall))
        {
            bounceCollectibles(object, TOP);
        }

        if (object->getColliderBottomSide() > static_cast<int>(bottomWall))
        {
            bounceCollectibles(object, BOTTOM);
        }
    }
}

void YasEngine::handleProtagonistWithWallsCollisions(GameObject* object)
{
    float leftWall = mapFrame.leftLineSegment.point0.x;
    float rightWall = mapFrame.rightLineSegment.point0.x;
    float topWall = mapFrame.topLineSegment.point0.y;
    float bottomWall = mapFrame.bottomLineSegment.point0.y;

    if (object->getColliderLeftSide() < static_cast<int>(leftWall))
    {
        moveObjectToMapBoundries(object, LEFT);
        // bounceCollectibles(object, LEFT);
    }

    if (object->getColliderRightSide() > static_cast<int>(rightWall))
    {
        moveObjectToMapBoundries(object, RIGHT);
        // bounceCollectibles(object, RIGHT);
    }

    if (object->getColliderTopSide() > static_cast<int>(topWall))
    {
        moveObjectToMapBoundries(object, TOP);
        // bounceCollectibles(object, TOP);
    }

    if (object->getColliderBottomSide() < static_cast<int>(bottomWall))
    {
        moveObjectToMapBoundries(object, BOTTOM);
        // bounceCollectibles(object, BOTTOM);
    }
}

void YasEngine::bounceCollectibles(GameObject* gameObject, Wall wall)
{
    Vector2D<float> normal;
    switch (wall)
    {
    case LEFT:
        normal.x = 1;
        normal.y = 0;
        break;
    case RIGHT:
        normal.x = -1;
        normal.y = 0;
        break;
    case TOP:
        normal.x = 0;
        normal.y = -1;
        break;
    case BOTTOM:
        normal.x = 0;
        normal.y = 1;
        break;
    default:
        ;
        break;
    }

    float dotProduct = Vector2D<float>::dotProduct(gameObject->velocity, normal);
    Vector2D<float>::multiplyByScalar(&normal, dotProduct * 2.0f);
    Vector2D<float>::substract(&gameObject->velocity, normal);

    // TO PREVENT COLLECTIBLE STUCK IN THE WALL
    // objectsToDraw[i]->setX(rightWall - objectsToDraw[i]->collider.radius - 1);
}

void YasEngine::moveObjectToMapBoundries(GameObject* gameObject, Wall wall)
{
    switch (wall)
    {
    case LEFT:
        gameObject->setX(mapFrame.leftLineSegment.point0.x + gameObject->collider.radius);
        break;
    case RIGHT:
        gameObject->setX(mapFrame.rightLineSegment.point0.x - gameObject->collider.radius);
        break;
    case TOP:
        gameObject->setY(mapFrame.topLineSegment.point0.y - gameObject->collider.radius);
        break;
    case BOTTOM:
        gameObject->setY(mapFrame.bottomLineSegment.point0.y + gameObject->collider.radius);
        break;
    default:
        ;
        break;
    }
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

    Mix_Init(MIX_DEFAULT_FORMAT);

    music = Mix_LoadMUS("music.wav");
    if (music == NULL)
    {
        std::cout << "Error while loading music. Cannot load music." << std::endl;
        std::cout << "SDL message: " << SDL_GetError() << std::endl << " | Mix library error: " << Mix_GetError() << std::endl;
        quit = true;
    }

    Mix_VolumeMusic(musicVolume);
	// Mix_VolumeMusic

    shootSound = Mix_LoadWAV("shoot.wav");
    Mix_VolumeChunk(shootSound, shootVolume);

    hitSound = Mix_LoadWAV("hit.wav");
    Mix_VolumeChunk(hitSound, hitVolume);

    otherSound = Mix_LoadWAV("other.wav");
    Mix_VolumeChunk(otherSound, otherVolume);


    if (shootSound == NULL || hitSound == NULL || otherSound == NULL)
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

    preparePrimesDrawing();
    prepareFibonacciDrawing();
    prepareSinusDrawing();
    prepareCosinusDrawing();

    // std::map<std::string, std::map<int, float>*> numbersMap;
    // std::map < std::string, std::map<int, std::map<float, float>>> pairNumbersMap;

    // std::vector<int> fibonacciNumbers = generateNfibonaccinumbers(40);
    // std::map<int, float>* fibbs = new std::map<int, float>;
    // numbersMap.insert({ "Fibonacci",  fibbs });
    // for(int i=0; i < fibonacciNumbers.size(); i++)
    // {
    //     numbersMap.at("Fibonacci")->insert(std::pair<int, float>(33, 33.44f));
    // }

    // std::vector<int> primeNumbers = generatePrimeNumbersLessThanN(1000);




    // std::vector<int> generateNfibonaccinumbers(int n)

    // std::vector<int> generatePrimeNumbersLessThanN(int n)



    // sinusPicture = new MathPicture(100, 0, 100, new SinusPointsGenerator(), new PointsSet());
    // cosinusPicture = new MathPicture(100, 0, 100, new CosinusPointsGenerator(), new PointsSet());
    // fibonacciePicture = new MathPicture(40, 0, 40, numbersMap.at("Fibonacci"), new FibonacciPointsGenerator(), new PointsSet());



    // sinusPicture->generateFloatPoints();
    // cosinusPicture->generateFloatPoints();
    // fibonacciePicture->generateFloatPoints();
    // primeNumbersPicture->generateFloatPoints();

}

void YasEngine::prepareSinusDrawing()
{
    std::map<float, float>* sinuses = generateSinNumbers(100);//generatePrimeNumbersLessThanN(1000);
    int numberOfPrimes = sinuses->size();
    sinPointsHarvested = 0;

    // std::map < std::string, std::map<int, std::map<float, float>>> pairNumbersMap;

    std::map<int, std::map<float, float>> numberedSines;

    pairNumbersMap.insert(std::pair < std::string, std::map<int, std::map<float, float>*>* > ("Sines", new std::map<int, std::map<float, float>* >));

    // for (int i = 0; i < sinuses->size(); i++)
    // {
    int i = 0;
    for(std::pair<float, float> pair: *sinuses)
    {
        std::map<float, float>* m = new std::map<float, float>();
        m->insert(pair);
        pairNumbersMap.at("Sines")->insert(std::pair<int, std::map<float, float>*>(i,m));
    }
        
    // }

    sinusPicture = new MathPicture(maxNtoCalculateSinus, sinuses, new SinusPointsGenerator(), new PointsSet());
}

void YasEngine::prepareCosinusDrawing()
{
    std::map<float, float>* cosine = generateCosNumbers(100);//generatePrimeNumbersLessThanN(1000);
    int numberOfPrimes = cosine->size();
    cosPointsHarvested = 0;

    // std::map < std::string, std::map<int, std::map<float, float>>> pairNumbersMap;

    std::map<int, std::map<float, float>> numberedSines;

    pairNumbersMap.insert(std::pair < std::string, std::map<int, std::map<float, float>*>* >("Cosines", new std::map<int, std::map<float, float>* >));

    // for (int i = 0; i < sinuses->size(); i++)
    // {
    int i = 0;
    for (std::pair<float, float> pair : *cosine)
    {
        std::map<float, float>* m = new std::map<float, float>();
        m->insert(pair);
        pairNumbersMap.at("Cosines")->insert(std::pair<int, std::map<float, float>*>(i, m));
    }

    // }

    cosinusPicture = new MathPicture(maxNtoCalculateCosinus, cosine, new CosinusPointsGenerator(), new PointsSet());
}

void YasEngine::prepareFibonacciDrawing()
{
    std::vector<int> fibbs = generateNfibonaccinumbers(40);

    fibbsPointsHarvested = 0;

    numbersMap.insert(std::pair<std::string, std::map<int, float>*>("Fibbs", new std::map<int, float>));

    for (int i = 0; i < fibbs.size(); i++)
    {
        numbersMap.at("Fibbs")->insert(std::pair<int, int>(i, fibbs.at(i)));
    }

    fibonacciePicture = new MathPicture(maxNtoCalculateFibonacci, numbersMap.at("Fibbs"), new FibonacciPointsGenerator(), new PointsSet());
}

void YasEngine::preparePrimesDrawing()
{
    std::vector<int> primes = generatePrimeNumbersLessThanN(1000);
    int numberOfPrimes = primes.size();
    primesPointsHarvested = 0;

    numbersMap.insert(std::pair<std::string, std::map<int, float>*>("Primes", new std::map<int, float>));

    for (int i = 0; i < primes.size(); i++)
    {
        numbersMap.at("Primes")->insert(std::pair<int, int>(i, primes.at(i)));
    }

    primeNumbersPicture = new MathPicture(maxNtoCalculatePrimes, numbersMap.at("Primes"), new PrimeNumbersPointsGenerator(), new PointsSet());
}

void YasEngine::prepareInterface()
{
    //Button 1
    buttons.push_back(new Button(Button::RESTART_START, "START", RED));
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

void YasEngine::changeAllCollectibleDirection(int dir)
{
    int randomNumber = 1;// Randomizer::drawNumberClosedInterval(1, 5);

    if (randomNumber == 1)
    {
        std::cout << "Zmieniam" << std::endl;
        for (int i = 0; i < objectsToDraw.size(); i++)
        {
            if (objectsToDraw[i]->iAm == GameObject::COLLECTIBLE)
            {
	            switch (dir)
	            {
	            case 1:
		            {
                    objectsToDraw[i]->velocity.x = abs(objectsToDraw[i]->velocity.x);
		            }
                    break;
	            case 2:
	                {
	                    objectsToDraw[i]->velocity.x = abs(objectsToDraw[i]->velocity.x)*-1;
	                }
	                break;
	            case 3:
	                {
	                    objectsToDraw[i]->velocity.x = abs(objectsToDraw[i]->velocity.y);
	                }
	                break;
	            case 4:
	                {
	                    objectsToDraw[i]->velocity.x = abs(objectsToDraw[i]->velocity.y)*-1;
	                }
	                break;

	            }
                
            }
        }
    }

    // if (randNumber == 2)
    // {
    //
    // }
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


// writer.write(0, 350, "GAME DESIGN PROGRAMMING AND MARKETING", YELLOW, *pixelsTable);
// writer.write(0, 325, "LUKASZ SAWICKI", YELLOW, *pixelsTable);
// writer.write(0, 275, "SOUND DESIGN AND MUSIC", YELLOW, *pixelsTable);
// writer.write(0, 250, "JAKUB TWAROGOWSKI", YELLOW, *pixelsTable);
// writer.write(0, 200, "QUALITY ASSURANCE", YELLOW, *pixelsTable);
// writer.write(0, 175, "BARTLOMIEJ KAWA", YELLOW, *pixelsTable);
// writer.write(0, 125, "SPECIAL THANKS:", PURPLE, *pixelsTable);
// writer.write(0, 75, "MY DEAR SISTER IZABELA", YELLOW, *pixelsTable);
// writer.write(0, 50, "MY LOVE MARIOLA", YELLOW, *pixelsTable);
// writer.write(0, 0, "MY FRIENDS FROM WARSAW SCHOOL OF COMPUTER SCIENCE:", YELLOW, *pixelsTable);
// writer.write(0, -25, "LUKASZ KRZYSZTOF MICHAL MAREK TOMASZ", YELLOW, *pixelsTable);
// writer.write(0, -75, "MY FRENDS FROM GDS 4:", YELLOW, *pixelsTable);
// writer.write(0, -100, "KASIA AND BARTOSZ", YELLOW, *pixelsTable);
// writer.write(0, -150, "WHOLE COMMUNITY OF KNTG POLYGON", YELLOW, *pixelsTable);
// writer.write(0, -200, "AND ALL MEMBERS OF TEAM XPORTAL", YELLOW, *pixelsTable);