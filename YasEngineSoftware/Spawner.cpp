#include<cstdlib>
#include"Spawner.hpp"
#include "Destroyable.hpp"

Spawner::Spawner() {
    currentTime = timePicker.getMiliseconds();
    previousTime = currentTime;
    timeBetweenSpawns = 800;
}

void Spawner::spawnObject(GameObject*& gameObject)
{
    currentTime = timePicker.getMiliseconds();
    if( (currentTime - previousTime) >= timeBetweenSpawns)
    {
		int oldTargetPositionX = 0;
		int oldTargetPositionY = 0;
		srand(clock());

		// int spawningMaxRadius;
		// int spawningMinRadius;

		int xPos = rand() % spawningMaxRadius + spawningMinRadius;
		int yPos = rand() % spawningMaxRadius + spawningMinRadius;
		int dirX = rand() % maxValueForDrawingSpawningDirection + 1;
		int dirY = rand() % maxValueForDrawingSpawningDirection + 1;

		int numberOfVertices = rand() % 7 + 3;

		if (dirX <= maxValueForDrawingSpawningDirection*0.5)
		{
			dirX = -1;
		}

		if (dirX >= maxValueForDrawingSpawningDirection * 0.5)
		{
			dirX = 1;
		}

		if (dirY <= maxValueForDrawingSpawningDirection * 0.5)
		{
			dirY = -1;
		}

		if (dirY >= maxValueForDrawingSpawningDirection * 0.5)
		{
			dirY = 1;
		}

		int targetPositionX = position.x + dirX * xPos;
		int targetPositionY = position.y + dirY * yPos;

		if (oldTargetPositionX != targetPositionX || oldTargetPositionY != targetPositionY)
		{
			gameObject = new Destroyable(16, static_cast<float>(targetPositionX), static_cast<float>(targetPositionY), Vector2D<float>(0.0F, 0.0F), numberOfVertices);
		}

        previousTime = currentTime;
    }
}

