#include"SpawnersQuadTree.hpp"

SpawnersQuadTree::SpawnersQuadTree(Vector2D<int>* position, int size, SpawnersQuadTree* parent, int& levelInTree)
{
	if(levelInTree == 2)
	{
		return;
	}
	this->position = position;
	this->size = size;

	short factorX = 1;
	short factorY = 1;
	
	int x = 0;
	int y = 0;

	levelInTree++;

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			factorX = -1;
			;
			break;
		case 1:
			factorX = 1;
			;
			break;
		case 2:
			factorX = -1;
			factorY = -1;
			;
			break;
		case 3:
			factorX = 1;
			;
			break;
		}

		if (parent != nullptr)
		{
			x = parent->position->x + ((factorX * parent->size) / 4);
			y = parent->position->y + ((factorY * parent->size) / 4);
			position = new Vector2D<int>(x, y);
			childNodes[i] = new SpawnersQuadTree(position, parent->size, this, levelInTree);
		}
		else
		{
			x = this->position->x + ((factorX * this->size) / 4);
			y = this->position->y + ((factorY * this->size) / 4);
		}

	}
}

// SpawnersQuadTree(Vector2D<int>* position, int size);
// void calculageTwoLayersOfQuads();
// Vector2D<int> position;
// int size;
// SpawnersQuadTree* childNodes[4];
// Spawner* spawner;
// bool isPlayerOnThisQuad;
// Spawner* takeOutSpawner();