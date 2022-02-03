#include"Player.hpp"

YasGL::Player::Player(int x, int y)
{

	bool directionSwitched = false;
	int  speedFactor = 255;
	int  speed = 2 * speedFactor;

	position.x = x;
	position.y = y;
	numberOfVertices = 7;
	vertices = new Vector2D<int>[numberOfVertices];
	generateRegularPolygonVertices(position, 16, 7);
}

YasGL::Player::~Player()
{
	delete[] vertices;
}

void YasGL::Player::move(double deltaTime)
{
	position.x = static_cast<int>(position.x + deltaTime * speed) * xDirection;
	position.y = static_cast<int>(position.y + deltaTime * speed) * yDirection;
	
	//int xDirection, int yDirection
	
	/*if (position.x < circumscribedCircleRadius && !directionSwitched)
	{
		speed = speed * -1;
		position.x = circumscribedCircleRadius;
	}

	if (position.x > 512 - circumscribedCircleRadius)
	{
		speed = speed * -1;
		position.x = 512 - circumscribedCircleRadius;
	}*/
}

void YasGL::Player::generate()
{
	vertices[0].x = position.x - 8;
	vertices[0].y = position.y - 16;

	vertices[1].x = position.x - 5;
	vertices[1].y = position.y + 0;

	vertices[2].x = position.x - 5;
	vertices[2].y = position.y + 8;

	vertices[3].x = position.x + 0;
	vertices[3].y = position.y + 16;

	vertices[4].x = position.x + 5;
	vertices[4].y = position.y + 8;

	vertices[5].x = position.x + 5;
	vertices[5].y = position.y + 0;

	vertices[6].x = position.x + 8;
	vertices[6].y = position.y - 16;
}

void YasGL::Player::generateRegularPolygonVertices(const Vector2D<int>& position, int circumscribedCircleRadius, int numberOfVertices)
{

}

void YasGL::Player::regeneratePolygon()
{
	generate();
}

void YasGL::Player::update(int xDirection, int yDirection)
{
}
