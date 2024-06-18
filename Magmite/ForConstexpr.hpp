#pragma once

#include <algorithm>

namespace magmite::meta
{
	template <auto begin, auto end, typename FN>
	void for_constexpr(FN fn)
	{
		if constexpr (begin != end)
		{
			fn.template operator() <begin> ();
			
			if constexpr (std::is_integral_v<decltype(begin)>)
			{
				for_constexpr<begin + 1, end, FN>(fn);
			}
			else
			{
				for_constexpr<std::next(begin), end, FN>(fn);
			}
		}
	}

	template <auto begin, auto end, typename FN>
	void for_constexpr_while(FN fn)
	{
		if constexpr (begin != end)
		{
			if (!fn.template operator() < begin > ())
			{
				return;
			}

			if constexpr (std::is_integral_v<decltype(begin)>)
			{
				for_constexpr_while<begin + 1, end, FN>(fn);
			}
			else
			{
				for_constexpr_while<std::next(begin), end, FN>(fn);
			}
		}
	}
}





