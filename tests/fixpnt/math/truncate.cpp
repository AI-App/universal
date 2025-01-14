// truncate.cpp: test suite runner for truncation functions trunc, round, floor, and ceil
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <universal/utility/directives.hpp>
// use default number system library configuration
#include <universal/number/fixpnt/fixpnt.hpp>
#include <universal/verification/fixpnt_math_test_suite.hpp>


#define MANUAL_TESTING 1
#define STRESS_TESTING 0

template<typename TestType>
int VerifyFloor(bool bReportIndividualTestCases) {
	using namespace sw::universal;
	constexpr size_t nbits = TestType::nbits;
	constexpr size_t NR_VALUES = (1 << nbits);
	int nrOfFailedTestCases = 0;

	TestType a;
	for (size_t i = 0; i < NR_VALUES; ++i) {
		a.setbits(i);
		auto l1 = sw::universal::floor(a);
		// generate the reference
		float f = float(a);
		auto l2 = std::floor(f);
		if (l1 != l2) {             // TODO: fix float to int64 comparison
			++nrOfFailedTestCases;
			if (bReportIndividualTestCases) ReportOneInputFunctionError("floor", "floor", a, TestType(l1), TestType(l2));
		}
	}
	return nrOfFailedTestCases;
}

int main()
try {
	using namespace sw::universal;

	bool bReportIndividualTestCases = true;
	int nrOfFailedTestCases = 0;

	std::string tag = "truncation failed: ";

#if MANUAL_TESTING
	// generate individual testcases to hand trace/debug

	nrOfFailedTestCases = ReportTestResult(VerifyFloor< fixpnt<8, 2, Saturating, uint8_t> >(bReportIndividualTestCases), "floor", "fixpnt<8,2,Saturating,uint8_t>");

	nrOfFailedTestCases = 0; // nullify accumulated test failures in manual testing

#else

	std::cout << "classic floating-point fixpnt truncation function validation\n";


#if STRESS_TESTING
	
#endif  // STRESS_TESTING

#endif  // MANUAL_TESTING

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
//catch (const sw::universal::fixpnt_quire_exception& err) {
//	std::cerr << "Uncaught fixpnt quire exception: " << err.what() << std::endl;
//	return EXIT_FAILURE;
//}
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
