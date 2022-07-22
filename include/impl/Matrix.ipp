#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_MATRIX_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_MATRIX_IPP






namespace BitGL
{
	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto Matrix<T, Rn, Cn>::operator*=(T const scalar)               -> Matrix<T, Rn, Cn> & { for (auto &x : m_internal_array) { x *= scalar; } return *this; }

	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto Matrix<T, Rn, Cn>::operator+=(Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn> &
	{ for (std::size_t i = 0; i < Rn * Cn; ++i) { m_internal_array[i] += rhs.m_internal_array[i]; } return *this; }
	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto Matrix<T, Rn, Cn>::operator-=(Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn> &
	{ for (std::size_t i = 0; i < Rn * Cn; ++i) { m_internal_array[i] -= rhs.m_internal_array[i]; } return *this; }
	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto Matrix<T, Rn, Cn>::operator*=(Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn> &
	{
		Matrix<T, Rn, Cn> temp {};
		for (std::size_t i = 0; i < Rn; ++i)
		{
			for (std::size_t j = 0; j < Cn; ++j)
			{
				for (std::size_t k = 0; k < Rn; ++k)
				{
					temp[i][j] += (*this)[i][k] * rhs[k][j];
				}
			}
		}
		m_internal_array = temp.m_internal_array;
		return *this;
	}



	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto BitGL::Matrix<T, Rn, Cn>::operator[](std::size_t n)       -> T       * { return m_internal_array.data() + n * Cn; }
	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto BitGL::Matrix<T, Rn, Cn>::operator[](std::size_t n) const -> T const * { return m_internal_array.data() + n * Cn; }



	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto operator*(Matrix<T, Rn, Cn> matrix, T const scalar)            -> Matrix<T, Rn, Cn> { matrix += scalar; return matrix; }

	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto operator+(Matrix<T, Rn, Cn> lhs, Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn> { lhs += rhs; return lhs; }
	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto operator-(Matrix<T, Rn, Cn> lhs, Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn> { lhs -= rhs; return lhs; }
	template<typename T, std::size_t Rn, std::size_t Cn>
	constexpr auto operator*(Matrix<T, Rn, Cn> lhs, Matrix<T, Rn, Cn> const &rhs) -> Matrix<T, Rn, Cn> { lhs *= rhs; return lhs; }
}






#endif
