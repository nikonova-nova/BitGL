#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_VECTOR_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_VECTOR_HPP






#define BITGL_VECTOR_DEFN_ACCESS(n, f, i)                                                                  \
template<typename T, std::size_t N>                                                                        \
constexpr auto Vector<T, N>::f()       -> T       &                                                        \
{                                                                                                          \
	static_assert(N >= n, "This function will index out of bounds on this size of Vector");                \
	return m_internal_array[i];                                                                            \
}                                                                                                          \
template<typename T, std::size_t N>                                                                        \
constexpr auto Vector<T, N>::f() const -> T const &                                                        \
{                                                                                                          \
	static_assert(N >= n, "This function will index out of bounds on this size of Vector");                \
	return m_internal_array[i];                                                                            \
}






namespace BitGL
{
	// VectorN
	BITGL_VECTOR_DEFN_ACCESS(2, x, 0)
	BITGL_VECTOR_DEFN_ACCESS(2, y, 1)
	BITGL_VECTOR_DEFN_ACCESS(3, z, 2)
	BITGL_VECTOR_DEFN_ACCESS(4, w, 3)

	BITGL_VECTOR_DEFN_ACCESS(2, r, 0)
	BITGL_VECTOR_DEFN_ACCESS(2, g, 1)
	BITGL_VECTOR_DEFN_ACCESS(3, b, 2)
	BITGL_VECTOR_DEFN_ACCESS(4, a, 3)

	BITGL_VECTOR_DEFN_ACCESS(2, s, 0)
	BITGL_VECTOR_DEFN_ACCESS(2, t, 1)
	BITGL_VECTOR_DEFN_ACCESS(3, p, 2)
	BITGL_VECTOR_DEFN_ACCESS(4, q, 3)

	BITGL_VECTOR_DEFN_ACCESS(2, width, 0)
	BITGL_VECTOR_DEFN_ACCESS(2, height, 1)
	BITGL_VECTOR_DEFN_ACCESS(3, depth, 2)
}






#endif
