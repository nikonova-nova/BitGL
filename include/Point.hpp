#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_POINT_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_POINT_HPP






#include "Vec.hpp"






constexpr auto to_1d_index(Vec2<int> const &position, int const width) -> std::size_t;






#include "impl/Point.ipp"






#endif
