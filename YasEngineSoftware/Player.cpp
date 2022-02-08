#include"Player.hpp"

YasGL::Player::Player(int x, int y)
{

	bool directionSwitched = false;
	int  speedFactor = 255;
	int  speed = 2 * speedFactor;

	position.x = x;
	position.y = y;
	numberOfVertices = 7;
	worldVertices = new Vector2D<int>[numberOfVertices];
	localVertices = new Vector2D<int>[numberOfVertices];

	localVertices[0].x = -80;
	localVertices[0].y = -160;

	localVertices[1].x = -50;
	localVertices[1].y = +0;

	localVertices[2].x = -50;
	localVertices[2].y = +80;

	localVertices[3].x = +0;
	localVertices[3].y = +160;

	localVertices[4].x = +50;
	localVertices[4].y = +80;

	localVertices[5].x = +50;
	localVertices[5].y = +0;

	localVertices[6].x = +80;
	localVertices[6].y = -160;

	generate();
	//generateRegularPolygonVertices(position, 16, 7);
}

YasGL::Player::~Player()
{
	delete[] worldVertices;
}

void YasGL::Player::move(double deltaTime)
{
	// LEFT
	if (input->left && !input->right)
	{
		position.x = static_cast<int>(position.x + deltaTime * (-speed));
	}

	// RIGHT
	if (input->right && !input->left)
	{
		position.x = static_cast<int>(position.x + deltaTime * speed);
	}

	// UP
	if (input->up && !input->down)
	{
		position.y = static_cast<int>(position.y + deltaTime * speed);
	}

	// DOWN
	if (input->down && !input->up)
	{
		position.y = static_cast<int>(position.y + deltaTime * (-speed));
	}
}

void YasGL::Player::rotate(double deltaTime, float angle)
{
	if (input->rotateClocwise)
	{
		angle = angle * 3.141592F / 180;
		for (int i = 0; i < numberOfVertices; i++)
		{
			worldVertices[i].x = worldVertices[i].x * cos(angle) - worldVertices[i].y * sin(angle);
			worldVertices[i].y = worldVertices[i].x * sin(angle) - worldVertices[i].y * cos(angle);
		}
	}
}

void YasGL::Player::generate()
{
	worldVertices[0].x = position.x + localVertices[0].x;
	worldVertices[0].y = position.y + localVertices[0].y;

	worldVertices[1].x = position.x + localVertices[1].x;
	worldVertices[1].y = position.y + localVertices[1].y;

	worldVertices[2].x = position.x + localVertices[2].x;
	worldVertices[2].y = position.y + localVertices[2].y;

	worldVertices[3].x = position.x + localVertices[3].x;
	worldVertices[3].y = position.y + localVertices[3].y;

	worldVertices[4].x = position.x + localVertices[4].x;
	worldVertices[4].y = position.y + localVertices[4].y;

	worldVertices[5].x = position.x + localVertices[5].x;
	worldVertices[5].y = position.y + localVertices[5].y;

	worldVertices[6].x = position.x + localVertices[6].x;
	worldVertices[6].y = position.y + localVertices[6].y;
}

void YasGL::Player::generateRegularPolygonVertices(const Vector2D<int>& position, int circumscribedCircleRadius, int numberOfVertices)
{

}

void YasGL::Player::regeneratePolygon()
{
	generate();
}


void YasGL::Player::setInput(YasInOut::Input* input)
{
	this->input = input;
}
