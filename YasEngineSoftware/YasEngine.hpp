#ifndef YASENGINE_HPP
#define YASENGINE_HPP
#include<stdio.h>
#include<iostream>
#include<vector>
#include<SDL_mixer.h>
#include<SDL_image.h>
#include"Vector2D.hpp"
#include"YasGraphicsLibrary.hpp"
#include"TimePicker.hpp"
#include"PixelsTable.hpp"
#include"GameObject.hpp"
#include"Player.hpp"
#include"InputOutputHandler.hpp"
#include"MathematicsFunSurface.hpp"
#include "PointsGenerator.hpp"
#include "PointsSet.hpp"
#include "Spawner.hpp"
#include "SDL_mixer.h"

//#define DEBUG_DRAWINGS

class YasEngine
{	
	public:

		GameObject* go;

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

		// old SDL_Image
		const bool endianness = std::endian::native == std::endian::big;

		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* screenTexture;
		// old SDL_Image
		SDL_Surface* windowSurface;
		SDL_Surface* customImageSurface;
		SDL_Surface* optimizedSurface;
		SDL_Rect* pictureRect;
		SDL_Rect* map;

		SDL_PixelFormat* windowsSurfaceFormat;
	
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
		int WINDOW_HEIGHT = 720;

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


		std::vector<std::string> filenames;
		std::vector<SDL_Surface*> tmpMonsterSurface;
		std::vector<SDL_Surface*> optimizedMonstersSurfaces;

		SDL_Rect* monsterRectangle;

		void loadMonsters()
		{
			std::string basePath = SDL_GetBasePath();
			for(int i=0; i < 3; i++)
			{
				std::string monsterFile;
				filenames.push_back(monsterFile.append(basePath).append("monster_v").append(std::to_string(i)).append(".png"));
			}

			for(int i=0; i<3; i++)
			{
				tmpMonsterSurface.push_back(IMG_Load(filenames.at(i).c_str()));
			}

			for(int i=0; i<3; i++)
			{
				optimizedMonstersSurfaces.push_back(SDL_ConvertSurface(tmpMonsterSurface.at(i), windowsSurfaceFormat, 0));
			}

			for(int i=0; i<3; i++)
			{
				SDL_FreeSurface(tmpMonsterSurface.at(i));
			}

			monsterRectangle = new SDL_Rect();
			monsterRectangle->x = 0;
			monsterRectangle->y = 0;
			monsterRectangle->w = 76;
			monsterRectangle->h = 81;


			SDL_Color rgb;
			for (int i = 0; i < 3; i++)
			{
				Uint32 data = getpixel(optimizedMonstersSurfaces.at(i), 1, 1);
				SDL_GetRGBA(data, optimizedMonstersSurfaces.at(i)->format, &rgb.r, &rgb.g, &rgb.b, &rgb.a);
			}
		}
		void loadBuildings();
		void loadProjectile();
		void loadTruck();

		void handleInput(SDL_Event& event);
		void update(double& deltaTime);
		void drawHudElements(double& deltaTime);
		void render(double& deltaTime);

		// old SDL_Image
		Uint32 getpixel(SDL_Surface* surface, int x, int y);

		void prepareSoundAndMusic();
};

#endif
