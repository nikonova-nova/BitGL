#include <cmath>



#include <chrono>



#include "DrawWindow.hpp"






auto main() -> int
{
	DrawWindow window(800, 800, "BitGL");
	window.restore();



	float time_now = 0;
	auto previous_time = std::chrono::high_resolution_clock::now();



	while (window.is_open())
	{
		auto current_time = std::chrono::high_resolution_clock::now();
		time_now += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - previous_time).count() / 1000.0f;
		previous_time = current_time;



		int r = (std::cos(time_now + 0      ) + 1) * 127;
		int g = (std::cos(time_now + 2.0944 ) + 1) * 127;
		int b = (std::cos(time_now + 4.18879) + 1) * 127;

		// Win32 uses BGR for this
		window.clear_framebuffer(RGB(b, g, r));
		window.draw();

		window.poll_events();
	}

	return EXIT_SUCCESS;
}
