#ifndef PLAYER_HPP
#define PLAYER_HPP
#include"InputOutputHandler.hpp"
#include"GameObject.hpp"
#include"Projectile.hpp"

class Player : public GameObject
{
	public:
		
		bool isShooting;
		int projectilePositionShift = 22;
		
		YasInOut::Input* input;
		YasInOut::MousePositionChangeInformation* mouse;

		float playerDirectionAngle = 90.0F * (3.141592F / 180.0F);
		float playerCurrentDirectionAngle = 0.0F;
		const Vector2D<float> xDirectionVector = Vector2D<float>(1.0F, 0.0F);
		Vector2D<float> lookAt = Vector2D<float>(1.0F, 0.0F);
		Vector2D<float> currentMouseAngleVector;

		Player(float x, float y);
		~Player();
		void move(float deltaTime) override;
		void rotateAllVerticesOverAnAngle(float angle);
		void rotate(float deltaTime);
		
		void rotateToMousePosition(float x, float y, Vector2D<int>* windowDimensions);
		void rotateToMousePositionInLocalCoordinateSystem(float x, float y, Vector2D<int>* windowDimensions);
		void setDirection(float x, float y);
		void generate() override;
		void generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;
		void setInput(YasInOut::Input* input);
		void setInput(YasInOut::MousePositionChangeInformation* mouse);
		Projectile* shoot();
	private:

};

#endif
