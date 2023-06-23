#ifndef SPAWNERSQUADTREE_HPP
#define SPAWNERSQUADTREE_HPP

#include<vector>
#include"Spawner.hpp"
#include"Vector2D.hpp"

class SpawnersQuadTree
{
	public:

		SpawnersQuadTree(Vector2D<int>* position, int size, SpawnersQuadTree* parent);
		Vector2D<int>* position;
		int size;
		SpawnersQuadTree* parentNode;
		SpawnersQuadTree* childNodes[4];
		Spawner* spawner;
		bool isPlayerOnThisQuad;
		Spawner* takeOutSpawner();
		void createSpanwer(const std::vector<int>& spawnerPositionNumber);

		static void addNodes(SpawnersQuadTree& spawnerQuadTree)
		{
			short factorX = 1;
			short factorY = 1;

			Vector2D<int>* position;

			int x = 0;
			int y = 0;
			for (int i = 0; i < 4; i++)
			{
				switch (i)
				{
				case 0:
					factorX = -1;
					factorY = 1;
					;
					break;
				case 1:
					factorX = 1;
					factorY = 1;
					;
					break;
				case 2:
					factorX = -1;
					factorY = -1;
					;
					break;
				case 3:
					factorX = 1;
					factorY = -1;
					;
					break;
				}

				x = spawnerQuadTree.position->x + (factorX * (spawnerQuadTree.size / 4));
				y = spawnerQuadTree.position->y + (factorY * (spawnerQuadTree.size / 4));
				position = new Vector2D<int>(x, y);
				spawnerQuadTree.childNodes[i] = new SpawnersQuadTree(position, spawnerQuadTree.size/2, &spawnerQuadTree);

			} // end for
		}
};

#endif // SPAWNERSQUADTREE_HPP
