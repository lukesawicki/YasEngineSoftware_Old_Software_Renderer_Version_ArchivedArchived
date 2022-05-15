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
#include"Vector2D.hpp"
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
			instance = new YasEngine();
			return instance;
		}
		
		void initialize();
		void YasEnginStart();

	private:
		static YasEngine* instance;
		
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

		int WINDOW_WIDTH = 1024;
		int WINDOW_HEIGHT = 768;

		std::vector<GameObject*> objectsToDraw;
		Player* player;

		YasEngine() {};
		bool shouldApplicationStopRunning = false;
		YasInOut::Input* input = new YasInOut::Input();
		YasInOut::MousePositionChangeInformation* mousePositionChangeInformation = new YasInOut::MousePositionChangeInformation();

		bool engineInstantiated = false;
		void prepareRendering();
		void prepareBasicSettings();
		void prepareGameWorld();
		void preparePlayer();
		void handleInput(SDL_Event& event);
		void update(double& deltaTime);
		void drawHudElements(double& deltaTime);
		void render(double& deltaTime);
};

#endif
