#include "Destroyable.hpp"
#include "YasGraphicsLibrary.hpp"
#include<cstdlib>     /* srand, rand */

Destroyable::Destroyable(float radius, float x, float y, int numberOfVertices)
{
	isAlive = true;
	iAm = GameObject::COLLECTIBLE;
	collider.radius = radius;
	speed = 20;
	Vector2D<float> position(x, y);
	this->position.x = x;
	this->position.y = y;
	this->collider.x = x;
	this->collider.y = y;
	float angle = Randomizer::drawNumberClosedInterval(0, 360);
	direction.x = 1;
	direction.y = 0;
	angle = angle * (PI / 180.0F); // PRZELICZYC NA RADIANY
	Vector2D<float>::rotateVectorOverTheAngle(&direction, angle);
	velocity.x = speed * direction.x;
	velocity.y = speed * direction.y;
	setRandomColor();
	generateRegularPolygonVertices(radius, numberOfVertices);
}

// void Player::rotateToMousePositionInLocalCoordinateSystem(float x, float y, Vector2D<int>* windowDimensions)
// {
// 	if (x <= windowDimensions->x && y <= windowDimensions->y)
// 	{
// 		float currentX = x;
// 		float currentY = y;
//
// 		windowPositionToCartesianPosition(currentX, currentY, windowDimensions);
//
// 		Vector2D<float> currentMousePosition = Vector2D<float>(currentX, currentY);
//
// 		Vector2D<float> mouseDirectionInLocalCoordynationSystem = Vector2D<float>::createUnitVectorFromBoundVector(currentMousePosition, position);
//
// 		float angleBetweenCurrentAndMouse = Vector2D<float>::angleBetweenVectors(direction, mouseDirectionInLocalCoordynationSystem);
//
// 		rotateAllVerticesOverAnAngle(angleBetweenCurrentAndMouse);
// 		Vector2D<float>::rotateVectorOverTheAngle(&direction, angleBetweenCurrentAndMouse);
// 	}
// }

// Projectile::Projectile(float radius, float x, float y, Vector2D<float> direction)
// {
// 	isAlive = true;
// 	iAm = WhoAmI::PROJECTILE;
// 	collider.radius = radius;
// 	directionSwitched = false;
// 	speed = 200;
// 	Vector2D<float> position(x, y);
// 	this->position.x = x;
// 	this->position.y = y;
// 	this->collider.x = x;
// 	this->collider.y = y;
//
// 	velocity.x = speed * direction.x;
// 	velocity.y = speed * direction.y;
// 	color = YELLOW;
// 	generateRegularPolygonVertices(radius, 4);
// 	startTime = timePicker.getMiliseconds();
// }

Destroyable::~Destroyable()
{
	delete[] worldVertices;
}

void Destroyable::generate()
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		worldVertices[i].x = position.x + localVertices[i].x;
		worldVertices[i].y = position.y + localVertices[i].y;
	}
}
// void Projectile::generate()
// {
// 	for (int i = 0; i < numberOfVertices; i++)
// 	{
// 		worldVertices[i].x = position.x + localVertices[i].x;
// 		worldVertices[i].y = position.y + localVertices[i].y;
// 	}
// }
void Destroyable::generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices)
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

void Destroyable::regeneratePolygon()
{
	generate();
}

void Destroyable::setPosition(float x, float y)
{
	GameObject::setPosition(x, y);
}

void Destroyable::setPosition(const Vector2D<float>& position)
{
	GameObject::setPosition(position);
}

void Destroyable::move(float deltaTime)
{
	position.x = position.x + deltaTime * velocity.x;
	position.y = position.y + deltaTime * velocity.y;
	moveCollider();
	regeneratePolygon();



	// void Projectile::move(float deltaTime)
	// {
	// 	if (timePicker.getMiliseconds() - startTime >= 2000)
	// 	{
	// 		this->isAlive = false;
	// 	}
	//
	// 	position.x = position.x + deltaTime * velocity.x;
	// 	position.y = position.y + deltaTime * velocity.y;
	// 	moveCollider();
	// 	regeneratePolygon();
	// }
}

void Destroyable::setColor(const Vector4D<Uint8>& color)
{
	GameObject::setColor(color);
}

void Destroyable::setRandomColor()
{
	int col = Randomizer::drawNumberClosedInterval(1, 4); // rand() % 5;
	switch(col)
	{
	case 0:
		setColor(RED);
		break;
	case 1:
		setColor(GREEN);
		break;
	case 2:
		setColor(BLUE);
		break;
	case 3:
		setColor(WHITE);
		break;
	case 4:
		setColor(YELLOW);
		break;
	default:
		setColor(BLUE);
		break;
	}
}

//v1 = rand() % 100;         // v1 in the range 0 to 99
//v2 = rand() % 100 + 1;     // v2 in the range 1 to 100
//v3 = rand() % 30 + 1985;   // v3 in the range 1985-2014 

//RED
//GREEN
//BLUE
//WHITE
//YELLOW