﻿#include"FibonacciPointsGenerator.hpp"

PointsSet* FibonacciPointsGenerator::generatePoints()
{
	pointsNumber = 16;

	Vector2D<float>* points = new Vector2D<float>[pointsNumber*2];
	std::vector<int> fibonacci = generateNfibonaccinumbers(pointsNumber);


	// Point constructor setting x and y to 0;
	// This loop creates pairs of points = ( (0,0) ; (fibonacci(i) ,y=0) )
	int j = 0;
	for(int i=1; i < (pointsNumber*2) - 1; i+=2)
	{
		points[i].x = 100.0F; // static_cast<float>(fibonacci.at(j++));
	}

	// DLUGOSC LINI JEST TEZ FIBONACCI NARAZIE
	// ALE WIECEJ LINI BEDZIE JESLI DLUGOSCI ZROBIE STALE
	j = 0;
	for (int i = 1; i < pointsNumber*2 - 1; i+=2)
	{
		Vector2D<float>::rotateVectorOverTheAngle(&points[i], static_cast<int>(fibonacci.at(j++)) * (PI / 180.0F));
	}

	PointsSet* pointsSet = new PointsSet();
	pointsSet->points = points;
	pointsSet->pointsNumber = pointsNumber;
	return pointsSet;
}