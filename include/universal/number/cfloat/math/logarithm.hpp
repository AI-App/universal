#pragma once
// logarithm.hpp: logarithm functions for classic floating-point cfloats
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.

namespace sw::universal {

// Natural logarithm of x
template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> log(cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x) {
	return cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>(std::log(double(x)));
}

// Binary logarithm of x
template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> log2(cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x) {
	return cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>(std::log2(double(x)));
}

// Decimal logarithm of x
template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> log10(cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x) {
	return cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>(std::log10(double(x)));
}
		
// Natural logarithm of 1+x
template<size_t nbits, size_t es, typename bt, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> log1p(cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating> x) {
	return cfloat<nbits, es, bt, hasSubnormals, hasSupernormals, isSaturating>(std::log1p(double(x)));
}

}  // namespace sw::universal
