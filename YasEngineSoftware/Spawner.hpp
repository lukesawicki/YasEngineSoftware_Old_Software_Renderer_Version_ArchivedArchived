#ifndef SPAWNER_HPP
#define SPAWNER_HPP
#include "GameObject.hpp"
#include "Timer.hpp"
#include "Vector2D.hpp"

class Spawner
{
	public:
		Timer timer = Timer();
		Vector2D<int> position;
		Vector2D<int> spawnPosition;
		//GameObject* 
			void spawnObject(GameObject*& gameObject);
	private:

};

#endif
