#pragma once
// test_suite_exceptions.hpp : test suite for arithmetic exceptions for arbitrary universal number systems
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <iostream>
#include <iomanip>
#include <typeinfo>

// CALLING ENVIRONMENT PREREQUISITE!!!!!
// We want the test suite to be used with different configurations of number systems
// so the calling environment needs to set the configuration
// This usually entails setting environment variables, such as <NUMBERSYSTEM>_THROW_ARITHMETIC_EXCEPTIONS
// as a function of the configured state of the number system.
// If it is not set, default is to turn it on.
//#ifndef THROW_ARITHMETIC_EXCEPTION
//#define THROW_ARITHMETIC_EXCEPTION 1
//#endif

#include <universal/number/shared/specific_value_encoding.hpp>
#include <universal/common/exceptions.hpp>

namespace sw::universal {


////////////////////////////// VERIFICATION TEST SUITES ///////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
///                     ARITHMETIC EXCEPTIONS TEST SUITES                           ///
///////////////////////////////////////////////////////////////////////////////////////

	constexpr size_t TAG_WIDTH = 30;

template<typename Scalar>
int TestDivisionByZero(bool bReportIndividualTestCases) {
	using namespace sw::universal;
	if (bReportIndividualTestCases) {
		auto flags = std::cerr.flags();
		std::cerr << std::left << std::setw(TAG_WIDTH) << "TestDivisionByZero: ";
		std::cerr.flags(flags);
	}
	bool thrownAndCaught = false;
	int nrOfFailedTestCases = 0;
	try {
		Scalar a{ 1 }, b{ 0 }, c;
		c = a / b;
	}
	catch (const universal_arithmetic_exception& err) {
		if (bReportIndividualTestCases) std::cerr << "PASS: caught arithmetic exception: " << err.what() << std::endl;
		thrownAndCaught = true;
	}
	catch (...) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: caught unknown exception" << std::endl;
		++nrOfFailedTestCases;
	}
	if (!thrownAndCaught) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: no exception was raised" << std::endl;
		++nrOfFailedTestCases;
	}
	return nrOfFailedTestCases;
}

template<typename Scalar>
int TestOverflowOnAddition(bool bReportIndividualTestCases, const Scalar& a, const Scalar& b) {
	using namespace sw::universal;
	if (bReportIndividualTestCases) {
		auto flags = std::cerr.flags();
		std::cerr << std::left << std::setw(TAG_WIDTH) << "TestOverflowOnAddition: ";
		std::cerr.flags(flags);
	}
	bool thrownAndCaught = false;
	int nrOfFailedTestCases = 0;
	try {
		Scalar c = a + b;
	}
	catch (const universal_arithmetic_exception& err) {
		if (bReportIndividualTestCases) std::cerr << "PASS: caught arithmetic exception: " << err.what() << std::endl;
		thrownAndCaught = true;
	}
	catch (...) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: caught unknown exception" << std::endl;
		++nrOfFailedTestCases;
	}
	if (!thrownAndCaught) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: no exception was raised" << std::endl;
		++nrOfFailedTestCases;
	}
	return nrOfFailedTestCases;
}

template<typename Scalar>
int TestOverflowOnSubtraction(bool bReportIndividualTestCases, const Scalar& a, const Scalar& b) {
	using namespace sw::universal;
	if (bReportIndividualTestCases) {
		auto flags = std::cerr.flags();
		std::cerr << std::left << std::setw(TAG_WIDTH) << "TestOverflowOnSubtraction: ";
		std::cerr.flags(flags);
	}
	bool thrownAndCaught = false;
	int nrOfFailedTestCases = 0;
	try {
		Scalar c = a - b;
	}
	catch (const universal_arithmetic_exception& err) {
		if (bReportIndividualTestCases) std::cerr << "PASS: caught arithmetic exception: " << err.what() << std::endl;
		thrownAndCaught = true;
	}
	catch (...) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: caught unknown exception" << std::endl;
		++nrOfFailedTestCases;
	}
	if (!thrownAndCaught) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: no exception was raised" << std::endl;
		++nrOfFailedTestCases;
	}
	return nrOfFailedTestCases;
}

template<typename Scalar>
int TestOverflowOnMultiplication(bool bReportIndividualTestCases, const Scalar& a, const Scalar& b) {
	using namespace sw::universal;
	if (bReportIndividualTestCases) {
		auto flags = std::cerr.flags();
		std::cerr << std::left << std::setw(TAG_WIDTH) << "TestOverflowOnMultiplication: ";
		std::cerr.flags(flags);
	}
	bool thrownAndCaught = false;
	int nrOfFailedTestCases = 0;
	try {
		Scalar c = a * b;
	}
	catch (const universal_arithmetic_exception& err) {
		if (bReportIndividualTestCases) std::cerr << "PASS: caught arithmetic exception: " << err.what() << std::endl;
		thrownAndCaught = true;
	}
	catch (...) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: caught unknown exception" << std::endl;
		++nrOfFailedTestCases;
	}
	if (!thrownAndCaught) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: no exception was raised" << std::endl;
		++nrOfFailedTestCases;
	}
	return nrOfFailedTestCases;
}

template<typename Scalar>
int TestOverflowOnDivision(bool bReportIndividualTestCases, const Scalar& a, const Scalar& b) {
	using namespace sw::universal;
	if (bReportIndividualTestCases) {
		auto flags = std::cerr.flags();
		std::cerr << std::left << std::setw(TAG_WIDTH) << "TestOverflowOnDivision: ";
		std::cerr.flags(flags);
	}
	bool thrownAndCaught = false;
	int nrOfFailedTestCases = 0;
	try {
		Scalar  c = a / b;
	}
	catch (const universal_arithmetic_exception& err) {
		if (bReportIndividualTestCases) std::cerr << "PASS: caught arithmetic exception: " << err.what() << std::endl;
		thrownAndCaught = true;
	}
	catch (...) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: caught unknown exception" << std::endl;
		++nrOfFailedTestCases;
	}
	if (!thrownAndCaught) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: no exception was raised" << std::endl;
		++nrOfFailedTestCases;
	}
	return nrOfFailedTestCases;
}

template<typename Scalar>
int TestNegativeSqrtArgument(bool bReportIndividualTestCases) {
	using namespace sw::universal;
	if (bReportIndividualTestCases) {
		auto flags = std::cerr.flags();
		std::cerr << std::left << std::setw(TAG_WIDTH) << "TestNegativeSqrtArgument: ";
		std::cerr.flags(flags);
	}
	bool thrownAndCaught = false;
	int nrOfFailedTestCases = 0;
	try {
		Scalar a{ -1 };
		sqrt(a);
	}
	catch (const universal_arithmetic_exception& err) {
		if (bReportIndividualTestCases) std::cerr << "PASS: caught arithmetic exception: " << err.what() << std::endl;
		thrownAndCaught = true;
	}
	catch (...) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: caught unknown exception" << std::endl;
		++nrOfFailedTestCases;
	}
	if (!thrownAndCaught) {
		if (bReportIndividualTestCases) std::cerr << "FAIL: no exception was raised" << std::endl;
		++nrOfFailedTestCases;
	}
	return nrOfFailedTestCases;
}

} // namespace sw::universal
