#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "YasPolygon.hpp"
#include "InputOutputHandler.hpp"
#include "Projectile.hpp"

class Player : public YasPolygon
{
	public:
		
		bool isShooting;
		YasInOut::Input* input;

		Player(float x, float y);
		~Player();
		void move(double deltaTime) override;
		void rotate(double deltaTime);
		void rotateToMousePosition(double oldX, double oldY, double x, double y, YasVector2D<int>* windowDimensions);
		void rotateDirection(float angle);
		void generate() override;
		void generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;
		void setInput(YasInOut::Input* input);
		Projectile* shoot();
};

#endif
