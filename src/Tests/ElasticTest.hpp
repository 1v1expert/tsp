#pragma once

#include <list>
#include <sstream>

#include "Helper.hpp"
#include "AbstractTest.hpp"
#include "../Utility/NodeFactory.hpp"
#include "../ElasticNet/ElasticNet.hpp"

namespace tsp_tests
{
	using std::unique_ptr;
	using std::string;
	using std::shared_ptr;
	using std::weak_ptr;
	using std::stringstream;
	using std::list;

	using std::move;
	using std::cout;
	using std::endl;
	using std::make_unique;
	using std::make_shared;
	using std::to_string;
	using std::get;


	template<typename NodeDistanceType>
	struct ElasticTest : AbstractTest
	{
		using NodeSpecialized = tsp::Node<NodeDistanceType>;
		using NodeFactorySpecialized = tsp::NodeFactory<NodeDistanceType>;

		static bool Create() { return true; }

	private:
		static void Go() {}
	};

	template<>
	struct ElasticTest<int32_t> : AbstractTest
	{
		using NodeSpecialized = tsp::Node<int32_t>;
		using NodeFactorySpecialized = tsp::NodeFactory<int32_t>;

		static bool Go();
	};

	template<>
	struct ElasticTest<float> : AbstractTest
	{
		using NodeSpecialized = tsp::Node<float>;
		using NodeFactorySpecialized = tsp::NodeFactory<float>;

		static bool Go();
	};

	inline bool ElasticTest<int32_t>::Go()
	{
		for (auto iteration = 0; iteration < 5; ++iteration)
		{
			auto names = RandomNames(50, 10);
			auto x = RandomCoordinates(50, 0, 1000);
			auto y = RandomCoordinates(50, 0, 1000);

			stringstream s;
			for (auto i = 0; i < 50; ++i)
				s << names[i] << "; " << x[i] << "; " << y[i] << ";\n";

			auto nodes = NodeFactorySpecialized::CreateFromStream(s);
			cout << "Test int input cities graph: " << *nodes << endl;

			auto elastic_net = tsp::ElasticNet<int32_t>(move(nodes));
			auto ham_path = elastic_net.Run();

			cout << "Test int output cities graph: " << *ham_path << endl;
		}

		return HadPassed();
	}

	inline bool ElasticTest<float>::Go()
	{
		for (auto iteration = 0; iteration < 5; ++iteration)
		{
			auto names = RandomNames(50, 10);
			auto x = RandomCoordinates(50, 0, 1000);
			auto y = RandomCoordinates(50, 0, 1000);

			stringstream s;
			for (auto i = 0; i < 50; ++i)
				s << names[i] << "; " << x[i] << "; " << y[i] << ";\n";

			auto nodes = NodeFactorySpecialized::CreateFromStream(s);
			cout << "Test float input cities graph: " << *nodes << endl;

			auto elastic_net = tsp::ElasticNet<float>(move(nodes));
			auto ham_path = elastic_net.Run();

			cout << " Test float output cities graph: " << *ham_path << endl;
		}

		return HadPassed();
	}
}
