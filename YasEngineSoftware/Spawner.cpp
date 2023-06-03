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
		int xPos = rand() % 75 + 10;
		int yPos = rand() % 75 + 10;
		int dirX = rand() % 10 + 1;
		int dirY = rand() % 10 + 1;

		int numberOfVertices = rand() % 7 + 3;

		if (dirX <= 5)
		{
			dirX = -1;
		}

		if (dirX >= 5)
		{
			dirX = 1;
		}

		if (dirY <= 5)
		{
			dirY = -1;
		}

		if (dirY >= 5)
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

