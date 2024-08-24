#ifndef MAPFRAME_HPP
#define MAPFRAME_HPP
#include "line_segment.hpp"

struct MapFrame {
  LineSegment left_line_segment;
  LineSegment right_line_segment;
  LineSegment top_line_segment;
  LineSegment bottom_line_segment;
};

#endif
