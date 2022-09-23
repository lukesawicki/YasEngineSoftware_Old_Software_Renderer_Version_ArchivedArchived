#include"Projectile.hpp"

Projectile::Projectile(float radius, float x, float y, Vector2D<float> direction)
{
	isAlive = true;
	iAm = WhoAmI::PROJECTILE;
	collider.radius = radius;
	directionSwitched = false;
	speed = 200;
	Vector2D<float> position(x, y);
	velocity.x = speed * direction.x;
	velocity.y = speed * direction.y;
	color = BLUE;
	generateRegularPolygonVertices(position, radius, 4);
	timer = Timer();
	//liveTime;
	//timer.setInterval([&]() {
	//	std::cout << "HELLO" << std::endl;
	//	}, 500);

	timer.setTimeout([&]() {
		//cout << "Hey.. After 5.2s. But I will stop the timer!" << endl;
		timer.stop();
		this->isAlive = false;
		}, liveTime);
}

Projectile::~Projectile()
{
	delete[] worldVertices;
}

void Projectile::move(float deltaTime)
{
	position.x = position.x + deltaTime * velocity.x;
	position.y = position.y + deltaTime * velocity.y;
	moveCollider();
	regeneratePolygon();
}

void Projectile::generate()
{
	for (int i = 0; i < numberOfVertices; i++)
	{
		worldVertices[i].x = position.x + localVertices[i].x;
		worldVertices[i].y = position.y + localVertices[i].y;
	}
}

void Projectile::generateRegularPolygonVertices(const Vector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices)
{
	this->circumscribedCircleRadius = circumscribedCircleRadius;
	this->numberOfVertices = numberOfVertices;
	this->position.x = position.x;
	this->position.y = position.y;
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

void Projectile::regeneratePolygon()
{
	generate();
}
