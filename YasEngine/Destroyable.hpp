#ifndef COLLECTIBLE_HPP
#define COLLECTIBLE_HPP
#include "GameObject.hpp"
#include "Randomizer.hpp"

class Destroyable: public GameObject
{
public:
	Randomizer randomizer;
	Destroyable(float radius, float x, float y, Vector2D<float> direction, int numberOfVertices);
	~Destroyable();
	void generate() override;
	void generateRegularPolygonVertices(float circumscribedCircleRadius, int numberOfVertices) override;
	void regeneratePolygon() override;
	void setPosition(float x, float y) override;
	void setPosition(const Vector2D<float>& position) override;
	void move(float deltaTime) override;
	void setColor(const Vector4D<Uint8>& color) override;
	void setRandomColor();
	Vector2D<float> velocity;
};

#endif