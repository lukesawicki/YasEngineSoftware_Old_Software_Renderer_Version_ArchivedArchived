#ifndef YASENGINE_HPP
#define YASENGINE_HPP
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
#include"MathematicsFunSurface.hpp"
#include "PointsSet.hpp"
#include "Spawner.hpp"
#include"ScreenWriter.hpp"
#include"Button.hpp"

class YasEngine
{	
	public:
        bool collided = false;
		GameObject* go;
        enum GameState
        {
            INTRO,
            MAIN_MENU_RESTART,
            GAMEPLAY,
            OUTRO
        };

        GameState gameState = GameState::INTRO;

        std::vector<GameObject*> buttons;

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
		Player* player;
		MathematicsFunSurface* mathPlay;
		
		Mix_Music* music;
		Mix_Chunk* shootSound;
		Mix_Chunk* hitSound;

		PointsSet* sinusPoints;
		PointsSet* cosinusPoints;
		PointsSet* fibonacciePoints;
		PointsSet* primeNumbersPoints;

        std::map<std::string, int> numberOfGivenColors;
        std::map<float, int> sinusNumbers;
        std::map<float, int> cosinusNumbers;
        std::map<float, int> fibonacciNumbers;
        std::map<float, int> primeNumbers;

		Spawner spawner;

        ScreenWriter writer;
        int step = 0;

		YasEngine() {};
		bool shouldApplicationStopRunning = false;
		YasInOut::Input* input = new YasInOut::Input();
		YasInOut::MousePositionChangeInformation* mousePositionChangeInformation = new YasInOut::MousePositionChangeInformation();

        int redShotDowns = 0;
        int greenShotdowns = 0;
        int blueShotdowns = 0;

		bool engineInstantiated = false;
		void prepareRendering();
		void prepareBasicSettings();
		void checkEndianness();
		void handlePhysics();
		void moveObjects();
		void prepareGameWorld();
		void preparePlayer();
        void prepareInterface();
		void handleInput(SDL_Event& event);
		void handleKeyboardInput(SDL_Event& event);
		void handleMouseInput(SDL_Event& event);
		void handleMouseMovement();
		void handleSpawningCollectibles();
		void handleProjectiles();
		void handlePlayer();
		void update(double& deltaTime);
		void drawHudElements(double& deltaTime);
		void render(double& deltaTime);
		void renderGameObjects(double& deltaTime);
		void renderViewports(double& deltaTime);
        Button::ButtonId checkWhichButtonClicked();
        void handleClickedButtons();
        void handleGameStateWhenESCbuttonPushed();
        void handleGameStateWhenSPACEbuttonPushed();
		void prepareSoundAndMusic();
        void drawButtons();
};

#endif
