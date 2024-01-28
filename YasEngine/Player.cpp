#include"Player.hpp"

#include "Randomizer.hpp"

Player::Player(float x, float y)
{

	collider.x = x;
	collider.y = y;
	collider.radius = 20;
	iAm = WhoAmI::PROTAGONIST;
	position.x = x;
	position.y = y;

	direction.x = 1;
	direction.y = 0;

	speed = 200;
	rotationSpeed = 5;

	numberOfVertices = 17;
	numberOfVerticesCopy = 17;

	worldVertices = new Vector2D<float>[numberOfVertices];
	localVertices = new Vector2D<float>[numberOfVertices];

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

	localVerticesCopy = localVertices;

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

	moveCollider();

	// SPACE
	if (input->shoot || mouse->leftMouseButton)
	{
		isShooting = true;
	}
	regeneratePolygon();
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

void Player::rotateToMousePosition(float x, float y, Vector2D<int>* windowDimensions)
{
	if (x <= windowDimensions->x && y <= windowDimensions->y)
	{
		float currentX = x;
		float currentY = y;

		windowPositionToCartesianPosition(currentX, currentY, windowDimensions);

		Vector2D<float> mousePositionVector(static_cast<float>(currentX), static_cast<float>(currentY));
		//Vector2D<float>::normalizedVector(mousePositionVector);

		float angleBetweenCurrentAndMouse = Vector2D<float>::angleBetweenVectors(direction, mousePositionVector);
		rotateAllVerticesOverAnAngle(angleBetweenCurrentAndMouse);
		setDirection(mousePositionVector.x, mousePositionVector.y);
	}
}

void Player::rotateToMousePositionInLocalCoordinateSystem(float x, float y, Vector2D<int>* windowDimensions)
{
	if (x <= windowDimensions->x && y <= windowDimensions->y)
	{
		float currentX = x;
		float currentY = y;

		windowPositionToCartesianPosition(currentX, currentY, windowDimensions);

		Vector2D<float> currentMousePosition = Vector2D<float>(currentX, currentY);

		Vector2D<float> mouseDirectionInLocalCoordynationSystem = Vector2D<float>::createUnitVectorFromBoundVector(currentMousePosition, position);

		float angleBetweenCurrentAndMouse = Vector2D<float>::angleBetweenVectors(direction, mouseDirectionInLocalCoordynationSystem);

		rotateAllVerticesOverAnAngle(angleBetweenCurrentAndMouse);
		Vector2D<float>::rotateVectorOverTheAngle(&direction, angleBetweenCurrentAndMouse);
	}
}


void Player::setDirection(float x, float y)
{
	direction.x = x;
	direction.y = y;
}

void Player::generate()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        worldVertices[i].x = position.x + localVertices[i].x;
        worldVertices[i].y = position.y + localVertices[i].y;
    }
}

void Player::generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices)
{
	this->circumscribedCircleRadius = circumscribedCircleRadius;
	this->numberOfVertices = numberOfVertices;
	this->worldVertices = new Vector2D<float>[numberOfVertices];
	this->localVertices = new Vector2D<float>[numberOfVertices];

	angleForGenerateInIsoscelesPolygons = startAngle;
	stepAngle = 360.0F / numberOfVertices;
	for (int i = 0; i < numberOfVertices; i++)
	{
		localVertices[i].x = 0.0F + static_cast<int>(circumscribedCircleRadius * cos(angleForGenerateInIsoscelesPolygons * (PI / 180.0F)));
		localVertices[i].y = 0.0F + static_cast<int>(circumscribedCircleRadius * sin(angleForGenerateInIsoscelesPolygons * (PI / 180.0F)));
		angleForGenerateInIsoscelesPolygons += stepAngle;
	}
	generate();
}


void Player::regeneratePolygon()
{
	generate();
}

void Player::rotateAllVerticesOverAnAngle(float angle)
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		Vector2D<float>::rotateVectorOverTheAngle(&localVertices[i], angle);
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

void Player::switchPolygon(int numberOfVertices, int collectibleRadius)
{
	generateRegularPolygonVertices(collectibleRadius, numberOfVertices);
}

Projectile* Player::shoot()
{
	if (isShooting)
	{
		isShooting = false;
		float projectileX = position.x + direction.x * projectilePositionShift;
		float projectileY = position.y + direction.y * projectilePositionShift;

		int randNumber = Randomizer::drawNumberClosedInterval(0, 5);



		int projectileSpeed = 200;

		if(randNumber==3)
		{
			projectileSpeed = 0;
			speed = speed * -1;
		}

		if (randNumber == 2)
		{
			projectileSpeed *= -1;
		}

		return new Projectile(8, projectileX, projectileY, direction, projectileSpeed);
	}
	else
	{
		return nullptr;
	}
}
