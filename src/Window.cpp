#include "Window.hpp"






Window::Window(int const width, int const height, std::string const &title) noexcept
{
	// Check if window class was already registered
	// If it wasn't, create and register one
	if (m_window_class_id == 0) { m_window_class_id = create_window_class(); }

	m_window = create_window(width, height, title);
	m_dc     = GetDC(m_window);
}
Window::~Window() noexcept
{
	ReleaseDC(m_window, m_dc);
	DestroyWindow(m_window);
	// Don't unregister window class yet, dev might still make another window
}



auto Window::restore()  -> void
{
	ShowWindow(m_window, SW_SHOW);
}
auto Window::minimize() -> void
{
	ShowWindow(m_window, SW_SHOWMINIMIZED);
}

auto Window::poll_events() -> void
{
	MSG message;
	while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessageA(&message);
	}
}
auto Window::wait_events() -> void
{
	WaitMessage();

	poll_events();
}



auto Window::get_hwnd() -> HWND
{
	return m_window;
}
auto Window::get_hdc()  -> HDC
{
	return m_dc;
}



auto Window::create_window_class() -> ATOM
{
	WNDCLASSA window_class
	{
		.style         = CS_HREDRAW | CS_OWNDC | CS_VREDRAW,
		.lpfnWndProc   = reinterpret_cast<WNDPROC>(&m_window_callback),
		.hInstance     = GetModuleHandleA(nullptr),
		.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)),
		.lpszClassName = "nikonova-nova | BitGL default window class"
	};

	return RegisterClassA(&window_class);
}
auto Window::create_window(int const width, int const height, std::string const &title) -> HWND
{
	return CreateWindowA(MAKEINTATOM(m_window_class_id),
	                     title.c_str(),
	                     WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU,
	                     CW_USEDEFAULT,
	                     CW_USEDEFAULT,
	                     width,
	                     height,
	                     nullptr,
	                     nullptr,
	                     GetModuleHandleA(nullptr),
	                     nullptr);
}



auto CALLBACK Window::m_window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) -> LRESULT
{
	switch (message)
	{
	default:
		{
			return DefWindowProcA(window, message, w_param, l_param);
		}
	}
}
