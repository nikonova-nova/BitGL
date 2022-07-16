#include <Windows.h>



#include <vector>



#include "Window.hpp"






auto CALLBACK window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) noexcept -> LRESULT;






auto main() -> int
{
	auto instance = GetModuleHandleA(nullptr);



	WNDCLASSA window_class
	{
		.style         = CS_HREDRAW | CS_OWNDC | CS_VREDRAW,
		.lpfnWndProc   = reinterpret_cast<WNDPROC>(&window_callback),
		.hInstance     = instance,
		.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)),
		.lpszClassName = "nikonova-nova | BitGL default window class"
	};

	auto window_class_id = RegisterClassA(&window_class);



	auto window = CreateWindowA(MAKEINTATOM(window_class_id),
	                            "BitGL",
	                            WS_CAPTION | WS_OVERLAPPED | WS_SYSMENU,
	                            CW_USEDEFAULT, CW_USEDEFAULT,
	                            800, 800,
	                            nullptr,
	                            nullptr,
	                            instance,
	                            nullptr);

	auto window_is_valid = true;

	SetWindowLongPtrA(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&window_is_valid));



	// SET UP RENDERING
	auto                  window_dc       = GetDC(window);
	std::vector<COLORREF> framebuffer       (800 * 800, RGB(0, 0, 255)); // DIBs use BGR
	auto                  framebuffer_dc  = CreateCompatibleDC(window_dc);
	auto                  framebuffer_bmp = CreateBitmap(800,
	                                                     800,
	                                                     1,
	                                                     sizeof(DWORD) * 8,
	                                                     reinterpret_cast<void *>(framebuffer.data()));
	SelectObject(framebuffer_dc, framebuffer_bmp);



	ShowWindow(window, SW_SHOW);

	MSG message;
	while (window_is_valid)
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
	ReleaseDC(window, window_dc);
	DestroyWindow(window);
	UnregisterClassA(MAKEINTATOM(window_class_id), instance);



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
