#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_MATRIX_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_MATRIX_IPP






#define BITGL_MATRIX_DEFN_INDEXING(rn, cn)                                                                                        \
template<typename T>                                                                                                              \
constexpr auto Matrix<T, rn, cn>::operator[](std::size_t const n)       -> T       * { return m_internal_array.data() + n * cn; } \
template<typename T>                                                                                                              \
constexpr auto Matrix<T, rn, cn>::operator[](std::size_t const n) const -> T const * { return m_internal_array.data() + n * cn; }






namespace BitGL
{
	// Matrix2x2
	BITGL_MATRIX_DEFN_INDEXING(2, 2)



	// Matrix3x3
	BITGL_MATRIX_DEFN_INDEXING(3, 3)



	// Matrix4x4
	BITGL_MATRIX_DEFN_INDEXING(4, 4)
}






#endif
