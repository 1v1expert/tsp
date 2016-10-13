#pragma once

#include <cmath>

namespace tsp
{
	template<typename Node>
	struct Distance
	{
		static decltype(auto) Count(const Node& node_1, const Node& node_2)
		{
			auto a = node_2.X() - node_1.X();
			auto b = node_2.Y() - node_1.Y();
			return sqrt((a * a) + (b * b));
		}
	};
}
