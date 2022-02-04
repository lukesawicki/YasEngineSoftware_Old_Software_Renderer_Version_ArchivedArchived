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
			

		Player(int x, int y);
		~Player();
		void move(double deltaTime) override;
		void generate() override;
		void generateRegularPolygonVertices(const Vector2D<int>& position, int circumscribedCircleRadius, int numberOfVertices) override;
		void regeneratePolygon() override;
		void setInput(YasInOut::Input* input);

		int xDirection = 1;
		int yDirection = 1;
	};

}

#endif
