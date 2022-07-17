#include "Vec.hpp"






constexpr auto to_colorref(Vec3<int> const &color) -> COLORREF
{
	return RGB(color[Vec::b], color[Vec::g], color[Vec::r]);
}
