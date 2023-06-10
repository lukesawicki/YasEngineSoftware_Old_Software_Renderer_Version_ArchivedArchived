#ifndef SPAWNERSQUADTREE_HPP
#define SPAWNERSQUADTREE_HPP

#include<vector>
#include"Spawner.hpp"
#include"Vector2D.hpp"

class SpawnersQuadTree
{
	public:
		
		SpawnersQuadTree(Vector2D<int>* position, int size, SpawnersQuadTree* parent, int& levelInTree,int& iteration);
		Vector2D<int>* position;
		int size;
		SpawnersQuadTree* childNodes[4];
		Spawner* spawner;
		bool isPlayerOnThisQuad;
		Spawner* takeOutSpawner();
		void createSpanwer(const std::vector<int>& spawnerPositionNumber);
};

#endif SPAWNERSQUADTREE_HPP
