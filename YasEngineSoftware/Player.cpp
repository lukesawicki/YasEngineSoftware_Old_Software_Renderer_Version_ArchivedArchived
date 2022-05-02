#include"Player.hpp"

Player::Player(float x, float y)
{
	speed = 200;
	rotationSpeed = 5;

	position.x = x;
	position.y = y;

	direction.x = 1;
	direction.y = 0;

	numberOfVertices = 7;
	worldVertices = new YasVector2D<float>[numberOfVertices];
	localVertices = new YasVector2D<float>[numberOfVertices];

	localVertices[0].x = -160;
	localVertices[0].y = -80;

	localVertices[1].x = 0;
	localVertices[1].y = -50;

	localVertices[2].x = 80;
	localVertices[2].y = -50;

	localVertices[3].x = 160;
	localVertices[3].y = 0;

	localVertices[4].x = 80;
	localVertices[4].y = 50;

	localVertices[5].x = 0;
	localVertices[5].y = 50;

	localVertices[6].x = -160;
	localVertices[6].y = 80;

	generate();

}

Player::~Player()
{
	delete[] worldVertices;
}

void Player::move(float deltaTime)
{
	// LEFT
	if (input->left && !input->right)
	{
		position.x = position.x + deltaTime * (-speed);
	}

	// RIGHT
	if (input->right && !input->left)
	{
		position.x = position.x + deltaTime * speed;
	}

	// UP
	if (input->up && !input->down)
	{
		position.y = position.y + deltaTime * speed;
	}

	// DOWN
	if (input->down && !input->up)
	{
		position.y = position.y + deltaTime * (-speed);
	}

	// SPACE
	if (input->shoot || mouse->leftMouseButton)
	{
		isShooting = true;
	}

}

void Player::rotate(float deltaTime)
{
	if (input->rotateCounterClockwise)
	{
		directionMouseAngle = directionMouseAngle * 3.141592F / 180.0F;
		directionMouseAngle = deltaTime * rotationSpeed;
		playerCurrentDirectionAngle = playerCurrentDirectionAngle + directionMouseAngle;
		if (playerCurrentDirectionAngle >= 6.28319F)
		{
			playerCurrentDirectionAngle = playerCurrentDirectionAngle - 6.28319F;
		}
		rotateAllVerticesOverAnAngle(directionMouseAngle);
		generate();
	}
}

void Player::rotateToMousePosition(float x, float y, YasVector2D<int>* windowDimensions)
{
	if (x <= windowDimensions->x && y <= windowDimensions->y)
	{
		float currentX = x;
		float currentY = y;

		windowPositionToCartesianPosition(currentX, currentY, windowDimensions);

		YasVector2D<float> mousePositionVector(static_cast<float>(currentX), static_cast<float>(currentY));
		YasVector2D<float>::normalizedVector(mousePositionVector);

		float angleBetweenCurrentAndMouse = YasVector2D<float>::angleBetweenVectors(direction, mousePositionVector);
		if (abs(angleBetweenCurrentAndMouse) > 0.0174533F)
		{
			direction.x = mousePositionVector.x;
			direction.y = mousePositionVector.y;

			rotateAllVerticesOverAnAngle(angleBetweenCurrentAndMouse);

			generate();
		}
	}
}

//void Player::rotateToMousePosition1(float x, float y, YasVector2D<int>* windowDimensions)
//{
//	if (x <= windowDimensions->x && y <= windowDimensions->y)
//	{
//		double currentX = x;
//		double currentY = y;
//
//		windowPositionToCartesianPosition(currentX, currentY, windowDimensions);
//
//		YasVector2D<float> mousePositionVector(static_cast<float>(currentX), static_cast<float>(currentY));
//		YasVector2D<float>::normalizedVector(mousePositionVector);
//
//		float angleBetweenCurrentAndMouse = YasVector2D<float>::angleBetweenVectors(direction, mousePositionVector);
//		
//		if (angleBetweenCurrentAndMouse > 0.0174533F)
//		{
//			direction.x = mousePositionVector.x;
//			direction.y = mousePositionVector.y;
//
//			rotateAllVerticesOverAnAngle(angleBetweenCurrentAndMouse);
//
//			generate();
//		}
//	}
//}

void Player::generate()
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

void Player::generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices)
{

}

void Player::regeneratePolygon()
{
	generate();
}

void Player::rotateAllVerticesOverAnAngle(float angle)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		YasVector2D<float>::rotateVectorOverTheAngle(localVertices+i, angle);
	}
}

void Player::setInput(YasInOut::Input* input)
{
	this->input = input;
}

void Player::setInput(YasInOut::MousePositionChangeInformation* mouse)
{
	this->mouse = mouse;
}

Projectile* Player::shoot()
{
	if (isShooting)
	{
		isShooting = false;
		return new Projectile(32, position.x, position.y, direction);
	}
	else
	{
		return nullptr;
	}
}
