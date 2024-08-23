#include <iostream>
#include <fstream>
#include <string>
#include <bit>
#include <SDL_mixer.h>
#include <set>
#include "YasEngine.hpp"
#include "Circle.hpp"
#include "Collider.hpp"
#include "CosinePointsGenerator.hpp"
#include "FibonacciPointsGenerator.hpp"
#include "PrimeNumbersPointsGenerator.hpp"
#include "SinePointsGenerator.hpp"

YasEngine* YasEngine::instance = nullptr;

void YasEngine::initialize() {
  engineVersion = "YasEngine 1 | Beauty of Math 1 version: " + std::to_string(MAJOR_REVISION) + "." +
    std::to_string(MINOR_REVISION) + "." + std::to_string(BUG_FIX_RELEASE) + "." + std::to_string(BUILD_NUMBER);
  std::cout << engineVersion << "\n";
  readSettingsFromFile();

  srand(clock());

  prepareBasicSettings();
  prepareRendering();
  preparePlayer();
  prepareGameWorld();
  prepareSoundAndMusic();
  prepareInterface();

  writer.initialize();

  surfaceWithMathBasedEffects = new SurfaceWithMathBasedEffects(0, static_cast<int>(windowDimensions->y * 0.5F),
                                                                static_cast<int>(windowDimensions->x * 0.5F),
                                                                static_cast<int>(windowDimensions->y), BLACK);
}

void YasEngine::clean() {
  for (auto drawableObject : objectsToDraw) {
    delete drawableObject;
  }

  delete surfaceWithMathBasedEffects;
  delete pixelsTable;
  delete windowDimensions;

  delete sinePicture;
  delete cosinePicture;
  delete fibonacciePicture;
  delete primeNumbersPicture;

  delete mousePositionChangeInformation;

  // delete player; // will be deleted in the loop at the beginning of that method

  delete input;

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

void YasEngine::YasEngineStart() {
  TimePicker timePicker = TimePicker();
  time = timePicker.getSeconds();
  fpsTime = 0.0F;
  frames = 0;

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      handleInput(event);
    }

    newTime = timePicker.getSeconds();
    deltaTime = newTime - time;
    time = newTime;

    ++frames;
    fpsTime = fpsTime + deltaTime;
    if (fpsTime >= 1.0F) {
      fps = frames / fpsTime;
      frames = 0;
      fpsTime = 0.0F;
    }

    update(deltaTime);
    render(deltaTime);
    if (levelChanged) {
      levelChanged = false;
    }
  }

  clean();
}

void YasEngine::readSettingsFromFile() {
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

void YasEngine::prepareRendering() {
  pixelsTable = new PixelsTable(WINDOW_WIDTH, WINDOW_HEIGHT, BLACK);
  renderer = SDL_CreateRenderer(window, NULL);
  SDL_SetRenderLogicalPresentation(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_DISABLED,
                                   SDL_SCALEMODE_NEAREST);
  screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBX32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH,
                                    WINDOW_HEIGHT);
}

void YasEngine::prepareBasicSettings() {
  checkEndianness();

  SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_VIDEO);

  windowDimensions = new Vector2D<int>(WINDOW_WIDTH, WINDOW_HEIGHT);
  Uint32 windowFlags = SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_BORDERLESS | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE |
    SDL_WINDOW_OPENGL; //SDL_WINDOW_ALWAYS_ON_TOP
  window = SDL_CreateWindow("YasEngine", WINDOW_WIDTH, WINDOW_HEIGHT, windowFlags);

  SDL_SetWindowMinimumSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  SDL_HideCursor();
}


void YasEngine::checkEndianness() {
  if constexpr (std::endian::native == std::endian::big) {
    std::cout << "BIG ENDIAN" << std::endl;
    endianness = 0;
  }
  else {
    if (std::endian::native == std::endian::little) {
      std::cout << "LITTLE ENDIAN" << std::endl;
      endianness = 1;
    }
    else {
      std::cout << "MIXED ENDIAN" << std::endl;
      endianness = 2;
    }
  }
}

void YasEngine::drawHudElements(double& deltaTime) {
  drawCrossHair(mouseX, mouseY, *pixelsTable, false);
}

void YasEngine::drawFrame(double& deltaTime) {
  drawHorizontalLine(*pixelsTable, static_cast<int>(mapFrame.topLineSegment.point0.x),
                     static_cast<int>(mapFrame.topLineSegment.point1.x),
                     static_cast<int>(mapFrame.topLineSegment.point0.y), RED);
  drawHorizontalLine(*pixelsTable, static_cast<int>(mapFrame.bottomLineSegment.point0.x),
                     static_cast<int>(mapFrame.bottomLineSegment.point1.x),
                     static_cast<int>(mapFrame.bottomLineSegment.point0.y), GREEN);

  drawVerticalLine(*pixelsTable, static_cast<int>(mapFrame.leftLineSegment.point0.y),
                   static_cast<int>(mapFrame.leftLineSegment.point1.y),
                   static_cast<int>(mapFrame.leftLineSegment.point0.x), YELLOW);
  drawVerticalLine(*pixelsTable, static_cast<int>(mapFrame.rightLineSegment.point0.y),
                   static_cast<int>(mapFrame.rightLineSegment.point1.y),
                   static_cast<int>(mapFrame.rightLineSegment.point0.x), YELLOW);
}

void YasEngine::handleInput(SDL_Event& event) {
  if (event.type == SDL_EVENT_QUIT) {
    quit = true;
  }
  else {
    handleKeyboardInput(event);
    handleMouseInput(event);
  }
}

void YasEngine::handleKeyboardInput(SDL_Event& event) {
  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.key) {
    case SDLK_ESCAPE:
      handleGameStateWhenESCbuttonPushed();
      break;
    case SDLK_SPACE:
      handleGameStateWhenSPACEbuttonPushed();
      break;
    case SDLK_W:
      input->up = true;
      break;
    case SDLK_S:
      input->down = true;
      break;
    case SDLK_A:
      input->left = true;
      break;
    case SDLK_D:
      input->right = true;
      break;
    case SDLK_O:
      input->test_o_button = true;
      break;
    case SDLK_RETURN:
      if (gameState == LEVEL_CHANGE_SCREEN) {
        gameState = GameState::GAMEPLAY;
      }
      if (gameState == GameState::YOU_WON) {
        gameState = GameState::MAIN_MENU_RESTART;
        playerWonAndExited = true;
      }
      break;
    case SDLK_TAB:
      if (gameState == LEVEL_CHANGE_SCREEN) {
        gameState = GameState::GAMEPLAY;
      }
      if (gameState == GameState::YOU_WON) {
        gameState = GameState::MAIN_MENU_RESTART;
        playerWonAndExited = true;
      }
      break;
    default:
      ;
    }
  }

  if (event.type == SDL_EVENT_KEY_UP) {
    switch (event.key.key) {
    case SDLK_W:
      input->up = false;
      break;
    case SDLK_S:
      input->down = false;
      break;
    case SDLK_A:
      input->left = false;
      break;
    case SDLK_D:
      input->right = false;
      break;
    case SDLK_O:
      if (input->test_o_button == true) {
        Mix_PlayChannel(-1, otherSound, 0);
        input->test_o_button = false;
      }
      break;
    default:
      ;
    }
  }
}

void YasEngine::handleMouseInput(SDL_Event& event) {
  if (event.type == SDL_EVENT_MOUSE_MOTION) {
    handleMouseMovement();
  }
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
    switch (gameState) {
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

  if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
    switch (gameState) {
    case GAMEPLAY:
      player->isShooting = false;
      break;
    }
  }
}

void YasEngine::handleMouseMovement() {
  float x;
  float y;
  SDL_GetMouseState(&x, &y);
  mousePositionChangeInformation->mouseMoved = true;
  mousePositionChangeInformation->x = x;
  mousePositionChangeInformation->y = y;
  mouseX = static_cast<float>(mousePositionChangeInformation->x);
  mouseY = static_cast<float>(mousePositionChangeInformation->y);

  windowPositionToCartesianPosition(mouseX, mouseY, windowDimensions);
}

void YasEngine::deleteNotAliveObjects() {
  for (int i = 0; i < objectsToDraw.size(); i++) {
    if (objectsToDraw[i]->isAlive == false) {
      objectsToDraw.erase(objectsToDraw.begin() + i);
    }
  }
}

void YasEngine::handleSpawningCollectibles() {
  for (int i = 0; i < 8; i++) {
    int randomSpawner = Randomizer::drawNumberClosedInterval(0, 15);
    int firstLevelNodeIndex = spawnersPositions[randomSpawner]->firstLevelNode;
    int secondLevelNodeIndex = spawnersPositions[randomSpawner]->secondLevelNode;
    if (Spawner::numberOfSpawnedObjects < MAX_COLLECTIBLES_TO_SPAWN) {
      if (isObjectInSameQuarterAsProtagonist(randomSpawner)) {
        continue;
      }
      spawners->childNodes[firstLevelNodeIndex]->childNodes[secondLevelNodeIndex]->spawner->spawnObject(go);
      if (go != nullptr) {
        Spawner::numberOfSpawnedObjects++;
        objectsToDraw.push_back(go);
        go = nullptr;
      }
    }
    else {
      spawners->childNodes[firstLevelNodeIndex]->childNodes[secondLevelNodeIndex]->spawner->resetTimes();
    }
  }
}

bool YasEngine::isObjectInSameQuarterAsProtagonist(int randomSpawner) {
  int quarterSize = spawners->childNodes[spawnersPositions[randomSpawner]->firstLevelNode]->childNodes[spawnersPositions
    [randomSpawner]->secondLevelNode]->size;
  return (
    (player->getPosition().x < (spawners->childNodes[spawnersPositions[randomSpawner]->firstLevelNode]->childNodes[
        spawnersPositions[randomSpawner]->secondLevelNode]->position->x +
      quarterSize / 2)) &&
    (player->getPosition().x > (spawners->childNodes[spawnersPositions[randomSpawner]->firstLevelNode]->childNodes[
        spawnersPositions[randomSpawner]->secondLevelNode]->position->x -
      quarterSize / 2)) &&
    (player->getPosition().y < (spawners->childNodes[spawnersPositions[randomSpawner]->firstLevelNode]->childNodes[
        spawnersPositions[randomSpawner]->secondLevelNode]->position->y +
      quarterSize / 2)) &&
    (player->getPosition().y > (spawners->childNodes[spawnersPositions[randomSpawner]->firstLevelNode]->childNodes[
        spawnersPositions[randomSpawner]->secondLevelNode]->position->y -
      quarterSize / 2))
  );
}

void YasEngine::handleProjectiles() {
  Projectile* projectile = player->shoot();

  if (projectile != nullptr) {
    Mix_PlayChannel(-1, shootSound, 0);
    objectsToDraw.push_back(projectile);
  }

  if (projectile != nullptr) {
    projectile = nullptr;
  }
}

void YasEngine::handlePlayer() {
  if (mousePositionChangeInformation->mouseMoved || input->up || input->down || input->left || input->right) {
    player->rotateToMousePositionInLocalCoordinateSystem(static_cast<float>(mousePositionChangeInformation->x),
                                                         static_cast<float>(mousePositionChangeInformation->y),
                                                         windowDimensions);
  }
}

void YasEngine::preparePlayer() {
  srand(clock());
  int sizeOfGameplaySpace = static_cast<int>(windowDimensions->x * 0.25F);
  int x = Randomizer::drawNumberClosedInterval(0, sizeOfGameplaySpace) - 64;
  int y = Randomizer::drawNumberClosedInterval(0, sizeOfGameplaySpace) - 64;

  player = new Player(static_cast<float>((-sizeOfGameplaySpace) + x), 0.0F + y);
  player->setColor(YELLOW);
  player->setInput(input);
  player->setInput(mousePositionChangeInformation);
  objectsToDraw.push_back(player);
}

void YasEngine::update(double& deltaTime) {
  if (levelChanged) {
    for (int i = 0; i < objectsToDraw.size(); i++) {
      if (objectsToDraw[i]->iAm != GameObject::PROTAGONIST) {
        objectsToDraw[i]->isAlive = false;
      }
    }
    Spawner::numberOfSpawnedObjects = 0;
  }

  deleteNotAliveObjects();

  switch (gameState) {
  case GAMEPLAY:
    handleSpawningCollectibles();
    handlePhysics();
    if (levelChanged) {
      gameState = LEVEL_CHANGE_SCREEN;
    }
    if (levelChanged && level == -1) {
      gameState = GameState::YOU_WON;
    }
    moveObjects();
    handleProjectiles();
    handlePlayer();
    break;
  }

  if (playerWonAndExited) {
    resetAll();
  }
}

void YasEngine::resetAll() {
  deleteNotAliveObjects();
  level = 1;
  previousLevel = 0;
  levelChanged = false;
  sinePointsHarvested = 0;
  cosinePointsHarvested = 0;
  primesPointsHarvested = 0;
  fibbsPointsHarvested = 0;
  playerWonAndExited = false;
}

void YasEngine::render(double& deltaTime) {
  pixelsTable->clearColor(BLACK);
  surfaceWithMathBasedEffects->clearColor(BLACK);

  switch (gameState) {
  case INTRO:
    writer.write((-238) / 2, 200, "BEOUTY.OF.MATH", LIGHT_BLUE, *pixelsTable);
  // TODO write title and version and tha game is powered by YasEngine
    writer.write((-170) / 2, 100, "POWERED.BY", RED, *pixelsTable);
    writer.write((-170) / 2, 0, "YAS.ENGINE", YELLOW, *pixelsTable);
    break;
  case MAIN_MENU_RESTART:
    drawButtons();
    break;
  case GAMEPLAY:
    renderGameObjects(deltaTime);
    renderOnViewports(deltaTime);
    drawFrame(deltaTime);
    break;
  case OUTRO:
    writer.write((-37 * 17) / 2, 350, "GAME.DESIGN.PROGRAMMING.AND.MARKETING", LIGHT_BLUE, *pixelsTable);
    writer.write((-14 * 17) / 2, 325, "LUKASZ.SAWICKI", PURPLE, *pixelsTable);
    writer.write((-22 * 17) / 2, 275, "SOUND.DESIGN.AND.MUSIC", LIGHT_BLUE, *pixelsTable);
    writer.write((-17 * 17) / 2, 250, "JAKUB.TWAROGOWSKI", PURPLE, *pixelsTable);
    writer.write((-17 * 17) / 2, 200, "QUALITY.ASSURANCE", LIGHT_BLUE, *pixelsTable);
    writer.write((-15 * 17) / 2, 175, "BARTLOMIEJ.KAWA", PURPLE, *pixelsTable);
    writer.write((-15 * 17) / 2, 125, "SPECIAL.THANKS:", GREEN, *pixelsTable);
    writer.write((-22 * 17) / 2, 75, "MY.DEAR.SISTER.IZABELA", YELLOW, *pixelsTable);
    writer.write((-15 * 17) / 2, 50, "MY.LOVE.MARIOLA", YELLOW, *pixelsTable);
    writer.write((-50 * 17) / 2, 0, "MY.FRIENDS.FROM.WARSAW.SCHOOL.OF.COMPUTER.SCIENCE:", BLUE, *pixelsTable);
    writer.write((-36 * 17) / 2, -25, "LUKASZ.KRZYSZTOF.MICHAL.MAREK.TOMASZ", YELLOW, *pixelsTable);
    writer.write((-21 * 17) / 2, -75, "MY.FRENDS.FROM.GDS.4:", BLUE, *pixelsTable);
    writer.write((-17 * 17) / 2, -100, "KASIA.AND.BARTOSZ", YELLOW, *pixelsTable);
    writer.write((-31 * 17) / 2, -150, "WHOLE.COMMUNITY.OF.KNTG.POLYGON", POLYGON, *pixelsTable);
    writer.write((-31 * 17) / 2, -200, "AND.ALL.MEMBERS.OF.TEAM.XPORTAL", XPORTAL, *pixelsTable);

    break;
  case LEVEL_CHANGE_SCREEN:
    renderLevelChange();
    break;
  case YOU_WON:
    renderWonScreen();
    break;
  default:
    ;
  }

  drawHudElements(deltaTime);

  SDL_UpdateTexture(screenTexture, NULL, pixelsTable->pixels, WINDOW_WIDTH * 4);
  SDL_RenderTexture(renderer, screenTexture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

void YasEngine::renderGameObjects(double& deltaTime) {
  for (auto object : objectsToDraw) {
    if (object->isAlive) {
      // TODO if gamestate == gameplay

      drawPolygon(object, *pixelsTable);
    }
  }
}

void YasEngine::renderOnViewports(double& deltaTime) {
  if (tests) {
    surfaceWithMathBasedEffects->drawCartesianAxies();
  }

  switch (level) {
  case 1:
    surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(primeNumbersPicture->pointsSet->points,
                                                           primeNumbersPicture->basePointsFuel, primesPointsHarvested,
                                                           LIGHT_BLUE, false);
    break;

  case 2:
    surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(fibonacciePicture->pointsSet->points,
                                                           fibonacciePicture->basePointsFuel, fibbsPointsHarvested,
                                                           PURPLE, false);
    break;
  case 3:
    surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(sinePicture->pointsSet->points, sinePicture->basePointsFuel,
                                                           sinePointsHarvested, BLUE, true);
    break;
  case 4:
    surfaceWithMathBasedEffects->drawNumbersAsGroupOfLines(cosinePicture->pointsSet->points,
                                                           cosinePicture->basePointsFuel, cosinePointsHarvested, RED,
                                                           true);
    break;
  default:
    ;
  }

  surfaceWithMathBasedEffects->copyPixelsInToPIxelTable(*pixelsTable);
}

void YasEngine::renderLevelChange() {
  switch (previousLevel) {
  case 1:

    writer.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.1", LIGHT_BLUE, *pixelsTable);
    writer.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", BLUE, *pixelsTable);
    writer.write((-221) / 2, 0, "PRIME.NUMBERS", GREEN, *pixelsTable);
    break;
  case 2:
    writer.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.2", LIGHT_BLUE, *pixelsTable);
    writer.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", BLUE, *pixelsTable);
    writer.write((-289) / 2, 0, "FIBONACCI.NUMBERS", GREEN, *pixelsTable);
    break;
  case 3:
    writer.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.2", LIGHT_BLUE, *pixelsTable);
    writer.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", BLUE, *pixelsTable);
    writer.write((-221) / 2, 0, "SINE.FUNCTION", GREEN, *pixelsTable);
    break;
  case 4:
    writer.write((-425) / 2, 200, "YOU.JUST.FINISHED.LEVEL.2", LIGHT_BLUE, *pixelsTable);
    writer.write((-544) / 2, 100, "YOU.ARE.HAPPY.TO.HAVE.DISCOVERED", BLUE, *pixelsTable);
    writer.write((-255) / 2, 0, "COSINE.FUNCTION", GREEN, *pixelsTable);
    writer.write((-187) / 2, -25, "AND.YOU.WON", YELLOW, *pixelsTable);
    break;
  default:
    ;
  }
}

void YasEngine::renderWonScreen() {
  writer.write((-119) / 2, 310, "YOU.WON", LIGHT_BLUE, *pixelsTable);
  writer.write((-408) / 2, 210, "MATHEMATICS.IS.BEAUTIFUL", YELLOW, *pixelsTable);
  writer.write((-578) / 2, 110, "YOU.ARE.NOT.SUPPOSED.TO.BELIEVE.ME", PURPLE, *pixelsTable);
  writer.write((-357) / 2, 10, "CHECK.IT.FOR.YOURSELF", PURPLE, *pixelsTable);
  writer.write((-935) / 2, -10, "FIND.AND.LEARN.MORE.ABOUT.WHAT.YOU.HAVE.JUST.DISCOVERED", PURPLE, *pixelsTable);
  writer.write((-221) / 2, -110, "PRIME.NUMBERS", GREEN, *pixelsTable);
  writer.write((-289) / 2, -160, "FIBONACCI.NUMBERS", YELLOW, *pixelsTable);
  writer.write((-425) / 2, -210, "SINE.AND.COSINE.FUNCTIONS", LIGHT_BLUE, *pixelsTable);
}

void YasEngine::handlePhysics() {
  if (objectsToDraw.size() >= 3) {
    for (int i = 0; i < static_cast<int>(objectsToDraw.size() - 2); i++) {
      if (objectsToDraw[i]->iAm == GameObject::COLLECTIBLE) {
        handleCollectiblesWithWallsCollisions(objectsToDraw[i]);
      }

      if (objectsToDraw[i]->iAm == GameObject::PROTAGONIST) {
        handleProtagonistWithWallsCollisions(objectsToDraw[i]);
      }

      for (int j = i; j < static_cast<int>(objectsToDraw.size()); j++) {
        if (
          objectsToDraw[i] == objectsToDraw[j] ||
          (objectsToDraw[i]->iAm == GameObject::PROJECTILE && objectsToDraw[j]->iAm == GameObject::PROJECTILE) ||
          (objectsToDraw[i]->iAm == GameObject::PROJECTILE && objectsToDraw[j]->iAm == GameObject::PROTAGONIST) ||
          (objectsToDraw[i]->iAm == GameObject::PROTAGONIST && objectsToDraw[j]->iAm == GameObject::PROJECTILE) ||
          (objectsToDraw[i]->iAm == GameObject::COLLECTIBLE && objectsToDraw[j]->iAm == GameObject::COLLECTIBLE)
        ) {
          continue;
        }

        // LEFT Projectile <-> Collectible && Protagonist <-> Collectible)
        if (objectsToDraw[i]->isAlive && objectsToDraw[j]->isAlive) {
          GameObject* protagonist = getProtagonist(objectsToDraw[i], objectsToDraw[j]);
          GameObject* gameObj = getNotProtagonist(objectsToDraw[i], objectsToDraw[j]);

          if ((protagonist != nullptr) && gameObj->iAm == GameObject::COLLECTIBLE && !gameObj->collider.isInCollision &&
            Collider::isCollision(objectsToDraw[i]->collider, objectsToDraw[j]->collider)) {
            // handleBuildingGraph
            handleDisassemblingGraphs(gameObj);

            gameObj->collider.isInCollision = true;
          }

          // if exited from collision
          if ((protagonist != nullptr) && gameObj->iAm == GameObject::COLLECTIBLE && gameObj->collider.isInCollision &&
            !Collider::isCollision(objectsToDraw[i]->collider, objectsToDraw[j]->collider)) {
            gameObj->collider.isInCollision = false;
          }

          if ((protagonist == nullptr) &&
            Collider::isCollision(objectsToDraw[i]->collider, objectsToDraw[j]->collider)) {
            objectsToDraw[i]->isAlive = false;
            objectsToDraw[j]->isAlive = false;
            Mix_PlayChannel(-1, hitSound, 0);

            if (gameObj->iAm == GameObject::COLLECTIBLE) {
              handleDestroingCollectibles(gameObj);
              handlingAssemblingGraphs(gameObj);
            }
          }
        }
      }
    }
  }
} // END OF handlePhysics()

void YasEngine::handleDisassemblingGraphs(GameObject* gameObj) {
  if (primesPointsHarvested < 0) {
    primesPointsHarvested = 0;
    return;
  }
  if (fibbsPointsHarvested < 0) {
    fibbsPointsHarvested = 0;
    return;
  }
  if (sinePointsHarvested < 0) {
    sinePointsHarvested = 0;
    return;
  }
  if (cosinePointsHarvested < 0) {
    cosinePointsHarvested = 0;
    return;
  }

  switch (level) {
  case 1:
    primesPointsHarvested -= gameObj->numberOfVertices;
    break;

  case 2:

    fibbsPointsHarvested -= gameObj->numberOfVertices;
    break;

  case 3:

    sinePointsHarvested -= gameObj->numberOfVertices;
    break;

  case 4:

    cosinePointsHarvested -= gameObj->numberOfVertices;
    break;

  default:
    ;
  }
}

void YasEngine::handleDestroingCollectibles(GameObject* gameObj) {
  if (Spawner::numberOfSpawnedObjects > 0) {
    --Spawner::numberOfSpawnedObjects;
  }
  else {
    Spawner::numberOfSpawnedObjects = 0;
  }
}

void YasEngine::handlingAssemblingGraphs(GameObject* gameObj) {
  int newValueOfPrimesPointsHarvested = primesPointsHarvested + gameObj->numberOfVertices;
  int newValueOfFibbsPointsHarvested = fibbsPointsHarvested + gameObj->numberOfVertices;
  int newSinePointsHarvested = sinePointsHarvested + gameObj->numberOfVertices;
  int newCosinePointsHarvested = cosinePointsHarvested + gameObj->numberOfVertices;

  int test1 = primesPointsHarvested;

  if (level == 1 && newValueOfPrimesPointsHarvested >= primeNumbersPicture->basePointsFuel) {
    primesPointsHarvested = primeNumbersPicture->basePointsFuel;
    previousLevel = level;
    level = 2;
    levelChanged = true;
    return;
  }

  if (level == 2 && newValueOfFibbsPointsHarvested >= fibonacciePicture->basePointsFuel) {
    fibbsPointsHarvested = fibonacciePicture->basePointsFuel;
    previousLevel = level;
    level = 3;
    levelChanged = true;
    return;
  }

  int some = sinePointsHarvested;

  if (level == 3 && newSinePointsHarvested >= sinePicture->basePointsFuel) {
    sinePointsHarvested = sinePicture->basePointsFuel;
    previousLevel = level;
    level = 4;
    levelChanged = true;
    return;
  }

  if (level == 4 && newCosinePointsHarvested >= cosinePicture->basePointsFuel) {
    cosinePointsHarvested = cosinePicture->basePointsFuel;
    previousLevel = level;
    level = -1;
    levelChanged = true;
    return;
  }

  switch (level) {
  case 1:

    if (newValueOfPrimesPointsHarvested <= primeNumbersPicture->basePointsFuel) {
      primesPointsHarvested = newValueOfPrimesPointsHarvested;
    }
    break;
  case 2:

    if (newValueOfFibbsPointsHarvested <= fibonacciePicture->basePointsFuel) {
      fibbsPointsHarvested = newValueOfFibbsPointsHarvested;
    }

    break;
  case 3:

    if (newSinePointsHarvested <= sinePicture->basePointsFuel) {
      sinePointsHarvested = newSinePointsHarvested;
    }

    break;
  case 4:

    if (newCosinePointsHarvested <= cosinePicture->basePointsFuel) {
      cosinePointsHarvested = newCosinePointsHarvested;
    }

    break;
  default:
    ;
  }
}

void YasEngine::handleCollectiblesWithWallsCollisions(GameObject* object) {
  float leftWall = mapFrame.leftLineSegment.point0.x;
  float rightWall = mapFrame.rightLineSegment.point0.x;
  float topWall = mapFrame.topLineSegment.point0.y;
  float bottomWall = mapFrame.bottomLineSegment.point0.y;

  if (object->iAm == GameObject::COLLECTIBLE) {
    if (object->getColliderLeftSide() < static_cast<int>(leftWall)) {
      bounceCollectibles(object, LEFT);
    }

    if (object->getColliderRightSide() > static_cast<int>(rightWall)) {
      bounceCollectibles(object, RIGHT);
    }

    if (object->getColliderTopSide() < static_cast<int>(topWall)) {
      bounceCollectibles(object, TOP);
    }

    if (object->getColliderBottomSide() > static_cast<int>(bottomWall)) {
      bounceCollectibles(object, BOTTOM);
    }
  }
}

bool YasEngine::isObjectProtagonist(GameObject* object) {
  return object->iAm == GameObject::PROTAGONIST;
}

GameObject* YasEngine::getProtagonist(GameObject* object0, GameObject* object1) {
  if (isObjectProtagonist(object0)) {
    return object0;
  }
  if (isObjectProtagonist(object1)) {
    return object1;
  }
  return nullptr;
}

GameObject* YasEngine::getNotProtagonist(GameObject* object0, GameObject* object1) {
  if (!isObjectProtagonist(object0)) {
    return object0;
  }
  if (!isObjectProtagonist(object1)) {
    return object1;
  }
  return nullptr;
}

void YasEngine::handleProtagonistWithWallsCollisions(GameObject* object) {
  float leftWall = mapFrame.leftLineSegment.point0.x;
  float rightWall = mapFrame.rightLineSegment.point0.x;
  float topWall = mapFrame.topLineSegment.point0.y;
  float bottomWall = mapFrame.bottomLineSegment.point0.y;

  if (object->getColliderLeftSide() < static_cast<int>(leftWall)) {
    moveObjectToMapBoundries(object, LEFT);
    // bounceCollectibles(object, LEFT);
  }

  if (object->getColliderRightSide() > static_cast<int>(rightWall)) {
    moveObjectToMapBoundries(object, RIGHT);
    // bounceCollectibles(object, RIGHT);
  }

  if (object->getColliderTopSide() > static_cast<int>(topWall)) {
    moveObjectToMapBoundries(object, TOP);
    // bounceCollectibles(object, TOP);
  }

  if (object->getColliderBottomSide() < static_cast<int>(bottomWall)) {
    moveObjectToMapBoundries(object, BOTTOM);
    // bounceCollectibles(object, BOTTOM);
  }
}

void YasEngine::bounceCollectibles(GameObject* gameObject, Wall wall) {
  Vector2D<float> normal;
  switch (wall) {
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

void YasEngine::moveObjectToMapBoundries(GameObject* gameObject, Wall wall, int shift) {
  switch (wall) {
  case LEFT:
    gameObject->setX(mapFrame.leftLineSegment.point0.x + gameObject->collider.radius + shift);
    break;
  case RIGHT:
    gameObject->setX(mapFrame.rightLineSegment.point0.x - gameObject->collider.radius - shift);
    break;
  case TOP:
    gameObject->setY(mapFrame.topLineSegment.point0.y - gameObject->collider.radius - shift);
    break;
  case BOTTOM:
    gameObject->setY(mapFrame.bottomLineSegment.point0.y + gameObject->collider.radius + shift);
    break;
  default:
    ;
    break;
  }
}

void YasEngine::moveObjects() {
  for (auto object : objectsToDraw) {
    if (object->isAlive) {
      object->move(static_cast<float>(deltaTime));
      object->regeneratePolygon();
    }
  }
}

void YasEngine::prepareSoundAndMusic() {
  audioSpecs.freq = 44100;
  audioSpecs.format = MIX_DEFAULT_FORMAT;
  audioSpecs.channels = 2;

  if (Mix_OpenAudio(0, &audioSpecs) < 0) {
    std::cout << "Error cannot open audio device" << std::endl;
  }

  Mix_Init(MIX_DEFAULT_FORMAT);

  music = Mix_LoadMUS("music.wav");
  if (music == NULL) {
    std::cout << "Error while loading music. Cannot load music." << std::endl;
    std::cout << "SDL message: " << SDL_GetError() << std::endl << " | Mix library error: " << Mix_GetError() <<
      std::endl;
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


  if (shootSound == NULL || hitSound == NULL || otherSound == NULL) {
    std::cout << "Error while loading sounds. Cannot load sounds." << std::endl;
    std::cout << "SDL message: " << SDL_GetError() << std::endl << " | Mix library error: " << Mix_GetError() <<
      std::endl;
    quit = true;
  }
  Mix_PlayMusic(music, 999);
}

void YasEngine::prepareGameWorld() {
  // srand(clock());

  int mainNodeX = -(windowDimensions->x / 4);
  int mainNodeY = 0;

  std::cout << "Main node X: " << mainNodeX << "\n";
  std::cout << "Main node Y: " << mainNodeY << "\n";

  spawners = new Node(new Vector2D<int>(-(windowDimensions->x / 4), 0), windowDimensions->x / 2, nullptr);

  // adding nodes(first level) to head node
  Node::addNodes(*spawners);
  for (int i = 0; i < 4; i++) {
    // adding nodes(second level) to nodes
    Node::addNodes(*spawners->childNodes[i]);
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      spawnersPositions.push_back(new NodeNumbersOnTwoProceedingLevels(i, j));
    }
  }

  int drawnNumbers = 0; // PL - wylosowane a nie narysowane w tym kontekscie
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
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (
        player->getPosition().x >= (spawners->childNodes[i]->childNodes[j]->position->x - spawners->childNodes[i]->
          childNodes[j]->size * 0.5) &&
        player->getPosition().x < (spawners->childNodes[i]->childNodes[j]->position->x + spawners->childNodes[i]->
          childNodes[j]->size * 0.5) &&
        player->getPosition().y <= (spawners->childNodes[i]->childNodes[j]->position->y + spawners->childNodes[i]->
          childNodes[j]->size * 0.5) &&
        player->getPosition().y > (spawners->childNodes[i]->childNodes[j]->position->y - spawners->childNodes[i]->
          childNodes[j]->size * 0.5)
      ) {
        playerPosition.firstLevelNode = i;
        playerPosition.secondLevelNode = j;
        goto afterFor;
      }
    }
  }
afterFor:

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      spawners->childNodes[i]->childNodes[j]->spawner = new Spawner(spawners->childNodes[i]->childNodes[j]->position->x,
                                                                    spawners->childNodes[i]->childNodes[j]->position->
                                                                    y);
    }
  }

  numberOfGivenColors.insert({"RED", 0});
  numberOfGivenColors.insert({"GREEN", 0});
  numberOfGivenColors.insert({"BLUE", 0});
  numberOfGivenColors.insert({"YELLOW", 0});

  prepareDataForDrawingGraphs();
}

void YasEngine::setFrameAroundGameplaySpace() {
  const int VERTHICAL_SHIFT = 10;
  const int HORIZONTAL_SHIFT = 10;

  // HORIZONTAL LINE SEGMENTS

  // Top              ---->
  // Left point     
  mapFrame.topLineSegment.point0.x = static_cast<float>((-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT);
  mapFrame.topLineSegment.point0.y = static_cast<float>((windowDimensions->y / 2) - VERTHICAL_SHIFT);
  // Right point
  mapFrame.topLineSegment.point1.x = static_cast<float>(-1 - HORIZONTAL_SHIFT);
  mapFrame.topLineSegment.point1.y = static_cast<float>((windowDimensions->y / 2) - VERTHICAL_SHIFT);

  // Bottom
  // Left point
  mapFrame.bottomLineSegment.point0.x = static_cast<float>((-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT);
  mapFrame.bottomLineSegment.point0.y = static_cast<float>((-(windowDimensions->y / 2)) + VERTHICAL_SHIFT);

  // Right point
  mapFrame.bottomLineSegment.point1.x = static_cast<float>(-HORIZONTAL_SHIFT);
  mapFrame.bottomLineSegment.point1.y = static_cast<float>((-(windowDimensions->y / 2)) + VERTHICAL_SHIFT);

  // VERTICAL LINE SEGMENTS
  // Left
  // Top point
  mapFrame.leftLineSegment.point0.x = static_cast<float>((-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT);
  mapFrame.leftLineSegment.point0.y = static_cast<float>((windowDimensions->y / 2) - VERTHICAL_SHIFT);
  // Bottom point
  mapFrame.leftLineSegment.point1.x = static_cast<float>((-(windowDimensions->x / 2)) + HORIZONTAL_SHIFT);
  mapFrame.leftLineSegment.point1.y = static_cast<float>((-(windowDimensions->y / 2)) + VERTHICAL_SHIFT);

  // Right
  // Top point
  mapFrame.rightLineSegment.point0.x = static_cast<float>(-1 - HORIZONTAL_SHIFT);
  mapFrame.rightLineSegment.point0.y = static_cast<float>((windowDimensions->y / 2) - VERTHICAL_SHIFT);
  // Bottom point
  mapFrame.rightLineSegment.point1.x = static_cast<float>(-1 - HORIZONTAL_SHIFT);
  mapFrame.rightLineSegment.point1.y = static_cast<float>((-(windowDimensions->y / 2)) + VERTHICAL_SHIFT);
}

void YasEngine::prepareDataForDrawingGraphs() {
  preparePrimesDrawing();
  prepareFibonacciDrawing();
  prepareSineDrawing();
  prepareCosineDrawing();
}

void YasEngine::prepareSineDrawing() {
  std::map<float, float>* sines = generateSineNumbers(40); //generatePrimeNumbersLessThanN(1000);
  sinePointsHarvested = 0;

  // std::map < std::string, std::map<int, std::map<float, float>>> pairNumbersMap;

  std::map<int, std::map<float, float>> numberedSines;

  pairNumbersMap.insert(
    std::pair<std::string, std::map<int, std::map<float, float>*>
              *>("Sines", new std::map<int, std::map<float, float>*>));

  // for (int i = 0; i < sinuses->size(); i++)
  // {
  int i = 0;
  for (std::pair<float, float> pair : *sines) {
    std::map<float, float>* m = new std::map<float, float>();
    m->insert(pair);
    pairNumbersMap.at("Sines")->insert(std::pair<int, std::map<float, float>*>(i, m));
  }

  // }

  sinePicture = new MathPicture(sines, new SinePointsGenerator());
}

void YasEngine::prepareCosineDrawing() {
  std::map<float, float>* cosines = generateCosineNumbers(40); //generatePrimeNumbersLessThanN(1000);
  cosinePointsHarvested = 0;

  // std::map < std::string, std::map<int, std::map<float, float>>> pairNumbersMap;

  std::map<int, std::map<float, float>> numberedSines;

  pairNumbersMap.insert(
    std::pair<std::string, std::map<int, std::map<float, float>*>*>(
      "Cosines", new std::map<int, std::map<float, float>*>));

  // for (int i = 0; i < sinuses->size(); i++)
  // {
  int i = 0;
  for (std::pair<float, float> pair : *cosines) {
    std::map<float, float>* m = new std::map<float, float>();
    m->insert(pair);
    pairNumbersMap.at("Cosines")->insert(std::pair<int, std::map<float, float>*>(i, m));
  }

  // }

  cosinePicture = new MathPicture(cosines, new CosinePointsGenerator());
}

void YasEngine::prepareFibonacciDrawing() {
  std::vector<int> fibbs = generateNfibonacciNumbers(40);
  fibbsPointsHarvested = 0;

  numbersMap.insert(std::pair<std::string, std::map<int, float>*>("Fibbs", new std::map<int, float>));

  for (int i = 0; i < fibbs.size(); i++) {
    numbersMap.at("Fibbs")->insert(std::pair<int, int>(i, fibbs.at(i)));
  }

  fibonacciePicture = new MathPicture(numbersMap.at("Fibbs"), new FibonacciPointsGenerator());
}

void YasEngine::preparePrimesDrawing() {
  std::vector<int> primes = generatePrimeNumbersLessThanN(1000);
  primesPointsHarvested = 0;

  numbersMap.insert(std::pair<std::string, std::map<int, float>*>("Primes", new std::map<int, float>));

  for (int i = 0; i < primes.size(); i++) {
    numbersMap.at("Primes")->insert(std::pair<int, int>(i, primes.at(i)));
  }

  primeNumbersPicture = new MathPicture(numbersMap.at("Primes"), new PrimeNumbersPointsGenerator());

  std::cout << "preparedPrimesDrawing" << "\n";
}

void YasEngine::prepareInterface() {
  //Button 1
  buttons.push_back(new Button(Button::RESTART_START, "START", RED));
  buttons.at(0)->setPosition(0, 50);
  dynamic_cast<Button*>(buttons.at(0))->horizontalMargin = 10;
  dynamic_cast<Button*>(buttons.at(0))->verticalMargin = 5;
  dynamic_cast<Button*>(buttons.at(0))->buttonWidth = writer.FONT_WIDTH * static_cast<int>(dynamic_cast<Button*>(buttons
    .at(0))->text.size()) + 2 * dynamic_cast<Button*>(buttons.at(0))->horizontalMargin;
  dynamic_cast<Button*>(buttons.at(0))->buttonHeight = writer.FONT_HEIGHT + 2 * dynamic_cast<Button*>(buttons.at(0))->
    verticalMargin;
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
  dynamic_cast<Button*>(buttons.at(1))->buttonWidth = writer.FONT_WIDTH * static_cast<int>(dynamic_cast<Button*>(buttons
    .at(1))->text.size()) + 2 * dynamic_cast<Button*>(buttons.at(1))->horizontalMargin;
  dynamic_cast<Button*>(buttons.at(1))->buttonHeight = writer.FONT_HEIGHT + 2 * dynamic_cast<Button*>(buttons.at(1))->
    verticalMargin;
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

void YasEngine::drawButtons() {
  for (unsigned int i = 0; i < buttons.size(); i++) {
    drawPolygon(buttons.at(i), *pixelsTable);
    writer.write(
      static_cast<int>(buttons.at(i)->getPosition().x - dynamic_cast<Button*>(buttons.at(i))->buttonTextWidth * 0.5F +
        ScreenWriter::FONT_WIDTH * 0.5F), static_cast<int>(buttons.at(i)->getPosition().y),
      dynamic_cast<Button*>(buttons.at(i))->text, dynamic_cast<Button*>(buttons.at(i))->color, *pixelsTable);
  }
}

Button::ButtonId YasEngine::checkWhichButtonClicked() {
  float x = static_cast<float>(mousePositionChangeInformation->x);
  float y = static_cast<float>(mousePositionChangeInformation->y);
  windowPositionToCartesianPosition(x, y, windowDimensions);
  for (unsigned int i = 0; i < buttons.size(); i++) {
    if (
      // mouse cursor under top Y
      y <= (buttons.at(i)->getPosition().y + dynamic_cast<Button*>(buttons.at(i))->buttonHeight * 0.5F) &&
      // mouser cursor above bottom Y
      y >= (buttons.at(i)->getPosition().y - dynamic_cast<Button*>(buttons.at(i))->buttonHeight * 0.5F) &&
      // cursor to the right of left X
      x >= (buttons.at(i)->getPosition().x - dynamic_cast<Button*>(buttons.at(i))->buttonWidth * 0.5F) &&
      // cursor to the left of X
      x <= (buttons.at(i)->getPosition().x + dynamic_cast<Button*>(buttons.at(i))->buttonWidth * 0.5F)
    ) {
      return dynamic_cast<Button*>(buttons.at(i))->buttonId;
    }
  }
  return Button::NONE;
}

void YasEngine::handleClickedButtons() {
  switch (checkWhichButtonClicked()) {
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

void YasEngine::handleGameStateWhenESCbuttonPushed() {
  switch (gameState) {
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
  case LEVEL_CHANGE_SCREEN:
    gameState = GameState::GAMEPLAY;
    break;
  case YOU_WON:
    gameState = GameState::MAIN_MENU_RESTART;
    playerWonAndExited = true;
    break;
  default:
    ;
  }
}

void YasEngine::handleGameStateWhenSPACEbuttonPushed() {
  switch (gameState) {
  case INTRO:
    gameState = GameState::MAIN_MENU_RESTART;
    break;
  case OUTRO:
    quit = true;
    break;
  case LEVEL_CHANGE_SCREEN:
    gameState = GameState::GAMEPLAY;
    break;
  case GAMEPLAY:
    levelChanged = false;
  // break;
    break;
  case YOU_WON:
    gameState = GameState::MAIN_MENU_RESTART;
    playerWonAndExited = true;
    break;
  default:
    ;
  }
}
