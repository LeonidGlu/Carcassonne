#pragma once
#include <iostream>
#include <string>

#ifdef DEBUG_MODE
	#define DEBUG_LOG(x) \
		std::cout << "[DEBUG] " << x << "\n"
	#define DEBUG_CALL(x) x
	#define DEBUG_LOG_LOCATION(x) \
		std::cout << "[DEBUG] " << __FILE__ << ":" \
				<< __LINE__ << " | " << x << "\n"
#else
	#define DEBUG_LOG(x)
	#define DEBUG_CALL(x)
	#define DEBUG_LOG_LOCATION(x)
#endif // DEBUG_MODE
