#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP
#include "GameObject.hpp"

class Collectible: public GameObject
{
public:
	Collectible(float radius, float x, float y, Vector2D<float> direction);
	~Collectible();
	void generate() override;
	void generateRegularPolygonVertices(const Vector2D<float>& position, float circumscribedCircleRadius, int numberOfVertices) override;
	void regeneratePolygon() override;
	void setPosition(float x, float y) override;
	void setPosition(const Vector2D<float>& position) override;
	void move(float deltaTime) override;
	void setColor(const Vector4D<Uint8>& color) override;
	void setRandomColor();
	Vector2D<float> velocity;
};

#endif