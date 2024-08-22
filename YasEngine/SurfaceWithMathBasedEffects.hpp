#ifndef MATHEMATICSFUNSURFACE_HPP
#define MATHEMATICSFUNSURFACE_HPP
#include "PixelsTable.hpp"
#include"ViewPort.hpp"

class SurfaceWithMathBasedEffects final : public ViewPort
{
  public:
    void render(double& deltaTime);
    void cartesianPositionToWindow(int& x, int& y) const
    {
      x = x + static_cast<int>(0.5F * viewPortSizes.x);
      y = -y + static_cast<int>(0.5F * viewPortSizes.y);
    }
    SurfaceWithMathBasedEffects(int x, int y, int width, int height, const Vector4D<Uint8>& defaultColor);
    SurfaceWithMathBasedEffects(Vector2D<int> position, int width, int height, const Vector4D<Uint8>& defaultColor);
    virtual ~SurfaceWithMathBasedEffects();
    void clearColor(const Vector4D<Uint8>& drawingColor) override;
    void drawPoint(int x, int y, const Vector4D<Uint8>& drawingColor) override;
    void drawLine(const Vector2D<float>& point0, const Vector2D<float>& point1, const Vector4D<Uint8>& drawingColor)  override;
    void drawPolygon(GameObject* polygon)  override;
    void copyPixelsInToPIxelTable(PixelsTable& pixelsTable);
    void drawNumbersAsGroupOfLines(Vector2D<float>* vertices, int maximumNumberOfVertices, int& currentNumberOfVertices, const Vector4D<Uint8>& color, bool areLinesContinuos);

    void horizontalLineOnSurface(int y, Vector4D<Uint8> color)
    {
      int maxX = static_cast<int>(0.5F * viewPortSizes.x);
      for (int i = -maxX; i < maxX; i++) //X
      {
        drawPoint(i, y, color);
      }
    }

    void verticalLineOnSurface(int x, Vector4D<Uint8> color)
    {
      int maxY = static_cast<int>(0.5F * viewPortSizes.y);
      for (int i = -maxY; i < maxY; i++) //X
      {
        drawPoint(x, i, color);
      }
    }

    void drawCartesianAxies();
};

#endif