#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Polygon.hpp"
#include "InputOutputHandler.hpp"
#include "Projectile.hpp"
namespace YasGL
{
	class Player : public Polygon
	{
		public:
			Vector2D<float> direction;
			bool isShooting;
			YasInOut::Input* input;

			Player(float x, float y);
			~Player();
			void move(float deltaTime) override;
			void rotate(double deltaTime);
			void rotateDirection(float angle);
			void generate() override;
			void generateRegularPolygonVertices(const Vector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
			void regeneratePolygon() override;
			void setInput(YasInOut::Input* input);
			YasGL::Projectile* shoot();
	};

}

#endif
