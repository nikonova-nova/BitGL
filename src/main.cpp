#include <cmath>



#include <chrono>



#include "Vec.hpp"
#include "DrawWindow.hpp"






auto main() -> int
{
	BitGL::DrawWindow window({ 800, 800 }, "BitGL");
	window.restore();



	float time_now = 0;
	auto previous_time = std::chrono::high_resolution_clock::now();



	while (window.is_open())
	{
		auto current_time = std::chrono::high_resolution_clock::now();
		time_now += std::chrono::duration_cast<std::chrono::milliseconds>(current_time - previous_time).count() / 1000.0f;
		previous_time = current_time;



		std::uint8_t r = (std::cos(time_now + 0      ) + 1) * 127;
		std::uint8_t g = (std::cos(time_now + 2.0944 ) + 1) * 127;
		std::uint8_t b = (std::cos(time_now + 4.18879) + 1) * 127;

		// Win32 uses BGR for this
		window.clear_colorbuffer({ r, g, b });
		window.draw();

		BitGL::Window::poll_events();
	}

	return EXIT_SUCCESS;
}
