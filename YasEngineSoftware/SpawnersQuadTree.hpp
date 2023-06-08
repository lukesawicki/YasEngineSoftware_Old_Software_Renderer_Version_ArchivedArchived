#ifndef SPAWNERSQUADTREE_HPP
#define SPAWNERSQUADTREE_HPP

#include "Spawner.hpp"
#include "Vector2D.hpp"

class SpawnersQuadTree
{
	public:
		SpawnersQuadTree(Vector2D<int>* position, int size, SpawnersQuadTree* parent, int& levelInTree);
		Vector2D<int>* position;
		int size;
		SpawnersQuadTree* childNodes[4];
		Spawner* spawner;
		bool isPlayerOnThisQuad;
		Spawner* takeOutSpawner();
};

#endif SPAWNERSQUADTREE_HPP
