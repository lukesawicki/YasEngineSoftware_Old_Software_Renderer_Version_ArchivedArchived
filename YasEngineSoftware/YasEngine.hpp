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

		enum MovingMonsters
		{
			HORIZONTALLY,
			VERTICALLY
		};

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


		int levelNumber = 0;

		std::vector<std::string> monstersFilenames;
		std::vector<SDL_Surface*> tmpMonsterSurface;
		std::vector<SDL_Surface*> optimizedMonstersSurfaces;
		std::vector<SDL_Rect*> monstersRectangles;
		std::vector<SDL_Rect*> monstersEndMovingPositions;

		void loadMonsters()
		{
			std::string basePath = SDL_GetBasePath();
			for(int i=0; i < 3; i++)
			{
				std::string monsterFile;
				monstersFilenames.push_back(monsterFile.append(basePath).append("monster_v").append(std::to_string(i)).append(".png"));
			}

			for(int i=0; i<3; i++)
			{
				optimizedMonstersSurfaces.push_back(IMG_Load(monstersFilenames.at(i).c_str()));
			}

			for(int i=0; i<3; i++)
			{
				//optimizedMonstersSurfaces.push_back(SDL_ConvertSurface(tmpMonsterSurface.at(i), windowsSurfaceFormat, 0));
			}

			for(int i=0; i<3; i++)
			{
				//SDL_FreeSurface(tmpMonsterSurface.at(i));
			}

			for (int i = 0; i < 3; i++)
			{

				monstersRectangles.push_back(new SDL_Rect());
				monstersRectangles.at(i)->x = 0;
				monstersRectangles.at(i)->y = 0;
				monstersRectangles.at(i)->w = 76;
				monstersRectangles.at(i)->h = 81;
			}

			for (int i = 0; i < 3; i++)
			{

				monstersEndMovingPositions.push_back(new SDL_Rect());
				monstersEndMovingPositions.at(i)->x = 0;
				monstersEndMovingPositions.at(i)->y = 0;
				monstersEndMovingPositions.at(i)->w = 76;
				monstersEndMovingPositions.at(i)->h = 81;
			}

			SDL_Color rgb;
			for (int i = 0; i < 3; i++)
			{
				SDL_SetSurfaceBlendMode(optimizedMonstersSurfaces.at(i), SDL_BLENDMODE_BLEND);
			}
		}

		std::vector<std::string> trashFilenames;
		std::vector<SDL_Surface*> tmpTrashSurface;
		std::vector<SDL_Surface*> optimizedTrashsSurfaces;
		std::vector<SDL_Rect*> trashRectangles;


		void loadTrashs()
		{
			std::string basePath = SDL_GetBasePath();
			for (int i = 0; i < 3; i++)
			{
				std::string TrashFile;
				trashFilenames.push_back(TrashFile.append(basePath).append("trash_v").append(std::to_string(i)).append(".png"));
			}

			for (int i = 0; i < 3; i++)
			{
				tmpTrashSurface.push_back(IMG_Load(trashFilenames.at(i).c_str()));
			}

			for (int i = 0; i < 3; i++)
			{
				optimizedTrashsSurfaces.push_back(SDL_ConvertSurface(tmpTrashSurface.at(i), windowsSurfaceFormat, 0));
			}

			for (int i = 0; i < 3; i++)
			{
				SDL_FreeSurface(tmpTrashSurface.at(i));
			}

			for (int i = 0; i < 3; i++)
			{
				trashRectangles.push_back(new SDL_Rect());
				trashRectangles.at(i)->x = 0;
				trashRectangles.at(i)->y = 0;
				trashRectangles.at(i)->w = 74;
				trashRectangles.at(i)->h = 75;
			}

			SDL_Color rgb;
			for (int i = 0; i < 3; i++)
			{
				Uint32 data = getpixel(optimizedTrashsSurfaces.at(i), 1, 1);
				SDL_GetRGBA(data, optimizedTrashsSurfaces.at(i)->format, &rgb.r, &rgb.g, &rgb.b, &rgb.a);
			}
		}

		std::vector<std::string> buildingFilenames;
		std::vector<SDL_Surface*> tmpBuildingurface;
		std::vector<SDL_Surface*> optimizedBuildingSurfaces;
		std::vector<SDL_Rect*> buildingRectangles;
 

		void loadBuildings()
		{
			std::string basePath = SDL_GetBasePath();
			for (int i = 0; i < 3; i++)
			{
				std::string monsterFile;
				buildingFilenames.push_back(monsterFile.append(basePath).append("building_").append(std::to_string(i)).append(".png"));
			}

			for (int i = 0; i < 3; i++)
			{
				tmpBuildingurface.push_back(IMG_Load(buildingFilenames.at(i).c_str()));
			}

			for (int i = 0; i < 3; i++)
			{
				optimizedBuildingSurfaces.push_back(SDL_ConvertSurface(tmpBuildingurface.at(i), windowsSurfaceFormat, 0));
			}

			for (int i = 0; i < 3; i++)
			{
				SDL_FreeSurface(tmpBuildingurface.at(i));
			}

			for (int i = 0; i < 3; i++)
			{
				buildingRectangles.push_back(new SDL_Rect());
				buildingRectangles.at(i)->x = 0;
				buildingRectangles.at(i)->y = 0;
				buildingRectangles.at(i)->w = 76;
				buildingRectangles.at(i)->h = 81;
			}

			SDL_Color rgb;
			for (int i = 0; i < 3; i++)
			{
				Uint32 data = getpixel(optimizedBuildingSurfaces.at(i), 1, 1);
				SDL_GetRGBA(data, optimizedBuildingSurfaces.at(i)->format, &rgb.r, &rgb.g, &rgb.b, &rgb.a);
			}
		}

		void changeLevel()
		{

		}

		void setBuildingsPositions()
		{
			switch (levelNumber)
			{
			case 0:
				buildingRectangles.at(0)->x = 50;
				buildingRectangles.at(0)->y = 110;
				//280
				//110
				break;
			case 1:
				break;
			case 2:
				break;

			}
		}

		void setupMonsters()
		{
			switch (levelNumber)
			{
			case 0:
				//162x
				//159y

				monstersRectangles.at(0)->x = 10;
				monstersRectangles.at(0)->y = 10;
				
				monstersEndMovingPositions.at(0)->x = 255;
				monstersEndMovingPositions.at(0)->y = 10;
				monstersEndMovingPositions.at(0)->w = 10;// start position
				monstersEndMovingPositions.at(0)->h = 10;// start position


				break;
			case 1:
				break;
			case 2:
				break;

			}
		}


		void loadProjectile();
		void loadTruck();

		void handeGamePhysics()
		{
			switch (levelNumber)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;

			}
		}

		void handleGameLogic()
		{
			switch (levelNumber)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;

			}
		}

		int monstersSpeed = 200;
		boolean monsterDirectionSwitched = false;

	// monstersRectangles.at(i)->
	// monstersEndMovingPositions
		void moveMonsters()
		{
			for(int i=0; i<3; i++)
			{
				monstersRectangles.at(i)->x = monstersRectangles.at(i)->x + static_cast<float>(deltaTime) * monstersSpeed;
				if (monstersRectangles.at(i)->x < 37 && !monsterDirectionSwitched)
				{
					monstersSpeed = monstersSpeed * -1;
					monstersRectangles.at(i)->x = 37;
				}

				if (monstersRectangles.at(i)->x > 512 - 37)
				{
					monstersSpeed = monstersSpeed * -1;
					monstersRectangles.at(i)->x = 512 - 37;
				}
			}
		}

		void handleInput(SDL_Event& event);
		void update(double& deltaTime);
		void drawHudElements(double& deltaTime);
		void render(double& deltaTime);

		// old SDL_Image
		Uint32 getpixel(SDL_Surface* surface, int x, int y);

		void prepareSoundAndMusic();
};

#endif
