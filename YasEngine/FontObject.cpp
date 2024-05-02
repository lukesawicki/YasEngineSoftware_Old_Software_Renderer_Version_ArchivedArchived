#include "FontObject.hpp"
#include "YasGraphicsLibrary.hpp"
#include<cstdlib>     /* srand, rand */

#include "VariousTools.hpp"

FontObject::FontObject()
{

}

void FontObject::initialize(float radius, float x, float y, const Vector2D<float>& direction, int numberOfVertices)
{
    isAlive = true;
    iAm = GameObject::GUI_ELEMENT;
    collider.radius = 17;
    speed = 200;
    this->direction.x = direction.x;
    this->direction.y = direction.y;
    this->position.x = x;
    this->position.y = y;
    this->collider.x = x;
    this->collider.y = y;
    startAngle = 90;
    velocity.x = speed * direction.x;
    velocity.y = speed * direction.y;
    setRandomColor();
}

FontObject::~FontObject()
{
    delete[] worldVertices;
}

void FontObject::generate()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        worldVertices[i].x = position.x + localVertices[i].x;
        worldVertices[i].y = position.y + localVertices[i].y;
    }
}

void FontObject::generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices)
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

void FontObject::regeneratePolygon()
{
    generate();
}

void FontObject::setPosition(float x, float y)
{
    GameObject::setPosition(x, y);
}

void FontObject::setPosition(const Vector2D<float>& position)
{
    GameObject::setPosition(position);
}

void FontObject::move(float deltaTime)
{
    //position.x = position.x + deltaTime * velocity.x;
    //position.y = position.y + deltaTime * velocity.y;
    //moveCollider();
    //regeneratePolygon();
}

void FontObject::setColor(const Vector4D<Uint8>& color)
{
    GameObject::setColor(color);
}

void FontObject::setRandomColor()
{
    int col = Randomizer::drawNumberClosedInterval(1, 4); //drawNumberClosedInterval(0, 5); //rand() % 5;
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
