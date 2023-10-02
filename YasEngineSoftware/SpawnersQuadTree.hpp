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

    static std::vector<Vector2D<int>*> generateTestPositions()
    {
        short factorX = 1;
        short factorY = 1;

        std::vector<Vector2D<int>*> positions;


        int zeroLevelQuadSize = 800;
        int zeroLevelQuadPosX = -400;
        int zeroLevelQuadPosY = 0;

        int firstLevelQuadPositionX = 0;
        int firstLevelQuadPositionY = 0;
        int firstLevelQuadSize = 0;

        int secondLevelQuadPositionX = 0;
        int secondLevelQuadPositionY = 0;
        int secondLevelQuadsize = 0;


        for(int j=0; j < 4; j++)
        {
            switch(j) {
                case 0:
                    factorX = -1;
                    factorY = 1;;
                    break;
                case 1:
                    factorX = 1;
                    factorY = 1;;
                    break;
                case 2:
                    factorX = -1;
                    factorY = -1;;
                    break;
                case 3:
                    factorX = 1;
                    factorY = -1;;
                    break;

            }
            firstLevelQuadSize = zeroLevelQuadSize * 0.5;
            firstLevelQuadPositionX = zeroLevelQuadPosX + (factorX * (firstLevelQuadSize * 0.5));
            firstLevelQuadPositionY = zeroLevelQuadPosY + (factorY * (firstLevelQuadSize * 0.5));

            for (int i = 0; i < 4; i++)
            {
                switch (i) {
                    case 0:
                        factorX = -1;
                        factorY = 1;;
                        break;
                    case 1:
                        factorX = 1;
                        factorY = 1;;
                        break;
                    case 2:
                        factorX = -1;
                        factorY = -1;;
                        break;
                    case 3:
                        factorX = 1;
                        factorY = -1;;
                        break;
                }

                secondLevelQuadsize = firstLevelQuadSize * 0.5;
                secondLevelQuadPositionX = firstLevelQuadPositionX + (factorX * (0.5 * secondLevelQuadsize));
                secondLevelQuadPositionY = firstLevelQuadPositionY + (factorY * (0.5 * secondLevelQuadsize));
                positions.push_back(new Vector2D<int>(secondLevelQuadPositionX, secondLevelQuadPositionY));
                //position = new Vector2D<int>(x, y);
//                spawnerQuadTree.childNodes[i] = new SpawnersQuadTree(position, spawnerQuadTree.size / 2,
//                                                                     &spawnerQuadTree);

            } // end for
        }

        return positions;
    }

};

#endif // SPAWNERSQUADTREE_HPP
