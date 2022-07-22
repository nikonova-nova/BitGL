#ifndef NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_VECTOR_IPP
#define NIKONOVA_NOVA_BITGL_INCLUDE_IMPL_VECTOR_IPP






#include <cmath>






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
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::normalize() -> void
	{
		*this /= length();
	}

	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::length() const -> T
	{
		return std::sqrt(dot(*this, *this));
	}



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
	constexpr auto Vector<T, N>::operator++()    -> Vector<T, N> & { for (auto &x : m_internal_array) { ++x; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator++(int) -> Vector<T, N>   { auto tmp { *this }; operator++(); return tmp; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator--()    -> Vector<T, N> & { for (auto &x : m_internal_array) { --x; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator--(int) -> Vector<T, N>   { auto tmp { *this }; operator--(); return tmp; }



	template<typename T, std::size_t N>
	constexpr auto operator+(Vector<T, N> vector) -> Vector<T, N> { return vector; }
	template<typename T, std::size_t N>
	constexpr auto operator-(Vector<T, N> vector) -> Vector<T, N> { for (auto &x : vector.m_internal_array) { x = -x; } return vector; }



	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator+=(T const scalar) -> Vector<T, N> & { for (auto &x: m_internal_array) { x += scalar; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator-=(T const scalar) -> Vector<T, N> & { for (auto &x: m_internal_array) { x -= scalar; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator*=(T const scalar) -> Vector<T, N> & { for (auto &x: m_internal_array) { x *= scalar; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator/=(T const scalar) -> Vector<T, N> & { for (auto &x: m_internal_array) { x /= scalar; } return *this; }

	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator+=(Vector<T, N> const &rhs) -> Vector<T, N> & { for (std::size_t i = 0; i < N; ++i) { m_internal_array[i] += rhs[i]; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator-=(Vector<T, N> const &rhs) -> Vector<T, N> & { for (std::size_t i = 0; i < N; ++i) { m_internal_array[i] -= rhs[i]; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator*=(Vector<T, N> const &rhs) -> Vector<T, N> & { for (std::size_t i = 0; i < N; ++i) { m_internal_array[i] *= rhs[i]; } return *this; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator/=(Vector<T, N> const &rhs) -> Vector<T, N> & { for (std::size_t i = 0; i < N; ++i) { m_internal_array[i] /= rhs[i]; } return *this; }

	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator*=(Matrix<T, N> const &matrix) -> Vector<T, N> &
	{
		Vector<T, N> temp {};
		for (std::size_t i = 0; i < N; ++i)
		{
			for (std::size_t j = 0; j < N; ++j)
			{
				temp[i] += matrix[i][j] * (*this)[j];
			}
		}
		*this = temp;
		return *this;
	}



	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator[](std::size_t const index)       -> T       & { return m_internal_array[index]; }
	template<typename T, std::size_t N>
	constexpr auto Vector<T, N>::operator[](std::size_t const index) const -> T const & { return m_internal_array[index]; }



	template<typename T, std::size_t N>
	constexpr auto operator+(Vector<T, N> vector, T const scalar) -> Vector<T, N> { vector += scalar; return vector; }
	template<typename T, std::size_t N>
	constexpr auto operator-(Vector<T, N> vector, T const scalar) -> Vector<T, N> { vector -= scalar; return vector; }
	template<typename T, std::size_t N>
	constexpr auto operator*(Vector<T, N> vector, T const scalar) -> Vector<T, N> { vector *= scalar; return vector; }
	template<typename T, std::size_t N>
	constexpr auto operator/(Vector<T, N> vector, T const scalar) -> Vector<T, N> { vector /= scalar; return vector; }

	template<typename T, std::size_t N>
	constexpr auto operator+(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N> { lhs += rhs; return lhs; }
	template<typename T, std::size_t N>
	constexpr auto operator-(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N> { lhs -= rhs; return lhs; }
	template<typename T, std::size_t N>
	constexpr auto operator*(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N> { lhs *= rhs; return lhs; }
	template<typename T, std::size_t N>
	constexpr auto operator/(Vector<T, N> lhs, Vector<T, N> const &rhs) -> Vector<T, N> { lhs /= rhs; return lhs; }

	template<typename T, std::size_t N>
	constexpr auto operator*(Vector<T, N> vector, Matrix<T, N> const &matrix) -> Vector<T, N> { vector *= matrix; return matrix; }



	template<typename T, std::size_t N>
	constexpr auto operator==(Vector<T, N> const &lhs, Vector<T, N> const &rhs) -> bool
	{ for (std::size_t i = 0; i < N; ++i) { if (lhs.m_internal_array[i] != rhs.m_internal_array[i]) { return false; } } return true; }



	template<typename T, std::size_t N>
	constexpr auto dot(Vector<T, N> const &a, Vector<T, N> const &b) -> T
	{
		auto tmp { a * b };
		T accum {};
		for (auto const &x : tmp.m_internal_array)
		{
			accum += x;
		}
		return accum;
	}
	template<typename T>
	constexpr auto cross(Vector3<T> const &a, Vector3<T> const &b) -> Vector3<T>
	{
		return {
			a.y() * b.z() - a.z() * b.y(),
			a.z() * b.x() - a.x() * b.z(),
			a.x() * b.y() - a.y() * b.x()
		};
	}
}






#endif
