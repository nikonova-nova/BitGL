#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_POINT_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_POINT_HPP






#include "Vec.hpp"






namespace BitGL
{
	using Point2D = Vec2<int>;






	constexpr auto to_1d_index(Point2D const &position, Vec2<int> const &size) -> std::size_t;
}






#include "impl/Point.ipp"






#endif
