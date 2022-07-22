#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_MATRIX_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_MATRIX_IPP






namespace BitGL
{
	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator*=(T const scalar)          -> Matrix<T, N> & { for (auto &x : m_internal_array) { x *= scalar; } return *this; }

	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator+=(Matrix<T, N> const &rhs) -> Matrix<T, N> &
	{ for (std::size_t i = 0; i < N * N; ++i) { m_internal_array[i] += rhs.m_internal_array[i]; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator-=(Matrix<T, N> const &rhs) -> Matrix<T, N> &
	{ for (std::size_t i = 0; i < N * N; ++i) { m_internal_array[i] -= rhs.m_internal_array[i]; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator*=(Matrix<T, N> const &rhs) -> Matrix<T, N> &
	{
		Matrix<T, N> temp {};
		for (std::size_t i = 0; i < N; ++i)
		{
			for (std::size_t j = 0; j < N; ++j)
			{
				for (std::size_t k = 0; k < N; ++k)
				{
					temp[i][j] += (*this)[i][k] * rhs[k][j];
				}
			}
		}
		m_internal_array = temp.m_internal_array;
		return *this;
	}



	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator[](std::size_t n)       -> T       * { return m_internal_array.data() + n * N; }
	template<typename T, std::size_t N>
	constexpr auto Matrix<T, N>::operator[](std::size_t n) const -> T const * { return m_internal_array.data() + n * N; }



	template<typename T, std::size_t N>
	constexpr auto operator*(Matrix<T, N> matrix, T const scalar)       -> Matrix<T, N> { matrix += scalar; return matrix; }

	template<typename T, std::size_t N>
	constexpr auto operator+(Matrix<T, N> lhs, Matrix<T, N> const &rhs) -> Matrix<T, N> { lhs += rhs; return lhs; }
	template<typename T, std::size_t N>
	constexpr auto operator-(Matrix<T, N> lhs, Matrix<T, N> const &rhs) -> Matrix<T, N> { lhs -= rhs; return lhs; }
	template<typename T, std::size_t N>
	constexpr auto operator*(Matrix<T, N> lhs, Matrix<T, N> const &rhs) -> Matrix<T, N> { lhs *= rhs; return lhs; }
}






#endif
