#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include"YasGraphicsLibrary.hpp"
#include"GameObject.hpp"
#include "TimePicker.hpp"


class Projectile : public GameObject {
  public:
    int liveTime = 500;
        TimePicker timePicker;

        double startTime = 0;
        double currentTime = 0;

    Vector2D<float> velocity;
    Projectile(float radius, float x, float y, Vector2D<float> direction);
    ~Projectile();
    void move(float deltaTime) override;
    void generate() override;
    void generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices) override;
    void regeneratePolygon() override;

};

#endif
