#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_VECTOR_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_VECTOR_HPP






#define BITGL_VECTOR_DEFN_ACCESS(n, f, i)                                           \
template<typename T>                                                             \
constexpr auto Vector<T, n>::f()       -> T       & { return m_internal_array[i]; } \
template<typename T>                                                             \
constexpr auto Vector<T, n>::f() const -> T const & { return m_internal_array[i]; }






namespace BitGL
{
	// Vector2
	BITGL_VECTOR_DEFN_ACCESS(2, x, 0)
	BITGL_VECTOR_DEFN_ACCESS(2, y, 1)

	BITGL_VECTOR_DEFN_ACCESS(2, r, 0)
	BITGL_VECTOR_DEFN_ACCESS(2, g, 1)

	BITGL_VECTOR_DEFN_ACCESS(2, s, 0)
	BITGL_VECTOR_DEFN_ACCESS(2, t, 1)

	BITGL_VECTOR_DEFN_ACCESS(2, width, 0)
	BITGL_VECTOR_DEFN_ACCESS(2, height, 1)



	// Vector3
	BITGL_VECTOR_DEFN_ACCESS(3, x, 0)
	BITGL_VECTOR_DEFN_ACCESS(3, y, 1)
	BITGL_VECTOR_DEFN_ACCESS(3, z, 2)

	BITGL_VECTOR_DEFN_ACCESS(3, r, 0)
	BITGL_VECTOR_DEFN_ACCESS(3, g, 1)
	BITGL_VECTOR_DEFN_ACCESS(3, b, 2)

	BITGL_VECTOR_DEFN_ACCESS(3, s, 0)
	BITGL_VECTOR_DEFN_ACCESS(3, t, 1)
	BITGL_VECTOR_DEFN_ACCESS(3, p, 2)

	BITGL_VECTOR_DEFN_ACCESS(3, width, 0)
	BITGL_VECTOR_DEFN_ACCESS(3, height, 1)
	BITGL_VECTOR_DEFN_ACCESS(3, depth, 2)



	// Vector4
	BITGL_VECTOR_DEFN_ACCESS(4, x, 0)
	BITGL_VECTOR_DEFN_ACCESS(4, y, 1)
	BITGL_VECTOR_DEFN_ACCESS(4, z, 2)
	BITGL_VECTOR_DEFN_ACCESS(4, w, 3)

	BITGL_VECTOR_DEFN_ACCESS(4, r, 0)
	BITGL_VECTOR_DEFN_ACCESS(4, g, 1)
	BITGL_VECTOR_DEFN_ACCESS(4, b, 2)
	BITGL_VECTOR_DEFN_ACCESS(4, a, 3)

	BITGL_VECTOR_DEFN_ACCESS(4, s, 0)
	BITGL_VECTOR_DEFN_ACCESS(4, t, 1)
	BITGL_VECTOR_DEFN_ACCESS(4, p, 2)
	BITGL_VECTOR_DEFN_ACCESS(4, q, 3)
}






#endif
