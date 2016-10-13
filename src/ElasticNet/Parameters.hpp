#pragma once

#include <unordered_map>

using std::unordered_map;
using std::string;

namespace tsp
{
	static unordered_map<string, double> ElasticNetParameters
	{ 
		{ "alpha",					0.2 },
		{ "beta",					2.0 },
		{ "init_k",					0.2 },
		{ "epsilon",				0.02 },
		{ "k_alpha",				0.99 },
		{ "k_update_period",		25 },
		{ "max_num_iter",			100000 },
		{ "num_neurons_factor",		2.5 },
		{ "radius",					0.1 },
	};
}
