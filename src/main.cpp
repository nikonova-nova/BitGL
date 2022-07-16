#include <Windows.h>






auto CALLBACK window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) noexcept -> LRESULT;






auto main() -> int
{

}






auto CALLBACK window_callback(HWND window, UINT message, WPARAM w_param, LPARAM l_param) noexcept -> LRESULT
{
	return DefWindowProcA(window, message, w_param, l_param);
}
