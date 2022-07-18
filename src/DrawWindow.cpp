#include <algorithm>



#include "Color.hpp"
#include "Point.hpp"
#include "DrawWindow.hpp"






namespace BitGL
{
	DrawWindow::DrawWindow(Vec2<int> const &size, std::string const &title) :
		Window               (size, title),
		m_colorbuffer        (size[Vec::width] * size[Vec::height], RGB(0, 0, 0)),
		m_colorbuffer_dc     { CreateCompatibleDC(get_hdc()) },
		m_colorbuffer_bitmap { CreateBitmap(size[Vec::width], size[Vec::height], 1, sizeof(decltype(m_colorbuffer)::value_type) * 8, m_colorbuffer.data()) },
		m_old_bitmap         { static_cast<decltype(m_old_bitmap)>(SelectObject(m_colorbuffer_dc, m_colorbuffer_bitmap)) }
	{}
	DrawWindow::~DrawWindow()
	{
		SelectObject(m_colorbuffer_dc, m_old_bitmap);
		DeleteObject(m_colorbuffer_bitmap);
		DeleteDC(m_colorbuffer_dc);
	}



	auto DrawWindow::clear_colorbuffer(Vec3<std::uint8_t> const &color) -> void
	{
		std::fill(m_colorbuffer.begin(), m_colorbuffer.end(), to_colorref(color));
	}
	auto DrawWindow::render_point(Vec2<int> const &position, Vec3<std::uint8_t> const &color) -> void
	{
		m_colorbuffer[to_1d_index(position, get_size()[Vec::width])] = to_colorref(color);
	}

	auto DrawWindow::draw() -> void
	{
		SetBitmapBits(m_colorbuffer_bitmap, m_colorbuffer.size() * sizeof(decltype(m_colorbuffer)::value_type), m_colorbuffer.data());
		SelectObject(m_colorbuffer_dc, m_colorbuffer_bitmap);

		auto window_size = get_size();

		BitBlt(get_hdc(),
		       0,
		       0,
		       window_size[Vec::width],
		       window_size[Vec::height],
		       m_colorbuffer_dc,
		       0,
		       0,
		       SRCCOPY);
	}
}
