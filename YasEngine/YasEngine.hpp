#ifndef YASENGINE_HPP
#define YASENGINE_HPP
#include <document.h>
#include<stdio.h>
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
#include "PointsSet.hpp"
#include "Spawner.hpp"
#include "Node.hpp"
#include"ScreenWriter.hpp"
#include"Button.hpp"
#include "MapFrame.hpp"
#include "MathPicture.hpp"
#include "Randomizer.hpp"

class YasEngine
{	
	public:
		// Randomizer randomizer;
		bool tests = false;
		std::string engineVersion = "1.0.0.0";

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
            OUTRO
        };

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
		void YasEnginStart();
		void clean();


	private:

		TimePicker timePicker; // 2023-12-15

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
		// std::vector<NodeNumbersOnTwoProceedingLevels*> fourRandomPositions;

		const int MAX_COLLECTIBLES_TO_SPAWN = 64;

		std::map<std::string, std::map<int, float>*> numbersMap;
		std::map < std::string, std::map<int, std::map<float, float>*>* > pairNumbersMap;

		// std::map<int, float>* numbers;

		Mix_Music* music;
		Mix_Chunk* shootSound;
		Mix_Chunk* hitSound;
		Mix_Chunk* otherSound;

		MathPicture* sinusPicture;
		MathPicture* cosinusPicture;
		MathPicture* fibonacciePicture;
		MathPicture* primeNumbersPicture;

		int sinPointsHarvested = 0;
		int cosPointsHarvested = 0;
		int primesPointsHarvested = 0;
		int fibbsPointsHarvested = 0;

		int maxNtoCalculatePrimes = 1000;
		int maxNtoCalculateFibonacci = 40;
		int maxNtoCalculateSinus = 100;
		int maxNtoCalculateCosinus = 100;

        std::map<std::string, int> numberOfGivenColors;
        // std::map<int, float> sinusNumbers;
        // std::map<int, float> cosinusNumbers;
        // std::map<int, float> fibonacciNumbers;
        // std::map<int, float> primeNumbers;

		//std::vector<Spawner*> spawners;
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
		void handleCollectiblesWithWallsCollisions(GameObject* object);
		void handleProtagonistWithWallsCollisions(GameObject* object);
		void moveObjectToMapBoundries(GameObject* gameObject, Wall wall);
		void bounceCollectibles(GameObject* gameObject, Wall wall);
		void moveObjects();
		void prepareGameWorld();
		void setFrameAroundGameplaySpace();
        void prepareDataForDrawingGraphs();
		void sinusDrawing();
		void prepareFibonacciDrawing();
		void preparePrimesDrawing();
		void preparePlayer();
        void prepareInterface();
		void handleInput(SDL_Event& event);
		void handleKeyboardInput(SDL_Event& event);
		void handleMouseInput(SDL_Event& event);
		void handleMouseMovement();
		void handleSpawningCollectibles();
		bool isObjectInSameQuarterAsProtagonist(int randomSpawner);
		void handleProjectiles();
		void handlePlayer();
		void update(double& deltaTime);
		void drawHudElements(double& deltaTime);
		void render(double& deltaTime);
		void renderGameObjects(double& deltaTime);
		void renderOnViewports(double& deltaTime);
        Button::ButtonId checkWhichButtonClicked();
        void handleClickedButtons();
        void handleGameStateWhenESCbuttonPushed();
        void handleGameStateWhenSPACEbuttonPushed();
		void prepareSoundAndMusic();
        void drawButtons();
};

#endif
