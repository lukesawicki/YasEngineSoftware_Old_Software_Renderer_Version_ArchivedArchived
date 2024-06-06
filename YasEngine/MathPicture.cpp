#include"MathPicture.hpp"

MathPicture::MathPicture(std::map<int, float>* numbers, PointsGenerator* pointsGenerator, PointsSet* npointsSet)
{
	this->basePointsFuel = static_cast<int>(numbers->size());
	this->pointsGenerator = pointsGenerator;
	this->numbers = numbers;
	this->floatNumbers = nullptr;
	generatePoints();
}

MathPicture::MathPicture(std::map<float, float>* floatNumbers, PointsGenerator* pointsGenerator, PointsSet* nPointsSet)
{
	this->basePointsFuel = static_cast<int>(floatNumbers->size());
	this->pointsGenerator = pointsGenerator;
	this->numbers = nullptr;
	this->floatNumbers = floatNumbers;
	generatePoints();
}

void MathPicture::generatePoints()
{
	if (numbers != nullptr)
	{
		pointsSet = pointsGenerator->generatePoints(static_cast<int>(numbers->size()), numbers);
	}
	if (floatNumbers != nullptr)
	{
		pointsSet = pointsGenerator->generateFloatPoints(static_cast<int>(floatNumbers->size()), floatNumbers);
	}

}