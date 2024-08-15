#ifndef YASENGINE_HPP
#define YASENGINE_HPP
#include<document.h>
#include<iostream>
#include<vector>
#include<string>
#include<SDL_mixer.h>
#include<map>
#include"Vector2D.hpp"
#include"PixelsTable.hpp"
#include"GameObject.hpp"
#include"Player.hpp"
#include"InputOutputHandler.hpp"
#include"SurfaceWithMathBasedEffects.hpp"
#include "Spawner.hpp"
#include "Node.hpp"
#include"ScreenWriter.hpp"
#include"Button.hpp"
#include "MapFrame.hpp"
#include "MathPicture.hpp"

class YasEngine
{	
	public:
		bool tests = false;
		std::string engineVersion;
		int MAJOR_REVISION = 1;
		int MINOR_REVISION = 3;
		int BUG_FIX_RELEASE = 0;
		int BUILD_NUMBER = 0;

		rapidjson::Document settings;
		int musicVolume = MIX_MAX_VOLUME;
		int shootVolume = MIX_MAX_VOLUME;
		int hitVolume = MIX_MAX_VOLUME;
		int otherVolume = MIX_MAX_VOLUME;

        bool collided = false;
		GameObject* go;
        enum GameState
        {
            INTRO,
            MAIN_MENU_RESTART,
            GAMEPLAY,
            OUTRO,
			PAUSE,
			LEVEL_CHANGE_SCREEN,
			YOU_WON
        };

		bool playerWonAndExited = false;

		enum Wall
		{
			LEFT,
			RIGHT,
			TOP,
			BOTTOM
		};

		struct NodeNumbersOnTwoProceedingLevels
		{
            int firstLevelNode = 0;
            int secondLevelNode = 0;
			NodeNumbersOnTwoProceedingLevels()
			{
                firstLevelNode = 0;
                secondLevelNode = 0;
			}
			NodeNumbersOnTwoProceedingLevels(int first, int second)
			{
				this->firstLevelNode = first;
				this->secondLevelNode = second;
			}
		};

        std::vector<Vector2D<int>*> testPositions;

        GameState gameState = GameState::INTRO;

        std::vector<GameObject*> buttons;

		int basePointsNumber = 64;

        std::vector<std::string> mainMenuTexts;
        std::vector<std::string> introTexts;
        std::vector<std::string> outroTexts;
        std::vector<std::string> inGameTexts;

		static YasEngine* GetInstance()
		{
			if (instance != nullptr)
			{
				return instance;
			} 
			instance = new YasEngine();
			return instance;
		}
		
		void initialize();
		void YasEngineStart();
		void clean();

	private:

		TimePicker timePicker;

		Vector2D<float> A = Vector2D<float>(-300, 200);
		Vector2D<float> B = Vector2D<float>(100, -350);

		static YasEngine* instance;
		
		int endianness;

		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* screenTexture;
		
		PixelsTable* pixelsTable;
		Vector2D<int>* windowDimensions;
		SDL_Event event;
		bool quit = false;

		double time;
		double newTime;
		double deltaTime;
		double fps;
		double fpsTime;
		unsigned int frames;

		float mouseX;
		float mouseY;

		int WINDOW_WIDTH = 1600;
		int WINDOW_HEIGHT = 800;

		std::vector<GameObject*> objectsToDraw;
		bool first16Spawned = false;
		int howMany = 0;
		Player* player;
		SurfaceWithMathBasedEffects* surfaceWithMathBasedEffects;
		std::vector<NodeNumbersOnTwoProceedingLevels*> spawnersPositions;

		const int MAX_COLLECTIBLES_TO_SPAWN = 64;

		std::map<std::string, std::map<int, float>*> numbersMap;
		std::map < std::string, std::map<int, std::map<float, float>*>* > pairNumbersMap;

		SDL_AudioSpec audioSpecs;

		Mix_Music* music;
		Mix_Chunk* shootSound;
		Mix_Chunk* hitSound;
		Mix_Chunk* otherSound;

		MathPicture* sinePicture;
		MathPicture* cosinePicture;
		MathPicture* fibonacciePicture;
		MathPicture* primeNumbersPicture;

		int level = 1;
		int previousLevel = 0;
		bool levelChanged = false;
		const int MAX_LEVEL = 4;
		int sinePointsHarvested = 0;
		int cosinePointsHarvested = 0;
		int primesPointsHarvested = 0;
		int fibbsPointsHarvested = 0;

		int maxNtoCalculatePrimes = 1000;
		int maxNtoCalculateFibonacci = 40;
		int maxNtoCalculateSine = 100;
		int maxNtoCalculateCosine = 100;

        std::map<std::string, int> numberOfGivenColors;
		Node* spawners;

		Vector2D<float> testPoint0;
		Vector2D<float> testPoint1;

        ScreenWriter writer;
        int step = 0;

		MapFrame mapFrame;

		YasEngine() {};
		bool shouldApplicationStopRunning = false;
		YasInOut::Input* input = new YasInOut::Input();
		YasInOut::MousePositionChangeInformation* mousePositionChangeInformation = new YasInOut::MousePositionChangeInformation();

        int redShotDowns = 0;
        int greenShotdowns = 0;
        int blueShotdowns = 0;
		bool engineInstantiated = false;
		void readSettingsFromFile();
		void prepareRendering();
		void prepareBasicSettings();
		void checkEndianness();
		void handlePhysics();
		void handleDisassemblingGraphs(GameObject* gameObj);
		void handleDestroingCollectibles(GameObject* gameObj);
		void handlingAssemblingGraphs(GameObject* gameObj);
		void handleCollectiblesWithWallsCollisions(GameObject* object);
		bool isObjectProtagonist(GameObject* object);
		GameObject* getProtagonist(GameObject* object0, GameObject* object1);
		GameObject* getNotProtagonist(GameObject* object0, GameObject* object1);
		void handleProtagonistWithWallsCollisions(GameObject* object);
		void moveObjectToMapBoundries(GameObject* gameObject, Wall wall, int shift = 0);
		void bounceCollectibles(GameObject* gameObject, Wall wall);
		void moveObjects();
		void prepareGameWorld();
		void setFrameAroundGameplaySpace();
        void prepareDataForDrawingGraphs();
		void prepareSineDrawing();
		void prepareCosineDrawing();
		void prepareFibonacciDrawing();
		void preparePrimesDrawing();
		void preparePlayer();
        void prepareInterface();
		void handleInput(SDL_Event& event);
		void handleKeyboardInput(SDL_Event& event);
		void handleMouseInput(SDL_Event& event);
		void handleMouseMovement();
		void deleteNotAliveObjects();
		void handleSpawningCollectibles();
		bool isObjectInSameQuarterAsProtagonist(int randomSpawner);
		void handleProjectiles();
		void handlePlayer();
		void update(double& deltaTime);
		void resetAll();
		void drawHudElements(double& deltaTime);
		void drawFrame(double& deltaTime);
		void render(double& deltaTime);
		void renderGameObjects(double& deltaTime);
		void renderOnViewports(double& deltaTime);
		void renderLevelChange();
		void renderWonScreen();
		Button::ButtonId checkWhichButtonClicked();
        void handleClickedButtons();
        void handleGameStateWhenESCbuttonPushed();
        void handleGameStateWhenSPACEbuttonPushed();
		void prepareSoundAndMusic();
        void drawButtons();
};

#endif
