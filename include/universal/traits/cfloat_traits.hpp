#pragma once
//  fixpnt_traits.hpp : traits for classic floating-point number systems
//
// Copyright (C) 2017-2021 Stillwater Supercomputing, Inc.
//
// This file is part of the universal numbers project, which is released under an MIT Open Source license.
#include <universal/traits/integral_constant.hpp>

namespace sw::universal {

	// define a trait for cfloat types
	template<typename _Ty>
	struct is_cfloat_trait
		: false_type
	{
	};
	template<size_t nbits, size_t es, typename BlockType, bool hasSubnormals, bool hasSupernormals, bool isSaturating>
	struct is_cfloat_trait< sw::universal::cfloat<nbits, es, BlockType, hasSubnormals, hasSupernormals, isSaturating> >
		: true_type
	{
	};

	template<typename _Ty>
	constexpr bool is_cfloat = is_cfloat_trait<_Ty>::value;

	template<typename _Ty, typename Type = void>
	using enable_if_cfloat = std::enable_if_t<is_cfloat<_Ty>, Type>;

} // namespace sw::universal
