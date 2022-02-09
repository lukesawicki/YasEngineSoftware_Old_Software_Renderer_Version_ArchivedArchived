#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Polygon.hpp"
#include "InputOutputHandler.hpp"
namespace YasGL
{
	class Player : public Polygon
	{
	public:

		YasInOut::Input* input;
			

		Player(float x, float y);
		~Player();
		void move(float deltaTime) override;
		void rotate(double deltaTime);
		void generate() override;
		void generateRegularPolygonVertices(const Vector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;
		void setInput(YasInOut::Input* input);

	};

}

#endif
