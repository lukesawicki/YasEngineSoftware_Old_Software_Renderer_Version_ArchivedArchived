#include "ViewPort.hpp"

ViewPort::ViewPort(int x, int y, int width, int height)
{
}

ViewPort::ViewPort(Vector2D<int> position, int width, int height)
{
}

ViewPort::~ViewPort()
{
}

void ViewPort::clearColor(const Vector4D<Uint8>& drawingColor)
{
}

void ViewPort::drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor)
{
}

void ViewPort::drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, PixelsTable& pixelsTable, const Vector4D<Uint8>& drawingColor)
{
}

void ViewPort::drawPolygon(GameObject* polygon, PixelsTable& pixelsTable)
{
}
