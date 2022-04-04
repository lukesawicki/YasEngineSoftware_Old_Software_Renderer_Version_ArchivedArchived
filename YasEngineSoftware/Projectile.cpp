#include"Projectile.hpp"

Projectile::Projectile(float radius, float x, float y, YasVector2D<double> direction)
{
	directionSwitched = false;
	speed = 200;
	YasVector2D<float> position(x, y);
	velocity.x = speed * direction.x;
	velocity.y = speed * direction.y;
	color = BLUE;
	generateRegularPolygonVertices(position, radius, 64);
}

Projectile::~Projectile()
{
	delete[] worldVertices;
}

void Projectile::move(double deltaTime)
{
	position.x = position.x + deltaTime * velocity.x;
	position.y = position.y + deltaTime * velocity.y;

}

void Projectile::generate()
{
	angleForGenerateInisoscelesPolygons = startAngle;
	stepAngle = 360.0F / numberOfVertices;
	for (int i = 0; i < numberOfVertices; i++)
	{
		worldVertices[i].x = position.x + static_cast<int>(circumscribedCircleRadius * cos(angleForGenerateInisoscelesPolygons * (PI / 180.0F)));
		worldVertices[i].y = position.y + static_cast<int>(circumscribedCircleRadius * sin(angleForGenerateInisoscelesPolygons * (PI / 180.0F)));
		angleForGenerateInisoscelesPolygons += stepAngle;
	}
}

void Projectile::generateRegularPolygonVertices(const YasVector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices)
{
	this->circumscribedCircleRadius = circumscribedCircleRadius;
	this->numberOfVertices = numberOfVertices;
	this->position.x = position.x;
	this->position.y = position.y;
	this->worldVertices = new YasVector2D<float>[numberOfVertices];
	generate();
}

void Projectile::regeneratePolygon()
{
	generate();
}
