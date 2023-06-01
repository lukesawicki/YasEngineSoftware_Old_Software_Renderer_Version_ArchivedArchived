#include<cstdlib>
#include"Spawner.hpp"
#include "Destroyable.hpp"

//GameObject* 
void Spawner::spawnObject(GameObject*& gameObject)
{
	int oldTargetPositionX = 0;
	int oldTargetPositionY = 0;
	//liveTime;
	timer.setInterval([&]() {
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

			gameObject = new Destroyable(16, targetPositionX, targetPositionY, Vector2D<float>(0.0F, 0.0F), 5);
			if (gameObject != nullptr)
			{
				//std::cout << "is not null" << std::endl;
			}
		}

		//std::cout << "AAAAAAAAAA" << std::endl;

		}, 750);

	//return gameObject;
}
