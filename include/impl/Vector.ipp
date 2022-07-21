#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_VECTOR_HPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_VECTOR_HPP






#define BITGL_VECTOR_DEFN_ACCESS(f, i)                                                          \
template<typename T, std::size_t N>                                                             \
constexpr auto Vector<T, N>::f()       -> T       &                                             \
{                                                                                               \
	static_assert(N >= i + 1, "This function will index out of bounds on this size of Vector"); \
	return m_internal_array[i];                                                                 \
}                                                                                               \
template<typename T, std::size_t N>                                                             \
constexpr auto Vector<T, N>::f() const -> T const &                                             \
{                                                                                               \
	static_assert(N >= i + 1, "This function will index out of bounds on this size of Vector"); \
	return m_internal_array[i];                                                                 \
}






namespace BitGL
{
	// VectorN
	BITGL_VECTOR_DEFN_ACCESS(x, 0)
	BITGL_VECTOR_DEFN_ACCESS(y, 1)
	BITGL_VECTOR_DEFN_ACCESS(z, 2)
	BITGL_VECTOR_DEFN_ACCESS(w, 3)

	BITGL_VECTOR_DEFN_ACCESS(r, 0)
	BITGL_VECTOR_DEFN_ACCESS(g, 1)
	BITGL_VECTOR_DEFN_ACCESS(b, 2)
	BITGL_VECTOR_DEFN_ACCESS(a, 3)

	BITGL_VECTOR_DEFN_ACCESS(s, 0)
	BITGL_VECTOR_DEFN_ACCESS(t, 1)
	BITGL_VECTOR_DEFN_ACCESS(p, 2)
	BITGL_VECTOR_DEFN_ACCESS(q, 3)

	BITGL_VECTOR_DEFN_ACCESS(width, 0)
	BITGL_VECTOR_DEFN_ACCESS(height, 1)
	BITGL_VECTOR_DEFN_ACCESS(depth, 2)



	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator[](std::size_t const index)       -> T       & { return m_internal_array[index]; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator[](std::size_t const index) const -> T const & { return m_internal_array[index]; }
}






#endif
