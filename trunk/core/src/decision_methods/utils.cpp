
#include <utils.h>
#include <istream>

namespace utils {
	std::istream &operator>>(std::istream &is, utils::Fraction &frac) {
		auto numerator{0};
		auto denominator{0};
		is >> numerator;
		is.ignore(1);
		is >> denominator;

		frac.set_numerator(numerator);
		frac.set_denominator(denominator);
		return is;
	};


}
