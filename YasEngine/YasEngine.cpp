#include"YasEngine.hpp"
//#include<SDL_endian.h>
#include<bit>
#include<SDL_mixer.h>
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
    for (int i = 0; i < 4; i++)
    {
        //exception here lukesawicki
        spawners->childNodes[fourRandomPositions[i]->firstLevelNode]->childNodes[fourRandomPositions[i]->secondLevelNode]->spawner->spawnObject(go);
        if (go != nullptr)
        {
            objectsToDraw.push_back(go);
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
//    srand(clock());
//    int number = rand() % 16;

    player = new Player(-windowDimensions->x * 0.25F, 0);
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

    for(int i=0; i<testPositions.size(); i++)
    {
        drawCrossHair(testPositions.at(i)->x, testPositions.at(i)->y, *pixelsTable, false, BLUE );
    }

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

    drawLine(testPoint0, testPoint1, *pixelsTable, YELLOW);
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
            if((objectsToDraw[i]->iAm == GameObject::PROTAGONIST) && Collider::isCollidingWithCustomWalls(objectsToDraw[i]->collider, *windowDimensions))
            {
                float leftWall = -static_cast<float>(windowDimensions->x) * 0.5F;
                float rightWall = static_cast<float>(windowDimensions->x) * 0.0F;
                float topWall = static_cast<float>(windowDimensions->y) * 0.5F;
                float bottomWall = -static_cast<float>(windowDimensions->y) * 0.5F;
                if(objectsToDraw[i]->getPosition().x - objectsToDraw[i]->collider.radius <  leftWall)
                {
                    objectsToDraw[i]->setX(leftWall + objectsToDraw[i]->collider.radius + 1);
                }
                if(objectsToDraw[i]->getPosition().x + objectsToDraw[i]->collider.radius >  rightWall)
                {
                    objectsToDraw[i]->setX(rightWall - objectsToDraw[i]->collider.radius - 1);
                }
                if(objectsToDraw[i]->getPosition().y + objectsToDraw[i]->collider.radius > topWall)
                {
                    objectsToDraw[i]->setY(topWall - objectsToDraw[i]->collider.radius - 1);
                }
                if(objectsToDraw[i]->getPosition().y - objectsToDraw[i]->collider.radius < bottomWall)
                {
                    objectsToDraw[i]->setY(bottomWall + objectsToDraw[i]->collider.radius + 1);
                }
                // collided = true;
            }

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

            if (!objectsToDraw[i]->isAlive || (objectsToDraw[i]->iAm == GameObject::PROTAGONIST))
            {
                continue;
            }

           if (Collider::isCollidingWithCustomWalls(objectsToDraw[i]->collider, *windowDimensions))
            {
                objectsToDraw[i]->isAlive = false;
                if(objectsToDraw[i]->iAm == GameObject::PROTAGONIST)
                {
                    writer.write(0, 0, "PLAYER COLLIDING",BLUE, *pixelsTable);
                }
                //std::cout << "HIT" << std::endl;
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
    srand(clock());
    // zero level node (root)
    spawners = new Node(new Vector2D<int>(-(windowDimensions->x / 4), 0), windowDimensions->x / 2, nullptr);

    // adding nodes(first level) to head node
    Node::addNodes(*spawners);
    for(int i=0; i<4; i++)
    {
        // adding nodes(second level) to nodes
        Node::addNodes(*spawners->childNodes[i]);
    }

    //static std::vector<Vector2D<int>*> generateTestPositions()
    testPositions = Node::generateTestPositions();

    // generate just simple position in nodes
    // first level of child nodes  -> firstLevelNode from left to right
    // second level of child nodes -> secondLevelNode from left to right
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
    // calculate position of player on tree 1 - level of nodes and number of node and 2 level of node and number
    for(int i=0; i<4; i++)
    {
//        if(
//            player->getPosition().x >= (spawners->childNodes[i]->position->x - spawners->childNodes[i]->size * 0.5) &&
//            player->getPosition().x < (spawners->childNodes[i]->position->x + spawners->childNodes[i]->size * 0.5) &&
//            player->getPosition().y <= (spawners->childNodes[i]->position->y + spawners->childNodes[i]->size * 0.5) &&
//            player->getPosition().y > (spawners->childNodes[i]->position->y - spawners->childNodes[i]->size * 0.5)
//            )
//        {

        std::cout << "pos X: " << player->getPosition().x << " pos Y: " << player->getPosition().y << "\n";

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
//        }
    }
    afterFor:

    std::cout << "Player, first node: " << playerPosition.firstLevelNode << "\n";
    std::cout << "Player, second node: " << playerPosition.secondLevelNode << "\n";

//    while (true)
    for(int i=0; i<4; i++)
    {
        srand(clock());
        int number = rand() % 16;
        if(!(playerPosition.firstLevelNode == spawnersPositions.at(number)->firstLevelNode &&
             playerPosition.secondLevelNode == spawnersPositions.at(number)->secondLevelNode))
        {
            fourRandomPositions.push_back(spawnersPositions.at(number));
            break;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // WHAT THE FUCK??
            spawners->childNodes[i]->childNodes[j]->spawner = new Spawner();
            spawners->childNodes[i]->childNodes[j]->spawner->position.x = spawners->childNodes[i]->childNodes[j]->position->x;
            spawners->childNodes[i]->childNodes[j]->spawner->position.y = spawners->childNodes[i]->childNodes[j]->position->y;
        }
    }

    bool foundNumber = false;
//         for(int i=0; i<fourRandomPositions.size(); i++)
//         {
    int checksWithTrueResult = 1;
//    int j = 0;
    double quadDiagonal = spawners->childNodes[fourRandomPositions.at(0)->firstLevelNode]->childNodes[fourRandomPositions.at(0)->secondLevelNode]->size * sqrt(2);
    while(fourRandomPositions.size() < 4) //checksWithTrueResult <= 4)
    {
        srand(clock());
        int position = rand() % 16;
        for (int i = 0; i < fourRandomPositions.size(); i++)
        {
            if(//!(playerPosition.firstLevelNode == spawnersPositions.at(i)->firstLevelNode && playerPosition.secondLevelNode == spawnersPositions.at(i)->secondLevelNode) &&
               (
                (sqrt(pow((spawners->childNodes[fourRandomPositions.at(i)->firstLevelNode]->childNodes[fourRandomPositions.at(i)->secondLevelNode]->position->x -
                           spawners->childNodes[spawnersPositions.at(position)->firstLevelNode]->childNodes[spawnersPositions.at(position)->secondLevelNode]->position->x), 2) +

                      pow((spawners->childNodes[fourRandomPositions.at(i)->firstLevelNode]->childNodes[fourRandomPositions.at(i)->secondLevelNode]->position->y -
                           spawners->childNodes[spawnersPositions.at(position)->firstLevelNode]->childNodes[spawnersPositions.at(position)->secondLevelNode]->position->y), 2)) > quadDiagonal)
                )
            )
            { // TODO check if checksWithResult is 4 then break all loops
                // TODO check if position is inside collection
                fourRandomPositions.push_back(spawnersPositions.at(position));
                checksWithTrueResult++;
            }
        }
//        j++;
    }

//         spawnerPositionNumber.push_back(3);
//         spawnerPositionNumber.push_back(3);

    // spawners->createSpanwer(spawnerPositionNumber);

    // testPoint0.x = spawners->childNodes[0]->position->x;
    // testPoint0.y = spawners->childNodes[0]->position->y;
    //
    // testPoint1.x = spawners->childNodes[spawnerPositionNumber.at(0)]->childNodes[spawnerPositionNumber.at(0)]->position->x;
    // testPoint1.y = spawners->childNodes[spawnerPositionNumber.at(0)]->childNodes[spawnerPositionNumber.at(0)]->position->y;

//        std::cout << "x: " << testPoint0.x << "y: " << testPoint0.y << "\n";
//        std::cout << "x: " << testPoint1.x << "y: " << testPoint1.y << "\n";

    numberOfGivenColors.insert({"RED", 0});
    numberOfGivenColors.insert({"GREEN", 0});
    numberOfGivenColors.insert({"BLUE", 0});
    numberOfGivenColors.insert({"YELLOW", 0});


    prepareDataForDrawingGraphs();
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
