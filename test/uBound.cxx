// hello.cxx (example1)

#include "fltk/Bound.h"
#include "fltk/Tests.h"

#include <sstream>

namespace
{

std::string
bounds_test0
	()
{
	std::ostringstream oss;

	fltk::Bound<int> const emptyone;
	if (! emptyone.empty()) {
		oss << "fail: ibounds empty" << std::endl;
	}

	fltk::Bound<float> floatone(0.f, 5.f);
	if (floatone != floatone) {
		oss << "fail: floatone != floatone test" << std::endl;
	}

	fltk::Bound<float> floattwo = floatone;
	if (floatone != floattwo) {
		oss << "fail: floatone != floattwo test" << std::endl;
	}

	floattwo.translate(-1.f);
	if (floattwo == floatone) {
		oss << "fail: floatone == floattwo test" << std::endl;
	}

	return oss.str();
}

}

int
main()
{
	fltk::Tests tests(__FILE__);
	tests.add(bounds_test0, "bounds_test0");
	return tests.run();
}
