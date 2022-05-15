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
		
		void initialization();
		void YasEnginStart();
	private:
		static YasEngine* instance;
		YasEngine() {};
		~YasEngine() {};
		bool shouldApplicationStopRunning = false;
		YasInOut::Input* input = new YasInOut::Input();
		YasInOut::MousePositionChangeInformation* mousePositionChangeInformation = new YasInOut::MousePositionChangeInformation();

		bool engineInstantiated = false;
		
};

#endif
