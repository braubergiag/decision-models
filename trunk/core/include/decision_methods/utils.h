#pragma once

#include <QString>
#include <optional>

namespace utils {
	inline double d(double p, double q) {
		return p / q;
	}

	inline bool approximatelyEqual(double a, double b, double epsilon = 0.01) {
		return abs(a - b) <= ((abs(a) < abs(b) ? abs(b) : abs(a)) * epsilon);
	}

	inline std::string wrap_with_spaces(const std::string &str) {
		return std::string(" ").append(str).append(" ");
	}

	class Fraction {
	public:
		Fraction(int numerator, int denominator) : numerator_(numerator), denominator_(denominator){};
		Fraction() : numerator_(1), denominator_(1){};

		double value() const { return denominator_ != 0 ? abs(d(numerator_, denominator_)) : d(1, 1); }

		double inv_value() const { return numerator_ != 0 ? abs(d(denominator_, numerator_)) : d(1, 1); }

		std::string view() const {
			return denominator_ == 1 ? std::to_string(numerator_)
									 : std::to_string(numerator_) + "/" + std::to_string(denominator_);
		}

		std::string inv_view() const {
			return numerator_ == 1 ? std::to_string(denominator_)
								   : std::to_string(denominator_) + "/" + std::to_string(numerator_);
		}

		int numerator() const { return numerator_; }

		void set_numerator(int numerator) { numerator_ = abs(numerator); }

		int denominator() const { return denominator_; }

		void set_denominator(int denominator) { denominator_ = abs(denominator); }

	private:
		int numerator_;
		int denominator_;
	};

	inline std::istream &operator>>(std::istream &is, Fraction &frac) {
		auto numerator{0};
		auto denominator{0};
		is >> numerator;
		is.ignore(1);
		is >> denominator;

		frac.set_numerator(numerator);
		frac.set_denominator(denominator);
		return is;
	};

} // namespace utils