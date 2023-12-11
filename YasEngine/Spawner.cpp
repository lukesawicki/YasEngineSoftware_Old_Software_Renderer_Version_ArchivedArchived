#include<cstdlib>
#include"Spawner.hpp"
#include "Destroyable.hpp"
#include "VariousTools.hpp"

Spawner::Spawner() {
    currentTime = timePicker.getMiliseconds();
    previousTime = currentTime;
	timeBetweenSpawns = 3000 + Randomizer::drawNumberClosedInterval(6000, 10000);
}

Spawner::Spawner(int x, int y) {
	position.x = x;
	position.y = y;
	currentTime = timePicker.getMiliseconds();
	previousTime = currentTime;
	timeBetweenSpawns = 3000 + Randomizer::drawNumberClosedInterval(6000, 10000);
}

void Spawner::spawnObject(GameObject*& gameObject)
{
    currentTime = timePicker.getMiliseconds();
    if( (currentTime - previousTime) >= timeBetweenSpawns)
    {
		int oldTargetPositionX = 0;
		int oldTargetPositionY = 0;
		// srand(clock());

		int xPos = Randomizer::drawNumberClosedInterval(spawningMinRadius, spawningMaxRadius); // % spawningMaxRadius + spawningMinRadius;
		int yPos = Randomizer::drawNumberClosedInterval(spawningMinRadius, spawningMaxRadius);
		int dirX = Randomizer::drawNumberClosedInterval(1, maxValueForDrawingSpawningDirection);
		int dirY = Randomizer::drawNumberClosedInterval(1, maxValueForDrawingSpawningDirection);

		int numberOfVertices = Randomizer::drawNumberClosedInterval(3, 7); //rand() % 7 + 3;

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
			gameObject = new Destroyable(16, static_cast<float>(targetPositionX), static_cast<float>(targetPositionY), numberOfVertices);
		}

        previousTime = currentTime;
    }
}

