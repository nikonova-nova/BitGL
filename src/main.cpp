#include <Windows.h>



#include <vector>



#include "Window.hpp"






auto CALLBACK window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) noexcept -> LRESULT;






auto main() -> int
{
	Window window(800, 800, "BitGL");



	// SET UP RENDERING
	auto                  window_dc       = window.get_hdc();
	std::vector<COLORREF> framebuffer       (800 * 800, RGB(0, 0, 255)); // DIBs use BGR
	auto                  framebuffer_dc  = CreateCompatibleDC(window_dc);
	auto                  framebuffer_bmp = CreateBitmap(800,
	                                                     800,
	                                                     1,
	                                                     sizeof(DWORD) * 8,
	                                                     reinterpret_cast<void *>(framebuffer.data()));
	SelectObject(framebuffer_dc, framebuffer_bmp);



	window.restore();

	MSG message;
	while (window.is_open())
	{
		// RENDER TO window USING BitBlt
		BitBlt(window_dc,
		       0,
		       0,
		       800,
		       800,
		       framebuffer_dc,
		       0,
		       0,
		       SRCCOPY);



		WaitMessage();

		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}



	DeleteObject(framebuffer_bmp);
	DeleteDC(framebuffer_dc);



	return EXIT_SUCCESS;
}






auto CALLBACK window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) noexcept -> LRESULT
{
	switch (message)
	{
	case WM_CLOSE:
		{
			auto window_is_valid = reinterpret_cast<bool *>(GetWindowLongPtrA(window, GWLP_USERDATA));
			*window_is_valid = false;
			return 0;
		}

	default:
		{
			return DefWindowProcA(window, message, w_param, l_param);
		}
	}
}
