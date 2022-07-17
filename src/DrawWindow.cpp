#include <algorithm>



#include "DrawWindow.hpp"






DrawWindow::DrawWindow(int const width, int const height, std::string const &title) :
	Window             (width, height, title),
	framebuffer        (width * height, RGB(0, 0, 0)),
	framebuffer_dc     { CreateCompatibleDC(get_hdc()) },
	framebuffer_bitmap { CreateBitmap(width, height, 1, sizeof(decltype(framebuffer)::value_type) * 8, framebuffer.data()) },
	old_bitmap         { static_cast<decltype(old_bitmap)>(SelectObject(framebuffer_dc, framebuffer_bitmap)) }
{}
DrawWindow::~DrawWindow()
{
	SelectObject(framebuffer_dc, old_bitmap);
	DeleteObject(framebuffer_bitmap);
	DeleteDC(framebuffer_dc);
}



auto DrawWindow::clear_framebuffer(COLORREF const color) -> void
{
	std::fill(framebuffer.begin(), framebuffer.end(), color);
}
auto DrawWindow::render_point(int const x, int const y, COLORREF const color) -> void
{
	RECT window_rect;
	GetWindowRect(get_hwnd(), &window_rect);
	auto width = window_rect.right - window_rect.left;

	framebuffer[y * width + x] = color;
}

auto DrawWindow::draw() -> void
{
	SetBitmapBits(framebuffer_bitmap, framebuffer.size() * sizeof(decltype(framebuffer)::value_type), framebuffer.data());
	SelectObject(framebuffer_dc, framebuffer_bitmap);

	RECT window_rect;
	GetWindowRect(get_hwnd(), &window_rect);
	auto width  = window_rect.right  - window_rect.left;
	auto height = window_rect.bottom - window_rect.top;

	BitBlt(get_hdc(),
	       0,
	       0,
	       width,
	       height,
	       framebuffer_dc,
	       0,
	       0,
	       SRCCOPY);
}
