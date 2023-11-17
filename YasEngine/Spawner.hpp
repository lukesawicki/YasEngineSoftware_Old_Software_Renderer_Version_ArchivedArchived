#ifndef SPAWNER_HPP
#define SPAWNER_HPP
#include "GameObject.hpp"
#include "Vector2D.hpp"
#include "TimePicker.hpp"

class Spawner
{
	public:
        int timeBetweenSpawns;
        TimePicker timePicker;
		Vector2D<int> position;
		Vector2D<int> spawnPosition;
		int spawningMaxRadius = 24; //100;
		int spawningMinRadius = 8;// 24;
		int maxValueForDrawingSpawningDirection = 5;
        double startTime = 0;
        double currentTime = 0;
        double previousTime = 0;

        Spawner();
			void spawnObject(GameObject*& gameObject);
	private:

};

#endif
