#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_VECTOR_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_VECTOR_HPP






#include <Windows.h>



#include <cstddef>



#include <array>






#define BITGL_VECTOR_DECL_ACCESS(f)    \
constexpr auto f()       -> T       &; \
constexpr auto f() const -> T const &;






namespace BitGL
{
	template<typename T, std::size_t N>
	class Vector
	{
	public:
		BITGL_VECTOR_DECL_ACCESS(x)
		BITGL_VECTOR_DECL_ACCESS(y)
		BITGL_VECTOR_DECL_ACCESS(z)
		BITGL_VECTOR_DECL_ACCESS(w)

		BITGL_VECTOR_DECL_ACCESS(r)
		BITGL_VECTOR_DECL_ACCESS(g)
		BITGL_VECTOR_DECL_ACCESS(b)
		BITGL_VECTOR_DECL_ACCESS(a)

		BITGL_VECTOR_DECL_ACCESS(s)
		BITGL_VECTOR_DECL_ACCESS(t)
		BITGL_VECTOR_DECL_ACCESS(p)
		BITGL_VECTOR_DECL_ACCESS(q)

		BITGL_VECTOR_DECL_ACCESS(width)
		BITGL_VECTOR_DECL_ACCESS(height)
		BITGL_VECTOR_DECL_ACCESS(depth)


	public:
		std::array<T, N> m_internal_array;
	};
	template<typename T>
	using Vector2 = Vector<T, 2>;
	template<typename T>
	using Vector3 = Vector<T, 3>;
	template<typename T>
	using Vector4 = Vector<T, 4>;
}






#include "impl/Vector.ipp"






#endif
