// api.cpp: test suite runner for class interface tests of the fixpnt<nbits,rbits,Modulo/Saturating,BlockType> type
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <universal/utility/directives.hpp>

// Configure the fixpnt template environment
// first: enable general or specialized fixed-point configurations
#define FIXPNT_FAST_SPECIALIZATION
// second: enable/disable fixpnt arithmetic exceptions
#define FIXPNT_THROW_ARITHMETIC_EXCEPTION 1
#include <universal/number/fixpnt/fixpnt.hpp>
#include <universal/verification/test_reporters.hpp> 

// Regression testing guards: typically set by the cmake configuration, but MANUAL_TESTING is an override
#define MANUAL_TESTING 1
// REGRESSION_LEVEL_OVERRIDE is set by the cmake file to drive a specific regression intensity
// It is the responsibility of the regression test to organize the tests in a quartile progression.
//#undef REGRESSION_LEVEL_OVERRIDE
#ifndef REGRESSION_LEVEL_OVERRIDE
#define REGRESSION_LEVEL_1 1
#define REGRESSION_LEVEL_2 1
#define REGRESSION_LEVEL_3 0
#define REGRESSION_LEVEL_4 0
#endif

int main()
try {
	using namespace sw::universal;

	std::string test_suite = "fixed-point class interface ";
	std::cout << test_suite << '\n';
	int nrOfFailedTestCases = 0;

	/////////////////////////////////////////////////////////////////////////////////////
	//// MODULAR fixed-point (the default)

	// construction
	{
		int start = nrOfFailedTestCases;
		// default construction using default arithmetic (Modulo) and default BlockType (uint8_t)
		fixpnt<8, 4> a, b(-8.125f), c(7.875), d(-7.875); // replace with long double init  d(-7.875l);
		// b initialized to -8.125 in modular arithmetic becomes 7.875: -8.125 = b1000.0010 > maxneg -> becomes b0111.1110
		if (a != (c + d)) ++nrOfFailedTestCases;
		if (a != (b - c)) ++nrOfFailedTestCases;
		if (nrOfFailedTestCases - start > 0) {
			std::cout << "FAIL : " << a << ' ' << b << ' ' << c << ' ' << d << '\n';
		}
	}

	{
		int start = nrOfFailedTestCases;
		// construction with explicit arithmetic type and default BlockType (uint8_t)
		fixpnt<8, 4, Modulo> a, b(-8.125), c(7.875), d(-7.875);
		// b initialized to -8.125 in modular arithmetic becomes 7.875: -8.125 = b1000.0010 > maxneg -> becomes b0111.1110
		if (a != (c + d)) ++nrOfFailedTestCases;
		if (a != (b - c)) ++nrOfFailedTestCases;
		if (nrOfFailedTestCases - start > 0) {
			std::cout << "FAIL: " << to_binary(a) << ' ' << to_binary(b) << ' ' << to_binary(c) << ' ' << to_binary(d) << '\n';
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	//// SATURATING fixed-point

	{
		int start = nrOfFailedTestCases;
		// construction with explicit arithmetic type and default BlockType (uint8_t)
		fixpnt<8, 4, Saturating> a(-8.0), b(-8.125), c(7.875), d(-7.875);
		// b initialized to -8.125 in saturating arithmetic becomes -8
//		if (0 != (c + d)) ++nrOfFailedTestCases; //cout << to_binary(c + d) << endl;
		if (a != b) ++nrOfFailedTestCases;

		if (a != (d - 1)) ++nrOfFailedTestCases; // saturating to maxneg
		if (a != (d - 0.5)) ++nrOfFailedTestCases; // saturating to maxneg
		if (nrOfFailedTestCases - start > 0) {
			std::cout << to_binary(a) << ' ' << to_binary(b) << ' ' << to_binary(c) << ' ' << to_binary(d) << '\n';
			std::cout << to_binary(d - 1) << ' ' << to_binary(d - 0.5) << '\n';
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	//// improving efficiency for bigger fixed-points through explicit BlockType specification

	{
		int start = nrOfFailedTestCases;
		// construction with explicit arithmetic type and BlockType
		fixpnt<16, 4, Modulo, uint16_t> a, b(-2048.125f), c(2047.875), d(-2047.875);
		if (a != (c + d)) ++nrOfFailedTestCases;
		if (a != (b - c)) ++nrOfFailedTestCases;
		//		cout << to_binary(a, true) << ' ' << to_binary(b, true) << ' ' << to_binary(c, true) << ' ' << to_binary(d, true) << endl;
		if (nrOfFailedTestCases - start > 0) {
			std::cout << "FAIL : construction " << to_binary(a) << ' ' << to_binary(b) << ' ' << to_binary(c) << ' ' << to_binary(d) << '\n';
			std::cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// selectors

		// type tag to identify the type without having to depend on demangle
	{
		using Fixed = fixpnt<16, 2>;
		Fixed a{ 0 };
		std::cout << "type identifier : " << type_tag(a) << '\n';
		std::cout << "type identifier : " << type_tag(fixpnt<8, 4>()) << '\n';
		std::cout << "type identifier : " << type_tag(fixpnt<8, 4, Saturating, uint16_t>()) << '\n';
	}

	{
		int start = nrOfFailedTestCases;
		constexpr size_t nbits = 8;
		constexpr size_t rbits = 4;
		fixpnt<nbits, rbits> a, b;
		a = 1;
		if (!a.test(4)) ++nrOfFailedTestCases;
		b.setbits(1); // set the ULP
		if (!b.at(0)) ++nrOfFailedTestCases;
		if (nrOfFailedTestCases - start > 0) {
			std::cout << "FAIL : selectors\n";
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// modifiers

	{
		int start = nrOfFailedTestCases;
		// state/bit management
		constexpr size_t nbits = 8;
		constexpr size_t rbits = 4;
		fixpnt<nbits, rbits> a, b, c, d;
		for (size_t i = 0; i < rbits; ++i) {
			a.setbit(i, true);
		}
		b.setbits(0x0F); // same as the fixpnt a above
		if ((a - b) != 0) ++nrOfFailedTestCases;
		c = b;
		// manually flip the bits of b: don't use flip() as we are going to confirm flip() is correct
		for (size_t i = 0; i < nbits; ++i) {
			b.setbit(i, !b.test(i));
		}
		c.flip();  // in-place 1's complement, so now b and c are the same
		if (b != c) ++nrOfFailedTestCases;	
		d.setbits(0xFFFFFFF);
		if (0 == d) ++nrOfFailedTestCases;
		d.setzero();
		if (d != 0) ++nrOfFailedTestCases;
		if (nrOfFailedTestCases - start > 0) {
			std::cout << "FAIL : modifiers\n";
		}
	}

	/////////////////////////////////////////////////////////////////////////////
	// complements
	{
		int start = nrOfFailedTestCases;
		constexpr size_t nbits = 8;
		constexpr size_t rbits = 4;
		fixpnt<nbits, rbits> a, b;
		a.setbits(0xFF);
		b = onesComplement(a);
		if (b != 0) ++nrOfFailedTestCases;
		a = -1;
		b = twosComplement(a);
		if (b != 1) ++nrOfFailedTestCases;
		if (nrOfFailedTestCases - start > 0) {
			std::cout << "FAIL : complements 1\n";
		}
	}
	{
		int start = nrOfFailedTestCases;
		constexpr size_t nbits = 8;
		constexpr size_t rbits = 4;
		fixpnt<nbits, rbits, Modulo, uint16_t> a, b; // testing poorly selected BlockType
		a.setbits(0xFF);
		b = onesComplement(a);
		if (b != 0) ++nrOfFailedTestCases;
		a = -1;
		b = twosComplement(a);
		if (b != 1) ++nrOfFailedTestCases;
		if (nrOfFailedTestCases - start > 0) {
			std::cout << "FAIL : complements 2\n";
		}
	}
	{
		int start = nrOfFailedTestCases;
		constexpr size_t nbits = 8;
		constexpr size_t rbits = 4;
		fixpnt<nbits, rbits, Modulo, uint32_t> a, b; // testing poorly selected BlockType
		a.setbits(0xFF);
		b = onesComplement(a);
		if (b != 0) ++nrOfFailedTestCases;
		a = -1;
		b = twosComplement(a);
		if (b != 1) ++nrOfFailedTestCases;
		if (nrOfFailedTestCases - start > 0) {
			std::cout << "FAIL : complements 3\n";
		}
	}

	#undef FIXPNT_PARSE
#ifdef FIXPNT_PARSE
	////////////////////////////////////////////////////////////////////////////////////
	// parsing of text input
	{
		constexpr size_t nbits = 8;
		constexpr size_t rbits = 4;
		fixpnt<nbits, rbits, Modulo, uint32_t> a, b;
		a.assign("7.98765");
		if (a != 7.98765) ++nrOfFailedTestCases;
		a.assign("0b0010.1111");
		b.setbits(0x2F);
		if (a != b) ++nrOfFailedTestCases;
	}
#endif
	///////////////////////////////////////////////////////////////////////////////////
	// arithmetic

	{
		int start = nrOfFailedTestCases;
		constexpr size_t nbits = 16;
		constexpr size_t rbits = 8;
		constexpr bool arithmetic = Modulo;
		using blocktype = uint32_t;
		fixpnt<nbits, rbits, arithmetic, blocktype> a, b, c, d;
		a.maxpos();
		b.maxneg();
		c.minpos();
		d.minneg();
		if ((c + d) != 0) ++nrOfFailedTestCases;

		if ((a + c) != b) ++nrOfFailedTestCases;
		if (nrOfFailedTestCases - start > 0) {
			std::cout << "FAIL: min/max\n";
			std::cout << to_binary(c + d) << " vs " << to_binary(fixpnt<nbits, rbits, arithmetic, blocktype>(0)) << '\n';
			std::cout << to_binary(a + c) << " vs " << to_binary(b) << '\n';
		}
	}

	///////////////////////////////////////////////////////////////////////////////////
	// logic, in particular, all the literal constant combinations
	{
		int start = nrOfFailedTestCases;
		constexpr size_t nbits = 8;
		constexpr size_t rbits = 4;
		constexpr bool arithmetic = Modulo;
		using blocktype = uint32_t;
		fixpnt<nbits, rbits, arithmetic, blocktype> a, b, c, d;
		a = 1;
		b = 2l;
		c = 3ll;
		d = 0ull;
		// unsigned literals
		if (a != 1u) ++nrOfFailedTestCases;
		if (b != 2ul) ++nrOfFailedTestCases;
		if (c != 3ull) ++nrOfFailedTestCases;
		if (1u != a) ++nrOfFailedTestCases;
		if (2ul != b) ++nrOfFailedTestCases;
		if (3ull != c) ++nrOfFailedTestCases;
		if (d != c - b - a) ++nrOfFailedTestCases;
		// signed literals
		if (-a != -1) ++nrOfFailedTestCases;
		if (-b != -2l) ++nrOfFailedTestCases;
		if (-c != -3ll) ++nrOfFailedTestCases;
		if (-1 != -a) ++nrOfFailedTestCases;
		if (-2l != -b) ++nrOfFailedTestCases;
		if (-3ll != -c) ++nrOfFailedTestCases;

		// less than unsigned literal
		d = 4.0f;
		if (d < 1u) ++nrOfFailedTestCases;
		if (d < 2ul) ++nrOfFailedTestCases;
		if (d < 3ull) ++nrOfFailedTestCases;
		d = 0.0;
		if (1u < d) ++nrOfFailedTestCases;
		if (2ul < d) ++nrOfFailedTestCases;
		if (3ull < d) ++nrOfFailedTestCases;

		// greater than unsigned literal
		if (d > 1u) ++nrOfFailedTestCases;
		if (d > 2ul) ++nrOfFailedTestCases;
		if (d > 3ull) ++nrOfFailedTestCases;
		d = 4ll;
		if (1u > d) ++nrOfFailedTestCases;
		if (2ul > d) ++nrOfFailedTestCases;
		if (3ull > d) ++nrOfFailedTestCases;

		// less than or equal unsigned literal
		if (d <= 1u) ++nrOfFailedTestCases;
		if (d <= 2ul) ++nrOfFailedTestCases;
		if (d <= 3ull) ++nrOfFailedTestCases;
		d = 0.0f;
		if (1u <= d) ++nrOfFailedTestCases;
		if (2ul <= d) ++nrOfFailedTestCases;
		if (3ull <= d) ++nrOfFailedTestCases;

		// greater than or equal unsigned literal
		if (d >= 1u) ++nrOfFailedTestCases;
		if (d >= 2ul) ++nrOfFailedTestCases;
		if (d >= 3ull) ++nrOfFailedTestCases;
		d = 4.0;
		if (1u >= d) ++nrOfFailedTestCases;
		if (2ul >= d) ++nrOfFailedTestCases;
		if (3ull >= d) ++nrOfFailedTestCases;

		// comparisons with signed literals
		// less than signed literal
		d = 4.0f;
		if (d < 1) ++nrOfFailedTestCases;
		if (d < 2l) ++nrOfFailedTestCases;
		if (d < 3ll) ++nrOfFailedTestCases;
		d = 0.0;
		if (1 < d) ++nrOfFailedTestCases;
		if (2l < d) ++nrOfFailedTestCases;
		if (3ll < d) ++nrOfFailedTestCases;

		// greater than signed literal
		if (d > 1) ++nrOfFailedTestCases;
		if (d > 2l) ++nrOfFailedTestCases;
		if (d > 3ll) ++nrOfFailedTestCases;
		d = 4ll;
		if (1 > d) ++nrOfFailedTestCases;
		if (2l > d) ++nrOfFailedTestCases;
		if (3ll > d) ++nrOfFailedTestCases;

		// less than or equal signed literal
		if (d <= 1) ++nrOfFailedTestCases;
		if (d <= 2l) ++nrOfFailedTestCases;
		if (d <= 3ll) ++nrOfFailedTestCases;
		d = 0.0f;
		if (1 <= d) ++nrOfFailedTestCases;
		if (2l <= d) ++nrOfFailedTestCases;
		if (3ll <= d) ++nrOfFailedTestCases;

		// greater than or equal signed literal
		if (d >= 1) ++nrOfFailedTestCases;
		if (d >= 2l) ++nrOfFailedTestCases;
		if (d >= 3ll) ++nrOfFailedTestCases;
		d = 4.0;
		if (1 >= d) ++nrOfFailedTestCases;
		if (2l >= d) ++nrOfFailedTestCases;
		if (3ll >= d) ++nrOfFailedTestCases;
		if (nrOfFailedTestCases - start > 0) {
			std::cout << "FAIL: logic operators\n";
		}
	}

#ifdef SHOW_STATE_SPACE
	{
		constexpr size_t nbits = 7;
		constexpr size_t rbits = 4;
		constexpr bool arithmetic = Modulo;
		constexpr size_t NR_VALUES = (1 << nbits);
		using blocktype = uint32_t;

		fixpnt<nbits, rbits, arithmetic, blocktype> a, b, c, d;
		for (size_t i = 0; i < NR_VALUES; ++i) {
			a.setbits(i);
			float f = float(a);
			b = int(f);
			c = f;
			d = double(a);
			if (a != c && a != d) ++nrOfFailedTestCases;
			std::cout << setw(3) << i << ' ' << to_binary(a) << ' ' << setw(10) << a << ' ' << setw(3) << int(f) << ' ' << to_binary(b) << ' ' << b << ' ' << to_binary(c) << ' ' << to_binary(d) << '\n';
		}
	}

	{
		constexpr size_t nbits = 8;
		constexpr size_t rbits = 4;
		constexpr bool arithmetic = Modulo;
		using blocktype = uint32_t;
		fixpnt<nbits, rbits, arithmetic, blocktype> a, b, c, d;

		for (int i = -16; i < 16; ++i) {
			a = i;
			std::cout << to_binary(i) << ' ' << a << ' ' << to_binary(a) << ' ' << to_binary(-a) << ' ' << -a << ' ' << to_binary(-i) << '\n';
		}
	}
#endif // LATER

	ReportTestSuiteResults(test_suite, nrOfFailedTestCases);
	return (nrOfFailedTestCases > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
catch (char const* msg) {
	std::cerr << msg << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::universal::fixpnt_arithmetic_exception& err) {
	std::cerr << "Uncaught fixpnt arithmetic exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const sw::universal::fixpnt_internal_exception& err) {
	std::cerr << "Uncaught fixpnt internal exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (const std::runtime_error& err) {
	std::cerr << "Uncaught runtime exception: " << err.what() << std::endl;
	return EXIT_FAILURE;
}
catch (...) {
	std::cerr << "Caught unknown exception" << std::endl;
	return EXIT_FAILURE;
}
