﻿// polynomial.cpp: evaluation of polynomial of degree N and Nd derivatives evaluate at point x
//
// Copyright (C) 2017-2020 Stillwater Supercomputing, Inc.
//
// This file is part of the UNIVERSAL project, which is released under an MIT Open Source license.
#include <universal/posit/posit>
#include <universal/integer/integer>
#include <universal/functions/ddpoly.hpp>


int main(int argc, char** argv)
try {
	using namespace std;
	using namespace sw::unum;
	using namespace sw::function;

	// print detailed bit-level computational intermediate results
	// bool verbose = false;

	// preserve the existing ostream precision
	auto precision = cout.precision();
	cout << setprecision(12);

	// define a polynomial
	// p(x) = c0 + c1 * x + c2 * x^2 + c3 * x^3
	std::vector<float> c = { 1, 2, 3, 4 };
	std::vector<float> pd(3);

	ddpoly(1.0f, c, pd);
	cout << pd[0] << endl;
	cout << pd[1] << endl;
	cout << pd[2] << endl;
	

	// restore the previous ostream precision
	cout << setprecision(precision);

	return EXIT_SUCCESS;
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const posit_arithmetic_exception& err) {
	std::cerr << "Uncaught posit arithmetic exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const quire_exception& err) {
	std::cerr << "Uncaught quire exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const posit_internal_exception& err) {
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
