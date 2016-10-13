#pragma once

namespace tsp
{
	struct Neuron
	{
		double X;
		double Y;

		vector<double> V() const { return{ X, Y }; }
		static Neuron FV(vector<double> v) { return{ v[0], v[1] }; }

		Neuron& operator+=(vector<double>& v) { X += v[0]; Y += v[1]; return *this; }
		Neuron& operator+=(const Neuron& n) { X += n.X; Y += n.Y; return *this; }
	};
}