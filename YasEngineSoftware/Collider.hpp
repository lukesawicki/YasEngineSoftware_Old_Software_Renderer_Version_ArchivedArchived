#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include"YasGraphicsLibrary.hpp"

class Collider
{
	public:
		float radius = 0.0F;
		float x = 0.0F;
		float y = 0.0F;
		Collider(float radius, float x, float y);
		static bool isInCollision(const Collider& object1,const Collider& object2);
		static bool isCollidingWithWall(const Collider& object1);
};

#endif
