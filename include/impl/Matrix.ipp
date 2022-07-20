#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_MATRIX_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_MATRIX_IPP






namespace BitGL
{
	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto BitGL::Matrix<T, Rn, Cn>::operator[](std::size_t n)       -> T       * { return m_internal_array.data() + n * Cn; }
	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto BitGL::Matrix<T, Rn, Cn>::operator[](std::size_t n) const -> T const * { return m_internal_array.data() + n * Cn; }
}






#endif
