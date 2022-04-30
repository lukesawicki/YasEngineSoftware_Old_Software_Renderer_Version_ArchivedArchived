#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "YasPolygon.hpp"
#include "InputOutputHandler.hpp"
#include "Projectile.hpp"
#include<cmath>

class Player : public YasPolygon
{
	public:
		
		bool isShooting;
		YasInOut::Input* input;
		YasInOut::MousePositionChangeInformation* mouse;

		float playerDirectionAngle = 90.0F * (3.141592F / 180.0F);
		float playerCurrentDirectionAngle = playerDirectionAngle;
		YasVector2D<float> currentMouseAngleVector;

		Player(float x, float y);
		~Player();
		void move(float deltaTime) override;
		void rotateAllVerticesOverAnAngle(float angle);
		void rotate(float deltaTime);
		void rotateToMousePosition(double oldX, double oldY, double x, double y, YasVector2D<int>* windowDimensions);
		void generate() override;
		void generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;
		void setInput(YasInOut::Input* input);
		void setInput(YasInOut::MousePositionChangeInformation* mouse);
		Projectile* shoot();
};

#endif
