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

	//static void normalizedVector(YasVector2D<Type>&vector)
	//static Type getVectorMagnitude(const YasVector2D<Type>&vector)

	//std::cout << YasVector2D::normlalize(localVertices[0])->


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

	YasVector2D<float>*

//i: 0 X : -160
//i : 0 Y : -80.0
//
//i : 1 X : 0.0
//i : 1 Y : -50
//
//i : 2 X : 80.0
//i : 2 Y : -50
//
//i : 3 X : 160
//i : 3 Y : 0.0
//
//i : 4 X : 80
//i : 4 Y : 50.0
//
//i : 5 X : 0.0
//i : 5 Y : 50
//
//i : 6 X : -160
//i : 6 Y : 80
//
//	//// JEDNORAZOWO PRZELICZAM SOBIE JAK TO BEDZIE W DOBRYM KIERUNKU
//	// 90 stopni:= 1.5708 radianow
//	double ninteDegree = 1.5708;
//	//this is clockwise
//	for (int i = 0; i < numberOfVertices; i++)
//	{
//		float x = localVertices[i].x * cos(ninteDegree) + localVertices[i].y * sin(ninteDegree);
//		float y = localVertices[i].x * sin(ninteDegree) - localVertices[i].y * cos(ninteDegree);
//
//		localVertices[i].x = x;
//		localVertices[i].y = y;
//	}
//
//	for (int i = 0; i < numberOfVertices; i++)
//	{
//		std::cout << "i: " << i << "X: " << localVertices[i].x << std::endl;
//		std::cout << "i: " << i << "Y: " << localVertices[i].y << std::endl;
//
//	}
//	int stop = 0;
//	std::cin >> stop;
	//zeroDegreeAngleVector.x = 1.0F;
	//zeroDegreeAngleVector.y = 0.0F;

	//currentPlayerDirectionVector.x = 1;
	//currentPlayerDirectionVector.y = 0;

	generate();

	//generateRegularPolygonVertices(position, 16, 7);
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


/*
void Player::rotateToMousePosition(double x, double y, YasVector2D<int>* windowDimensions)
{
	double currentX = x;
	double currentY = y;
	windowPositionToCartesianPosition(currentX, currentY, windowDimensions);
	YasVector2D<double> mousePositionVector(currentX, currentY);
	YasVector2D<double>::normalizedVector(mousePositionVector);


	//directionMouseAngle = atan2f(
	//	// uzyc nie diraction a old mouse position
	//	(zeroDegreeAngleVector.x * mousePositionVector.x + zeroDegreeAngleVector.y * mousePositionVector.y),
	//	(YasVector2D<double>::getVectorMagnitude(zeroDegreeAngleVector) * YasVector2D<double>::getVectorMagnitude(mousePositionVector))
	//);

	//oldDirectionMouseAngle = directionMouseAngle;

	rotateDirection(directionMouseAngle);
	
	//float angleToRotateOf = directionMouseAngle - playerCurrentDirectionAngle;

	//for (int i = 0; i < numberOfVertices; i++)
	//{
	//	float x = localVertices[i].x * cos(angleToRotateOf) - localVertices[i].y * sin(angleToRotateOf);
	//	float y = localVertices[i].x * sin(angleToRotateOf) + localVertices[i].y * cos(angleToRotateOf);

	//	localVertices[i].x = x;
	//	localVertices[i].y = y;
	//}



	//playerCurrentDirectionAngle = directionMouseAngle;
	generate();
}

*/

 // COMMENTED 2022 04 04 
void Player::rotateToMousePosition(double oldX, double oldY, double x, double y, YasVector2D<int>* windowDimensions)
{
	double currentX = x;
	double currentY = y;
	windowPositionToCartesianPosition(currentX, currentY, windowDimensions);
	YasVector2D<float> mousePositionVector(static_cast<float>(currentX), static_cast<float>(currentY));
	YasVector2D<float>::normalizedVector(mousePositionVector);

	double angleBetweenCurrentAndMouse = YasVector2D<float>::angleBetweenVectors(direction, mousePositionVector);
		
	oldDirectionMouseAngle = directionMouseAngle;


	direction.x = mousePositionVector.x;
	direction.y = mousePositionVector.y;
	// CHYBA NIE MUSZE UZYWAC KATOW WYSTARCZY MIEC PIERWOTNA DLUGOSC WEKTOROW WIERZCHOLKOW I WETKRO KIERUNKOWY
	// kolejny raz dochodze do tego samego ze tak sie nie da bo kazdy wierzcholek ma swoj kierunek
	for (int i = 0; i < numberOfVertices; i++)
	{
		float x = static_cast<float>(localVertices[i].x * cos(angleBetweenCurrentAndMouse) - localVertices[i].y * sin(angleBetweenCurrentAndMouse));
		float y = static_cast<float>(localVertices[i].x * sin(angleBetweenCurrentAndMouse) + localVertices[i].y * cos(angleBetweenCurrentAndMouse));

		localVertices[i].x = x;
		localVertices[i].y = y;
	}
	generate();
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

		/*float x = localVertices[i].x * cos(directionMouseAngle) - localVertices[i].y * sin(directionMouseAngle);
		float y = localVertices[i].x * sin(directionMouseAngle) + localVertices[i].y * cos(directionMouseAngle);

		localVertices[i].x = x;
		localVertices[i].y = y;*/
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
