#pragma once
// fractional.hpp: fractional functions for fixed-points
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

namespace sw::universal {

template<size_t nbits, size_t rbits, bool arithmetic, typename bt>
fixpnt<nbits, rbits, arithmetic, bt> fmod(fixpnt<nbits, rbits, arithmetic, bt> x, fixpnt<nbits, rbits, arithmetic, bt> y) {
	return fixpnt<nbits, rbits, arithmetic, bt>(std::fmod(double(x), double(y)));
}

template<size_t nbits, size_t rbits, bool arithmetic, typename bt>
fixpnt<nbits, rbits, arithmetic, bt> remainder(fixpnt<nbits, rbits, arithmetic, bt> x, fixpnt<nbits, rbits, arithmetic, bt> y) {
	return fixpnt<nbits, rbits, arithmetic, bt>(std::remainder(double(x), double(y)));
}

template<size_t nbits, size_t rbits, bool arithmetic, typename bt>
fixpnt<nbits, rbits, arithmetic, bt> frac(fixpnt<nbits, rbits, arithmetic, bt> x) {
	return fixpnt<nbits, rbits, arithmetic, bt>(double(x)-long(x));
}


}  // namespace sw::universal
