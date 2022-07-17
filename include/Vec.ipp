#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_VEC_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_VEC_IPP






#include "Vec.hpp"






constexpr auto to_colorref(Vec3<int> const &color) -> COLORREF
{
	return RGB(color[Vec::b], color[Vec::g], color[Vec::r]);
}






#endif
