#ifndef SIMPLE_TIMER_HPP
#define SIMPLE_TIMER_HPP

#include <iostream>
#include <chrono>

class SimpleTimer
{
public:

	SimpleTimer()
	{
		_start = std::chrono::high_resolution_clock::now();
	}
	~SimpleTimer()
	{
		_end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float, std::milli> duration = _end - _start;
		std::cout << "Duration = " << duration.count() << std::endl;
	}
private:

	std::chrono::time_point<std::chrono::steady_clock> _start, _end;
};

#endif 