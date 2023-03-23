#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include"YasGraphicsLibrary.hpp"
#include"GameObject.hpp"
#include "Timer.hpp"
#include<SDL_timer.h>


class Projectile : public GameObject
{
	private:
		bool directionSwitched = false;
	public:
		int liveTime = 2000;
		Timer timer;
		SDL_TimerID timerId;
		Vector2D<float> velocity;
		Projectile(float radius, float x, float y, Vector2D<float> direction);
		~Projectile();
		void move(float deltaTime) override;
		void generate() override;
		void generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;
		// static Uint32 kill(Uint32 interval, void* param);
};

#endif
