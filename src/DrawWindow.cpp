#include <algorithm>



#include "DrawWindow.hpp"






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



auto DrawWindow::clear_colorbuffer(Vec3<int> const &color) -> void
{
	std::fill(m_colorbuffer.begin(), m_colorbuffer.end(), to_colorref(color));
}
auto DrawWindow::render_point(Vec2<int> const &position, Vec3<int> const &color) -> void
{
	RECT window_rect;
	GetWindowRect(get_hwnd(), &window_rect);
	auto width = window_rect.right - window_rect.left;

	m_colorbuffer[position[Vec::y] * width + position[Vec::x]] = to_colorref(color);
}

auto DrawWindow::draw() -> void
{
	SetBitmapBits(m_colorbuffer_bitmap, m_colorbuffer.size() * sizeof(decltype(m_colorbuffer)::value_type), m_colorbuffer.data());
	SelectObject(m_colorbuffer_dc, m_colorbuffer_bitmap);

	RECT window_rect;
	GetWindowRect(get_hwnd(), &window_rect);
	auto width  = window_rect.right  - window_rect.left;
	auto height = window_rect.bottom - window_rect.top;

	BitBlt(get_hdc(),
	       0,
	       0,
	       width,
	       height,
	       m_colorbuffer_dc,
	       0,
	       0,
	       SRCCOPY);
}
