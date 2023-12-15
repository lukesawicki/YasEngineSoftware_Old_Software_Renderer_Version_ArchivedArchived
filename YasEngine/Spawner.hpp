#ifndef SPAWNER_HPP
#define SPAWNER_HPP
#include "GameObject.hpp"
#include "Randomizer.hpp"
#include "Vector2D.hpp"
#include "TimePicker.hpp"

class Spawner
{
	public:
		// Randomizer randomizer;
        int timeBetweenSpawns;
        TimePicker timePicker;
		Vector2D<int> position;
		Vector2D<int> spawnPosition;
		int spawningMaxRadius = 24; //100;
		int spawningMinRadius = 8;// 24;
		int maxValueForDrawingSpawningDirection = 4;
        double startTime = 0;
		double currentTime = 0;
		double previousTime = 0;
		bool firstSpawned=false;

        Spawner();

		Spawner(int x, int y);
		void spawnObject(GameObject*& gameObject);
	private:
		void prepareObjectToSpawn(GameObject*& gameObject);

};

#endif
