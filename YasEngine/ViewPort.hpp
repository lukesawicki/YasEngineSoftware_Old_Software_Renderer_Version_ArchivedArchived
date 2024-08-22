#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP
#include"Vector2D.hpp"
#include"Vector4D.hpp"
#include"GameObject.hpp"

// Point of origin is on bottom left
class ViewPort
{
  public:
    Vector2D<int> position;
    Vector2D<int> viewPortSizes;
    Uint8* pixels = nullptr;

    virtual void clearColor(const Vector4D<Uint8>& drawingColor) = 0;
    virtual void drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor) = 0;
    virtual void drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, const Vector4D<Uint8>& drawingColor) = 0;
    virtual void drawPolygon(GameObject* polygon) = 0;

};

#endif
