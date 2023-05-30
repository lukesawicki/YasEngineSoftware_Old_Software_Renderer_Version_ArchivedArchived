#include "Button.hpp"
#include "ScreenWriter.hpp"

void Button::generate()
{
    for (int i = 0; i < numberOfVertices; i++)
    {
        worldVertices[i].x = position.x + localVertices[i].x;
        worldVertices[i].y = position.y + localVertices[i].y;
    }
}

void Button::generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices)
{

}

void Button::regeneratePolygon()
{
    generate();
}

void Button::move(float deltaTime)
{

}

Button::Button(const ButtonId& buttonId, std::string text, const Vector4D<Uint8>& color)
{
    this->buttonId = buttonId;
    this->text.assign(text);
    this->buttonTextWidth = ScreenWriter::FONT_WIDTH * text.size();
    this->color = color;
    numberOfVertices = 4;
}
