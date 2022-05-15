#ifndef PLAYER_HPP
#define PLAYER_HPP
#include<cmath>
#include"InputOutputHandler.hpp"
#include"YasPolygon.hpp"
#include"Projectile.hpp"

class Player : public YasPolygon
{
	public:
		
		bool isShooting;
		int projectilePositionShift = 22;
		
		YasInOut::Input* input;
		YasInOut::MousePositionChangeInformation* mouse;

		float playerDirectionAngle = 90.0F * (3.141592F / 180.0F);
		float playerCurrentDirectionAngle = 0.0F;
		const YasVector2D<float> xDirectionVector = YasVector2D<float>(1.0F, 0.0F);
		YasVector2D<float> lookAt = YasVector2D<float>(1.0F, 0.0F);
		YasVector2D<float> currentMouseAngleVector;

		Player(float x, float y);
		~Player();
		void move(float deltaTime) override;
		void rotateAllVerticesOverAnAngle(float angle);
		void rotate(float deltaTime);
		
		void rotateToMousePosition(float x, float y, YasVector2D<int>* windowDimensions);
		void rotateToMousePositionInLocalCoordinateSystem(float x, float y, YasVector2D<int>* windowDimensions);
		void setDirection(float x, float y);
		void generate() override;
		void generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;
		void setInput(YasInOut::Input* input);
		void setInput(YasInOut::MousePositionChangeInformation* mouse);
		Projectile* shoot();
};

#endif
