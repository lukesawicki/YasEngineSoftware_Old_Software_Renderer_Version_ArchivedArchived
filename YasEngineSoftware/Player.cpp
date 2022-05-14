#include"Player.hpp"

Player::Player(float x, float y)
{
	speed = 200;
	rotationSpeed = 5;

	position.x = x;
	position.y = y;

	direction.x = 1;
	direction.y = 0;

	numberOfVertices = 17;
	worldVertices = new YasVector2D<float>[numberOfVertices];
	localVertices = new YasVector2D<float>[numberOfVertices];

	localVertices[0].x = -12;
	localVertices[0].y = -11;

	localVertices[1].x = -2;
	localVertices[1].y = -11;

	localVertices[2].x = 8;
	localVertices[2].y = -9;

	localVertices[3].x =-2 ;
	localVertices[3].y = -7;

	localVertices[4].x = -2;
	localVertices[4].y = -3;

	localVertices[5].x = 12;
	localVertices[5].y = 0;

	localVertices[6].x = -2;
	localVertices[6].y = 3;

	localVertices[7].x = -2;
	localVertices[7].y = 7;

	localVertices[8].x = 8;
	localVertices[8].y = 9;

	localVertices[9].x = -2;
	localVertices[9].y = 11;

	localVertices[10].x = -12;
	localVertices[10].y = 11;

	localVertices[11].x = -8;
	localVertices[11].y = 7;

	localVertices[12].x = -12;
	localVertices[12].y = 3;

	localVertices[13].x = -8;
	localVertices[13].y = 3;

	localVertices[14].x = -8;
	localVertices[14].y = -3;

	localVertices[15].x = -12;
	localVertices[15].y = -3;

	localVertices[16].x = -8;
	localVertices[16].y = -7;


	//rotateAllVerticesOverAnAngle(-90.0F);

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

		// MOUSE POSITION TO PLAYER POSITION
		//currentX = currentX - x;
		//currentY = currentY - y;

		YasVector2D<float> mousePositionVector(static_cast<float>(currentX), static_cast<float>(currentY));
		YasVector2D<float>::normalizedVector(mousePositionVector);

		float angleBetweenCurrentAndMouse = YasVector2D<float>::angleBetweenVectors(direction, mousePositionVector);


		//if (abs(angleBetweenCurrentAndMouse) > 0.0174533F) // jesli obrot jest wiekszy niz 1 stopien.... komentuje bo to bez sensu
		//{
			rotateAllVerticesOverAnAngle(angleBetweenCurrentAndMouse);
			setDirection(mousePositionVector.x, mousePositionVector.y);
			
		//}
	}
}

void Player::rotateToMousePositionInLocalCoordinateSystem(float x, float y, YasVector2D<int>* windowDimensions)
{
	if (x <= windowDimensions->x && y <= windowDimensions->y)
	{
		float currentX = x;
		float currentY = y;

		windowPositionToCartesianPosition(currentX, currentY, windowDimensions);

		YasVector2D<float> currentMousePosition = YasVector2D<float>(currentX, currentY);

		YasVector2D<float> mouseDirectionInLocalCoordynationSystem = YasVector2D<float>::createUnitVectorFromBoundVector(currentMousePosition, position);

		float angleBetweenCurrentAndMouse = YasVector2D<float>::angleBetweenVectors(direction, mouseDirectionInLocalCoordynationSystem);

		rotateAllVerticesOverAnAngle(angleBetweenCurrentAndMouse);
		YasVector2D<float>::rotateVectorOverTheAngle(&direction, angleBetweenCurrentAndMouse);
	}
}


void Player::setDirection(float x, float y)
{
	direction.x = x;
	direction.y = y;
}

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

	worldVertices[7].x = position.x + localVertices[7].x;
	worldVertices[7].y = position.y + localVertices[7].y;

	worldVertices[8].x = position.x + localVertices[8].x;
	worldVertices[8].y = position.y + localVertices[8].y;

	worldVertices[9].x = position.x + localVertices[9].x;
	worldVertices[9].y = position.y + localVertices[9].y;

	worldVertices[10].x = position.x + localVertices[10].x;
	worldVertices[10].y = position.y + localVertices[10].y;

	worldVertices[11].x = position.x + localVertices[11].x;
	worldVertices[11].y = position.y + localVertices[11].y;

	worldVertices[12].x = position.x + localVertices[12].x;
	worldVertices[12].y = position.y + localVertices[12].y;

	worldVertices[13].x = position.x + localVertices[13].x;
	worldVertices[13].y = position.y + localVertices[13].y;

	worldVertices[14].x = position.x + localVertices[14].x;
	worldVertices[14].y = position.y + localVertices[14].y;

	worldVertices[15].x = position.x + localVertices[15].x;
	worldVertices[15].y = position.y + localVertices[15].y;

	worldVertices[16].x = position.x + localVertices[16].x;
	worldVertices[16].y = position.y + localVertices[16].y;

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
		YasVector2D<float>::rotateVectorOverTheAngle(&localVertices[i], angle);
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

void Player::recalculateLookAt()
{

}

Projectile* Player::shoot()
{
	if (isShooting)
	{
		isShooting = false;
		float projectileX = position.x + direction.x * projectilePositionShift;
		float projectileY = position.y + direction.y * projectilePositionShift;
		return new Projectile(8, projectileX, projectileY, direction);
	}
	else
	{
		return nullptr;
	}
}
