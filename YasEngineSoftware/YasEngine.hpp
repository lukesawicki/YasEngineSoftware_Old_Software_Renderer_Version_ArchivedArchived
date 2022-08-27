#ifndef YASENGINE_HPP
#define YASENGINE_HPP
#include<stdio.h>
#include<iostream>
#include<vector>
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

//#define DEBUG_DRAWINGS


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

		Vector2D<float> A = Vector2D<float>(-300, 200);
		Vector2D<float> B = Vector2D<float>(100, -350);

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

		int WINDOW_WIDTH = 1280;
		int WINDOW_HEIGHT = 800;

		std::vector<GameObject*> objectsToDraw;
		Player* player;
		MathematicsFunSurface* mathPlay;
		//std::vector<PointsGenerator*> pointsGenerators;
		PointsSet sinusPoints;
		PointsSet cosinusPoints;

		YasEngine() {};
		bool shouldApplicationStopRunning = false;
		YasInOut::Input* input = new YasInOut::Input();
		YasInOut::MousePositionChangeInformation* mousePositionChangeInformation = new YasInOut::MousePositionChangeInformation();

		bool engineInstantiated = false;
		void drawMathArt();
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
