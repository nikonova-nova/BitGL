#include <Windows.h>






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



	auto window_dc = GetDC(window);



	ShowWindow(window, SW_SHOW);



	MSG message;
	while (window_is_valid)
	{
		SetPixel(window_dc, 400, 400, RGB(255, 0, 0));



		WaitMessage();

		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessageA(&message);
		}
	}



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
