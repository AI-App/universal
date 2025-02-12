﻿// rounding_error_multiplication.cpp: evaluation of rounding errors of multiplication in the posit number systems 
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the UNIVERSAL project, which is released under an MIT Open Source license.
#include <universal/utility/directives.hpp>
// pull in the posit number system
#include <universal/number/posit/posit.hpp>

int main()
try {
	using namespace sw::universal;

	constexpr size_t nbits = 16;
	constexpr size_t es = 1;
	using Posit = posit<nbits,es>;

	// print detailed bit-level computational intermediate results
	// bool verbose = false;

	// preserve the existing ostream precision
	auto precision = std::cout.precision();
	std::cout << std::setprecision(12);

	// with dynamic precision, we have the situation where multiplying
	// extreme numbers creates precision we do not have..
	Posit maxpos(SpecificValue::maxpos);
	Posit minpos(SpecificValue::minpos);
	Posit one = minpos * maxpos;
	std::cout << "maxpos : " << info_print(maxpos) << '\n';
	std::cout << "minpos : " << info_print(minpos) << '\n';
	std::cout << "one    : " << info_print(one) << '\n';

	// restore the previous ostream precision
	std::cout << std::setprecision(precision);

	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::universal::posit_arithmetic_exception& err) {
	std::cerr << "Uncaught posit arithmetic exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::universal::quire_exception& err) {
	std::cerr << "Uncaught quire exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::universal::posit_internal_exception& err) {
	std::cerr << "Uncaught posit internal exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (std::runtime_error& err) {
	std::cerr << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
