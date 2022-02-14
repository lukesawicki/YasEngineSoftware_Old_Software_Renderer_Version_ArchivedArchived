#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "YasPolygon.hpp"
#include "InputOutputHandler.hpp"
#include "Projectile.hpp"

class Player : public YasPolygon
{
	public:
		YasVector2D<float> direction;
		bool isShooting;
		YasInOut::Input* input;

		Player(float x, float y);
		~Player();
		void move(float deltaTime) override;
		void rotate(double deltaTime);
		void rotateDirection(float angle);
		void generate() override;
		void generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;
		void setInput(YasInOut::Input* input);
		Projectile* shoot();
};

#endif
