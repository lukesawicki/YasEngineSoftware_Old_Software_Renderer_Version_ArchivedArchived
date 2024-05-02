#ifndef MAPFRAME_HPP
#define MAPFRAME_HPP
#include "LineSegment.hpp"

struct MapFrame
{
	LineSegment leftLineSegment;
	LineSegment rightLineSegment;
	LineSegment topLineSegment;
	LineSegment bottomLineSegment;
};

#endif

