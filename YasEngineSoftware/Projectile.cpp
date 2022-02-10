#include"Projectile.hpp"

YasGL::Projectile::Projectile(float radius, float x, float y, Vector2D<float> direction)
{
	directionSwitched = false;
	speed = 200;
	Vector2D<float> position(x, y);
	velocity.x = speed * direction.x;
	velocity.y = speed * direction.y;
	color = YasGL::BLUE;
	generateRegularPolygonVertices(position, radius, 64);
}

YasGL::Projectile::~Projectile()
{
	delete[] worldVertices;
}

void YasGL::Projectile::move(float deltaTime)
{
	position.x = position.x + deltaTime * velocity.x;
	position.y = position.y + deltaTime * velocity.y;

}

void YasGL::Projectile::generate()
{
	angle = startAngle;
	stepAngle = 360.0F / numberOfVertices;
	for (int i = 0; i < numberOfVertices; i++)
	{
		worldVertices[i].x = position.x + static_cast<int>(circumscribedCircleRadius * cos(angle * (YasGL::PI / 180.0F)));
		worldVertices[i].y = position.y + static_cast<int>(circumscribedCircleRadius * sin(angle * (YasGL::PI / 180.0F)));
		angle += stepAngle;
	}
}

void YasGL::Projectile::generateRegularPolygonVertices(const Vector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices)
{
	this->circumscribedCircleRadius = circumscribedCircleRadius;
	this->numberOfVertices = numberOfVertices;
	this->position.x = position.x;
	this->position.y = position.y;
	this->worldVertices = new Vector2D<float>[numberOfVertices];
	generate();
}

void YasGL::Projectile::regeneratePolygon()
{
	generate();
}
