#pragma once

namespace utils {
	inline double d(double p, double q) {
		return p / q;
	}

	inline bool approximatelyEqual(double a, double b, double epsilon = 0.01) {
		return abs(a - b) <= ((abs(a) < abs(b) ? abs(b) : abs(a)) * epsilon);
	}
	inline std::string wrap_with_spaces(const std::string & str) {
		return std::string(" ").append(str).append(" ");
	}

} // namespace utils