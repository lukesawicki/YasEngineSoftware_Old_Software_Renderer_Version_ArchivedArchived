#ifndef YASENGINE_HPP
#define YASENGINE_HPP
#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<SDL2/SDL_mixer.h>
#include<bit>
#include"Vector2D.hpp"
#include"YasGraphicsLibrary.hpp"
#include"TimePicker.hpp"
#include"PixelsTable.hpp"
#include"GameObject.hpp"
#include"Player.hpp"
#include"InputOutputHandler.hpp"
#include"MathematicsFunSurface.hpp"
#include"PointsGenerator.hpp"
#include"PointsSet.hpp"
#include"Spawner.hpp"
#include"ScreenWriter.hpp"
#include"Button.hpp"
//using namespace std;

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

		int endianness;// = std::endian::native == std::endian::big;

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

		int WINDOW_WIDTH = 1280;
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

		Spawner spawner;

        ScreenWriter writer;
        int step = 0;

		YasEngine() {};
		bool shouldApplicationStopRunning = false;
		YasInOut::Input* input = new YasInOut::Input();
		YasInOut::MousePositionChangeInformation* mousePositionChangeInformation = new YasInOut::MousePositionChangeInformation();

		bool engineInstantiated = false;
		void drawMathArt();
		void prepareRendering();
		void prepareBasicSettings();
		void handlePhysics();
		void prepareGameWorld();
		void preparePlayer();
        void prepareInterface();
		void handleInput(SDL_Event& event);
		void update(double& deltaTime);
		void drawHudElements(double& deltaTime);
		void render(double& deltaTime);
        Button::ButtonId checkWhichButtonClicked();
        void handleClickedButtons();
        void handleGameStateWhenESCbuttonPushed();
        void handleGameStateWhenSPACEbuttonPushed();
		void prepareSoundAndMusic();
        void drawButtons();
};

#endif
