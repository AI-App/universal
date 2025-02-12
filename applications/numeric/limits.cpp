// limits.cpp example program comparing numeric_limits of different number systems
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <limits>
#include <universal/utility/number_system_properties.hpp> //minmax_range etc. for native types

// select the number systems we would like to compare
#include <universal/number/integer/integer.hpp>
#include <universal/number/fixpnt/fixpnt.hpp>
#include <universal/number/areal/areal.hpp>
#include <universal/number/posit/posit.hpp>
#include <universal/number/lns/lns.hpp>
#include <universal/number/valid/valid.hpp>

//constexpr long double pi     = 3.14159265358979323846;
//constexpr long double e      = 2.71828182845904523536;
//constexpr long double log_2e = 1.44269504088896340736;

int main(int argc, char** argv)
try {
	using namespace sw::universal;

	std::cout << "numeric_limits for different number systems\n";

	using int32    = integer<32>;
	using fixpnt32 = fixpnt<32, 16>;
	using posit32  = posit<32,2>;
	using areal32  = areal<32,8,uint32_t>; // should use a uint32_t for efficiency
	using lns32    = lns<32>;

	// report on precision and dynamic range of the number system

	std::streamsize precision = std::cout.precision();

	constexpr size_t columnWidth = 30;
	numberTraits<int32, columnWidth>(std::cout);
	numberTraits<fixpnt32, columnWidth>(std::cout);
	numberTraits<float, columnWidth>(std::cout);
	numberTraits<areal32, columnWidth>(std::cout);
	numberTraits<posit32, columnWidth>(std::cout);
	numberTraits<lns32, columnWidth>(std::cout);

	std::cout << minmax_range<float>() << '\n';
	std::cout << minmax_range<posit32>() << '\n';
	std::cout << minmax_range<lns32>() << '\n';

	std::cout << dynamic_range<float>() << '\n';
	std::cout << dynamic_range<posit32>() << '\n';
	std::cout << dynamic_range<lns32>() << '\n';

	std::cout << symmetry<float>() << '\n';
	std::cout << symmetry<posit32>() << '\n';
	std::cout << symmetry<lns32>() << '\n';

	compareNumberTraits<float, areal32>(std::cout);
	compareNumberTraits<float, posit32>(std::cout);
	compareNumberTraits<float, lns32>(std::cout);

	std::cout << std::setprecision(precision) << std::endl;
	
	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << "Caught exception: " << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const std::runtime_error& err) {
	std::cerr << "Caught runtime exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
