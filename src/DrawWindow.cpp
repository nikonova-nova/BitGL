#include <algorithm>



#include "DrawWindow.hpp"






DrawWindow::DrawWindow(int const width, int const height, std::string const &title) :
	Window               (width, height, title),
	m_colorbuffer        (width * height, RGB(0, 0, 0)),
	m_colorbuffer_dc     { CreateCompatibleDC(get_hdc()) },
	m_colorbuffer_bitmap { CreateBitmap(width, height, 1, sizeof(decltype(m_colorbuffer)::value_type) * 8, m_colorbuffer.data()) },
	m_old_bitmap         { static_cast<decltype(m_old_bitmap)>(SelectObject(m_colorbuffer_dc, m_colorbuffer_bitmap)) }
{}
DrawWindow::~DrawWindow()
{
	SelectObject(m_colorbuffer_dc, m_old_bitmap);
	DeleteObject(m_colorbuffer_bitmap);
	DeleteDC(m_colorbuffer_dc);
}



auto DrawWindow::clear_framebuffer(COLORREF const color) -> void
{
	std::fill(m_colorbuffer.begin(), m_colorbuffer.end(), color);
}
auto DrawWindow::render_point(int const x, int const y, COLORREF const color) -> void
{
	RECT window_rect;
	GetWindowRect(get_hwnd(), &window_rect);
	auto width = window_rect.right - window_rect.left;

	m_colorbuffer[y * width + x] = color;
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
