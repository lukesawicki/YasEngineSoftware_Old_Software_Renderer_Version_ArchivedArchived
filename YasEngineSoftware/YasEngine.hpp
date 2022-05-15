#ifndef YASENGINE_HPP
#define YASENGINE_HPP
#include<SDL_endian.h>
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<cmath>
#include"VariousTools.hpp"
#include"YasVector2D.hpp"
#include"YasGraphicsLibrary.hpp"
#include"TimePicker.hpp"
#include"PixelsTable.hpp"
#include"Circle.hpp"
#include"YasPolygon.hpp"
#include"Player.hpp"
#include"InputOutputHandler.hpp"

#define DEBUG_DRAWINGS

class YasEngine
{	
	public:
		static YasEngine* GetInstance()
		{
			if (instance != nullptr)
			{
				return instance;
			} 

			return new YasEngine();
		}
		
		void initialize();
		void YasEnginStart();

	private:
		static YasEngine* instance;
		
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* screenTexture;
		
		PixelsTable* pixelsTable;
		YasVector2D<int>* windowDimensions;
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

		int WINDOW_WIDTH = 1024;
		int WINDOW_HEIGHT = 768;

		YasVector2D<int> zeroVector;
		YasVector2D<int> direction;

		YasVector2D<int> testA;
		YasVector2D<int> testB;

		std::vector<YasPolygon*> objectsToDraw;

		Player* player;

		YasEngine() {};
		~YasEngine() {};
		bool shouldApplicationStopRunning = false;
		YasInOut::Input* input = new YasInOut::Input();
		YasInOut::MousePositionChangeInformation* mousePositionChangeInformation = new YasInOut::MousePositionChangeInformation();

		bool engineInstantiated = false;
		void prepareRendering();
		void prepareBasicSettings();
		void preparePlayer();
		void handleInput(SDL_Event& event);
		void update(double deltaTime);
		void render(double& deltaTime);
};

#endif
