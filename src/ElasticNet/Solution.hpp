#pragma once

#include <vector>

using std::vector;
using std::numeric_limits;
using std::pair;

using std::min_element;
using std::for_each;
using std::sort;

namespace tsp
{
	template<typename DistanceType>
	class NodeContainer;

	template<typename DistanceType>
	struct Solution
	{
		static unique_ptr<NodeContainer<DistanceType>> 
		DecodeSolution(vector<vector<double>>& dist, const NodeContainer<DistanceType>& nodes)
		{
			// Return the permutation associated to the elastic

			auto solution = make_unique<NodeContainer<DistanceType>>();
			vector<pair<size_t, size_t>> neuron_city_pair;

			for (auto i = 0; i < nodes.NodesCount(); ++i)
			{
				vector<double> mins;
				for_each(dist.cbegin(),
						 dist.cend(),
						 [&](const auto& v) {mins.emplace_back(*min_element(v.cbegin(), v.cend())); });
				auto city = min_element(mins.cbegin(), mins.cend()) - mins.cbegin();
				auto neuron = min_element(dist[city].cbegin(), dist[city].cend()) - dist[city].cbegin();

				for_each(dist[city].begin(), dist[city].end(), [](auto& d) { d = numeric_limits<double>::infinity(); });
				for_each(dist.begin(), dist.end(), [neuron](auto& d) { d[neuron] = numeric_limits<double>::infinity(); });

				neuron_city_pair.emplace_back(neuron , city);
			}
			
			sort(neuron_city_pair.begin(), neuron_city_pair.end(), [](auto& t1, auto& t2) { return t1.first < t2.first; });

			for (const auto& n: neuron_city_pair)
				solution->AddNode(nodes[n.second]);

			return solution;
		}
	};
}